#pragma once

#include "TWeak.inl"
#pragma message "4-2-2-2"
#include "../bases/TGettable.hpp"
#pragma message "4-2-2-3"
#include "../world.hpp"
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
    TEMPL THIS::operator wbool() const { return isBind(); }
    TEMPL const T* THIS::operator->() const { return &get(); }
    TEMPL T* THIS::operator->() { return &get(); }
    TEMPL const T* THIS::operator*() const { return &get(); }
    TEMPL T* THIS::operator*() { return &get(); }

    TEMPL Res& THIS::bind(const T& new1)
    {
        //  pre:
        //      param-validation:
        Block& blk = const_cast<Block&>(new1.getBlock());
        WRD_IS_NULL(blk)

        //  main:
        unbind();
        _setId(new1.getID);
        _setSerial(blk.getSerial());
        return blk.look();
    }

    TEMPL Res& THIS::bind(const T* new1)
    {
        WRD_IS_NULL(new1);
        return bind(*new1);
    }

    TEMPL const T& THIS::get() const
    {
        WRD_IS_THIS(T)
        const Instance& inst = World::get().getInstancer()[_id].getInstance();
        //  정확한 인터페이스가 나오지 않았다.
        if(inst.getSerial() != getSerial()) {
            unbind();
            wasbindfail.warn("...");
            // TODO: uncomment return Nuller<Instance>::ref;
        }

        return inst;
    }

    TEMPL T& THIS::get()
	{
		WRD_UNCONST()
		return const_cast<T&>(unconst->get());
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
