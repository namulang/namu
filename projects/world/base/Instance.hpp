#pragma once

#include "Thing.inl"
#include "Id.hpp"

namespace wrd
{
	class Block;
	class Instancer;

	class Instance : public Thing
	{	WRD_CLASS_DECL(Instance, Thing)
		friend class Block;
		friend class Akashic; // for _chk_n_from_alloc
		friend class Chunks; // _chk_n_from_alloc
		//	Instance는 World에서 인스턴스 관리를 대신해준다. 여기서부터 bind가 가능하다.

	public:
		Instance();
		Instance(Id id);
		virtual ~Instance();
		//	why was virtual copyconstructor defined with private accessor?:
		//		WorldFrx basically is based on class Node.
		//		So, if all classes returns TStrong<Instance> as a returntype of clone()
		//		user may needs to cast it to Node. inconvenient.
		//		however, if we declared this as a private member-function and 
		//		define clone() non-virtual function as public, we can return Node
		//		as a return-type of clone if it's subclass of Node.
		//
		//	in summary:
		//		clone()  : a wrapper for providing easy-to-use return type.
		//		_clone() : it's a really what cloning happens. subclasses will
		//		override it.

	public:
		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;
		void* operator new(size_t sz);
		void operator delete(void* pt, size_t sz);

	public://Instance:
		Id getId() const;
		virtual wbool isHeap() const;
		virtual Strong toStrong() = 0;
		CStrong toStrong() const;
		virtual Weak toWeak() = 0;
		CWeak toWeak() const;
		const Block& getBlock() const;
		//	Thing:
		virtual Res& release();

	protected:
		Res& _setId(Id new1);

	private:
		Id _id;

	protected:
		static Block& _getBlock(Id id);
		static Instancer& _getMgr();

	private:
		static Id _from_dtor;
		static widx _chk_n_from_alloc;
	};
}
