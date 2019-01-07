#pragma once

#include "ObjectClass.hpp"
#include "../memory/TStrong.hpp"

namespace wrd
{
	//	TODO: MgdClass는 복수 인스턴스가 있어야 하므로 static으로 변수를 공유하는 Class 의 것을 그대로 사용하면 안된다.
	//	대부분의 메소드를 재정의해야 한다.
	//	이 과정에서 가능하면 MgdObject의 것과 변수나 함수 로직이 중복정의하지 말고 재사용할 수 있는 방안을 생각해야 한다.
	//	예), MgdObject에 대한 Proxy.
	class MgdObject;
    class MgdClass : public ObjectClass
    {	WRD_CLASS(MgdClass, ObjectClass)
	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);

	public:	//	Class:
        virtual const Origin& getOrigin() const;
        virtual TStrong<Instance> instance() const;
		//	Node:
		virtual const Container& getNodes() const;

    private:
        TStrong<Origin> _org;
		TStrong<Chain> _nodes;
    };

	WRD_CLASS_INIT(MgdClass)
}
