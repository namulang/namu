Object
    isValid()
    Instance
        getID()
        Node
            call() = 0
            bool has() = false
            Function[]
            Function : Unique, Named
                call(Node&)
            ClassBase
                TClass
                    WorldClass
                        동적으로 Function을 넣을 수 있음.
                        Reference
                        Integer
                        Float
                        Void
                        Array
                        Sequence
                        List
                        Map

            WObject
                WorldClass* klass
                WObject[] Members
            
            Caller
                Function& func
                Node[] args --> [0] : this
                execute()

예)
    int a
    a = 5
        // 파싱하는 순간 밑에 처럼 Caller객체가 생성됨.
        Caller[] = {
            Caller(Integer, construct, "a")
            Caller(THIS["a"], Assign, Caller(Integer, construct, {"", 5}))
        }

    MyClass1 b
    b.foo()
        Caller[] = {
            Caller(TypeManager["MyClass1"], construct, {"b"}) // 일단 TypeManager로 찾으면 바인딩된걸 넘겨주므로 execute는 빠름.
            Caller(THIS["b"], "foo"/*여기서 호출이 불가능하면 logical error*/, {}) // Q. foo가 여러개 있을텐데, 이게 함수인지 아닌지도 모르는데.. --> 구분할 필요 없음. 객체나 함수나 모두 똑 같은 "메시지"를 수신하는 거다.
                // 결과적으로,
                THIS["b"].call("foo", {});
                    Reference::call(string any)
                        return this->actual->call(any)
                    Reference::canCall(string any)
                        return this->actual->canCall(any)
        }




//  #1 ByVal and ByRef policy
class Class1
    int age = 5
    void print()
        Console.out("age = " + age)

class Class2
    result main(string[] args)
        int a1 = 5, a2 = 8    
        a2 = a1
        a1 = 0

        int a3
        int a3_1 = 0
        int a3_2(0)
        int a3_3 = int(0) // a3 == a3_1 == a3_2 == a3_3
        
        Class1 cls1
        Class1 cls1_1()
        Class1 cls1_2 = Class1() // cls1 == cls1_1 == cls1_2
        foo(cls1)

        //int a4 = null --> make sense. but logical error.
        //  Logical error:
        //      Make sense. and World can construct structure for parsed string.
        //      But it's prohibited. this also is detected at compile time.
        Class1 cls2 = null // it's "null" object of Class1.
        
        Console.out(cls2.getAge()) // runtime error.
        object cla = Console
        cla.out(cls2.getAge()) // same as above.
        cls2.getAge() // runtime error


        
        /***** 값 레퍼런싱 *****/
        //  규칙1. 객체를 생성할때 2가지 경우의 수가 있다. 1번은 레퍼런스에 이름을 붙이고 이것으로부터 가리키게 만드는 간접생성,
        //          2번은 객체를 직접 생성하고 이름을 붙이는 직접생성.
        //  규칙2. 간접생성을 통해서 생성된 객체인 인스턴스를 가리키는 인스턴스를 레퍼런스라고 한다.
        //  규칙3. 미리 정의된 타입에 한해서만 직접생성이 가능하다. 그 이외에는 간접생성이다.
        //  규칙4. 객체 자체는 공유할 수 있는 방법이 없다. 공유를 하려면 간접생성 한후 레퍼런스를 통해 이루어져야 한다.
        MyClass my1 // my1은 객체 MyClass()를 가리키는 레퍼런스다.
        MyClass my2 = null // my2는 널을 가리키는 레퍼런스다. "널이 되었다." 고도 표현한다.
        my2 = my1 // my2가 가리키는 대상이 my1이 가리키는 대상이 되었다. my2와 my1은 객체를 공유한다.
        my2 = my1.clone() // my1이 가리키는 대상의 복제품을 my2가 가리킨다. 

        int a1 // a1은 0의 값을 갖는 class int의 객체다.
        //int a2 = null --> logical error. null은 다른 타입으로 캐스팅 될 수 없다.
        int a2 = 0
        a1 = a2 // 이 둘은 객체이므로 값은 공유되지 않는다.            
        
            /****** immutable *****/
            //  규칙1. 소프트웨어 공학에서는 1번으로 나온 객체를 mutable객체, int 같은걸 immutable 객체라고 한다.
            //  mutable객체는 자기자신의 값을 바꾸는 방법을 1개라도 제시하는 객체.
            //  immutable은 string, int와 같이 변경하는 방법이 1개도 없는 걸 말한다.
            //  규칙2. immutable이 되려면 const 메소드만 있어야 한다.
            //  규칙3. immutable이 되려면 size가 비교적 작아야 한다. --> 얼마나 작아야 하는지는 개발자에게 달렸다. 즉, 사용자의 개입이 반드시 필요하다.
            //  규칙4. 자식이 immutable이 되려면, 부모는 immutable이거나 immutable이 될 수 있어야한다.
            //  규칙5. 사용자가 만든 모든 변수는 사실 레퍼런스 이며, 레퍼런스가 가리키는 객체가 immutable일때는 =연산이 다르게 동작하는 것 뿐이다.
        
            class Value // null메소드를 가지고 있으므로 이것은 ADT다. ADT는 immutable이 될 수 없다.
                void print() const // const null메소드

            immutable class Integer from Value // Integer는 구체클래스다. 그리고 const 메소드만 있으므로 immutable 가능한 클래스다.
                int value
                void print() const // null메소드를 채워넣었다. 
                    Console.out(value)

            immutable class Float from Value
                float value
                void print() const
                    Console.out(value)

            class SoManyBytes from Value //immutable 가능하다. 하지만 크기가 크므로 개발자는 하고싶지 않은 케이스다.
                byte[] value
                void print() const
                    Console.out(value)

            SoManyBytes bytes1, bytes2
            Integer int1, int2(1) // int1과 int2, bytes1 모두 레퍼런스다. 그러나 레퍼런스 어떤 객체(immutable인가, 아닌가)에 대한 레퍼런스인가에 따라 동작이 달라진다.
            int1 = int2 // 이경우 int1 레퍼런스의 =()가 호출되며, 그 안에서 int1이 가리키는 객체의 =()로 redirection 한다.
            bytes1 = bytes2 // 이경우 bytes1 레퍼런스 자체에 =()가 처리한다.
            object obj = int1 // object는 int1과 같은 클래스를 공유하고 있다.
            obj = int2  // 이 역시 object 타입이 존재하지 않는, mutable인 객체로 간주한다. obj는 그러한 object에 대한 레퍼런스이다. 
                        // 결과 obj는 int2와 공유하게 된다.
            object obj2 = bytes1
            obj2 = bytes2 // obj2와 bytes2는 같은 객체를 가리킨다.
            //  object가 mutable로 간주하는 이유:
            //      World는 디폴트로 클래스를 mutable로 간주한다.
            //      mutable은 immutable을 대체할 수 있다. clone() 메소드등을 사용하면.
            //      그러나 immutable은 mutable로 대체될 수 없기 때문이다. SoManyBytes같은 경우는 크기가 크기때문에 절대로 immutable이 되어서는 안된다.
            //      Immutable을 사용하는 목적은 어디까지나 개발의 편의 때문이다. 빌트인타입인 int, float은 새로운 인스턴스로 만들어져야 하는 케이스가 많기 때문에
            //      매번 .clone()을 호출하도록 할 수 없기때문에 사용하는 것이다.
            //      위의 이유를 이해한 뒤, object[] 배열안에 int, float, 사용자의 객체에 대한 레퍼런스 등이 담겨있는 상황을 생각해보자.
            //          object는 구체 클래스를 모르는 상황에서 작성되어져야 한다.
            //          개발자는 배열에 담겨있는 것이 mutable인지 immutable인지 따질 수 없기에 개발자는 모든 원소가 둘 중 1가지라고 가정하고 작성해야 한다.
            //          따라서 mutable은 immutable을 대신할 수 있으므로 object는 mutable로 간주되어야 하는 것이다.
            
            int age = 5
            object obj3 = age
            age = 7 // obj3 == 7.
            
            //  Q. 다음과 같은 상황을 보라. immutable이 mutable로 되어버리는 상황이 발생한다.
            class A
                void foo(object) const
                    object++


                                                        //  방법1. 만약 immutable이란 건 그냥 =()에 대해서 객체 자체에 할당을 하는 것. 이라고정의하면 어떻게 되나?
                                                        //  const 같은 조건은 다 빼버리고. --> 이게 맞는거 같은데? =()에 대해서 다른 컨셉을 갖는것. 그게 다인거 같다.[
                                                            ';'
                                                        ]


            
            A a
            int age = 28
            a.foo(age)
            Console.out(age)
            age == 29 // ok. 





                                                        //  Q. 사용자가 만든 객체인데, 직접생성을 사용하고 싶은 경우가 있지 않을까
                                                        //      Q. 이를테면?
                                                        //      A. SuperInt 같은거.
                                                        //          합당해보인다.
                                                        //      Q. 사용자는 클래스를 만들때 "immutable" 클래스다라는 걸 어떻게 잘 표현하게 할 수 있을까?
                                                        //          방법1. 상속시 지정
                                                        //              Q. 부모클래스는 간접생성인데 자식클래스만 직접생성으로 하고 싶은 경우도 있을까?
                                                        //                  A1. 시나리오를 나누어 생각해보자. 일단 4가지 경우가 있다.
                                                        //                      [x] 1. 부모 mutable - 자식 immutable
                                                        //                          가능하다. 보통은 immutable이란건 하나라도 자신을 변경하는 메소드가 없는 걸 말하기 때문에.
                                                        //                          자식이 immutable이면 부모도 immutable이 되어야 한다.
                                                        //                          하지만 부모가 immutable 속성을 가지고 있으나 mutable로 취급하는 경우라면 얘기가 다르다.
                                                        //                      [o] 2. 부모 mutable - 자식 mutable
                                                        //                      [o] 2. 부모 immutable - 자식 immutable
                                                        //                      [x] 2. 부모 immutable - 자식 mutable
                                                        //
                                                        //                  A2. 아직 상속을 어떻게 한다는 걸 정하지 않았다. 상속을 정하면 길이 보일 수 있다.
                                                        //
                                                        //          방법2. immutable인지 아닌지 판정은 컴파일러가 const 메소드만 존재하는가 아닌가로 판정한다.
                                                        //              [x] Q. 시나리오를 만들어보자. 제대로 동작할 것인가? --> 이것만으로는 부족하다.
                                                        //                  [x] Q. 그러면 ADT 같은 경우는 어떻게 되나? --> 안된다.
                                                        //                      예를보자.
                                                        //                      class JPEGImage
                                                        //                          int getAge() // immutable인 int를 반환하므로 이것은 const 함수다.
                                                        //                          char[] data
                                                        //
                                                        //                      동시에 Value는 const 함수만 있으므로 immutable 객체가 된다.
                                                        //                      따라서 저 data는 매번 복사 될 것이다.
                                                        //                  따라서 const 메소드가 없다는 건 "immutable이 가능하다" 정도는 판정할수는 있는 도구가
                                                        //                  될 수 있을뿐, 이거 자체가 immutable 확정은 되지 않는다.

                                                        //  Q. object는 어떠한 것도 담을 수 있다. 만약, object에다가 객체 자체를 넣으면 어떻게 되나?
                                                        //      A. object는 logical 에러를 무시하는 기능이 있을 뿐이다. 나머지는 똑같다.
                                                        //      컴파일러 입장에서 연산을 시뮬레이션 해보면 결과가 나온다.
                                                        //      시나리오1. object obj = int(3) 가 있다고 해보자.
                                                        //          객체를 직접 이름을 붙여 


        /***** 명명법 ************/
        // Q. 자주 쓰는 클래스 몇개를 소문자로 하는걸 선택했다. 근데 그러면 object, code 같은 것들도 
        //  keyword가 되므로 사용자가 당황할 수 있지 않을까?
        //  Q.  일반적으로 메소드명에 낙타식을 사용한다. 하지만 대문자를 중간중간 입력하는건 귀찮기도 하다.
        //      더 좋은 방법은?
        //      [x] 방법1. - 를 사용하게 한다.
        //          createOnlyWhatHave(int args) --> create-only-what-have(int args)
        //          쉬프트를 안눌러서 편할 것 같지만 -를 누르면 손의 위치가 벗어나므로 더 힘들어진다는걸 알았다.
        //          make-instance()
        //          게다가 이런걸 보자. 
        //              a1.make-instance() 
        //          이건 마치 a1.make 라는 변수가 있고, instance() 라는 함수는 int를 반환한다고 했을때의 연산
        //          처럼 보이지 않는가. 
        //      방법2. 



        /***** 코드도 객체다 ******/
        //  코드 1줄도 객체가 될수 있다. 실행() 이라는 객체가 될 수 있는 것이다.
        //  code 클래스는 execute()가 되었을때 미리 지정된 코드를 1줄 실행시킨다.
        //  Q. 어떻게 코드를 code안에 넣게 할것인가.
        //      단순히 code a = my_age.getAge() 처럼 적으면 이건 단순히 age를 반환한걸 저장한게 되버린다.
        code[] codes = []


        /***** 연산 우선순위 ******/
        //  규칙1. 기본컨셉은 "니가 캐스팅해!" 다. 단, 그렇게 되면 매우 귀찮기 때문에 다음과 같은 것들은 대신 해준다.
        //  규칙2. 레퍼런스의 경우: upcasting
        //  규칙3. predefined class의 경우: "표현 가능성의 부피" 를 기준으로 적은데에서 많은 곳으로 전이한다.
        //          bool -> char -> int -> float -> string
        //              \-> result --------------/
        //          예를들어, string -> int 가 되기 위해서는 to() 함수를 사용하는 수밖에 없다.
        //  규칙4. 모든 객체는 to(type) 함수가 존재한다. 클래스 개발자는 이 함수를 overide 할 수 있다.
        //  Q. 이렇게 되면 casting은 런타임에러의 영역이 되어버린다. 에러탐지에 취약해져 버리는 것이다. 개선점은?
        //      방법1. logical 에러로 판단이 가능한가?
        //  Q. 이렇게 해도 과연 편리할지 한번은 생각해볼 필요가 있다.

    
        /***** 수열 **************/
        //  규칙1. 람다의 미니버전으로, 일정 공식에 따른 결과값을 내보내는 수열(배열과 비슷한 인터페이스를 가짐)
        //          를 만들 수 있다.
        //  규칙2. 인덱스 참조시 1부터 시작한다.
        //  규칙3. 인덱스 참조가 일어날때, 값이 계산되서 나온다. 수열은 메모리를 원소마다 차지하지 않는다.
        //  규칙4. 좌측이 각 원소의 템플릿절, 오른쪽이 범위절이다.
        //  규칙5. 템플릿절에는 약속된 키워드 "n"에 오른쪽의 값이 evaluate되어 나오게 된다.N
        //  규칙6. 범위절은 ... 라는 기호를 중심으로 왼쪽을 start, 오른쪽을 end로 표현한다.
        //  규칙7. 범위절에 int 값 1개만 적으면 "1 ..." 라는 뜻이 생략된걸로 간주한다.
        //  규칙8. 템플릿절를 적지 않고 생략하면 "n"이 대신 들어간다.
        sequence seq = {2*n + 1 | 1 ... 10}
        seq[1] // int(3)
        seq[5] // int(11)
        sequence seq1 = {2*n+1|10}
        seq[5] == seq1[5] // true

        //  Q. 수열에 객체를 반환하도록 할수도 있는가?
        //      Q. 그때 타입체크로 컴파일타임에 할 수 있도록 할 수 있는가?
        //      Q. 이것은 배열에도 해당되는 이야기가 된다.
        


        /***** scope ************/
        //  규칙1. "break 값" 을 통해서 scope를 벗어남과 동시에 값을 전달 할 수 있다.
        //  규칙2. --> 기호를 사용하면 개행하지 않고도 1줄은 이어서 적을 수 있다.



        /***** 명령문도 객체다 ****/
        //  규칙1. 명령문.it 을 하면, 최근 사용한 명령문의 인자가 들어있다.
        if a < 4
            Console.out(if.it) // "true"가 찍힌다.
            //  Q. 이게 과연 장점이 있을까?
            //  Q. 중간에 함수 호출이 있고, 그 함수 안에 if가 있는 경우는?


        /***** 반복문 ************/
        result r = for int a in {5} // 1 ... 5
            Console.out(a) // r에는 마지막 Console.out(5)을 하고난 결과물이 들어가게 된다.
            //  Q. 이 말은 개발자는 할당하기 전에 for문 마지막 문장의 결과가 무엇인지 주시하고 있어야 하는 말이 된다.
            //  Q. 이게 효력이 있는가?

        result r2 = for int a in {5}
            if a <= 4 --> Console.out(a)
            else --> break fail // r2는 fail이다.
            //  Q. 이말도 역시 개발자가 break 하는 것들은 모두 같은 종류의 타입이어야 한다는 것이다.
            //  Q. 효력이 있는가?

        while true


        /***** switch문 **********/
        //  Q. 만약 이렇게 사용한다고 했을때
        int a2 = if a1 > 55 --> break a1 * 2
            elif a1.getClass() != int --> break 0
            else --> break a1
        string a2 = if int(a1*2 + 1).getClass().getName() != "int" --> break int(a1*2+1).getClass().getName()
        //  좀 더 편하게 작성할 수 있는 방법이 있을까?
            //  방법1. if.it을 사용한다. --> 안됨. if.it은 bool이 나오게 된다.
            //  방법2. basic의 with처럼 대상으로 묶어주는 명령어는? --> 이럴 바에야 걍 변수 만들고 말지.
            with int(a1*2 + 1).getClass().getName()
                string a2 = it != "int" --> break it
            //  조건1. 변수할당없이 즉흥적으로 값을 지정할 수 있어야 하고
            //  조건2. 그 즉흥적인 값들 가운데 한개를 정확하게 지정할 수 있어야 하며
            //  조건3. 가급적 로직이 추가되더라도 의미가 변경/변형 되어어서는 안된다.
        
            //  방법3. if와 -->로 대체가 가능한가?
            string case = (a1*2+1).getClass().Name()
            if case == "int" --> Console.out(name)
            elif case == getClass().getName() --> Console.out("ok")
            else
                return error

            //  [유력] 방법4. case는 문법이 아니라 switch 문 안에 넣어둔 값을 가리키는 변수다.
            //      요런식으로 사용이 가능함.
            switch((a1*2+1).getClass().getName())
                case == "int" --> Console.out(name)
                case == getClass().getName() --> Console.out("ok")
                case.to(int) == int --> Console.out("wow")
                else
                    error

                //  Q. 이게 elif로 쓰는 거 대비 얼마나 효과가 있나?
                //  A.  물론 좀 더 타이핑이 줄고, indent가 들어가기 때문에 여기에 속해있다, 묶여있다는 느낌도 줄 수 있지만
                //      가장 중요한 것은 switch를 쓴다는 것은 이후에 특정 값에 대한 branch가 쭉 이어진다는 힌트를 줄 수 있다는 점이 
                //      가장 큰 효과라고 생각한다.



        /***** 함수 호출자 선택 ***/
        //  레퍼런스의 경우 모든 함수가 레퍼런스 자체를 기준으로 호출되지 않는다. 그 반대도 아니다. 기준을 설명한다.
        //      레퍼런스 자체가 호출자가 되는 경우 : 할당연산자, 생성자, ==()


        
        /****** null object ******/
        cls.getAge() // x
        Class1 cls3 = cls // ok. null.
        int age = cls3.getAge() // error?
        Binder b1 = cls3.getBinder() // error?
        string b1_name = cls3.getBinder().getString() // error?
        Class1 b1_class = cls3.getBinder().getClass() // error?
        string b1_class_name = cls3.getBinder().getClass().getName() // error?
        //      전통적으로 C/C++/Java는 위의 모든 케이스에서 에러를 내뱉는다.
        //      그래서 우리는 수많은 null 체크를 사용하게 되는 것이다. 더불어 그때의 에러출력도 함께.
        //      이는 분명히 많은 양의 복붙 코드를 늘리는 셈이다. 
        //      개선점을 찾아보자.
        //          1. 결국 이상황에서 개발자가 하려는 건 무엇인가?
        //              예외가 발생했다. --> 에러를 뿌려준다. --> 작업을 취소하거나 대체작업을 수행한다. --> 에러를 반환한다

        //      방법1.
        //          규칙1. null obj에 다음의 함수들 +, +=, =, -=, -, >, <, <=, >=, 생성자, 소멸자, to()를 호출하지 않는다면 에러로 간주 하지 않는다.
        //          규칙2. null obj에 위의 지정한 함수를 호출하는 경우에는 nullexception이 발생한다.
        //          규칙3. 규칙1의 응용. null obj 안의 다른 식별자에 접근하는 경우도 null 만 반환된다.
        //          규칙2-보충. to() 할 수 없으므로 null은 다른 객체로 캐스팅될 수 없다.
        //
        //          시나리오.
        string b1_class_name = cls3.getBinder().getClass().getName() // getBinder()가 null이 나올경우, null.getClass()는 null, null.getName()은 null이 나온다.
        result r = cls3.getBinder().getClass().setName(b1_class_name) // getBinder()가 null, null.getClass()는 null, null.setName()은 null.
            //  setName() 안에서 null this나 this의 변수를 가지고 할당연산자나 값을 변경하는 경우에는 에러가 발생한다.            
            result setName(string new)
                my._text = new // my._text 는 에러가 발생하지 않는다. null 이 반환된다. 그러나 null = new 는 에러가 된다.
                //  주의
                MyClass myc = null // myc는 레퍼런스. null은 오브젝트다.
                myc = MyClass() // 레퍼런스인 myc에 새로운 오브젝트를 지정한다. 문제없다.
                null = MyClass() // 오브젝트인 null을 새로운 오브젝트로 할당연산을 한다. 이것은 null의 =() 연산을 호출하며, 결과적으로 에러가 발생한다.

                //  예를들어
                MyClass myc1 = MyClass(1)
                myc = myc1 // 을 했다고해서 myc가 가리키고 있던 오브젝트의 값이 1로 되는 것이 아니다. 단순히 myc이 재지정되었을 뿐이다.
                //그러나 
                MyClass(1) = myc1 // 을 한다면 1로 초기화된 임시객체는 myc1이 가리키는 값으로 할당연산된다. null이란 이름이 붙어있는 유니크한 오브젝트다.

    void foo(Class1 cls)
        cls.print()
        Class1 cls2 = cls1 // copy
        cls2.age = 6
        if cls2.age == cls.age
            Console.out("Never happen this.")
        cls2 -> cls1 // share
        if cls2.age == cls.age
            Console.out("ok")

        Class1 cls3 -> cls1 // share.