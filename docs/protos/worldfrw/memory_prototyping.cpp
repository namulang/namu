#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cstdlib>
using namespace std;

#define LOG(x) cout << __PRETTY_FUNCTION__ << "#" << __LINE__ << "() " << x << "\n";

typedef int wint;
typedef int widx;
typedef int wcnt;
typedef unsigned int wuint;
typedef bool wbool;
typedef unsigned char wuchar;
typedef int64_t wint64;
typedef char wchar;

class Thing {
public:
	virtual ~Thing() {}
	wbool isExist() const { return this; }
	wbool isNull() const { return !this; }
};

union Id
{
    struct SeperatedId
    {
        widx blk_n:21;
		widx chk_n:21;
        wcnt serial:22;
    } sep;
    wint64 num;

    Id(wint64 it = -1) : num(it) {}
    Id(widx new_n, wcnt new_serial) : sep {new_n, new_serial} {}
};

class Class {
public:
	virtual wcnt getSize() const = 0;
};

class Instancer;
class Block;
class Instance : public Thing {
	friend class Instancer;
	friend class Chunks;
public:
    Instance(Id id) : _id(id) {}
	Instance();
	virtual ~Instance();
    Id getId() const { return _id; }
    void* operator new(size_t size);
	void operator delete(void* pt, size_t sz);
	const Block& getBlock() const;
	Block& _getBlock() { return (Block&) getBlock(); }

	virtual const Class& getClass() const = 0;
	static Instancer& _getMgr();

    Id _id;

private:
	static Id _from_dtor;
};

Id Instance::_from_dtor;

template <typename T>
T& nulr()
{
    T* ret = 0;
    return *ret;
}

template <typename T>
class TStrong : public Instance {
};

class Node : public Instance {};
template <typename T>
class TClass : public Class {
public:
    virtual wcnt getSize() const { return sizeof(T); }
};
class Object : public Node {};
class Res : public Object {
public:
	virtual const Class& getClass() const { 
		static TClass<Res> in;
		return in;
	}
    operator wbool() const { return false; }
};
Res wasgood, wasoob;

class MemoryHaver : public Thing {
public:
	void* operator[](widx n) { return get(n); }
	const void* operator[](widx n) const { return get(n); }

public:
	void* get(widx n) { return _get(n); }
	const void* get(widx n) const { return ((MemoryHaver*) this)->_get(n); }
    virtual wcnt getLen() const = 0;
    virtual wcnt getSize() const = 0;
    wbool isFull() const { return getLen() >= getSize(); }
    wbool isCapable() const { return getLen() < getSize(); }
	virtual wbool has(const Instance& it) const = 0;

protected:
	virtual void* _get(widx n) = 0;
};

class Allocator : public MemoryHaver {
public:
    Allocator(wcnt blkbyte = 1) : _blkbyte(blkbyte) {}


public:
    virtual void* new1() = 0;
    virtual Res& del(void* used, wcnt sz) = 0;
    virtual Res& resize(wcnt new1) = 0;
    wcnt getBlkSize() const { return _blkbyte; }

private:
    wcnt _blkbyte;
};
//	AUTO RESIZE.
class Chunk : public Allocator {
public:
    Chunk(wcnt blksize=1, wbool is_fixed=true) : Allocator(blksize), _head(0), _len(0), _sz(0), _heap(0), _is_fixed(is_fixed) { LOG("") }
    ~Chunk() { Chunk::release(); }

	static constexpr wcnt INIT_SZ = 20;

public:
    virtual wcnt getLen() const { return _len; }
    virtual wcnt getSize() const { return _sz; }
    virtual void* new1() {
		//LOG("_len=" << _len << ", _sz=" << _sz << ", _blksize=" << _getRealBlkSize())
		//LOG("_head=" << _head << ", _heap=" << (void*) _heap)
        if(_len >= _sz)
            if(resize((getSize()+1)*2))
                return NULL;

        widx* ret = (widx*) _get(_head);
        _head = *ret;
		//LOG("_get(_head=" << *ret << ")=" << (void*) ret)
        _len++;
        return ret;
    }
    virtual Res& del(void* used, wcnt) {
		LOG("")
        widx* cast = (widx*) used;
        *cast = _head;

		wuchar* end = (wuchar*) used;
		wuint bytes = (wuint) (end - _heap);
        _head = bytes / _getRealBlkSize();
        _len--;
        return wasgood;
    }
    virtual Res& release() {
		LOG("")
		_freeHeap(_heap);
        _len = _sz = 0;
        return wasgood;
    }

    virtual Res& resize(wcnt new_size) {
		if(new_size < INIT_SZ) new_size = INIT_SZ;
		if(_is_fixed && new_size > INIT_SZ) new_size = INIT_SZ;

		//LOG("new_size=" << new_size << ", malloc(" << new_size * _getRealBlkSize() << ")")
		if(new_size == _sz)
			return wasoob;
        wuchar* new1 = (wuchar*) _allocHeap(new_size);
		LOG((void*) new1 << " = malloc(" << new_size * _getRealBlkSize() << ")")
        memcpy(new1, _heap, _sz*_getRealBlkSize());

        int prev_len = _len,
            prev_size = _sz;
		//LOG("newsize=" << new_size << ", prev_len= " << prev_len << ", prev_size=" << prev_size)
        release();
        _len = prev_len;
        _heap = new1;
        _sz = new_size;
		//LOG("len=" << _len << ", size=" << _sz)
        return _index(prev_size);
    }
    virtual wbool has(const Instance& it) const {
		LOG((void*) _heap << " <= " << &it << " <= " << (void*) getEOB())
		void* pt = (void*) &it;
        return _heap <= pt && pt <= getEOB();
    }
    const wuchar* getEOB() const { /*....*/ return ((Chunk*) this)->_getEOB(); }
	const wuchar* getHeap() const { return _heap; }

protected:
	virtual void* _get(widx n) {
		if(n < 0 || n >= _sz) {
			LOG("oor. n=" << n << ", _sz=" << _sz)
			return NULL;
		}
		//LOG("_get(" << n << ") = " << (void*) (_heap + n * _getRealBlkSize()))
		return _heap + n * _getRealBlkSize();
	}

private:
    wuchar* _getEOB() { return (wuchar*) _get(_sz-1) + _getRealBlkSize()-1; }
    Res& _index(widx start) {
        wuchar* eob = _getEOB(),
              * e = (wuchar*) _get(start); 
		_head = start;
		//LOG("eob=" << (void*) eob  << ", e=" << (void*) e << ", start=" << start)
		//LOG("_head=" << _head)

		widx* put = NULL;
        do {
			put = (widx*) e;
			*put = ++start;
			//LOG("*(" << (void*) e << ")[" << start-1 << "] = " << start)
		} while((e+=_getRealBlkSize()) < eob);

		*put = -1;
		//LOG("_index end.")
    }
    wcnt _getRealBlkSize() const {
        wcnt sz = getBlkSize();
        return sz < 4 ? 4 : sz;
    }
	virtual void* _allocHeap(wcnt new_size) {
		LOG("new_size=" << new_size)
		void* ret = malloc(new_size * _getRealBlkSize());
		LOG("ret=" << ret)
		return ret;
	}
	virtual void _freeHeap(void* heap) {
		LOG("heap=" << heap)
        if(heap)
            free(heap);
		heap = NULL;
	}

private:
    wuchar* _heap;
    wcnt _sz, _len;
    widx _head;
	wbool _is_fixed;
};

class Chunks : public Allocator {
public:
	Chunks(wcnt blkbyte=0) : Allocator(blkbyte) {}
	virtual ~Chunks() { _release(); }

public:
    Chunk& operator[](widx n) { return get(n); }
	Chunk& operator[](const Instance& inst) { return get(inst); }
    const Chunk& operator[](widx n) const { return get(n); }
    const Chunk& operator[](const Instance& inst) const { return get(inst); }

	Chunk& get(widx n) { return *(Chunk*) _get(n); }
	Chunk& get(const Instance& it) { return *(Chunk*) _get(it.getId().sep.chk_n); }
	const Chunk& get(const Instance& it) const { return ((Chunks*) this)->get(it); }
    const Chunk& get(widx n) const { return ((Chunks*) this)->get(n); }

	virtual Res& release() {
		_release();
		return wasgood;
		//return Allocator::release();
	}

	virtual wcnt getLen() const { return _chunks.size(); }
	virtual wcnt getSize() const { return getLen(); }

	virtual void* new1() { return _findCapable().new1(); }
	virtual Res& del(void* pt, wcnt sz) {
		LOG("to_del.chk_n=" << Instance::_from_dtor.sep.chk_n)
		return _chunks[Instance::_from_dtor.sep.chk_n].del(pt, sz);
	}

	Chunk& _findCapable() {
		for(Chunk& e : _chunks) {
			if(e.isFull()) continue;
			//LOG("found e=" << &e)
			return e;
		}

		resize(getLen()+1);
		return _chunks[_chunks.size()-1];
	}

	virtual wbool has(const Instance& it) const {
		//LOG("")
		return _chunks[it.getId().sep.chk_n].has(it);
	}

	virtual Res& resize(wcnt new1) {
		LOG("new1=" << new1)
		_chunks.resize(new1);
		return wasgood;
	}

	Res& _release() {
		_chunks.clear();
		return wasgood;
	}

	void* _get(widx n) {
		//LOG("n=" << n << ", _chunks.size=" << _chunks.size())
        if(0 > n || n >= _chunks.size()) {
			LOG("0 > n")
            return NULL; 
		}

		//LOG("*_chunks[" << n << "]=" << (void*) &_chunks[n])
        return &_chunks[n];
	}

private:
	vector<Chunk> _chunks;
};

class Pool : public MemoryHaver {
public:
	Pool() {}
	virtual ~Pool() { release(); }

public:
    Chunks& operator[](widx n) { return get(n); }
	Chunks& operator[](const Instance& inst) { return get(inst); }
    const Chunks& operator[](widx n) const { return get(n); }
    const Chunks& operator[](const Instance& inst) const { return get(inst); }


public:
	Chunks& get(const Instance& inst) { return get(inst.getClass().getSize()); }
	const Chunks& get(const Instance& inst) const { return get(inst.getClass().getSize()); }
    const Chunks& get(widx n) const { return ((Pool*) this)->get(n); }
    Chunks& get(widx n) { return *(Chunks*) _get(n); }

    virtual wbool has(const Instance& it) const {
        const Chunks& got = get(it.getClass().getSize());
		LOG("got=" << (void*) &got << ", size=" << it.getClass().getSize())
        return got.has(it);
    }

    virtual wcnt getSize() const { return _chunkset.capacity(); }
    virtual wcnt getLen() const { return _chunkset.size(); }
    virtual Res& release() {
		LOG("")
		int n = 0;
        for(Chunks* e : _chunkset)
        {
			LOG("n=" << n++)
			if( ! e) continue;
			LOG("elem[" << e->getBlkSize() << "].release();")
            e->release();
            delete &e;
        }

        _chunkset.clear();
        return wasgood;
    }

protected:
	virtual void* _get(widx n) {
		//LOG("n=" << n << ", _chunkset.size=" << _chunkset.size())
        if(0 > n) {
			LOG("0 > n")
            return NULL; 
		}

		while((int)_chunkset.size()-1 < n)
            _chunkset.push_back(NULL);

        if( ! _chunkset[n]) {
			LOG("create new chunk[" << n << "]")
            _chunkset[n] = new Chunks(n);
		}

		//LOG("*_chunkset[" << n << "]=" << (void*) &_chunkset[n])
        return _chunkset[n];
    }

private:
    vector<Chunks*> _chunkset;
};

class Instancer; 
struct Unit;
class Block : public Instance {
	friend class Akashic;
	friend class Unit;
	Block() : Instance(-1) {}
	Block(Id id) : Instance(id) { LOG("this=" << this << ", id.sep.blk_n=" << id.sep.blk_n << ", chk_n=" << id.sep.chk_n) }
public:
	const Chunk& getChunk() const;
	wbool isHeap() const {
		const Chunk& chk = getChunk();
		return chk.isExist() && chk.has(*_pt);
	}

	virtual const Class& getClass() const {
		static TClass<Block> in;
		return in;
	}

	Res& bind(const Instance& it) { return _bind(it); }

	Instance* _pt;
	wcnt _weak, _strong;

	virtual Res& release() {
		// TODO:
		return wasgood;
	}

protected:
	virtual Res& _bind(const Instance& it) {
		LOG("Block.this=" << this)
		release();
		_pt = (Instance*) &it;
		_pt->_id = getId();
		LOG("_pt=" << (void*) &it << ", _pt.sep.blk_n=" << _pt->_id.sep.blk_n << ", chk_n=" << _pt->_id.sep.chk_n)
		return wasgood;
	}
};

struct Unit {
	widx next;
	Block blk;
};
class Akashic : public Chunk {
	friend class Instancer;
	friend class Block;
public:
	Akashic() : Chunk(sizeof(Unit), false) { LOG("") }

public:
	Unit& operator[](widx n) { return get(n); }
	Unit& operator[](Id id) { return get(id.sep.blk_n); }
	const Unit& operator[](widx n) const { return get(n); }
	const Unit& operator[](Id id) const { return get(id.sep.blk_n); }

public:
	Unit& get(widx n) { return *(Unit*) _get(n); }
	const Unit& get(widx n) const { return ((Akashic*) this)->get(n); }
	virtual void* new1() {
		LOG("")
		Unit* res = (Unit*) Chunk::new1();
		if( ! res)
			return res;

		LOG("res=" << res << ", sz=" << TClass<Block>().getSize() << ", blk=" << &(res->blk));
		::new (&res->blk) Block(_genId(res));
		return res;
	}

protected:
	virtual void* _allocHeap(wcnt new_size) {
		LOG("new Unit[" << new_size << "]")
		void* ret = ::new Unit[new_size];
		LOG("ret=" << ret);
		return ret;
	}
	virtual void _freeHeap(void* heap) {
		LOG("heap=" << heap)
		if(heap)
			delete [] (Unit*) heap;
		heap = NULL;
	}
	Id _genId(void* pt) const {
		static wcnt serial = 0;
		return Id(_getIdx(pt), ++serial);
	}
	widx _getIdx(void* it) const {
		if( ! has(*(Instance*) it)) { // "has" func will treat it as void*, too.
			LOG("! rcrd.has(*this)")
			return -1;
		}

		widx ret = ((wuchar*)it - getHeap()) / getBlkSize();
		LOG("this=" << (void*) it<< ", heap=" << (void*) getHeap() << " / blksize=" << getBlkSize() << "--> " << ret)
		return ret;
	}
};

class Instancer {
	friend class Instance;
public:
    void bind(Instance& it) {
		LOG("")
		Unit& new1 = *(Unit*) _akashic.new1();
		LOG("new1=" << &new1 << ", new1.next=" << new1.next << ", block=" << &(new1.blk))
		Block& got = new1.blk;

		got.bind(it);
    }
	void unbind(Instance& it) {
		LOG("it=" << &it)
		Unit& un = _akashic[it.getId()];
		_akashic.del(&un, sizeof(Unit));
	}
    void* _new1(size_t size) {
		LOG("size=" << size)
		return _pool[size].new1();
    }
	void _del(void* pt, wcnt sz) {
		LOG("start: pt=" << pt << ", sz=" << sz)
		_pool[sz].del(pt, sz);
		LOG("end")
	}
	const Pool& getPool() const { return _pool; }
	const Akashic& getAkashic() const { return _akashic; }

private:
    Pool _pool;
	Akashic _akashic;
};

class World {
public:
    static World& get() {
        static World inner;
        return inner;
    }

    Instancer& getInstancer() { return _instancer; }

private:
    Instancer _instancer;
};

Instance::Instance() { _getMgr().bind(*this); }
Instance::~Instance() { 
	_getMgr().unbind(*this);
	Instance::_from_dtor = _id;
}
const Block& Instance::getBlock() const {
	LOG("_id.sep.blk_n=" << _id.sep.blk_n << ", chk_n=" << _id.sep.chk_n)
	return _getMgr().getAkashic()[_id].blk;
}
Instancer& Instance::_getMgr() { World::get().getInstancer(); }
void Instance::operator delete(void* pt, size_t sz) {
	_getMgr()._del(pt, sz);
}
const Chunk& Block::getChunk() const {
	return Instance::_getMgr().getPool()[*_pt][*_pt];
}
void* Instance::operator new(size_t size) {
	LOG("size=" << size)
	return _getMgr()._new1(size);
}

class A : public Object {
public:
	A() { cout << "!!!!!!!!! A::A() !!!!!! \n"; }
	virtual const Class& getClass() const {
		static TClass<A> in;
		return in;
	}

	int age;
};

class B : public A {
public:
	B() { cout << "!!!!!!!!! B::B() !!!!!! \n"; }
	virtual const Class& getClass() const {
		static TClass<B> in;
		return in;
	}

	float grade;
};

void print(vector<A*>& arr) {
	for(int n=0; n < arr.size() ;n++)
		cout << "arr[" << n << "].id.chk_n=" << arr[n]->getId().sep.chk_n << ", blk_n=" << arr[n]->getId().sep.blk_n << ", ptr=" << arr[n] << "\n";

	cout << "print blocks\n";
	const Akashic& aka = World::get().getInstancer().getAkashic();
	for(int n=0; n < aka.getLen() ;n++) {
		const Unit& u = aka[n];
		cout << "[" << n << "]: .next=" << u.next << ", u.blk=" << &u.blk << ", u.blk.id=" << u.blk.getId().sep.chk_n << ", " << u.blk.getId().sep.blk_n << "\n";
	}
}

int main()
{
/*	cout << " - start\n";
	A a;
	B b;
	cout << a.getClass().getSize() << ", " << b.getClass().getSize() << "\n";

	cout << " - blk test\n";
	LOG(" - &wasgood=" << &a<< ", &blk=" << &a.getBlock() << ", blk._pt=" << a.getBlock()._pt << ", isHeap=" << a.getBlock().isHeap())
	LOG(" - &wasgood=" << &wasgood << ", &blk=" << &wasgood.getBlock() << ", blk._pt=" << wasgood.getBlock()._pt << ", isHeap=" << wasgood.getBlock().isHeap())
	wasgood.getBlock();

	cout << " - Chunk test\n";
	Chunk test(4);
	for(int n=0; n < 10; n++)
		test.new1();

	cout << " - new test\n";
	*/
	/*vector<A*> arr;
	print(arr);
	for(int n=0; n < 9; n++) {
		B* b = new B();
		cout << ">>>>> NEW b=" << b << "\n";
		arr.push_back(b);
		print(arr);
	}

	cout << " - DELETE\n";
	print(arr);

	while(arr.size()) {
		cout << ">>>>> DEL b[" << arr.size()-1 << "]=" << arr[arr.size()-1] << "\n";
		delete arr[arr.size()-1];
		arr.pop_back();
		print(arr);
	}*/

	// CHUNK TEST:
	Chunk c1(20, false);
	cout << "- NEW\n";
	for(int n=0; n < 300 ; n++)
		c1.new1();
	cout << "- DEL\n";
	while(c1.getLen()) {
		c1.del(c1[0], 20);
	}
	cout << " - END!\n";

	//	CHUNKS TEST:
	Chunks c2(45);
	cout << "- NEW\n";
	for(int n=0; n < 300 ; n++)
		c2.new1();
	cout << "- DEL\n";
	c2.release();
	cout << " - END!\n";

    return 0;
}

//    TODO:
// Apply WRD_GET, WRD_IS_NULL
