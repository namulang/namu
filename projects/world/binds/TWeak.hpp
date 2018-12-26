#pragma once

#include "TWeak.inl"
#include "../bases/TGettable.hpp"
#include "../world.hpp"
#include "../memory/Block.hpp"
#pragma message "4-2-2-4"

namespace wrd
{
#define TEMPL template <typename T>
#define THIS TWeak<T>

	WRD_CLASS_DEFINE(TEMPL, THIS)

    TEMPL THIS::TWeak() { }
    TEMPL THIS::TWeak(const T& it) { bind(it); }
    TEMPL THIS::TWeak(const T* it) { bind(it); }

    TEMPL THIS& THIS::operator=(const This& rhs)
    {
        bind(rhs);
        //  Super::operator=()를 해서는 안된다.
        return *this;
	}

    TEMPL THIS& THIS::operator=(const T& new1)
    {
        bind(new1);
        return *this;
    }

    TEMPL THIS& THIS::operator=(const T* new1)
    {
        bind(new1);
        return *this;
    }

    TEMPL wbool THIS::operator==(const This& rhs) const { return &this->get()  == &rhs.get(); }
    TEMPL wbool THIS::operator!=(const This& rhs) const { return &this->get() != &rhs.get(); }

    TEMPL Res& THIS::bind(const Instance& new1)
    {
        //  pre:
        //      param-validation:
        Block& blk = const_cast<Block&>(new1.getBlock());
        WRD_IS_NULL(blk)

        //  main:
        unbind();
        this->_setId(new1.getId);
        this->_setSerial(blk.getSerial());
        return blk.look();
    }

    TEMPL Instance& THIS::_get()
    {
        WRD_IS_THIS(T)
        Instance& ins = _getBlock().get();
		WRD_IS_NULL(ins)
        //  정확한 인터페이스가 나오지 않았다.
        if(ins.getSerial() != this->getSerial()) {
            unbind();
            wasbindfail.warn("...");
            // TODO: uncomment return Nuller<Instance>::ref;
        }

        return ins;
    }

    TEMPL Res& THIS::unbind() { return release(); }

    TEMPL wbool THIS::isBind() const
    {
        const Block& block = getBlock();
        return block.isExist() && block.getSerial() == _serial;
    }

    TEMPL Res& THIS::release()
    {
        if(isBind())
            _getBlock().ignore();
        return Super::release();
    }

    //TODO: TEMPL ResSet isValid() const;
    TEMPL const Block& THIS::getBlock() const { return World::get().getInstancer()[_id]; }
    TEMPL Block& THIS::_getBlock() { return World::get().getInstancer()[_id]; }

#undef TEMPL
#undef THIS
}
