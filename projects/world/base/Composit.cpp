#include "Composit.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"
#include "../containers/Chain.hpp"

namespace wrd
{
#define THIS Composit
	WRD_CLASS_DEF(THIS)

	THIS::THIS() : _nodes(0) {}
	THIS::THIS(const This& rhs) : Super(rhs) { _assign(rhs); }
	THIS::~THIS() { _release(); }

	THIS& THIS::_assign(const This& rhs)
	{
		_release();
		//TODO: if(rhs._nodes)
		//	_nodes = new Chain(*rhs._nodes);
		return *this;
	}

	Res& THIS::_release()
	{
		if(_nodes)
			_nodes->release();
		_nodes = NULL;
		return wasgood;
	}

	THIS& THIS::operator=(const This& rhs)
	{
		WRD_ASSIGN_GUARD()
		Super::operator=(rhs);
		return _assign(rhs);
	}

	Res& THIS::init()
	{
		WRD_IS_SUPER(init())
		return _initNodes();
	}

	Res& THIS::release()
	{
		_release();
		return Super::release();
	}

    const Container& THIS::getNodes() const
    {
		//	TODO: 
		//if( ! _nodes)
		//	_nodes = new Chain();
        //if(_nodes.getLength() <= 0)
        //   _initNodes();
        return *_nodes;
    }

    Res& THIS::_initNodes()
    {
		/* TODO:
        _getNodes().release();

        const Chain& chain = WRD_GET(cls.getNodes().down<Chain>());
        if(_nodes.chain(chain.getControl()[0])) // first elem as a container owned by "chain"
            return wasfuncfail.warn("");
		*/
        return wasgood;
    }
}
