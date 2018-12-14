#include "TWeak.inl"
#include "../mgrs/World.hpp"

namespace wrd
{
#define THIS TWeak<T>
#define TEMPLATE template <typename T>

    TEMPLATE THIS::TWeak() { }
    TEMPLATE THIS::TWeak(T& it) { bind(it); }
    TEMPLATE THIS::TWeak(T* it) { bind(it); }
    TEMPLATE THIS::TWeak(Bindable& rhs) { bind(rhs); }

    TEMPLATE This& THIS::operator=(const This& rhs)
    {
        bind(rhs);
        //  Super::operator=()를 해서는 안된다.
        return *this;
    TEMPLATE This& THIS::operator=(T& new1)
    {
        bind(new1);
        return *this;
    }

    TEMPLATE This& THIS::operator=(T* new1)
    {
        bind(new1);
        return *this;
    }

    TEMPLATE wbool THIS::operator==(const This& rhs) const { return &get()  == &rhs.get(); }
    TEMPLATE wbool THIS::operator!=(const This& rhs) const { return &get() != &rhs.get(); }
    TEMPLATE THIS::operator wbool() const { return isBind(); }
    TEMPLATE const T* THIS::operator->() const { return &get(); }
    TEMPLATE T* THIS::operator->() { return &get(); }
    TEMPLATE const T* THIS::operator*() const { return &get(); }
    TEMPLATE T* THIS::operator*() { return &get(); }

    TEMPLATE Result& THIS::bind(T& new1)
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

    TEMPLATE Result& THIS::bind(Bindable& rhs) { return bind(rhs.get()); }
    TEMPLATE Result& THIS::bind(T* new1)
    {
        WRD_IS_NULL(new1);
        return bind(*new1);
    }

    TEMPLATE const T& THIS::get() const
    {
        WRD_IS_THIS(T)
        const Instance& inst = World::get().getInstancer()[_id].getInstance();
        //  정확한 인터페이스가 나오지 않았다.
        if(inst.getSerial() != getSerial()) {
            unbind();
            WrongBind.warn("...");
            return Nuller<Instance>::ref;
        }

        return inst;
    }

    TEMPLATE T& THIS::get() { return const_cast<T&>((const_cast<This*>(this))->get()); }
    TEMPLATE Result& THIS::unbind() { return release(); }

    TEMPLATE wbool THIS::isBind() const
    {
        const Block& block = getBlock();
        return block.isExist() && block.getSerial() == _serial;
    }

    TEMPLATE Result& THIS::release()
    {
        if(isBind())
            _getBlock().ignore();
        return Super::release();
    }

    //TODO: TEMPLATE ResultSet isValid() const;
    TEMPLATE const Block& THIS::getBlock() const { return World::get().getInstancer()[_id]; }
    TEMPLATE Block& THIS::_getBlock() { return World::get().getInstancer()[_id]; }
}
