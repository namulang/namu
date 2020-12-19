#pragma once

#include "../interface/Instance.hpp"
#include "../bind/Bindable.hpp"

namespace wrd { namespace memlite {

    class Chunk;
    class BindTag : public Instance, public Bindable {
        WRD_DECL_THIS(BindTag, Instance)
        WRD_INIT_META(This)
		template <typename T> friend class TWeak;
		template <typename T> friend class TStrong;

    public:
		BindTag();
		BindTag(Id id);

		const Chunk& getChunk() const;
		wcnt getStrongCnt() const;
		//	Bindable:
		virtual wbool unbind();
		virtual wbool isBind() const;
		virtual const Type& getBindable() const;
		using Bindable::canBind;
		virtual wbool canBind(const Type& cls) const;
		//	Instance:
		virtual Id getId() const;
		virtual wbool isHeap() const;
		virtual wbool rel();
        //  TypeProvidable:
        const Type& getType() const {
            return TType<BindTag>::get();
        }

	protected:
		virtual Instance& _get();
		virtual wbool _bind(const Instance& new1);

	private:
        wbool _onStrong(wcnt vote);
		wbool _completeId(Instance& it);
		wbool _sync(Id new1);

		Instance* _pt;
		wcnt _strong;
    };
}}
