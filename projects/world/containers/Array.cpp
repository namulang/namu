#include "Array.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Array
	WRD_CLASS_DEF(THIS)

	Node& THIS::operator[](widx n) { return get(n); }
	const Node& THIS::operator[](widx n) const { return get(n); }
	Node& THIS::get(widx n) { return _get(n); }

	const Node& THIS::get(widx n) const
	{
		WRD_UNCONST()
		return unconst._get(n);
	}

	widx THIS::insert(widx n, Strong new1)
	{
		_arr.insert(_arr.begin()+n, new1);
		return n;
	}

	widx THIS::push(Strong new1) { return insert(getLen(), new1); }

	widx THIS::push(const Container& rhs)
	{
		//	TODO: imple propely.
		Array& cast = (Array&) rhs;
		widx n = 0;
		for(std::vector<Strong>::const_iterator e=cast._arr.begin(); e != cast._arr.end() ;e++)
			n = push(*e);
		return n;
	}

	wcnt THIS::getSize() const { return _arr.size();}
	wcnt THIS::getLen() const { return _arr.size(); }
	
	Node& THIS::_get(widx n)
	{
		if(0 < n || n >= _arr.size())
			return nulr<Node>();
		return _arr[n].get();
	}
}
