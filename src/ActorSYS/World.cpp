/**************************************************************************/
/*
  Copyright (C) 2017 Antonino Maniscalco (alias pac85)

  This file is part of Engine.

  Engine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Engine is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Engine.  If not, see http://www.gnu.org/licenses/

*/
/**************************************************************************/
#include "World.h"
#include "internal_actors.h"
#include "../game/GameMain.h"

uint64_t WorldActorIndex::l_index = 1;
mutex WorldActorIndex::gen_mutex;

World::World()
{
    //creates root hierarchy element
    hierarchy.insert(make_pair(WorldActorIndex(0),
                                  make_pair(WorldActorPtr((BaseActor*)nullptr),
                                  unordered_set<WorldActorIndex*>())));
}

World::~World()
{

}

void World::add_actor(BaseActor * actor_to_add)
{
    //makes sure we don't add an actor that is already there
    if(ptr_to_index.find(actor_to_add) != ptr_to_index.end()) return;

	if(actor_to_add->bTick)
	{
        WorldActorIndex index(ACTIVE);
        WorldActorPtr ptr(actor_to_add);
        add_map_element(index, ptr, &active_actors);
        actor_to_add->set_world_index(&index);
	}
	else
	{
        WorldActorIndex index(INACTIVE);
        WorldActorPtr ptr(actor_to_add);
        add_map_element(index, ptr, &active_actors);
        actor_to_add->set_world_index(&index);
	}
}

void World::remove_actor( WorldActorIndex &index, bool destroy_attached)
{
    switch(index.get_state())
    {
    case ACTIVE:
        remove_map_element(index, &active_actors);
        break;
    case INACTIVE:
        remove_map_element(index, &inactive_actors);
        break;
    case ATTACHED:
        if(destroy_attached)
        {
            recursive_delete(index);
        }
        else
        {
            //all the actors attached to the actor that is being deleted get attached to the parent

            //the parent for each of those is set to the deleted actor's parent
            for(auto &element : hierarchy[index].second)
            {
                //all the leaves are transfered either in the active or inactive maps
                if(hierarchy[*element].second.empty())
                {
                    actor_state new_state = hierarchy[*element].first->is_active()? ACTIVE:INACTIVE;
                    element->set_state(new_state);
                    add_map_element(*element, hierarchy[*element].first, new_state == ACTIVE? &active_actors:&inactive_actors);
                    hierarchy[index].second.erase(element);
                    hierarchy.erase(*element);
                }
                else //all the actors attached to the actor that is being deleted get attached to the parent
                    element->set_parent(index.get_parent());
            }
            //the attached actors get added to the deleted actor's adiacency list
            hierarchy[index.get_parent()].second.insert(hierarchy[index].second.begin(), hierarchy[index].second.end());
            //the deleted actor finally gets removed
            remove_map_element(index, &hierarchy);
        }
        break;
    }
}


void World::aa_attach(WorldActorIndex &parent, WorldActorIndex &child)
{
    unordered_map<WorldActorIndex, pair<WorldActorPtr, unordered_set<WorldActorIndex*>>>::iterator parent_it = hierarchy.find(parent);
    unordered_map<WorldActorIndex, pair<WorldActorPtr, unordered_set<WorldActorIndex*>>>::iterator child_it = hierarchy.find(child);

    bool parent_is_in_hierarchy = parent_it != hierarchy.end(),
         child_is_in_hierarchy = child_it != hierarchy.end();

    if(!parent_is_in_hierarchy && !child_is_in_hierarchy)
    {
        parent.set_parent(WorldActorIndex(0));
        child.set_state(ATTACHED);
        child.set_parent(parent);

        WorldActorPtr parent_ptr = get_actor(parent);
        WorldActorPtr child_ptr = get_actor(child);

        parent_it = hierarchy.insert(make_pair(   parent,
                                      make_pair(parent_ptr,
                                      unordered_set<WorldActorIndex*>()))).first;

        hierarchy.insert(make_pair(   child,
                                      make_pair(child_ptr,
                                      unordered_set<WorldActorIndex*>())));
        parent_it->second.second.insert(&child);
    }
    else if(parent_is_in_hierarchy && !child_is_in_hierarchy)
    {
        parent.set_parent(WorldActorIndex(0));
        child.set_state(ATTACHED);
        child.set_parent(parent);
        WorldActorPtr child_ptr = get_actor(child);
        hierarchy.insert(make_pair(   child,
                                      make_pair(child_ptr,
                                      unordered_set<WorldActorIndex*>())));
        parent_it->second.second.insert(&child);
    }
    else if(!parent_is_in_hierarchy && child_is_in_hierarchy)
    {

    }
    //otherwise they are both already present and there is nothing to do
}

void World::aa_deteach(WorldActorIndex &child)
{
    if(child.get_state() != ATTACHED) return;
    remove_actor(child, false);
}

void World::recursive_update(double delta_time, WorldActorIndex root)
{
    unordered_map<WorldActorIndex, pair<WorldActorPtr, unordered_set<WorldActorIndex*>>>::iterator root_it = hierarchy.find(root);
    if(root_it == hierarchy.end()) return;
    //updates the actor
    if(!root.is_root()) root_it->second.first->tick(delta_time);
    //does the recursive call for each attached actor
    for(auto &sub_actor : root_it->second.second)
        recursive_update(delta_time, *sub_actor);
}

void World::UpdateWorld(float delta_time)
{
    //updates all the active actors
    for(auto &actor_ptr : active_actors)
        actor_ptr.second->tick(delta_time);
    //updates all the actached actors
    recursive_update(delta_time);
}
