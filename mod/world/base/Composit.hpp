#pragma once

#include "Node.hpp"
#include "../memory/TStrong.inl"

namespace wrd
{
	class Chain;

    class Composit : public Node
    {	WRD_CLASS_DECL(Composit, Node)
    public:
		Composit();
		Composit(const me& rhs);
		virtual ~Composit();

	public:
		me& operator=(const me& rhs);

	public:
		//    Node:
        virtual const Container& getNodes() const;
        //  State:
        virtual Res& init();
        //  Thing:
        virtual Res& release();

    private: //    Node:
        virtual Res& _initNodes();
		Res& _release();
		me& _assign(const me& rhs);

    private:
        //    _nodes can't be declared with protected accessor:
        //        if we do that, module developers can use _nodes and remove or insert some Node at runtime.
        Chain* _nodes; // of Container.
    };
}
