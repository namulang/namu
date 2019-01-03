#pragma once

#include "TWeak.inl"
#include "../world.hpp"
#include "../memory/Block.hpp"

namespace wrd
{
#define TEMPL template <typename T>
#define THIS TWeak<T>

	WRD_CLASS_DEF(TEMPL, THIS)

    TEMPL THIS::TWeak() { }
    TEMPL THIS::TWeak(T& it) { this->bind(it); }
    TEMPL THIS::TWeak(T* it) { this->bind(it); }
    TEMPL THIS::TWeak(Bind& it) { this->bind(it); }
    TEMPL THIS::TWeak(Bind* it) { this->bind(it); }
    TEMPL const T* operator->() const { return &get(); }
    TEMPL const T* operator*() const { return &get(); }
    TEMPL T* operator->() { return &get(); }
    TEMPL T* operator*() { return &get(); }

	TEMPL This& operator=(This& rhs)
	{
		if(this == &rhs) return *this;

		bind(rhs);
		return *this;
	}

    TEMPL Res& THIS::bind(const Instance& new1)
    {
        //  pre:
        //      param-validation:
        Block& blk = WRD_GET(const_cast<Block&>(new1.getBlock()));

        //  main:
        unbind();
        this->_setId(new1.getId());
        this->_setSerial(blk.getSerial());
        return blk._onWeak(1);
    }

    TEMPL Instance& THIS::_get()
    {
        WRD_IS_THIS(T)
        Instance& ins = WRD_GET(this->_getBlock(_its_id).get());
        //  정확한 인터페이스가 나오지 않았다.
        if(ins.getSerial() != this->getSerial()) {
            unbind();
            wasbindfail.warn("...");
            // TODO: uncomment return nulr<Instance>();
        }

        return ins;
    }

    TEMPL Res& THIS::unbind() { return release(); }

    TEMPL wbool THIS::isBind() const
    {
        const Block& block = this->getBlock();
        return 	block.isExist() &&
				block.getSerial() == this->getSerial();
    }

    TEMPL Res& THIS::release()
    {
        if(isBind())
            this->_getBlock().ignore();
        return Super::release();
    }

	TEMPL Block& THIS::_getItsBlock()
	{
		WRD_IS_THIS(Block)
		return 
	}

    //TODO: TEMPL ResSet isValid() const;
#undef TEMPL
#undef THIS
}
