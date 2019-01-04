#pragma once

#include "../base/Instance.hpp"
#include "Bindable.hpp"

namespace wrd
{
    class Block : public Instance, public Bindable
    {	WRD_CLASS_DECL(Block, Instance)
		template <typename T> friend class TWeak;
		template <typename T> friend class TStrong;
    public:
		//	Block:
		Res& setSerial(wcnt new1);
		wcnt getSerial() const;
		//	Bindable:
		virtual Res& unbind();
		virtual wbool isBind() const;
		using Super::bind;
		virtual Res& bind(const Instance& new1);
		//	Instance:
		virtual wbool isHeap() const;

	protected:
		//	Block:
        Res& _onWeak(wcnt vote);
        Res& _onStrong(wcnt vote); // TODO: check isHeap(), apply only if isHEAP() == true.
		virtual Instance& _get();
		virtual Res& _bind(const Instance& new1);

	private:
		wcnt _serial;
    };
}
