#pragma once

#include "../base/Id.hpp"
#include "../base/Trace.hpp"

namespace wrd
{
    class Block : public Trace
    {	WRD_CLASS_DECL(Block, Trace)
    public:
        /// increase refcnt.
        Res& onWeak(wcnt vote);
        Res& onStrong(wcnt vote); // TODO: check isHeap(), apply only if isHEAP() == true.
		//		TBindable:
		using Super::bind;
		virtual Res& bind(const Instance& new1);
		virtual Res& unbind();
		virtual wbool isBind() const;
		//		Instance:
		virtual wbool isHeap() const;

	protected:
		//	TGettable:
		virtual Instance& _get();
    };
}
