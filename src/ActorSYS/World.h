 
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
#ifndef WORLD_H
#define WORLD_H
#include"../common.h"
#include"BaseActor.h"
#include"ActorIndexers.hpp"

class World
{
public:
    World();
    virtual ~World();
	
    void add_actor(BaseActor * actor_to_add);                                   //adds a BaseActor to the world
    void remove_actor( WorldActorIndex &index, bool destroy_attached = true);   //removes BaseActor from world
	
    void aa_attach(WorldActorIndex &parent, WorldActorIndex &child);          //adds an BaseActor-BaseActor attachment
    void aa_deteach(WorldActorIndex &child);         //removes the attachment

	void load_level(istream input_stream);      //Loads a level from an xwl file

    void UpdateWorld(float delta_time);              //Does all the update stuff

    inline WorldActorIndex * get_index(BaseActor* ptr)
    {
        return ptr_to_index[ptr];
    }

protected:
private:
	unordered_map<WorldActorIndex, WorldActorPtr> active_actors, inactive_actors;
    unordered_map<WorldActorIndex, pair<WorldActorPtr, unordered_set<WorldActorIndex*>>> hierarchy;
    unordered_map<BaseActor*, WorldActorIndex*> ptr_to_index;

    void recursive_update(double delta_time, WorldActorIndex root = WorldActorIndex(0));

    inline void add_map_element(WorldActorIndex &index, WorldActorPtr &ptr, unordered_map<WorldActorIndex, WorldActorPtr> * to_add_map)
    {
        to_add_map->insert(make_pair(index, &ptr));
        ptr_to_index.insert(make_pair(&ptr, &index));
    }

    inline void remove_map_element(WorldActorIndex &index, unordered_map<WorldActorIndex, WorldActorPtr> * to_remove_map)
    {
        unordered_map<WorldActorIndex, WorldActorPtr> &defrenced_map = *to_remove_map;
        ptr_to_index.erase(&defrenced_map[index]);
        defrenced_map.erase(index);
    }

    inline void remove_map_element(WorldActorIndex &index, unordered_map<WorldActorIndex, pair<WorldActorPtr, unordered_set<WorldActorIndex*>>> * to_remove_map)
    {
        auto &defrenced_map = *to_remove_map;
        ptr_to_index.erase(&defrenced_map[index].first);
        defrenced_map.erase(index);
    }


    inline WorldActorPtr get_actor(const WorldActorIndex &index)
    {
        switch(index.get_state())
        {
        case ACTIVE:
            return active_actors[index];
            break;
        case INACTIVE:
            return inactive_actors[index];
            break;
        case ATTACHED:
            return hierarchy[index].first;
            break;
        }
    }

    inline void recursive_delete(WorldActorIndex &index)
    {
        for(auto &element : hierarchy[index].second)
        {
            recursive_delete(*element);
        }
        remove_map_element(index, &hierarchy);
    }
};
#endif // WORLD_H
