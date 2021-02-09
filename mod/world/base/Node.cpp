#include "Node.hpp"
#include "../meta.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define THIS Node
	WRD_CLASS_DEF(Node)

	Node& THIS::operator[](widx n) { return getNode(n); }
	const Node& THIS::operator[](widx n) const { return getNode(n); }
	wbool THIS::operator==(const This& rhs) { /*TODO:*/ return false; }
	wbool THIS::operator!=(const This& rhs) { return ! operator==(rhs); }
	wbool THIS::isOccupy() const { return getClass().isOccupy(); }
	Node& THIS::getNode(widx n) { return _getNodes()[n]; }
	const Node& THIS::getNode(widx n) const { return getNodes()[n]; }
	Node& THIS::getNode(const Str& name) { /*TODO: return _get(false, [&name](Node& e) { return e.getName() == name; });*/ return nulOf<Node>(); }

	const Node& THIS::getNode(const Str& name) const
	{
		/* TODO: WRD_UNCONST()
		return unconst._get(true, [&name](Node& e) { return e.getName() == name; }); */
		return nulOf<Node>();
	}

	Strong THIS::use(Msg& msg)
	{
		// TODO: Nodes들을 검색해서 msg를 canUse인지 체크할것.
		return Strong();
	}

	CStrong THIS::use(Msg& msg) const
	{
		//	TODO:
		return CStrong();
	}
	
	wbool THIS::canUse(const Msg& msg) const { /*TODO: return msg.getName() == getName(); */ return false;}
	wbool THIS::isStatic() const { return false; }
	wbool THIS::isConst() const { return false; }

	Strong THIS::implicit(const Class& cls)
	{
		if(isSub(cls))
			return Strong(*this);
		return Strong();
	}
	CStrong THIS::implicit(const Class& cls) const
	{
		WRD_UNCONST()
		return CStrong((const CStrong&) unconst.implicit(cls));
		// we code inliney because of prevention to releasing instance of returned variable from unconst.implicit()
	}

	Strong THIS::toStrong() { return *this; }
	Weak THIS::toWeak() { return *this; }
	Container& THIS::_getNodes() { return const_cast<Container&>(getNodes()); }

	Node& THIS::_get(wbool want_const, std::function<wbool(Node&)> tester)
	{
		/* TODO:
		WRD_ARE_NULL(nulOf<Node>(), msg, members)

		Node* found = NULL;
		if(_getNodes().each<T>([&found, want_const, tester](Node& e) {
			if(e.isConst() != want_const) return wasgood;
			if( ! tester(e)) return wasgood;
			if(found)
				return Duplicated.err(".."); // if ret isn't Success, it means that stop eaching.
			
			found = &e;
			return wasgood; // means keep eaching.
		}))
			return wasdup.err(".....").returns(nulOf<Node>());

		return *found;
		*/
		return nulOf<Node>();
	}
}
