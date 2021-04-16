#include "Composit.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"
#include "../containers/Chain.hpp"

namespace wrd
{
#define ME Composit
	WRD_CLASS_DEF(ME)

	ME::ME() : _nodes(0) {}
	ME::ME(const me& rhs) : super(rhs) { _assign(rhs); }
	ME::~ME() { _release(); }

	ME& ME::_assign(const me& rhs)
	{
		_release();
		//TODO: if(rhs._nodes)
		//	_nodes = new Chain(*rhs._nodes);
		return *this;
	}

	Res& ME::_release()
	{
		if(_nodes)
			_nodes->release();
		_nodes = NULL;
		return wasgood;
	}

	ME& ME::operator=(const me& rhs)
	{
		WRD_ASSIGN_GUARD()
		super::operator=(rhs);
		return _assign(rhs);
	}

	Res& ME::init()
	{
		WRD_IS_SUPER(init())
		return _initNodes();
	}

	Res& ME::release()
	{
		_release();
		return super::release();
	}

    const Container& ME::getNodes() const
    {
		//	TODO: 
		//if( ! _nodes)
		//	_nodes = new Chain();
        //if(_nodes.getLength() <= 0)
        //   _initNodes();
        return *_nodes;
    }

    Res& ME::_initNodes()
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
