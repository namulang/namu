#pragma once

#include "Node.hpp"
#include "../binds.hpp"

namespace wrd
{
	class Chain;
    class Composit : public Node
    {	WRD_CLASS_DECLARE(Composit, Node)
    public: //    Node:
        //        getNodes(); 는 공개하지 않는다:
        //        사용자는 Container채로 받게 되면 밖에서 remove, insert를 할 수 있게 된다.
        virtual const Container& getNodes() const;
        //  State:
        virtual Result& init();
        //  Thing:
        virtual Result& release();

    private: //    Node:
        virtual Result& _initNodes();

    private:
        //    _nodes can't be declared with protected accessor:
        //        if we do that, module developers can use _nodes and remove or insert some Node at runtime.
        TStrong<Chain> _nodes; // of Container.
    };
}
