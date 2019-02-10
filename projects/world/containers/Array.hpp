#pragma once

#include "Container.hpp"

namespace wrd
{
	class Array : public Container
	{	WRD_CLASS_DECL(Array, Container)
	public:
		Node& operator[](widx n); 
		const Node& operator[](widx n) const; 

	public:
		//	Container:
		Node& get(widx n); 
		const Node& get(widx n) const; 
		virtual widx insert(widx n, Strong new1); 
		widx push(Strong new1); 
		widx push(const Container& rhs); 
		//	Lengthable:
		virtual wcnt getSize() const; 
		virtual wcnt getLen() const; 
		
	protected:
		virtual Node& _get(widx n); 

	private:
		std::vector<Strong> _arr;
	};
}
