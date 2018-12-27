#pragma once

#include "../base/Composit.hpp"
#include "Refer.hpp"

namespace wrd
{
    //    Object는 Nodes를 가져야 하는데, 여러가지를 고려해야만 한다.
    //        1. Class에 속한것(Method + static variable)과 객체에 속한것을 구분해야 한다
    //            이는 빠른 Object생성과 메모리 효율을 위해 반드시 필요하다.
    //        2. private, public을 구분해야 하는가?
    //        3. static을 구분해야 하는가?
    //        4. const 와 nonconst를 구분해야 하는가?
    //    여기서는
    class Container;
    class Object : public Composit
    {	WRD_CLASS_DECLARE(Object, Composit)
    public:    // Object:
        ///    shared means what was shared between all of object instance.
        ///    they're all of from Class, mostly Methods.
        /// this's a convinient methods.
        Container& getShared();
        const Container& getShared() const;
        Container& getVars();
        const Container& getVars() const;

    public:    //    Node:
        virtual Refer use(Msg& msg);
        virtual Refer use(Msg& msg) const;
        virtual wbool canUse(const Msg& msg) const;
        virtual const Origin& getOrigin() const;

        //    객체의 멤버변수:
        //        Object Chain = Method.Nodes + Method.ObjectVariables.clone().
        //        클래스이 member는 공유되어야 하며, Method의 Object용 member는 객체마다 따로 갖고 있어야 한다.
        //        늦은 초기화:
        //            배경:
        //                _nodes는 native의 메소드들이나 Managed의 멤버변수를 모아두는, 실질적인 visible 의 한 축을 담당한다. (나머지 한 축은 scope)
        //                문제는 native의 메소드를 visible하게 할때 일어나는데, Native환경에서 사용자가 Object를 상속한 임의의 클래스 A를 지역변수로 생성한 경우, 객체를 사용하기 전에 어딘가에서는 Native메소드들을 담고있는 메타클래스로부터 메소드목록을 객체가 fetching 해야한다.
        //                하지만 이 경우 Object의 생성자에서는 최종 구체클래스 A가 뭔지 모르므로 할 수 없다. 반면 A는 사용자의 클래스이므로, A의 생성자에서도 할 수 없다. (사용자에게 limitation을 거는 꼴이다) 따라서, Nodes의 늦은 초기화로 이문제를 해결한다.
        //
        //                A 생성자안에서 사용자가 사용하든, 밖에서 사용하든 Nodes를
        //                처음 사용하려고 하는 그 순간, Nodes가 아직 초기화되지 않은
        //                경우라면 초기화 로직을 먼저 시작한다.
        //
        //                이 방법의 가장 중요한 점은, 외부에서는 처음부터 Nodes가
        //                채워져 있다고 생각하게 만드는 것이다. 이걸 배신하면 안된다.
        //            Limitation:
        //                생성자 안에서 getNodes()를 호출하면 안된다. 초기화는 1번만 일어난다. 여러번 하게도 할 수 있으나, 그렇게하면 기존의 ObjectVariables를 덮어써야 하므로 어짜피 로직은 망하게 된다.
        //    만약 아래의 함수가 visible이 된다면 어떻게 반환형 const가 전달되지?:
        //        TNativeMethod가 반환형 T = const Container임을 알고있다.
        //        TRefer<const Container> ret = (obj->*fptr)().to<const Container>();
        //        return ret;

    private:    // Node:
        virtual Res& _initNodes();
    };
}
