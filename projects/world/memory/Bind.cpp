#include "Bind.hpp"
#include "TStrong.hpp"
#include "../pretypes/Reses.hpp"

namespace wrd
{
#define THIS Bind
	WRD_CLASS_DEF(THIS)

	wbool THIS::operator==(const This& rhs) const { return &get() == &rhs.get(); }
	wbool THIS::operator!=(const This& rhs) const { return ! operator==(rhs); }

	THIS& THIS::operator=(const This& rhs)
	{
		WRD_ASSIGN_GUARD()
		
		_assign(rhs);
		return *this;
	}

	wbool THIS::isBind() const { return _getBlock(_its_id).isExist(); }

	Res& THIS::unbind()
	{
		_its_id.num = WRD_INDEX_ERROR;
		return wasgood;
	}

	Id THIS::getItsId() const { return _its_id; }
	wbool THIS::canBind(const Class& cls) const { return getClass().isSub(cls); }

	CStrong THIS::use(Msg& msg) const
	{
		const Node& got = WRD_GET(get<Node>());
		return got.use(msg);
	}

	Strong THIS::use(Msg& msg)
	{
		Node& got = WRD_GET(get<Node>());
		return got.use(msg);
	}

	const Origin& THIS::getOrigin() const
	{
		const Node& got = WRD_GET(get<Node>(), Super::getOrigin());
		return got.getOrigin();
	}

	const Container& THIS::getNodes() const
	{
		const Node& got = WRD_GET(get<Node>(), Super::getNodes());
		return got.getNodes();
	}

	Strong THIS::to(const Class& cls)
	{
		/* TODO:
		if( ! _bean)
			return Super::to(cls);

		//	다운캐스팅으로 _bean->to()가 동작한 경우에만 isConst()가 영향을 미치게 된다.
		//	고찰 결과, _bean->to()가 전혀다른 타입(사용자가 정의한)으로 값복사되어 반환된 경우는
		//	isConst()가 동작하지 않아야 한다.
		if(cls.isSub(_cls))
			return Super::to(cls);
		return _bean->to(cls);
		*/
		return Strong();
	}

	Res& THIS::assign(const Thing& it)
	{
		/* TODO:
		// Null체크는 Thing::assign()에서 한다.
		WRD_IS_SUPER(assign(it))

		//	Sharable, Occupiable:
		//		여기서는 실질적인 sharing vs occupying의 동작차이를 만들어내는 곳이다.
		//		Occupiable이라도 const 인 경우에는 인터프리터에 의해서 const Bind에 감싸서 scope나 멤버함수에 들어가게 된다.
		//		또한 이문제는 it이 occupiable인지 sharable인지 구분할 필요가 없다. 오로지 this가 occupiable인지 아닌지만 중요하다.
		if(_cls.isOccupy()) // Occupiable은 상속이 된다.
		{
			//	이경우 const건 아니건 사실 중요하지 않다. 오직 중요한건 occupiable이면 실제 객체에게 assign을 떠 넘기면 된다는 사실이다.
			Node& bean = WRD_GET(get()); // 만약 isConst() 일 경우, 여기서 NULL이 나오게 된다.
			return bean.assign(it);
		}
	
		//	sharable 이라면 이렇게 간단히 끝난다.
		Bind& refered = it.down<This>();
		if(refered.isExist())
			return bind(refered);
		return bind(it.down<Object>()); // null이 들어가도 상관없다. */
		return wasgood;
	}

	Res& THIS::_bind(const Instance& it)
	{
		WRD_ASSERT(canBind(it), waswrongtype);
	
	    unbind();
		_its_id = it.getId();
	    return wasgood;
	}
	
	Instance& THIS::_get()
	{
	    Instance& ins = WRD_GET(this->_getBlock(_its_id).get());
	    if(ins.getId().sep.serial != this->_its_id.sep.serial) {
	        unbind();
	        wasbindfail.warn("...");
	        // TODO: uncomment return nulr<Instance>();
	    }
	
	//    TODO: impl _get()
	    return ins;
	}
	
	Thing& THIS::_down(const Class& cls)
	{
		Thing& got = get();
		return got.isExist() ? got._down(cls) : nulr<Thing>();
	}

	Res& THIS::_assign(const This& rhs)
	{
	    WRD_ASSIGN_GUARD(rhs, wasnull)
	    //    Only not available combination between this and rhs is,
	    //    when this is nonconst but rhs is const.
	    //    because when we accept this case, in consequence, rhs's binded one will loose their constness.
	    if( ! isConst() && rhs.isConst())
	        return waswrongargs; // the only case can't accept.
	
	    return _bind(rhs.get());
	}

#undef THIS
}
