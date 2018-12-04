#pragma once

#include "Node.hpp"

namespace wrd
{
    class Result;
    class Container;
    class Composit : public Node
    {
    public: //    Node:
        //        getMember(); 는 공개하지 않는다:
        //        사용자는 Container채로 받게 되면 밖에서 remove, insert를 할 수 있게 된다.
        virtual const Container& getNodes() const;

    private: //    Node:
        virtual Result& _initNodes();

    private:
        //    _nodes can't be declared with protected accessor:
        //        if we do that, module developers can use _nodes and remove or insert some Node at runtime.
        Chain _nodes; // of Container.
    };
}
