#pragma once

#include "../interface/Instance.hpp"
#include "../bind/Bindable.hpp"

namespace wrd {

    class Chunk;
    class BindTag : public Instance, public Bindable {
        WRD_DECL_THIS(BindTag, Instance)
        WRD_INIT_META(This)
		template <typename T> friend class TWeak;
		template <typename T> friend class TStrong;
        template <typename T> friend class TWeakTactic;
		template <typename T> friend class TStrongTactic;

    public:
        //  BindTag:
		BindTag();
		BindTag(Id id);

		const Chunk& getChunk() const;
		wcnt getStrongCnt() const;
		wbool rel();
		//	Bindable:
		wbool unbind();
		wbool isBind() const;
		const Type& getBindable() const;
		using Bindable::canBind;
		wbool canBind(const Type& cls) const;
		//	Instance:
		Id getId() const;
		wbool isHeap() const;
        //  TypeProvidable:
        const Type& getType() const {
            return TType<BindTag>::get();
        }

	protected:
        //  Bindable:
		Instance& _get();
		wbool _bind(const Instance& new1);

	private:
        //  BindTag:
        wbool _onStrong(wcnt vote);
		wbool _completeId(Instance& it);
		wbool _sync(Id new1);

		Instance* _pt;
		wcnt _strong;
    };
}
