 
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

class World
{
public:
	world();
	virtual ~world();
	
	void add_actor(BaseActor * actor_to_add);       //adds a BaseActor to the world
    void remove_actor(BaseActor* actor_to_remove);  //removes BaseActor from world
	
	void aa_attach(attachment _attachment);     //adds an BaseActor-BaseActor attachment
	void aa_deteach(attachment _attachment);    //removes the attachment

	void load_level(istream input_stream);      //Loads a level from an xwl file

	void UpdateWorld(float delta);              //Does all the update stuff
	
protected:
private:
	unordered_map<WorldActorIndex, WorldActorPtr> active_actors, inactive_actors;
	unrordered_map<WorldActorIndex, unordered_map<WorldActorIndex, WorldActorPtr> hierarchy;
	
};
#endif // WORLD_H
