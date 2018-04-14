#include"../common.h"
#include"BaseActor.h"

enum actor_state
{
    ACTIVE,
    INACTIVE,
    ATTACHED
};

struct WorldActorPtr
{
private:
    BaseActor * ptr;

public:

    bool attached = false;

    WorldActorPtr(){}

    WorldActorPtr(BaseActor * ptr)
    {
        this->ptr = ptr;
    }

    BaseActor * operator&()
    {
        return ptr;
    }

    BaseActor& operator*()
    {
        return *ptr;
    }

    BaseActor* operator->()
    {
        return ptr;
    }

    inline bool operator== (const WorldActorPtr &b) const
    {
        return b.ptr == ptr;
    }

    inline bool operator!= (const WorldActorPtr &b) const
    {
        return b.ptr != ptr;
    }
};

class WorldActorIndex
{
private:
	uint64_t index;
	static uint64_t l_index;	//the last used index
	static mutex gen_mutex;		//a mutex to thread safely generate a new index

    actor_state state;

    WorldActorIndex * parent = nullptr;

    inline void set_parent(WorldActorIndex parent)
    {
        this->parent = &parent;
    }

    inline void set_state(actor_state state)
    {
        this->state = state;
    }

    friend class World;


public:

    WorldActorIndex(const WorldActorIndex &b)
    {
        index = b.index;
        this->state = b.state;
    }

    WorldActorIndex(actor_state state)
	{
		lock_guard<mutex> lock(gen_mutex);
		l_index++;
		index = l_index;
        this->state = state;
	}

    WorldActorIndex(uint64_t index)
    {
        this->index = index;
    }

    unsigned long get_index() const
	{
		return index;
    }
	
    inline bool operator==(const WorldActorIndex &b) const
	{
		return index == b.index;
	}

    inline bool is_root()
    {
        return index == 0;
    }

    inline actor_state get_state() const
    {
        return state;
    }

    inline WorldActorIndex get_parent() const
    {
        return *parent;
    }
};

namespace std 
{

  template <>
  struct hash<WorldActorIndex>
  {
    std::size_t operator()(const WorldActorIndex& k) const
    {
      return hash<uint64_t> () (k.get_index());
    }
  };

} 
