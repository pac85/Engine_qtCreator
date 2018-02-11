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
#ifndef BaseActor_H
#define BaseActor_H
#include "../common.h"
#include "Transform.h"

using namespace glm;


#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class WorldActorIndex;

#define REGISTER_DEC_TYPE(NAME) \
    static BaseActorRegister<NAME> reg

#define REGISTER_DEF_TYPE(NAME) \
    BaseActorRegister<NAME> NAME::reg(#NAME)

class BaseActor
{
    public:

        BaseActor();
        virtual ~BaseActor();

        string get_instance_name();
        void set_instance_name(string _instance_name);

        Transform get_transform();
        void set_transform(Transform _transform);

        WorldActorIndex * get_world_index();
        void set_world_index(WorldActorIndex * world_index);

        inline bool is_active()
        {
            return bTick;
        }

        /*//socket management
        void add_socket(Transform, string);      //adds a socket to the actor
        //returns the absolute transform of the socket
        Transform get_absolute_socket_transform(string);*/

        //events
        virtual void tick(float delta) = 0;      //called every frame, after update
        virtual void GameStart() = 0;            //called when the game starts

        bool bTick;                              //if true tick() will be called every frame

    protected:
        Transform ATransform;

    private:
        //map<string, Transform>socket_offset;      //An array of sockets' relative transforms
        string instance_name;
        WorldActorIndex * world_index;              //an index to find itself in the world
};

/*
 *The following code allows a actor derived class instance to be created from an assigned name
 *Some of the code was taken from here:
 *http://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name
*/

template<typename T> BaseActor * createT()
{
    return new T;
}

struct BaseActorFactory
{
    typedef map<std::string, BaseActor*(*)()> BaseActor_map_type;

    public:
        //Creates an instance of the Actor the witch name is s, returns 0 if there is no Actor named s.
        static BaseActor* createInstance(string const& s, string instance_name);


    protected:
        //returns the map witch associates names with Actors
        static BaseActor_map_type * getMap();

    private:
        //the map witch associates names with Actors
        static BaseActor_map_type * BaseActor_name_map;
};

template<typename T>
struct BaseActorRegister : BaseActorFactory                         //Every Actor derived class must have a static member of
{                                                                   //this type and the constructor's argument is the name
    BaseActorRegister(string const& s)                              //that will be used  when the class is referenced by string.
    {
        getMap()->insert(make_pair(s, &createT<T>));
    }
};




#endif // BaseActor_H
