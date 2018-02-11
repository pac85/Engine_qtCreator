#include"../common.h"
#include"BaseActor.h"

struct WorldActorPtr
{
private:
	BaseActor * ptr;
	WorldActorPtr * parent = null;

public:
	
	bool attached = false;

	WorldActorPtr(){}

	WorldActorPtr(BaseActor * ptr)
	{
		this->ptr = ptr;
	}

	inline bool operator== (const WorldActorPtr &b) const
	{
		return b.ptr == ptr;
	}

	inline bool operator!= (const WorldActorPtr &b) const
	{
		return b.ptr != ptr;
	}
	
	inline bool is_root()
	{
		return parent == nullptr;
	}
	
	inline WorldActorPtr * get_parent()
	{
		return parent;
	}
};

static WorldActorIndex
{
private:
	uint64_t index;
	static uint64_t l_index;	//the last used index
	static mutex gen_mutex;		//a mutex to thread safely generate a new index
public:
	WorldActorIndex()
	{
		lock_guard<mutex> lock(gen_mutex);
		l_index++;
		index = l_index;
	}
	unsigned long get_index() const
	{
		return index;
	}
	
	bool Operator==(const WorldActorIndex &b) const
	{
		return index == b.index;
	}
}

namespace std 
{

  template <>
  struct hash<WorldActorIndex>
  {
    std::size_t operator()(const WorldActorIndex& k) const
    {
      return hash<uint64_t> k.get_index();
    }
  };

} 
