#include "Composit.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"
#include "../containers/Chain.hpp"

namespace wrd
{
#define THIS Composit
	WRD_CLASS_DEF(THIS)

	Res& THIS::init()
	{
		WRD_IS_SUPER(init())
		return _initNodes();
	}

	Res& THIS::release()
	{
		_nodes.release();
		return Super::release();
	}

    const Container& THIS::getNodes() const
    {
		//	TODO: 
        //if(_nodes.getLength() <= 0)
        //   _initNodes();
        return *_nodes;
    }

    Res& THIS::_initNodes()
    {
		/* TODO:
        _nodes.release();

        const Chain& chain = WRD_GET(cls.getNodes().down<Chain>());
        if(_nodes.chain(chain.getControl()[0])) // first elem as a container owned by "chain"
            return wasfuncfail.warn("");
		*/
        return wasgood;
    }
}
