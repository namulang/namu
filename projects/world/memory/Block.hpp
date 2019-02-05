#pragma once

#include "../base/Instance.hpp"
#include "Bindable.hpp"
#include "Chunk.hpp"

namespace wrd
{
    class Block : public Instance, public Bindable
    {	WRD_CLASS_DECL(Block, Instance)
		template <typename T> friend class TWeak;
		template <typename T> friend class TStrong;
    public:
		Block();
		Block(Id id);

	public:
		Res& setSerial(wcnt new1);
		wcnt getSerial() const;
		const Chunk& getChunk() const;
		//	Bindable:
		virtual Res& unbind();
		virtual wbool isBind() const;
		virtual const Class& getBindable() const;
		using Bindable::canBind;
		virtual wbool canBind(const Class& cls) const;
		//	Instance:
		virtual Id getId() const;
		virtual wbool isHeap() const;
		virtual Strong toStrong();
		virtual Weak toWeak();
		//	Thing:
		virtual Res& release();

	protected:
		//	Block:
		virtual Instance& _get();
		virtual Res& _bind(const Instance& new1);

	private:
        Res& _onStrong(wcnt vote);
		Res& _completeId(Instance& it);
		Res& _sync(Id new1);

	private:
		Instance* _pt;
		wcnt _strong;
    };
}
