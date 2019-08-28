# Worldlang Specification Noted

## 수정내역

| #    | 버전 | 내용                                                  | 날짜        |
| ---- | ---- | ----------------------------------------------------- | ----------- |
| 1    | 0.1  | 초안                                                  | 21 Jun 2019 |
| 2    | 0.2  | 문법 경량화<br />구현내용까지 포함한 단일 문서로 작성 | 21 Aug 2019 |
|      |      |                                                       |             |

## 개요
* World 프로그래밍 언어의 철학, 개념, 문법과 알고리즘을 모두 서술한다.
* 개발 과정에 있었던 고민과 메모, 지금과 같은 결론에 이르기까지 있었던 제안들과 그것들이 왜 실패했는지도 모조리 기록한다.



## 순서




## 목적

### 게임을 하듯, 취미로 하는 프로그래밍

### 디버깅에 시간을 줄이자

### 간결한 문법, 보다 적은 키워드


## 철학
###  빠른 개발은 빠른 디버깅이다.






## 특징
### 프로토타이핑 기반

### 간결한 문법

### 정적 타입

### C-REPL









## 문법과 알고리즘

### Hello World



### 변수

상수/변수의 의미 / 캐스팅



### 

### 연산자

우선순위





#### 캐스팅

##### Casting의 기본

- Casting은 3가지를 요구사항이 있다.

  - \1. 월드의 형변환은 1가지 문법으로 100% 대체가 가능한데, to() 함수다. to 함수는 다음과 같은 순서로 우선순위를 갖는다.
    - \1. 사용자가 정의한 캐스팅코드
    - \2. 거기에 없으면 클래스 계층상 구체클래스타입을 원하는 경우(= RTTI)
    - \3. 거기에 없으면 주체자(= This)의 생성자를 통한 호환
    - \4. 거기에도 없으면 실패. 끝.
  - 1번을 제외한 2-3번은 모두 WorldFrx 안에 탑재되어있어야 한다.
  - \2. 월드Frx의 실체는 Native에 있기에 형변환을 실질적으로 수행하는 코드는 Native여야 한다. 따라서 Node를 binding하는 Refer가 반환형이기 때문에, Node에 정의된 virtual Refer to(Class&) 함수가 실질적인 형변환을 수행한다. 
  - \3. Native환경에서는 타입이 구체적으로 나와야 편하기 때문에 TRefer<T> to<T>()를 제공한다.

- 추가적으로 지역변수에다가 to를 사용한 경우에는 #로컬바인딩 을 가능하게 함으로써 해결되었다.

- 고찰내용

  - 요구사항

    - **1. 월드에서는 형변환을 지원하는 1가지의 유일하진 않지만 강력한 방법을 통해 다른 사람이 이것만 사용하도록 하고 싶다.**
      - c++에서는 형변환은 여러 방법이 있다.
        - Integer.parseString()
        - (T)
        - atoi(int)
        - stringbuffer << int
        - String(int)
      - World에서는 한가지 문법으로 사용자가 사용하도록 했으면 좋겠다.
    - \2. 또한 월드Frx의 실체는 Native에 있기 때문에 형변환을 위한 함수가 있다면 모두 Native에서 먼저 사용가능한 상태가 되어야 한다. 이는 반환형을 깊이 생각해야 할 것이다.
    - \3. Managed와 달리 Native는 타입이 구체적이어야 사용이 편하다. 형변환 결과가 구체타입으로 바로 나올 수있는 방법을 마련해야 한다.

  - x 1안 형변환은 대상자의 생성자와 자신의 생성자 중에서 호환되는 걸 선택하는 것이다. extend로 이를 해결한다.

    extend는 위험하다. private를 사용해야 하는 경우도 있으므로 friend를 필요로 한다. 

    - int 와 string 관계에서 int->string은 string(int)가, string->int는 int(string)이 대신할 수 있지 않겠냐는 것이다.
      - 그러나 int가 먼저 생긴 클래스이므로 int(string)은 extend로 들어가야 한다. 이는 상대방의 private를 다 알고있어야만 하므로 extend는 피하고 싶다.

  - v 2안 형변환은 대상자의 **생성자**와 **to()** 중에서 호환되는 걸 선택하는 것이다.

    - int->string은 string(int)가, string->int는 [string.to](http://string.to/)(int)가 대신하도록 한다면?
      - 생성자는 visible하게 할 수있을 것으로 보인다
      - to함수가 native에 노출되어야 한다. 따라서 (T)보다는 to자체를 managed에서도 사용하게 한는게 좋을 것이다.
      - 먼저 to()를 시도하고 나서, 안되면 대상자 생성자로 처리하는 편이 좋을 것이다. 대상자 생성자를 바인딩하는 알고리즘은 주어진 타입cls에 대한 근접치 정도(== getProximity)로 판단해야 할 것이다.
      - 문제
        - \#로컬바인딩 문제를 해결해야만 한다. --> 해결함.
        - 반환형을 뭐로 할것인가?
          - Refer로 해야 한다. 그래야 Object가 나올수는 없다. *this가 나올수도 있어야 하기 때문이다.
          - Refer는 Class를 들고 있는다. 
          - 구체클래스 타입으로 to를 한 경우에는 반환할 Refer에서 Class만 구체클래스의 것으로만 바꿔줘서 넘겨주면 된다.
          - Native의 편의를 위해서는 TRefer를 사용하면 된다.



##### to함수의 signature.

- to함수는 World에 visible해야 하므로 반환형은 Bind가 될 수없다. Refer다. Refer는 Strong을 기본으로 하고 있다. 
- Strong로 나간걸 Weak로 받을 수 있다. 따라서 to함수로 Strong인채로 나가야만 한다. (weak로만 나가면 to함수 안에서 새로 객체를 생성해서 내보낼 수가 없게 된다는 얘기다. 선택권은 호출자(caller)에게 줘야하므로 Strong으로만 내보내야 한다)



##### C 타입 캐스팅을 어떻게 지원할까?

- C++ native 타입들 (주로, ptr이 선언된)들에 대한 casting은 어떻게 되야 할까?  이게 필요한 이유는 mashalling을 지원하기 위해서다.
- NativeWrapperMetaClass를 만든다. 그 안에서는 ctor을 하나 만들어서 자동으로 넣어둔다. 그리고 이걸 가지고 casting (WorldObject -> C++NativeType)으로 가면 된다.
- 예) 
  - (this->*_fptr)(msg[0].to<TClass<my_char_struct*>(), msg[1].to<Type2>());



##### 명시적캐스팅

- 요약 : 명시적 캐스팅 = #묵시적캐스팅(=다운캐스팅 + pretype캐스팅) + 사용자 커스텀 캐스팅
- to()로 호출한다.  반환값은 Refer이며, to<T>()도 지원한다. 
- to<const T>()를 적으면 Refer<const T>가 반환되며, 그것의 isConst()는 true가 된다.
- 임의의 클래스 A. const A& a = ...; 일때 [a.to](http://a.to/)(참고 -> #명시적캐스트에서_다운캐스팅으로_반환된경우만_isConst함수가_영향력을_발휘한다. 







##### Worldlang-개발자가-to에다가-캐스팅을-추가하려면 어떻게 해야 할까?

- 고찰을 통해 알아낸 방법

  - 이와 비슷한 케이스들이 많이 있을 수 있다는 걸 알아냈다.
    - class A
      - A operator+(C c)
      - A operator+(B b)
    - class B : A
      - B operator+(C c)
      - B oeprator+(D d)
    - A& a = new B()
    - B b;
    - a + b // c++은 에러. 메소드 hided.
  - 비슷해 보이지만 좀 다른게, +는 모든 타입마다 지원하는 게 아니다. 그러므로 c++처럼 +를 사용하고 싶다면 구체타입으로 캐스팅 하라! 라고 가이드를 주면 된다.
  - 하지만 캐스팅 함수는 아니다.

- 고찰을 통한 요구사항 도출

  - \1. 사용자 관점에서 편해야 한다. managed와 native 모두 동일한 경험을 제공해야 한다.
    - 배열은 잊어버려라. Native 이든 Managed 배열을 만들게 해서는 안되며, Native 한쪽만 배열을 만들도록 해서도 안된다.
  - \2. 먼저 Native 관점에서 생각해야 한다.
    - 1번에 나온 것으로, 경험이 동일해야 하기 때문에 더 제약이 많은 Native 관점에서 먼저 생각해야한다.
  - \3. 멀티메소드는 사용할 수 없다. 다운캐스팅도 안된다.
    - 모두 컴파일에러를 잡을 수 없기 때문이다.
  - \4. 가능하다면 사용자는 일반 함수를 작성하는 것처럼 만들면 알아서 캐스팅 함수에서 redirection되도록 해야한다.
  - \5. 최적화가 가능해야 한다. 속도가 빨라야 한다.

- x 1안 worldlang은 to를 오버라이드하도록 한다
  사용자의 경험상, 올바르지 않다. if-else가 반복되게된다. 

- x 2안 멀티메소드를 지원한다.

  폐기 

  - 멀티메소드란 추상타입에 담긴 구체타입으로 자동 다운캐스팅을 지원하여, 그쪽으로 디스패치되도록 하는 것이다.
    - 예) class A
      - void #print(Node n)
        - Console.out(n)
      - void #print(String n)
        - Console.out("msg = " + n)
    - node msg = string("hello world")
    - A.print(msg) // "msg = hello world"
  - C++은 디자인 불가능의 이유로, 멀티메소드를 거절했다.
    - Straight from the horse's mouth:
      - "I rejected multi-methods with regret, because I liked the idea, but couldn't find an acceptable form under which to accept it."
    - Bjarne Stroustrup, The Design and Evolution of C++ (p297)
    - And later:
      - "Multi-methods is one of the interesting what-ifs of C++. Could I have designed and implemented them well enough at the time? [...] What other work might have been left undone to provide the time to design and implement multi-methods?"
    - (p298f)
    - In general, whenever you feel the urge to know why some particular C++ feature was implemented, or was not implemented, or was implemented the way it is now, and if that feature pre-dates the standardization, you want to read D&E.
  - 멀티메소드가 만약 된다면, 
    - \1. native개발자는 to를 오버로딩해서 사용한다. worldlang 개발자도 to를 오버라이딩한다. (반환형 Refer가 노출된다는 문제가 있는데, 이건 일단 패스)
    - \2. WorldFrx는 오버로딩된 to함수들을 클래스에 담아둘것이다. 
    - \3. worldlang 개발자가 to()를 호출하면 멀티메소드에 의해서 저 to함수중 하나로 자동으로 매치된다. 
    - \4. native개발자가 기존 to함수인 to(Class&)를 호출하면 3번으로 redirection 되게 한다.
    - 즉, 캐스팅에 대해서 따로 클래스를 만들 필요도, 배열로 관리할 필요도 없으며, 멀티메소드라는 좋은 아이디어도 함께 얻게 된다.
  - v 고찰로 알아낸 팩트
    - v 멀티메소드는 단점이 매우 많다
      - v 인자가 가지게될 가능성이 커지므로 당연히 모호성 오류가 증가한다.
      - v 동적에 타입의 결정되기 때문에 vtable을 적용할 수 없고 따라서 최적화가 불가능하다.
      - v 캐스팅 문제는 멀티메소드와 관련이 없다. 오히려 주어진 타입A가 hiding하고 있을 메소드까지 어떻게 dispatch하냐는 문제다. 

- v 다른 언어는 사용자의 캐스팅을 어떻게 끼워넣을까?

  - 동적바인딩언어는 제끼자.
  - C#
    - class A {
      - static A explicit A(int a) {
        - A ret = new A();
        - a.setValue(a);
        - return ret;
      - }
    - }
  - *x 커피스크립트*
  - *boo (C#과 비슷) C# 계열이니까..*
  - *자바 (캐스팅 자체가 없다)*

- *[x] 1안 사용자가 캐스팅을 추가하는 방법*

  - 객체에 대한 배열을 사용한다. 직접 to를 오버라이드 하지 않게 한다. 사용자는 자신이 지원할 타입1에 대해서 캐스팅 클래스를 정의해야만 한다.
  - to를 직접 override하는 것 대비, 
    - 장점
      - isTo() 함수를 작성할 수 있으며 기존대비 빠르다.
      - override시 사용자가 해야할 명시적캐스팅을 대신해줄 것이다.
      - to함수가 override되지 않고 하나의 함수안에서 for-loop으로 모든것이 될것이다.
      - else-if 구조 타파
    - 단점
      - 클래스를 매번 만들어야 한다. 귀찮다.
        - 람다로 대체는 불가능하다. 월드는 이 람다가 무슨 타입을 인자로 받는지까지는 알 수가 없기 때문이다.
  - 캐스팅 가능한 목록은 모든 객체가 공유해야 하므로 이것은 당연히 클래스가 소유하고 있어야 한다. 클래스가 초기화될때 사용자가 집어넣은 캐스팅 가능 배열을 메타클래스가 가져와야 한다.

- *[x] 2안 to를 오버라이드*

  - C++의 operator type()캐스팅은 모호성의 오류를 너무 많이 야기한다. 
  - 그렇다고 사용을 안할 수는 없다. World는 managed <-> native의 간극을 wrapping으로 메꾸고 있고 wrapping의 핵심은 캐스팅이기 때문에 native환경에서 managed 데이터를 가져오기 위해서는 캐스팅이 필수이다.
  - 따라서 World는 custom타입에 대한 이를 지원은 하지만, 되도록이면 사용하지 않는 방향으로 간다.
  - 캐스팅은 to() 함수이다. 2종류가 있다.
    - virtual Reference<Node> Node::to(const Class&) const
      - 핵심함수다. Node는 Object 될 수있고 c++만의 타입일 경우에는 Classizer<HWND> 식으로 넣으면 된다.
    - 월드코드에 캐스팅 코드를 추가하고 싶다면 역시 to를 override하면 된다.
      - class MyModule (from Object가 생략되어 있다)
        - Node to(Class type)
          - [super.to](http://super.to/)(type) // 이렇게 해야 Object::to()가 실행된다)
          - if (type == Int)
            - return Int(getAge())
    - native에서 to를 override할 수도 있다.
      - class MyModule : public Object {
        - virtual Reference to(const Class& rhs) const {
          - if(rhs.isSubOf<HWND>())
          - //== if(rhs.isSubOf<Classizier<HWND>>())
          - //== if(rhs.isSubOf(Classizier<HWND>()))









##### 묵시적형변환, 묵시적바인딩, 명시적형변환문법, 연산자 오버로딩에 관한 총체적인 컨셉

- 명시적 형변환은 to(타입) 으로 해결한다. native, managed 모두 to(Class&)을 define함으로써 형변환 지원을 추가 할 수있다. 그러나 되도록이면 권장하지는 않는데 모호성 오류를 야기시키기 때문이다.
- 참고 -> #명시적캐스팅
- 연산자 오버로딩에서 기존타입 + 커스텀타입의 형태를 지원하는 것은 까다로운 문제며, World는 클래스 확장기능으로 이를 해결한다. extend 키워드를 써야한다. 
  - extend 키워드를 사용하는 이유는 World에게 "원본이 이거다. 원본을 먼저 파싱해서 읽어라"라는 힌트를 주기 위해서이다.
  - 원본이 바이너리로 최적화된 상태라면 함수의 순서에 크게 영향을 받는다. 클래스의 메소드가 확장되었을때 기존 메소드가 정상적으로 호출되기 위해서는 확장된 메소드가 뒤에 붙어야 한다.
- extend시 이미 기존 메소드가 존재하는 경우에는 에러가 발생한다.
- extend된 함수에서도 private 멤버를 접근할 수 있다. 이것은 C++의 "원천금지는 하지 않는다. 오직 실수하지 않게끔 한다"는 철학이 옳다고 판단했기 때문이다. 
- 묵시적 바인딩에서 묵시적 형변환이 일어난다. (다른곳에서도 묵시적 형변환은 일어난다) 묵시적바인딩시 to함수(이건 명시적 캐스팅이다)가 아니라 묵시적캐스팅함수(미정이나, 아마도 toImplicit가 될것이다)에 의해서 캐스팅이 가능한가 아닌가로 판단하게 된다. 
  - --> 이것은 to함수가 어떤 캐스팅을 지원하는가를 World가 알고 있어야 한다.
    World가 임의의타입 T가 어떠한 캐스팅을 지원하는지 알려면? 참고 
- 고찰내용
  - 팩트1. 타입 A가 B로 캐스팅이 가능한가의 여부는 각 클래스의 개발자가 define해놓아야 한다.
  - 팩트2. 역(reversed)함수가 필요로 해지는 것들이 1개 이상 존재한다.
    - [A.to](http://a.to/)(B)와 더불어 [B.to](http://b.to/)(A)도 있어야 하며, A.operator+(B)와 B.operator+(A)도 마찬가지다. 
  - 팩트3. 그러나 타입A가 외부에서 가져온 모듈일 경우 타입A는 타입B를 알지못한다. 이 경우 해결할 방법은 
    - 1안 타입B에 타입A를 받을 수있는 역함수, B.operator+(A)와 B.operator_reversed(A)를 만드는 방법 - python방식.
      - 단점1. reversed된 함수를 사용자가 추가로 알고 있어야 하며
      - 단점2. World는 A.operator+()를 먼저 try하고 없으면 B.reversed_operator+(A)를 try하는 형태로 가야하기 때문에 약간의 퍼포먼스 loss가 있다.
    - v 2안 타입A의 operator+, to() 함수를 타입B와 함께 define해서 타입A 코드에 inject 하는 방법 - 비슷한게 C#에 있긴 하다.
    - 3안 아예 그냥 캐스팅, operator+지원하지 않는 방법 - java 방식
      - 단점1. 일부 상황에서 불편한게 사실이다.
    - 4안 클래스에 속하지 않는 일반 함수를 define해서 friend로 해결하는 방법 - c++방식
      - 단점1. 순수 객체지향언어에서는 클래스에 속하지 않는 일반함수라는게 없다.
  - 4가지 있다. World는 2안을 따라간다. extend 키워드를 추가함으로써 해결한다.
  - extend from 기능 (이름은 수정할 필요 있다)
    - 이미 존재하는 클래스A에 메소드, 멤버변수를 추가하는, 클래스의 내용물을 add 하는 기능이다.
    - import kukullza.print
    - class COut extend from kukullza.print



##### 중요!!! --> 헷갈리기  쉬운 묵시적형변환과 연산자 우선순위 주체 <-- !!!중요

- 연산자 우선순위는 파서제네레이터에 의해서 결정된다.
- 묵시적형변환은 코드블럭이 생성되는 시점에서 몇번째 동적디스패칭을 해야 하는지 결정하면서 같이 정해진다.
- 동적디스패치는 호출해야할 함수의 프로토타입은 알고있는 상태에서 누구의 함수를 호출해야하는지가 정해진다.
- 시나리오 검증
  - class A
    - int foo(int)
    - float foo(float)
    - int foo(string)
  - class B
    - int foo(int) // 만약 foo(int)는 동일하나, 뒤에 반환형이 int가 아니라면 컴파일 에러가 난다.
  - foo(3) + foo(3) * (foo(2.5) - hoo("gogo")) / foo(2)
  - 가 있을때...
  - 파서제네레이터가 일한다. 연산자 우선순위를 바탕으로 해서 foo(2.5) - hoo("gogo") 가 먼저 파싱되고, foo(2.5)를 통해 미완성 코드블럭을 계속해서 생성한다. 정의된 함수자체는 올바르게 등록되어 들어간다. 미완성인 것은 오직 statement인 코드블럭뿐이다.
  - 다음은 syntaxer가 일한다. syntaxer는 생성된 코드블럭들을 linking + validation을 수행한다. foo("gogo")를 보고, 





##### 타입변환

- dynamic_class를 더 좋은 퍼포먼스와 활용성을 커스터마이즈 하는 것이 목표다.
- 클래스A -> 클래스B되기 위해서는 클래스A 안에 인자로 클래스가 들어오면 이걸 어떠한 형태로 내보내겠다는 코드를 적어놓는다.
- 클래스B는 클래스A의 계층 중 하나가 될 수 도 있고, 전혀다른 클래스가 될 수도 있어야 한다. 
- x to() 결과 캐스팅이 된 StrongBind가 임시변수로 넘겨지며 caller는 이를 Weak 혹은 StrongBind로 선택할 수 있다.
  - x 왜 그런가? 왜 weak로 내보내야하지?
  - x 만약 weak로도 내보내야 한다면, Refer는 weak와 Strong 양쪽 다 안되나?
- 설계
  - class Instance {
    - Bind<T> to() const {
      - return Bind<T>(_onTo(TClass<T>()));
    - }
    - virtual Bind<Instance> _onTo(const Class& klass) {
      - return Bind<Instance>();
    - }
  - };
- 고찰 내용
  - 하나의 타입이 다른 타입으로 변환하려면 변화시키려는 주체가 지원해줘야 한다.
    - 예) Integer가 Float이 되려면 [Integer.to](http://integer.to/)<Float>()을 해야하고 Integer._onTo(Class&) 안에서 Float일때 어떻게 Float()을 생성해서 내보내는지 코드로 되어있어야 한다.
  - to로 변환할 수 있는 것은 Object를 상속 클래스에 한 한다.
  - to의 결과가 참조자가 되는 경우도 있는 반면, 새로운 객체가 나오는 경우도 있어야 한다.
    - View& someview = component[0].cast<View>()->getValue();
    - Integer age = component[0].cast<Integer>()->getValue();
    - TBind는 getValue() 할때 T&가 나온다. TBind<View>(*this)
  - 설계해보라
    - class Object {
      - template <typename T>
      - TBind<T> to() const {
        - TBind<Object> obj = _onTo(TClass<T>());
        - if obj // == isBinded()
          - return TBind<T>(obj);
        - return TBind<T>();
      - }
      - virtual TBind<Object> _onTo(const Class& klass) { return TBind<Object>(); }
    - };
  - to<T>() 는 필요할 지 모른다. to(Class&)는 필요하는가?
    - 필요 없다.
    - 다만 _onTo(Class&) 이런건 필요하겠다.
  - 문제점
    -  참조자로 나올 수도 있고 값으로 나올 수도 있다고 했다. 그런데 그 둘의 타입이 같아야 하므로 결국은 TBind<>로 나오게된다. 이것은 참조자로 나올때 참조카운트가 1개 증가되는 문제를 낳는다.
    - 참조자로 나올 때는 TWeak<>로, 값으로 나올때는 TBind<>로 나오되, 타입은 같게 만들되, 사용자가 사용할때는 확실하게 각각 동작되도록 하는 방법은?
      - 1안
        - TWeak가 범용적이므로 to()반환형은 TWeak다. 
        - 남은 문제는 Float을 내보내는 경우는 밖에서 참조카운트 관리를 해줘야 한다는 점이다.
        - 반환형이 참조자라면 원본을 유지한채로 밖으로 꺼낼 수 있다. 
        - 반환형이 TWeak&가 된다는 것이지.
      - [v] 2안
        - TBind<int> foo();
        - TWeakBind<int> ret = foo(); 
          - foo의 반환형은 TBinder. 하지만 임시변수이기 때문에 이 한줄이 사라지면 소멸된다. 즉 사용하는 쪽에서 임시변수를 TBind로 받을 것인지, TWeak로 받을 것인지를 선택할 수 있다. 
          - foo()안에서 기존 인스턴스를 캐스팅만 달리해서 넘긴 경우라면, Weak로 받아도 아무런 문제없다.
          - 게다가 표준에 의하면 값으로 넘긴걸(rvalue) 레퍼런스로 받을 수 없다. (MSVC는 허용함. 그러므로 얘는 쓰지 말자) 그러므로 홀이 아니다.
      - [x] 3안
        - 전혀다른 인스턴스로 변환되는 건 없도록 한다.
        - Integer -> Float은 그럼 어떻게 할것인가.





##### 명시적캐스트에서_다운캐스팅으로_반환된경우만_isConst함수가_영향력을_발휘한다.

- 참고 -> #명시적캐스팅





##### 묵시적캐스팅 

- 배경
  - 함수 디덕션 과정 (참고로 함수디덕션은 단순히 함수호출을 의미하는게 아니다. World는 모든 것이 msg의 송수신, 즉, 함수로 보기 때문에 생성자 생성과 연산자, if 같은 keyword까지 포함한 모든 것을 의미한다)에서 주어진 인자로 이 함수를 호출 할 수 있는 지를 판단하기 위해 타입의 교량역할을 하는 것이다.
  - 사용자가 함수 호출 인자로 명시적으로 캐스팅 하지 않아도 자동으로 되는 것을 말한다.
  - 함수 디덕션에서는 묵시적캐스팅을 적용한 결과, 호출이 가능할 것인지, 가능하다면 얼마나 우선순위가 되는지를 종합적으로 판단해서 가장 적합한 best fit을 찾아서 그걸로 링킹을 시도하게 된다.
- 묵시적캐스팅의 내용
  - \1. pretype들간의 명시적 캐스팅
    pretype 들 간 이다. 한쪽이 pretype인 경우는 해당하지 않는다. 
  - \2. 업캐스팅
  - [미정] 3. 다운캐스팅
    지원하게 되면 멀티메소드를 지원하게 되는 것이다. 
- 왜 pretype들간의 명시적 캐스팅만 지원하는가? 다른 타입은?
  - pretype들은 프로그램 내에서 가장 빈번하게 사용될 타입이다. 따라서 이들을 가지고 함수를 호출하는 경우도 많다. 매번 이러한 경우마다 사용자보고 명시적으로 함수캐스팅을 하라고 하는 것은 사용성이 너무 떨어진다.
  - C++의 경험을 보았을때 커스텀타입들에 대해 업캐스팅 정도만 묵시적으로 동작해도 사용에 크게 무리는 없었다.
  - 명시적 캐스팅을 모두 묵시적으로 동작하게 해버리면, 모호성의 오류가 너무 많아진다.
- 묵시적캐스팅을 위한 API가 필요한가?
  - 묵시적 캐스팅을 사용하게 될 알려진 장소는 현재 컴파일러(함수 디덕션을 하는 곳), Bidge component 2곳이다. 
  - 설계의 관점에서 책임을 놓고 보면 캐스팅을 전담하는 것은 타입이므로 타입에서 API로 캐스팅을 두는 것이 많다. 
  - 단, 이러면 API가 늘어나는 것이며 이 API를 사용자가 오버라이딩해서 함수 디덕션에 자신의 타입을 묵시적캐스팅되도록 추가할 수 있게 된다.
- Thing에 그대로 묵시적 캐스팅을 두기로 했다. (invisible)



##### 기본 타입간의 #묵시적-캐스팅-정책

- 요구사항
  - \#worldlang-개발자가-to에다가-캐스팅을-추가하려면 에 따르면, 명시적 캐스팅은 생성자에 의해서 자동으로 추가된다.
  - 묵시적 캐스팅은 pretype 들에 대해서만 world가 미리 정의한 캐스팅이다. 즉, 사용자가 추가한 명시적 캐스팅들은 함수 디덕션에 반영되지 않는다.
  - \1. 이 우선순위가 어떻게 정해질 것인가
  - \2. 이 우선순위를 정하는 코드를 어떻게 어느 클래스가 소요하도록 할것인가가 중요해진다.







##### 최소화된 묵시적 형변환

- 애매모호한것보다 번거로운게 낫고, 버거로운것보단 심플한게 낫다.
- built-in 타입들에 대해서 최소한의 묵시적형변환을 지원해준다. 그 이외에는 직접 개발자가 캐스팅을 코드에 명시해야 한다.
- 사용자가 작성한 타입을 부득이 다른 타입으로 변환한다는 것은 World가 적절한 타입으로 변경해준다는 걸 의미한다. 여기서 "적절함" 이란 일종의 AI를 의미한다. AI를 넣을 수 없다면 그걸 대신 할 수 있는 대중의 합의점에 해당하는 데이터가 필요로 해진다.
- 형변환 테이블에는 비슷한 그룹군이 담겨있다. 우선순위는 존재하지 않는다.
  - 원칙
    - 작은것은 큰것으로 흘러가는 것이 원칙이다. 그러나 사용성을 위하여 몇가지 예외를 둔다. (int -> float, char -> int, int -> string)
    - 예외적으로 숫자 그룹군끼리는 서로 호환된다. 
    - 대부분의 built 타입은 string으로 변환될 수 있다.
  - int --> float, char, bool
  - float --> int, bool
  - char --> float, int, bool
  - bool --> int, string
  - result --> string, bool





##### 함수와 참조자와 캐스팅 문제

- 시나리오
  - class A
    - void print(string a)
      - a += "msg = "
      - Console.out(a)
  - A a
  - string msg = "hello world"
  - a.print(msg) // msg = "msg = hello world"
  - a.print(35)
  - 문제는, 사용자는 void print(string)의 parameter a가 내부에서 set 되는 함수이니까 정확하게 string 타입으로 인자를 주지 않으면 제대로 값이 할당되지 않겠다..... 라는 걸 알기가 힘들다는 것이다. c++의 경우라면 a&나 *a로 적혀있을테니 쉽게 예상해볼 수 있다. 어떻게 할까?
- 구버전
  - Int를 받는 모듈이 있을때, int가 아닌 타입을 인자로 넣었다면 "컴파일에러가 나올수도 있고 나오지 않을 수도 있다". 이는 최소화된 묵시적 형변환 룰에 의해서 예외적으로 인정받는 경우를 제외하고는 명시적으로 사용자가 어떠한 타입으로 변환하겠다는 것을 명시하는 것을 권장한다.
  - 고찰내용
    - World dust 버전에서 가장 큰 문제였다. 상황을 설명해보지.
    - class MyModule : public Module
      - NETArgument<NEIntKey> age;
      - virtual type_result _onExecute() {
        - int& aage = age.getValue();
        - aage += 3
      - }
    - 보다시피 단순한 예제다. 하지만 만약 MyModule에게 넘겨졌던 인자가 String일때는 어떻게 되는가?
    - read를 위해서 string -> int로 하는 건 매우 단순하다.
    - 하지만 write는?
      - World는 모든 것이 메시지 위주로 돌아간다. 사용자가 작성한 코드도 결국은 메시지로 번역된다.
      - 따라서 aage += 3을 World 문법으로 작성하면 이는 결국은 
        - aage.call("set", aage.call("add", aage, int(3));
      - 같이 번역되기 때문에 문제는 없을 것이다.



### 블록문

#### 블록문 기본

- 블록문이라는 클래스를 만든다. 람다, 클로져, 함수는 블록문의 일종이 될 수 있다.
- 블록문은 execute()를 받으면 Scope의 index를 기억하고 가지고 있는 Statement들을 execute한다.
  - Statement들은 지역변수를 Stack인 LocalSpace에 push하게 된다.
- execute(Statements)가 끝나면 블록문은 기억했던 index까지 LocalSpace[n]을 release()하고 LocalSpace._setIndex(index)를 한다.
- 고찰내용 
  - 블록문이 끝나면 블록문 안에 정의된 지역변수들은 LocalSpace[n].release()로 사라져야 한다.
  - 1안 LocalSpace는 placeBorder() reclaimBorder() 2가지 함수가 있다. reclaimBorder를 하면 가장 최근에 placeBorder()를 한 시점까지pop이 된다
  - v 2안 블록문이라는 클래스를 만든다. 
    - 함수는 블록문의 일종이라고 하면 설명이 된다. 게다가 블록문 자체를 객체로 보내거나, 클로저나, 람다같은 거 구현할때도 지역변수 관리는 자동으로 되게 만들 수 있다.
    - 블록문은 시작 시점에서 Scope의 index를 기억하고, 끝나는 시점에 여기까지 release()를 호출하고 _setLength(index)를 해버린다. 
      - 매번 pop을 하면 지역변수 인스턴스가 해제되지 않으며 속도 문제도 있다.
    - 이 사실에서, Scope는 전역공간이 낮은 인덱스, 지역변수가 높은 인덱스를 가지게 되는 Stack임을 알 수 있다.
      - 증명 : 왜냐하면 먼저 생긴 지역변수가 나중에 생긴 지역변수보다 먼저 죽는 경우는 생기지 않는다. 

####  블록문과 static 

- 블록문 안의 static 변수들은 블록문의 것이다. LocalSpace에 index를 기억하고 나서 자신이 소유한 static 변수들을 추가한다.
- 이는 메소드가 실행전에 자신의 인자리스트와 자신의 메소드들을 미리 push해놓는것과 동일하다.





### 흐름 제어














### 메소드
* 정의, 호출, 캐스팅을 사용하고 있는 점

#### Method 는 클래스다.

- Object는 독립적인 ObjectSpace 유지하는 인스턴스적인 개체를 의미한다. 이것은 Class를 하나 모방 하고있으며, 그 클래스로부터 메소드 내역을 pointing하고 객체내역을 cloning 함으로써 고유값을 갖는다.
- Method는 하나의 종말메소드를 가질 수 있는 LocalSpace에서 동작되는 Static Unique 클래스이다. 
  - 값을 가질 수 없으나, 메소드는 가질 수 있다. 
  - **동작시 LocalSpace에서 관리된다. --> #Method는_ThisPtr이_꼭_필요하다_어떻게_얻을_수_있을까 참고**
- Nested Things
  - 클래스가 Nested 된 경우, 이 클래스는 owner클래스에 대한 어떠한 정보도 갖고 있지 않다.
    - FAQ. 자동으로 NestedClass는 OwnerClass의 this를 갖도록 하면 더 편하지 않을까?
      - NestedClass가 OwnerClass와 1:1로 사용되리란 법이 없다. 극단적인 예를들면 OwnerClass는 1000개가 instance가 나왔을때 random확률로 1개의 NestedClass가 나오는 상황도 있을 수 있다. 또는 OwnerClass는 instance 나오지 않았는데 NestedClass만 나오는 상황도 있을 수 있다.
  - 외부에서도 NestedClass의 객체를 만들 수 있다. _ prefix가 안붙어있다면 말이지.
- Exception 핸들링또한 Nested Method를 통해서 돌아간다. 그 함수안에서 발생된 Exception은 그 메소드의 _except() 로 넘겨지게 된다.
- Method는 World의 Class가 될 수 없다. (단, 객체의 일종이긴 한것이다. World의 클래스는 TClass<T>로 생성되어야 한다). 왜냐하면 멤버변수를 가질 수 없고 (멤버변수를 갖기 위해서는 별도의 getVariableMembers변수가 필요하다) 객체를 만들 수 없기 때문이다.
- 그러나 Method와 Class는 같은 계통의 부모클래스인 Node를 갖는다. 왜냐하면 Membre로 Method를 가질 수 있다는 공통점이 있기 때문이다.
- 고찰내용
  - Nested Method에서 확장된 아이디어인데, 이게 생각보다 괜찮다.
  - 먼저 다음의 아이디어에서 출발한다.
    - World에서 보여지는 Method는 사실 Class다. Method는 다만 변수를 가질 수 없으며,  Method를 선언됨과 동시에 자신을 소유한 클래스에게 등록되며, 함수가 호출될때 인자1로 클래스의 thisptr를 가지고 있으며, call(args)라고 하는 실질적으로 명령을 수행할 수 있는 창구가 디폴트로 있다는 점이다.
    - 따라서 설계상, class Method : public Class 가 된다.
    - Method는 클래스이므로 virtual void onIn(), onOut() 이런걸 재 사용하게끔 할 수 있다.
  - Nested Method
    - Method도 클래스이므로 Method에서 메소드를 정의할 수 있다. thisptr는 최초 object가 call을 받은시점에서 삽입되어있으므로 Nested Method 안에서도 thisptr은 그대로 유지 및 참조가 가능하다.
    - 다형성을 사용하면 여러가지 이벤트 핸들링이나 exception처리를 메소드에서 할 수 있다.
    - 중첩메소드는 Owner메소드의 지역변수를 참조할 수 있다. --> Scope알고리즘 참조
    - 중첩메소드에서 다른 중첩메소드를 호출 할 수 있는가? --> 네.
      - 룰을 정한다.
      - class MyClass
        - void foo()
          - int a = 0, c
          - console.out("foo")
          - void _boo()
            - int a = 1, b = 0
            - console.out("boo")
            - void _koo()
              - int a = 2
              - // 여기서 c를 접근할 수 있는가? --> 네.
              - // 접근할 수 있다면 여기서 a의 값은 얼마가 되는가? --> 2. LocalSpace에서 top부터 검색하니까.
              - // 그렇다면 여기서 d에 접근 할 수 있는가? --> 모른다. 이 함수가 언제 수행될지는 돌려봐야 아니까.
              - console.out("koo")
              - void _hoo()
                - console.out("hoo")
          - void _goo()
            - console.out.("goo")
            - // 여기서 boo를 호출 가능한가? --> 가능하다. 함수내의 모든 식별자는 me._goo()처럼 me에서 찾게 된다. (= 실제로 me에게 call을 하는게 아니라 scope에 이미 그렇게 들어있는 것이다) me에 없을 경우, 자연스럽게 this에서도 찾게 되며, 만약 this와 me에 둘다 있는 경우는 me로 인식되게 된다.
            - 이는 함수 내의 블록문이 중첩된 경우, 블록문 밖과 안에 같은 변수명의 변수가 있는 경우 묻지않고 가장 안쪽 블록문의 변수로 인식하는 컨셉과 동일한 것이다.
          - int d = 25
    - 중첩메소드는 public private 제한은 없다. 따라서 다음의 코드도 맞는 코드다.
      - class MyClass
        - int foo()
          - int add(int a)
            - return a + a;
          - int a = add(5)
          - return a
        - int boo()
          - **int another_integer = foo.add(5)** // ok.
          - return a
      - MyClass.foo(void).add(5) --> #nonstatic메소드를_static처럼_사용한_경우는_어떻게_되는가  참고
    - 중첩메소드는 execute()를 가지고 있는 클래스이다. 당연히 execute() 내에 자신의 private 메소드들을 호출 할 수 있다.
    - Exception 문제를 해결가능.
      - class MyClass
        - int transfer(char[] packet)
          - void _init(char[] packet)
            - packet  = new char[255]
            - void _except(MemoryException e)
              - e.printStack()
              - ERR("ERROR!")
              - packet = new char[255] // try again
              - void _except(MemoryException e)
                - ERR("failed again. quit.")
            - packet
    - 중복되는 함수를 작게 빨리 만들고 scope를 제한시킴으로써 가독성 높임, 여기서만 사용하는 세부로직을 명시적으로 나눔
    - 잘생각해보자. Method는 객체처럼 동작한다. Method도 Method를 가지고 있다면, 이것은 마치 진짜 객체가 아닌가? Nested Method와 Nested Class의 차이가 무엇인가?
      - class MyClass



#### Method의 생성과 초기화

- Method는 생성과 동시에 초기화가 일어난다. 그러나 메소드의 생성은 lazy하게 이루어지기 때문에 무한 재귀에 빠지지 않게 된다. (반면 클래스의 초기화는 처음에 일괄적으로 진행된다)
- Method의 멤버구성은 초기화는 자신의 소유자의 getMembers()가 호출되는 순간 이루어진다.
  - 초기화가 이루어지는 일반적인 흐름은 이렇다 > Object::getMembers() > getClass().getMembers() > TClass<...>::getMembers() > T::onInitializeMethod() > return Method<MyC++Method>()     --> TClass<...>::getMembers()가 초기화 된것이다.



#### 어떻게_하면_이_메소드를_호출할_수_있는지_아닌지를_알_수있을까

- 바로 call을 해버리면 곤란하다. 왜냐하면 interpreter는 validation에서 모호성 오류를 검증하기위해 이 msg를 받을 수있는 곳이 1곳인가를 반드시 짚고 넘어가야 하기 때문이다. 따라서 기존의 컨셉인 "일단 call해서 안되면 return error 하라"는 통하지 않는다. 잘못하면 2번 각기 다른 곳에서 동작이 될 수 있다. 
- x 1안 flag를 사용해서 "1번 이미 동작했다로 알린다. --> 1번째는 이미 실행이 되게 된다.
- v 2안 isCallable()을 만들고, casting을 매번 수행한다.
- x 3안 casting없이 알아내는 방법
  - 코드가 복잡해지고, 사용자가 작성하는 로직이 어려울 것이다.



#### Unique성을_구현하는_방법

- \#Method가_만약_Type의_일종이_아니라면  과 관련이 있다.
-  Type과 같이 상속을 통해서 Unique를 표현하는것이 아니라 인스턴스가 누구에게 속해 있느냐로 Unique를 결정한다.
- 시스템에 1개만 존재한다는 것은 다음 2가지 조건을 만족해야한다.
  - \1. scope 밑바닥에 추가되어야 한다. 왜냐하면 scope를 통한 접근이, 이것들을 접근할 수있는 유일한 방법이기 때문이다.
  - \2. 런타임 도중 사용자의 의한 이것들의 복제 및 인스턴스 생성을 막아야한다. 이는 C++과 World 양쪽에서 모두 방어가 되어야 한다.
- Unique성을 갖는 대부분의 것들은 Class와 그 밑에 있는 것들이다. 이것들은 C++ 코드 자체에 생성자가 private로 막혀있으며 오직 몇 friend 클래스에서만 마음대로 추가 및 생성이 가능하게 되어있다. 
- World코드에 의해서 Node의 인스턴스 가 생성되는 과정은 항상 Class객체로부터 Object를 생성해 내는 것이다. 그리고 Class.getClass()를 하면 Class 자체가 나오며, Class는 ADT이기 때문에 instantiate()는 null을 반환한다.
- 주의 - 전역변수는 Unique 성이 아니다. 
  - \1. 이것은 일단 class가 아니며(이를테면 Class, Method 모두 클래스다) 그말은 복수의 객체가 나올 수 있다는 것이다.
  - \2. 같은 타입으로 복제가 될 수있다.
- 고찰내용
  - Unique성이란?
    - 시스템에 1개만 나올 수있다는 것을 시스템에서 보장해주는 것이다.
    - 정확히 말하면 World에 의해서 생성은 가능하지만 사용자는 이걸 생성할 수 없고, 사용은 가능해. 라고 말해주는 것과 같다.
  - 고찰을 통해 얻은 팩트
    - **1. class는 const여야 한다.**
    - **2. overriding때문에, call의 반환값은 확정되야 한다. 즉, 1번에 의해서 class로부터는 const인 call()만 호출가능해진다.**
    - **3. 멤버변수가 static인 것은 sharaable이나 occupiable과는 관계가 없다.**
  - 어떻게 구현하는가?
    - C++적으로 모듈개발자가 Unique속성을 가진 것들을 생성이 불가능하게 할 수 있다면 World개발자는 당연히 못하게 된다. 그러므로 C++적으로 생각한 뒤에, 아귀를 맞춰나가자.
    - 1안 const
      - unique를 갖는 것들은 Class, Function, 클래스안의 멤버변수 들일 것이다.
        - 착각하면 안된다. 전역변수, static변수는 해당되지 않는다. 이들을 Type이 아니니까. 모든 변수는 중복정의가 되지 않는다.
      - Function, 멤버변수는 모두 Class에서 나오는 것으로 결과적으로 우리는 ClassManager에서 반환되는 것들을 const로만 반환하면 된다는 것을 알수 있다.
      - static변수는?
        - Unique성은 Type클래스가 아니라 const로 반환되는 ClassManager를 통해서 구현되어야 한다. 그러나 static은 Class 안에 속해 있으면서 언제든 그 갑이 외부로부터 변경될 수 있어야 만 한다.
        - 생각을 해보자. World개발자가 static변수를 참조하려고 한다면 scope를 통해서 Class에 접근하고, 그 안에 있는 static변수를 접근할것이다.
          - stmt {
            - .thisptr = stmt {
              - .thisptr = scope
              - .name = "getMember"
              - .args = {"MyClass"}
              - }
            - .name = "getMember"
            - .args = {"my_static_variable"}
            - }
          - call()은 2종류가 있다. 
            - const TStrong<Node>& call(...) const;
            - TStrong<Node>& call(.....);
            - 물론 const버전을 쓰면 static 변수를 접근 할 수 없지만, 최초 scope에 접근할때는 nonconst call()를 쓰게 될 것이다. scope는 const가 아니니까. 따라서 이후로 호출되는 모든 것들도 사실은 const가 아니게 된다.
            - 고로 악의적인 목적을 가진 모듈개발자는 런타임에 class의 구성을 마음껏 변경할 수 있게 된다.
      - Method는 정말 const라고 생각하는가? method가 execute되면 Method가 가지고있는 멤버변수를 건드리지 않을까? 이를테면 반환값을 저장하는 멤버변수 같은거.
        - 그렇다고 해서, 클래스는 변경되선 안된다. 그러니 클래스가 const인거는 맞다.
        - 1안 mutable?
    - 2안 class => const. class.members => const reference. objects => nonconst.
      - 클래스는 const로만 제공된다. 클래스의 멤버들도 모두 const다.
      - 그러나 클래스 멤버들이 가리키고 있는 실체(object. 즉, Method, static변수)는 nonconst다.  nonconst를 const reference가 가리키고 있는 상황이지.
      - --> 안된다. 결정적으로 이문제는 sharable과 occupiable과는 관계없다. sharable이 static일 수도, occupiable이 static일 수도 있다.
    - 3안 call안에서 어떤건 const로, 어떤건 nonconst로 반환할 수 있을까?
      - 안된다. overriding을 하려면 타입이 확정되야 하니까.
    - 4안 static 변수는 class가 아니라 Object에 있게 한다면? 그리고 메소드안의 반환값은 mutable.
      - 네. 모든 문제를 해결할 수 있을것이다. static이 좀 낭비지만.
      - c++에서 클래스의 static변수에 접근한다면?
        - 그럼 진짜 static변수에 접근하는 것이다. 이 문제와 관련 없지.
          - 
      - static변수가 여러개가 될때마다 모든 객체들은 여러개를 들고 있어야 한다. 메모리 낭비.
    - v 5안 보안 문제는 나중으로 미루고 일단은 classmanager는 class를 그냥 공개해버린다.
    - \#static변수는_어떻게_구현하는가  로 해결하였다.



#### Method는_ThisPtr이_꼭_필요하다_어떻게_얻을_수_있을까.

- class Message {
  - mutable TStrong<Object> _origin;
- }
- class Object {
  - call(const Message& msg) {
    - bool is_updated = false;
    - if(msg._origin == null) 
      - msg.getOrigin() = *this
      - is_updated = true
    - .... call to members ....
    - if(is_updated)
      - msg.getOrigin() = null
  - }
- }
- Message msg(......)
- Object obj.call(msg) // mutable이니까 인자가 const Message& 라도 괜찮다.
- obj2.call(msg) // 같은 메시지를 다른 객체에 던져도 잘 동작한다.
- Method m = .....
- m.call(msg) // 안에서 msg.origin = null이므로 에러를 탐지할 수 있다.
- Method static = .....
- static.call(msg) // 안에서 msg.origin을 안쓸것이므로 잘 동작할것이다.
- 고찰내용
  - 고찰을 통해 알아낸 팩트
    - **1. Object에서 Method로 전파될때 Method는 엄밀하게 말해서 Object들에서 공유하고 있는 것이므로 thisptr를 알아야할 필요가 있다. 일단 Method가 진짜 모듈개발자가 정의한 c++함수를 호출하고 난 뒤에는 고 안에서는 thisptr가 필요없다. 오직 Object->Method 로 call되는 구간에서만 thisptr가 필요하다.**
    - **2. 해당 메소드가 실행중일때만 메소드에 넘겨진 thisptr가 누구인지 알 수있어야 한다. 고로 thisptr자체는 method가 소유하고 있어서는 안되며 이사실을 외부에 알려서도(접근자메소드로 만들어도)안된다.**
    - \3. 방법은 크게 2종류로, 하나는 call을 하면서 같이 thisptr를 넘기는 방법이며, 2번째는 call이외의 다른 경로(전역객체든, 접근자든)로 thisptr를 따로 전달하게 하는 방법이다.
    - \4. call(const msg&) 에 건내지는 msg는 어떠한 상황에서도 수정되어서는 안된다.  --> #Message는_name_thisptr_args를_모두_하나의_Array로_구성한다? 참고. 따라서 thisptr 자체는 msg에 들어있어서는 안된다.
    - \5. Native에서 Method 객체를 가지고 있다가 Object 개입없이 바로 호출이 가능해야 한다. 즉, 외부에 thisptr를 주입함으로써 호출할 수 있어야 한다.
      - 예) void A::foo(Method& m) {
        - m.call(thisptr, msg)
      - }
  - *x 1안 모든 Node는 Owner를 갖고 있다고 하며, Method는 부모를 갖고 있으므로 이것은 Object이거나 또 다른 Method일 것이다. 이걸 활용하자.*
    - Method의 Owner는 thisptr가 아니라 Class다.
    - 가장 설계상으로 합리적인 안이지만 동시에 ptr를 set하는 것은 메모리 및 퍼포먼스 이슈가 있기 마련이다. 다른 용도로도 활용한 용도가 무진장 많다면 이걸 할 수 있을것이다.
  - *2안 Stack&Scope를 사용한다.*
    - 그러나 이경우, Stack을 사용하지 않는 Method는 누구의 Object인가는 알수 없다. 
      - Limitaion으로 두는 수밖에 없다.
    - Object는 어짜피 ObjectSpace 구성을 위해서 자신을 Scope에 등록을 해야한다. 따라서 고때 같이 scope가 object를 가지고 있으면 될 것이다. 
    - API명은 scope::getRunningObject() 정도로 하면 될까? 이건 좀 더 생각해보자.
  - *3안 그래서 나온게 Message안에 argument로 ThisPtr를 넣자는 것이다.*
    - --> #Message는_name_thisptr_args를_모두_하나의_Array로_구성한다  참조
  - *4안 msg안에 .thisptr로 따로 빼놓자.*
  - *5안 call의 인자를 하나 더 받게 해서 거기다 넘기자.*
    - static 함수같은 경우에는 thisptr를 사용하지 않는다.
  - *x 6안 Method에 추가적으로 set을 하게 한다.*
    - Arguments는 이런식으로 전달하게 하고 있다?
      - 그건 별도의 함수이다. DynamicBindingExpr을 통해서 들어오는 call(Message&)는 name이 "execute" 일때 execute()로 빠지도록 하고 있다. 즉 제대로 Message로부터 받도록 되어있는 것이지 추가적으로 set을 할 필요는 없다.
  - *x 7안 Message는 static으로 thisptr를 담게 한다.*
    - scope와 다를건 없다. 다만 그 위치가 message로 옮겨지게 한다는 것.
  - *x 8안 Message origin 알고리즘 --> 이 방법은 Native에서 메소드를 호출할 방법이 없게 만든다.*
    - class Message {
      - mutable TStrong<Object> _origin;
    - }
    - class Object {
      - call(const Message& msg) {
        - bool is_updated = false;
        - if(msg._origin == null) 
          - msg.getOrigin() = *this
          - is_updated = true
        - .... call to members ....
        - if(is_updated)
          - msg.getOrigin() = null
      - }
    - }
    - Message msg(......)
    - Object obj.call(msg) // mutable이니까 인자가 const Message& 라도 괜찮다.
    - obj2.call(msg) // 같은 메시지를 다른 객체에 던져도 잘 동작한다.
    - Method m = .....
    - m.call(msg) // 안에서 msg.origin = null이므로 에러를 탐지할 수 있다.
    - Method static = .....



#### 타입 포함된 함수ptr를 어떻게 world frx에서 구현할 수 있을까?

- 이미 Expr & stmt는 target이 Node이기만 하면 validation을 한다. 그러므로 함수ptr라 하더라도 Node것처럼 validation을 돌리면 된다.
- 고찰내용
  - v validate를 먼저 해결해야 한다.
    - validate는 friend로 선언된, classManager안에 있는 별도의 visitation에 의해서 수행된다. 
    - call()에서 사용된 _precall, _prerun을 visitation 안에도 동일하게 사용한다.
  - world의 함수포인터인데이 이 함수포인터는 이러한 인자타입들을 가지고 있다는 걸 어떻게 컴파일러에게 알려줄수 있을까? 어떻게 컴파일에러가 나도록 할 수 있을까?
  - ptr가 아니라 일반 함수가 컴파일에러가 나는 과정을 먼저 clearify하자. 함수호출은 stmt(expr)이 담당한다. 고로 exprValidation.visit()함수가 수행되면 
    - \1. expr이 들고있는 args 자체에 문제가 있는지 확인함.
    - \2. 현재 구성된 scope에서 호출할 method를 찾아서, 그것에게 args를 set하는 식의 scope를 제어하는 Expr._precall()을 여기서 호출함.
    - \3. visitor는 Expr가 들고있는 Strong target을 재귀적으로 탐색한다. 하지만 그렇다고 해서 target이 가리키는 원본까지 visitation을 하는 것은 아니다. 이러한 차이를 항상 염두해 두고 expr같은 TVisitation들은 어디까지 직접 재귀적은 visit을 해야하는지를 생각해야 한다.
  - 결국은 Expr이다. Expr.target = methodptr가 들어있을 것이다. 즉, 기본적으로 함수ptr에 대한 validation 기능이 있는 것이다. 이는 Expr입장에서 target이 base가 Node로 보고 있기 때문이다. Node기반으로 validation을 하기 때문에 target이 methodptr인지 아닌지 상관없이 동일하게 validate가 가능하다.





#### 메소드ptr 정의하는 Stmt 클래스를 구현하라

- 월드 : 메소드 delegator를 생성할때 this를 넣어줬는가 아닌가를 "컴파일타임"에 판단하여 적절한 MethodDelegationExpression을 생성한다. this를 넣어준 경우는 CreateMethodDelegationExpression의 target이 그 this로 채워질 것이다.
  - class MethodDelegation
    - target = scope["a"] **// <-- Stmt가 이값을 이렇게 채우면 된다.**
    - Weak<Method> to = ...
- class A
  - void print(int a)
    - ...
  - void go(int b)
    - ...
  - static void no(int c)
    - ...
- A a
- void(int)[3] fptrs = {a.print(int), a.go(int), [a.no](http://a.no/)(int)}
- fptrs[1] = null
- for void(int) e in fptrs
  - e(3) // a.go와 a.no만 호출됨



#### 메소드 식별문법

- 메소드는 오버로딩이 가능하기 때문에 이름만으로는 애매모호하다. 따라서, 인자타입리스트((type1, type2) 처럼 변수명 없이 타입만 써있는것)도 같이 명시해줘야 한다.
- 이게 정석이나, 일부의 경우 method deduction을 해달라는 요구사항이 있었다.
- 시나리오
  - class A
    - void print()
    - void print(int age)
    - void print(string msg, float grade)
  - A.print(void) // 이건 함수에 접근하는 것.
  - A.print() // 이건 함수를 호출하는 것
  - A.print(string, float).getName()
- 시나리오2-인자가 복잡해지면 읽기 어려워지는데
  - class A 
    - int print(int a)
      - ..
    - int(int) print(float b) // 여기서 print(int b)로 하면 중복정의가 된다.
      - return print(int)
  - int(int)(int) fptr = A.print(float)





#### Method가_만약_Type의_일종이_아니라면, Type이라는 클래스가 필요없다면, execute()를 virtual로 상속받게 할 수 있다. 

* Contextual_REPL_based_development  가 먼저 해결되어야 한다.
* Type은 자신을 Generating한 SourceCode가 누구인지 적어놓는 역할이다. 아마 이는 C-REPL때문에 생긴것이다.

- 1안 필요없다. Type은 Unique성을 부여하기 위해서 넣은 클래스일 것이다. Type 클래스를 없애기 위해서는 Unique성이란 무엇인지, 이걸 부여하기 위해서 어떻게 할 것인지를 정해야 한다.
- 2안 내 소스코드가 어디인지, 어디서부터인지는 기록할 필요가 있지 않은가?







#### 월드코드에서의 함수식별을 어떻게 할 것인가? a.print() 와 a.print(void).execute

- 월드코드에서 a.print()는, 인터프리터가 a.print(void).execute 로 인자추론하여 정적바인딩으로 함수 확정후, 코드블럭이 만들어질 것이다. 즉, syntatic sugar다.
- Node.getMember()은 인터프리터가 바인딩을 할때 주로 사용하게 될 함수다. getMember(index)와 getMember(string), getMember(msg) **3종류**가 있어야 한다.
  - getMember(string) {
    - return getMember(Msg(string)); // 이 Msg는 args가 없다.
  - }
- Object::isConsumable은 name만, Method::isConsumable()은 ((name == name(paramlist) && noArgs) || msg를 consume 가능할때)) 통과시킨다.
- 이때 일부 pretype은 name을 소문자로 해야한다. 
  - 예) String은 C++에서 봤을때 그런거고, world에서는 string이다.
- name(paramlist)은 Method._name이며, Method::initialize()나 lazy로 한번 define된다.
- 고찰내용
  - 함수 식별문제 때문이다. World코드에 a.print(void).getName() 과 a.print() 2개가 있다고 해보자. 이때 인터프리터는 저 2가지 케이스에 대해서 어떠한 코드블럭을 만들어야 할까?
    - x 1안 2가지의 output이 다르게 한다.
      - 이 경우 Node는 subnode에게 isConsumable(msg)를 물어볼때, subnode가 MEthod 라면 "print(void)" or ("print" && args[0] == void) 로 따져줘야 한다. 즉 isConsumable의 true 요건이 2개가 되는 것이다.
      - **이건 동적바인딩을 하겠다는 것이다. 어떤 print함수가 될지 이름만 줄테니, 함수바인딩은 실행할때 하겠다는 것이지.**
    - v 2안 2가지의 output이 같다. 
      - 이경우 a.print()는 인터프리터가 실제로 어떠한 함수인지를 인자추론을 통해서 판단한 뒤, a.print(void).execute 로 변경한다. 즉, **syntatic sugar**가 되는 것이다.
      - 따라서 이경우, 인터프리터가 함수를 판단한 뒤 코드블럭을 만들면서 확정해버린다. C-REPL 문제와 관련이 있게 된다.
      - C-REPL의 초기안은 코드 수정이 나면, 수정난 것에 영향을 받는 모든 코드를 전수조사 및 역추적해서 그 부분들을 다시 바인딩 및 검증을 돌리는 방법이었으나 이게 시간이 너무 걸리는건 뻔한 이야기다.
      - [3/28] 그래도 그렇게 해야 한다. 동적바인딩을 해버리면 에러를 탐지할 방법이 없기 때문이다.





#### 메소드 타입리스트 deduction

- 시나리오
  - class A
    - void print(int)
      - ...
    - void print(float)
  - A a
  - void(int) f1 = a.print(int) // 이게 정석이나,
  - void(int) f1 = a.print // 어짜피 a.print(float)이 여기에 오면 에러가 되기 때문에 이건 해당사항이 되지 않는다.
- 구현방법은?
  - v 1안 정보가 부족한 경우, 필요한 인자를 끼워넣어 여러가지 candidates를 만든다. 그리고 에러로 판정되는 것은 삭제를 해버린다. == SFINAE. 
    - 최종 컴파일 결과가 에러로 판정된다면, 미리부터 candidates라고 사용자에게 알릴필요가 없다는 것이다. 
    - candidates에서 제끼는 게 이 안의 구현사항이 아니다. 처음부터 부족한 정보를 제공한 경우에도 정보를 보간하여 candidates를 만들어내는 것이 요구사항이다.
    - 즉, 함수명만 제공된 경우, 해당 클래스의 같은 함수명을 가지고 있는 모든 member가 candidates가 된다. validator는 이중에 어떠한 것들이 최종적으로 에러가 아닌지를 판단해서 candidates가 1개가 되면 그걸 채택한다.
    - 대충 맞을 것 같긴하다. validation에 상세한 알고리즘을 구현해보자.
  - x 2안 파싱 rule을 추가하여 정보가 부족한 경우에 자동으로 딱 1개의 정보를 채워넣는 일종의 syntactic sugar로 동작한다.
    - void(int) f1 = a.print를 한 경우, 자동으로 a.print(int)로 채워넣는 파싱rule을(혹은 파싱전 사전작업) 추가한다는 것이다.
    - v 하지만 이와 같은 경우, 앞뒤 타입으로 유추가 가능하면 사용할 수 있으나 다음과 같은 상황은 해당되지 않는다.
    - class A
      - void print(float)
    - A a
    - string c = A.print.getName() // 요 stmt만 놓고 보면 print를 특정하는 정보가 일체 없다. A는 print가 함수1개만 있다는 걸 컴파일러가 알아야 보간가능한 상황이다.





#### 람다를_지원할것이기_때문에_fptr같은게_있어야_한다_어떻게_함수ptr를_정의하도록_할까. 중요한 점은, 가능하면 타입체킹이 가능하도록 해야 한다는 것이다.

- [v] 런타임시 함수ptr 생성

  - Method를 가리키는 함수ptr에 해당하는 타입을 만들어야 한다. 

- [v] 함수ptr의 정의

  string(int, float) funcptr = A.foo(int, float) typedef string(int, float) FuncPtr FuncPtr funcptr2 = funcptr 로 한다. 

  - *x 1안 Node형태로 사용하게 한다.*
    - class A
      - int foo(int a , float b)
        - return a + b
    - method foo1 = A.foo
    - Console.out("foo = " + foo(3, 3.5f))
    - foo1("wow")
    - **이럴바에야, method 대신 node를 쓰라고 하면 된다. node는 어떠한 call도 런타임에 바인딩을 판단하는 타입이다. 어떠한 것도 코딩할 수 있다.**
    - 그리고 node도 제공하지만 이것 정말 어쩔 수 없을때 사용하는 거고 그 외에는 타입을 체킹할 수 있는 수단을 제공하고 싶다.
  - *x 2안 method라는 독특한 정의법을 만든다.*
    - 시나리오 
      - class A
        - string foo(int a, int b)
      - method foo1 = A.foo
      - foo1(2, "msg") // compile err
    - 안된다. 
    - 이유1. validation에서는 실행은 하지 않는다. 따라서 foo1 자체는 scope에 있지만 foo1의 값인 foo메소드는 없는 것이다. 따라서 foo1이 어떠한 메소드와 binding이 되어있는지 알 수 없다.
    - 이유2. method의 타입은 초기화시에 어떠한 함수와 binding되었는가에 의해서 결정된다. c++의 auto와 같다. 따라서 
      - method foo1 = null
      - foo1 = A.boo
      - or
      - method[] foos
      - foos[rand()] = A.boo
    - 여기서 A.boo가 들어갈 수 있는지 없는지 컴파일타임에 정할 수 없다.  돌려봐야 아는 것이다. 이문법은 사실 node와 거의 동일하다.
  - 시나리오
    - class A
      - string foo(int a, float b)
        - ..
    - string foo(int a, float b) = A.foo *// [x] 굳이 필요도 없는 변수명을 적을 이유가 없다.*
    - Console.out("foo = " + foo(3, 3.5))
    - foo(2, "msg") // compile err
    - string foo(int, float) = A.foo *// [x] 3안 --> 이경우, 같은 타입의 변수를 여러개 지정하지 못한다.*
    - string(int,float) foo1 = A.foo // 4안
      - string(int,float) foo1, foo2 = A.foo
      - string(int, float)[] foos
      - foos[0] = A.foo
      - foos[1] = A.boo
      - for e in foos
        - e(3, 3.5)
    - ref string foo_type(int, float)
    - foo_type foo1, foo2  *// [x] 5안 C#, boo, cobra 스타일 -> 3안 + typedef 한것과 동일하다*
      - string function(int, float)  = A.foo *// D 스타일*
      - def (int, float) *// boo*
  - v 4안으로 한다.
    - .NET 계열언어에서는 5안을 많이 사용한다. 
    - js, python같은 애들은 애초에 동적타입이므로 이문제에서 벗어난다. 
    - 자바는 interface 클래스를 만들고, 이를 이름없는 객체를 생성하여 에둘러 해결한다. 그러나, 이 방법은 사용자가 정의할 cb을 받아들이는 데 적합할 뿐, 이미 존재하는 다른 클래스의 메소드를 그대로 참조는 불가능하다.
    - 결과 4안을 하기로 했다. 여기서 typedef를 사용하면 5안과 차이가 없다는 점이 핵심이다. 
    - 메소드 정의와 ptr정의를 동일하게 가져가는 것도 좋지만, 이렇게 해버리면 한번에 복수개의 변수를 만들 수 없으며, 타입명 중간에 변수명이 들어가게되므로 통일성도 깨진다.





#### "지금 이 메소드는 이 객체에 속한 것이다" 라는걸 expr이 끝나도 알 수 있는 방법은?

- 시나리오
  - class A
    - void print(int)
  - A a
  - void(int) fp = a.print
  - a.print 가 끝나고 나면 Method가 MethodDelegator에 들어가게 될 것이다. 이 MethodDelegator객체는 인자인 Method의 Object가 누구인지 생성자에서 알 수 있으면 편할 것이다.









#### 함수_바인딩_퍼포먼스_알고리즘_최적화

- World의 모든 Statement는 사실 Expression이다. --> #Statment와_Expression은_구분해야_할까 
- Expression은 execute()가 가능하고, 반환값을 얻을 수 있다. 전달할 Msg와 전달받을 Target을 가지고 있다.
  - Expression설계상, execute()를 해야만 반환값을 얻을 수 있는 것은 아니다.
- Expr은 Expression 컴포넌트의 기반클래스이며, 이 밑으로 RawExpr, AccessExpr, ExecuteExpr, DynBindExpr 4종류가 있다.
  - RawExpr은 Generation단계에서 링킹을 위해서 정보를 잠시 담아둘 용도로 사용되는것이며(미확정)
  - DynBindExpr은 다이나믹바인딩 특성을 갖게 하는 Expression이다. 이는 C-REPL 기반에서 런타임시, 매 호출마다 묵시적형변환과 오버로딩을 고려한, 동적바인딩을 통해서 적당한 심볼로 바인딩을 한다. 당연히 시간이 많이 소요된다.
  - AccessExpr, ExecuteExpr은 DynBindExpr의 시간이 많이 소요되는 것을 최적화하기 위해서 추가되는 것으로 Optimization 단계에서 Optimizer(명칭 미확정)가 DynBindExpr들을 분석해서 적절하게 변환해준다. 
    - 현재로써는 AccessExpr(= getMember(index)), ExecuteExpr(= call("execute")) 2가지로 모든 DynBindExpr이 대체가능할것으로 보인다.
  - 차후 더 최적화 과정이 이루어지면 더 다양한 Expr이 나오게 될 것으로 보인다.
- 고찰내용
  - 요구사항
    - \1. Linking이 끝나고 코드블럭이 나오면, 함수호출statement에서 어떠한 함수를 호출해야 하는지 바로 접근이 가능하게 해야한다. 오버로딩을 고려하기 시작하면 매번 call에 던질때마다 Object는 msg 파악해서 묵시적형변환 고려하고 적당한 함수로 redirection하는 과정을 거칠 수 밖에 없는 것이다.
    - \2. 2가지 기능은 모두 필요하다. 직접접근도 돼야 하지만 파서를 위해서 오버로딩+묵시적형변환 을 고려하는 로직도 같이 있어야 한다.
  - **고찰로 얻어낸 팩트**
    - \1. **기존 설계에서는 "모든것은 call" 이라고 하였으나, call에는 "이 msg를 받을 수 있는 것은 누구인가" 라는 것을 찾아야하는 의무가 있다. 따라서 "call안에 msg를 받을 수 있는 것은 누구인지 찾지 않게 한다" 라는 걸 넣기가 어렵다.**
    - \2. "msg 받을 수 있는건 누구인가" 를 찾는 과정은, 오버로딩과 묵시적 형변환을 필요로 하며 많은 시간이 소요된다.
    - \3. C-REPL를 사용한다면 getMember(35) 처럼 인덱스 기반으로 만들기는 쉽지 않다. 왜냐하면 런타임과 빌드가 mix된 상태가 계속 이어지므로 member가 추가되거나 삭제될 수 있다.
    - \4. 따라서 C-REPL을 위해서라면 언제든지 멤버접근방법이 2가지가 제공되어야 한다. 하나는 msg(곧, string)을 통해서, 하나는 인덱스를 통해서.
  - 1안 **Access, Executor** 라는 걸 만든다. 이건, execute시 call을 사용않고 직접 멤버에 direct로 접근한다.
    - World는 설계상으로는 Statement와 Expression를 구분하지 않는다 --> #Statment와_Expression은_구분해야_할까  참조. 모든것은 Expression 인것이다.
    - getMember(Msg)는 동적바인딩을 수행하는 함수이며, call(MSG)를 호출한 경우에는 getMember()를 타게 된다. 이것은 코드블럭이 막 완성된 상태, C-REPL일때는 이걸로 코드블럭이 call(MSG)를 사용하도록 완성되어있으므로, 이걸 사용하게 된다. 이때는 모든 코드블럭이 DynamicBindingStatement 같은 걸로만 구성되어있으며, 해당 클래스는 execute()시에 call(MSG)를 통해서 심볼을 접근, 메소드를 수행하도록 되어있다.
    - Optimization단계에서는 일률적이던 DynamicBindingStatement를 분석해서 Accessor나 ExecutorStatement로 구분해서 객체를 변경한다.
    - Accessor는 execute()되면 target.call(MSG)가 아니라 return target.getMember(index) 로 바로 접근하는 것이므로, call("getMember", {...}) 일때와 달리 동적바인딩이 없다. call()로 하는 경우는 총 2번의 동적바인딩을 타야만 한다.
      - 1번은 call로 인하여, 2번째는 call을 통해서 호출된 getMember(Msg&) 안에서 주어진 args를 대상으로 수행된다.
    - executor는 target.execute(Msg&)를 수행하도록 한다. Method는 기본적으로 상속받은 virtual execute()가 있으며, 오버로딩한 execute(Msg&)는 내부적으로 
      - setArgs(msg.getArgs())
      - execute()
    - 를 할 뿐인 편의함수다.
    - 이 역시 call()를 거치지 않으므로 동적바인딩이 1번 생략된다.
    - 코드
      - class Node {
        - getMember(int index, wlevel& level = wlevel())
        - virtual Node& getMember(const Message& msg, wlevel& lv = wlevel()) // msg를 받을 수 있는 Member를 반환한다. level은 얼마나 근접한지를 나타낸다. 0은 일치, 높을 수록 불일치.
          - wlevel&를 인자로 넣는 거 말고 더 좋은 방법은 없을까?
          - struct Unit {
            - TStrong<Node> trg
            - wlevel lv;
          - } unit;
          - [unit.lv](http://unit.lv/) = 99999999;
          - for(m in members)
            - wlevel trg_lv = 0
            - Node& trg = m.getMember(msg, trg_lv)
            - if( ! trg_lv)
              - return trg;
            - if(trg_lv < [unit.lv](http://unit.lv/))
              - unit.trg.bind(trg)
              - [unit.lv](http://unit.lv/) = trg_lv
          - return unit.trg.get()
      - }
      - class Func : Node {
        - virtual Node& getMember(const Message& msg, Result& res = Result())
          - // **묵시적 형변환**도 고려해서 msg를 받을 수 있는 경우,
          - return *this;
      - }
    - 시나리오
      - a.foo.boo(void).getName().toInteger() 라는 world코드가 있다고 가정하자.
      - Generting단계에서는 파서가 저것들을 끊어주면 단순히 Statement 정보만 갖고 있는 candidate로 만들어준다.
        - StatementCandidate {
          - trg = StatementCandidate {
            - trg = StatementCandidate {
              - trg = StatementCandidate {
                - trg = StatementCandidate {
                  - trg = StatementCandidate {
                    - trg = scope
                    - msg = {.name = a, .args={}}
                  - }, msg = {.name = "foo", .args={}}
                - }, msg = {.name = "boo(void)", .args={}}
              - }, msg = {
            - }, msg = {.name="getName", .args={}}
          - }, msg = {.name="()", .args={}}







### Expression

#### Statement는 Visible 하지 않는다.

#### Statment와_Expression은_구분해야_할까

- 블록문을 위해서라도 Statement와 Expression은 구분해야 한다.
- 고찰내용
  - 이것은 Statement 쪽 클래스 계층을 설계하는데 있어서 중요한 질문이다.
  - Statement는 execute()만 되는거? Expression은 get(), to<Node> 등이 되는거?
  - 다른데는 뭐라고 할까?
    - Expression은 Value의 복합적인 형태를 말한다. 결국은 값으로 치환되어야 한다. 반면, Statement는 말그대로 실행가능한 1줄을 의미하는 것으로, Expression은 아니나, Statement에 속하는 것은 대표적으로는 if, for, while등이 있다.
  - 고찰을 통한 팩트 정리
    - \1. Expression은 값이 나와야 한다. Statement는 Expression을 포함한 모든 코드 1줄을 의미한다. 값으로 나오지 않아도 된다.
    - \2. 방향은 2가지로, 
      - "구분한다"를 선택하면 다른 언어처럼 가는것이다. 설계를 바꿀 필요가 있을 것이다. 
      - "구분하지 않는다"를 선택하면 "모든 Statement는 값을 반환한다." 를 만족시켜야 할것이다. 이말은 "Void가 인자로써 어떻게 예외처리 할 수 있는가"에 답하는 게 된다.
  - x 1안 모든것은 함수라고 본다면, 둘은 구분할 필요가 없을 것이다.
    - 위의 규칙으로 본다면 a == 5는 expression이다. 하지만 C++에서는 a==5 만 달랑있어도  컴파일은 가능하다. a++는 무엇인가?
      -  --> Expression이다. 왜냐하면 값이 있기 때문이다. Expression은 그자체로 Statement가 될 수 있다. 여기서 논의해야 하는 것은 Expression이 아닌 Statement가 어떻게 Expression으로 다루어질 수 있는가다. 그럴러면 Void 타입을 어떻게 인자로써 함수에 넣을 수 있는가가 되는 것이고.
  - x 2안 논리적으로는 Statement, Expression은 구분되지만, 설계상으로는 구분하지 않는다.
    - 모든것은 걍 Expression == 함수호출. Void가 인자로 나온 경우는 에러를 발생시킨다. 
    - 결과적으로는 지금의 설계와 동일하다. 이름도 동일하게 Statement로 하자.
    - --> 그러나 이런 논리라면 Method 혹은 Block문 또한 Expression이 되버리고 만다.
    - 블록문을 함수의 인자로 넣을 수가 있는가? 안되지.
  - v 3안 블록문을 위해서라도 Expression과 Statement는 구분해야 한다.
- v 시나리오 고찰
  - 일단 문제는 없어보인다. 하지만 시나리오를 많이 생각해봐야 한다.
  - 시나리오1 함수호출
    - int abc_func()
    - 일때, abc_func()의 반환값인 int를 반환
  - 시나리오2 변수 정의
    - 반환값은 정의된 변수.
    - 예) foo(int a, int b = 5) // a는 블록문의 lifecycle을 가지므로 
    - a += 5 // 여기서도 유효함
  - 시나리오3 블록문
    - 반환값은 블록문의 마지막 expr
      - 이말은 return이 필요 없다는 것이기도 하다.
    - 예1
      - int b = if(a==5)
        - foo(a)
      - else
        - foo(5)
    - 예2
      - class A
        - void foo()
          - 5 // return 5와 동일함.
  - 괜찮은 것 같다. 굳이 stmt를 두는 것보다 제약도 적어지고.
  - 적용하자.
- World에서 Statement라는건 없다. 굳이 구분해서 코드에 제약을 둘 필요가 없다. 모든 코드라인은 Expression이다.
  - 1 이말은, 변수 정의또한 인자로써 들어갈 수 있다.
  - 2 함수 정의 또한 인자로써 들어갈 수 있다. -> #인라인_람다 , #world_inline_메소드메소드 참고
  - 3 클래스 정의 또한 변수 인자로써 들어갈 수 있다.
- 가 된다.
- 아무튼, 1과 2까지는 동의하므로 일단 stmt라는 건 없애버리자. 굳이 stmt와 expr를 구분해서 어렵게 만들 필요가 없다. 처음보는 사용자가 "이게 된다면, 이것되 되나?" 싶다면 젤다처럼 되야 한다.
- Expr은 쉽게 말하면 함수 호출이다. 함수 자체와는 다르다. 함수호출이란 Msg와 함수를 묶어주는 것을 의미한다. 모든 코드라인의 근간이 되는 셈이다. Method는 실행시 필요한 인자가 외부에서 제공되어지지만, Expr은 프로그램이 컴파일됨과 동시에 필요한 인자가 박혀있다. 필요한것은 그것들을 수행하고 난 결과값을 외부에서 받을 수 있도록만 하면 된다.
- Expr의 종류는 이렇다.
  - this가 필요한 경우와 필요하지 않은 경우
  - 특정 함수를 정확히 아는 경우와, 또다른 expr에게 물어보면 아는 경우
  - 결국은 caller.call(msg[this가 있을수도 있음]); 의 꼴이 되어야 한다.
- this를 넣어주는건 사용자의 책임이므로 Expr이 넣어줘야 한다. 
  - ThisExpr과 StaticExpr 2개가 있다고 하자.
  - ThisExpr은 caller를 뽑아내서 msg 맨 뒤에 set을 해줘야만 한다. caller가 필요하다는 말씀.
- Expr에 call()을 하면 execute()를 하고 난 결과값에 call을 하게 된다. proxy처럼. 이말은 최소 Node로부터는 상속을 받아야 한다.
- Expr은 Object로부터 상속받지는 않는다. 때문에 Node의 일종이긴 하지만 Expr은 invisible하게 된다. (정확히 말하면 metaclass로부터 함수들을 물려받지 못하게 된다)

#### Expression 블록을 어떻게 최적화 할 수 있을까?

- [][v] 최적화가 완료되면 get(n) 으로 될 수 없다. call(n)을 만들어야 한다. 왜냐하면 get(n)은 scope를 구성하지 않기 때문이다.
- call(n) // same as call(msg("name of variable"))
  - _precall()
  - refer r = get(n)
  - _postcall()
  - return r
- 최적화 시나리오
  - scope["myfoo"].call("age"); --->  scope["myfoo"].call(5)





### 오버로딩

#### 1
-   Node간 연산자 동작 컨셉
    -   컨셉과 방향 정의하기
        -   C++과 World는 성격이 다르기 때문에 설계도, limitation도 다르다. World는 물리적으로 타입체킹이 없으나 논리적으로 타입체킹을 수행하는 철학이며, C++은 항상 타입체킹을 엄밀하게 수행한다. 이러한 차이를 그대로 설계에도 적용하는 것이 바람직하다고 판단했다.
        -   World는 메시지 기반이므로 적절한 메시지인, ++, +, -, <, >, == 등등 작성되어 C++코드로 호출하면 그 대상이 지원하든 하지 않든 일단 실행하려 시도는 한다.
        -   Native Framework 에서는 해당 operator 오버로딩함수가 필요한 곳에서만 정의 한다. 예를들면 Node 같은 ADT는 ++, +, - 와 같은 산술타입과 String에서만 필요로할 것같은 이러한 operator 오버로딩을 두지 않도록 한다. operator+ 같은 걸 수월하게 하려면 downcasting용 함수를 사용하자. 2-3줄이면 의도한 내용을 쉽게 할 수 있다.
        -   단, ==, !=, = 는 매우 기본적인 연산이고 모든 타입이 갖을 수 있으므로 Node에서도 이를 지원한다.
    -   사용
        -   이 문제가 어려운 이유는 다름 아닌 역의존성 삽입에 의한 것이다.
            -   class MyModule을 개발자가 만든다고 가정하자. MyModule개발자는 int -> MyModule, MyModule->int를 모두 지원해주고 싶다. 이때 int -> MyModule 은 쉽게 이루어진다. 왜냐하면 MyModule에서 int값을 받아서 적절하게 생성해주면 되니까. 하지만 반대의 경우는 문제가된다. 왜냐하면 int는 MyModule보다 먼저 나온 것이기 때문이다. 고로 이러한 역의존성을 해결할 필요가 있다.
            -   int는 이미 나온 클래스이기 때문에 여기에 MyModule을 받아들이는 코드를 추가할 수 없다는 게 문제가 되는것이다.
            -   크게 3가지 방법이 있다.
                -   방법1. C++, C#에서 사용하는 방법으로, 외부의 제 3의 일반함수를 만든다.  
                    --> 그러나 World는 순수객체지향언어라 일반함수라는 게 없다.
                -   방법2. python에서 사용하는 방법으로 reverse 버전을 만든다.
                    -   operator+의 경우 reversed_operator+() 같은 것을 월드가 호출하도록 한다.
                -   방법3. 클래스 확장을 사용한다.  
                    --> world만의 방법
            -   월드는 클래스 확장하는 방법을 채택했다. 클래스 확장을 전면 지원한다.
            -   클래스 확장은 class ~~~ extend <package>
                -   함수선언 or 변수선언
            -   으로 사용하는 것으로, 이미 정의된 클래스에 함수나 변수를 추가하게 한다. extend라는 키워드를 붙이는 이유는 인터프리터가 "원본을 먼저 읽도록" 자연스럽게 유도하기 위해서이다.
            -   중복으로 정의되면 당연히 에러가 난다. 즉, 같은 클래스내에서 오버라이딩을 하는건 불가능하다.
            -   컴파일이 완료되어, !수정불가! 로 도장찍혀서 배포되는 외부 클래스를 final클래스라고 한다. 이경우는 extend가 불가능하다. 이 경우 컴파일이 완료되면 변수정보가 남아있지 않게 만들기 때문이다. 모든게 getMember(n) 인덱스로 접근되기 때문에. 이경우에는 extend를 할 수 없다. 인터프리터가 파싱하는 시점에서 getMember("변수명")으로 찾는게 불가능하게 된다.
    -   고찰 내용
        -   Node간에 =, -, +, --, ++, +=, >, <, == 등은 어떻게 지원되어야 할까?
            -   1안
                -   포인트는 C++은 타입체킹이 엄격해야 한다. World는 논리적으로 엄격하다. 물리적으로는 가능하다는 얘기다.
                -   이를 종합하면 C++ 개발자는 2가지 접근을 할 수 있다. C++적인 접근을 한다면 Integer, Float과 같은 산술형 Type인지 아닌지를 타입캐스팅해서 알아내서, 그 시점에서 +, += 같은 걸 하면 된다.
                -   아니면 call("+") 같은 걸 사용해서 일반적인 방법으로 접근하도록 한다면 어떠한가?
                -   call을 쓸바에야 차라리 캐스팅을 하려 할 것이다. 일반적으로 항상 통용되는 명령어인 =, ==, != 지원하는 건 무리가 없다.
                -   그리고 C++개발자가 무슨 타입을 원하는지 정해져있다면 그냥 캐스팅을 하면 될것이다.
                -   그렇다면 무슨 타입인지 정확히 모르는 상황에서 Node1과 Node2에 대해서 2항연산을 하고 싶은 케이스만 문제가 된다. 이런 케이스가 존재할 것인가?
                    -   String 혹은 산술연산타입 모두에 적용가능한 걸 하고 싶다면 어떠한가?
                        -   그러한 경우는 일반적으로 존재하지 않는다고 본다. 정 그런 케이스가 있다면 call("")을 사용하라. 아니면 RTTI를 하던가. C++에서도 자동으로 되는 건 절대 아니다.
                -   Integer, Float 같은 것은 ArithmeticType을 부모클래스로 가질 것이다. 그리고 여기에 +, -, ++ 같은 것들이 있겠지.
                -   Reference 같은 케이스는 어떻게 되는가?
                    -   World에서는 Node 인 채로 다룬다. 그게 무슨 타입인지는 실제 중요하지 않다. 이걸 가능하게 하는 것은 call() 기반으로 동작하며 오로지 빠른 디버깅을 위해서만 논리적으로 컴파일 에러를 내보낸다.
                    -   C++은 타입체킹이 엄밀하게 동작한다.
                    -   즉, 이 질문은 C++ FRX에서도 개발자의 메인 타입이 Node로 삼을 것이냐? 라는 걸로 요약할 수 있다. Node 기준으로 다룬다면 +, - 등등 모든 것들이 Node에도 있어야 한다.
                    -   반면 아니오 라고 한다면 operator+() 메소드는 주어진 타입이 산술 타입인지를 명확히 이해하고 있을때만 동작한다.
                    -   다행이 산술타입은 occupiable이므로 Reference가 존재하지 않는다. (가능하지만 논리적으로 막혀있다)
                    -   그렇다면 String 같은 sharable이면 +가 존재하는 것들은 어떠한가?
                    -   String 에 대한 Reference라고 해도, +는 되면 안된다. 이때 방법은 2가지다.
                        -   1. if node.isSubOf(Reference)
                            -   Reference& ref = node;
                            -   if ref.get().isSubOf(String)
                                -   String& str = ref.get()
                                -   cout << str + msg
                        -   2. downcasting은 그냥 편하게 함수를 써라. 직접하지 말고.
                            -   String& str = [node.to](http://node.to/)<String>();
                            -   if ! str.isNull()
                                -   cout << str + msg
        -   연산 주체
            -   구체적인 설계는?
                -   구현자체는 어렵지 않다. 하지만 퍼포먼스를 고려와, 무슨 문제가 있을수 있는지를 생각해봐야 한다.
                -   1안
                    -   일단 앞에 있는 operand로 가고, 그것이 뒤에있는 operand와 자신의 우선순위를 따져서 누가 이걸 진짜 처리해야 하는지 정한다.
                    -   Arithmetic::operator+(Node& rhs)
                        -   if getPriroity() >= rhs.getPriority()
                            -   내가 handle
                        -   else
                            -   return rhs.operator+(*this);
                    -   문제점
                        -   이 코드는 어디에 위치해야 하는가?
                        -   rhs.operator+()에서도 같은게 또 일어난다. 해결방법은?
                        -   일단 함수가 호출되고 나서 다시 redirection 되는것이기 때문에 함수 호출자체는 loss가 된다.
                -   2안
                    -   전역적으로 일단 허용한다.
                    -   전역함수 : Bind<Node> operator+(Node& left, Node& right)
                        -   left와 right의 우선순위를 구한다.
                            -   우선순위 높거나 같은쪽이 right라고 가정한다.
                        -   left를 right로 변경할 수 있는가? 그리고 right.operator+()를 가지고 있는가?
                            -   둘다 YES라면 left -> right 한 뒤, right + right를 수행한다.
                        -   아니라면 right -> left가 가능하며, left + left가 존재하는지 확인한다.
                            -   된다면 right -> left 한 뒤, left + left
                        -   모두 아니라면 변환이 불가능 하다.
                    -   검증
                        -   int + string
                            -   우선순위 검출 : 1(built-in occupiable) < 2(built-in sharable)
                            -   int -> string이 가능?
                    -   문제점
                        -   내껄 다른 타입으로 내보내는 to()가 아니라, 다른 타입을 내껄로 만드는 from()이 필요 하다.
                            -   그렇게 되면 to()와 from()이 모두 있으므로 어느걸 적용해야 하는지 모호성 오류가 다시 나올것이다. 옛 설계처럼.
                -   3안
                    -   심플하게, 심플하게 가자.
                    -   class MyInt : public Arith
                        -   Bind<Arith> operator+(Arith& rhs)
                            -   Bind<MyInt> res = [rhs.to](http://rhs.to/)<MyInt>()
                            -   if res.isNull()
                                -   return
                            -   Bind<MyInt> cloned = clone()
                            -   cloned.get() += res.get()
                            -   return cloned
                    -   class MyBigClass : public Node
                        -   MyBigClass operator+(Node& rhs)
                            -   Bind<This> res = [rhs.to](http://rhs.to/)<This>()
                            -   if res.isNull()
                                -   return
                            -   MyBigClass temp = *this
                            -   temp.setAge(temp.getAge() + res.getAge())
                            -   return temp
                    -   문제점
                        -   A.operator+를 하려면 Node를 A로 캐스팅 한 상태에서만 가능하다. Node 간의 operator+가 지원된다면, 수행하고 싶은 경우 제대로 작동하지 않는다.
                            -   Node& a, &b
                            -   Bind<Node> c = a + b
                        -   operator+를 하고 싶다면 내 클래스만 수정해서는 되지 않는다. integer 타입이 MyBigClass로 to<>()가 가능하도록 만들어야 한다.
                        -   World에서 MyBigClass + int를 하게 되면 어떻게 되는가?
                            -   class MyBigClassOperatorFunction
                                -   MyBigClass ret;
                                -   virtual Node& getResult() { return ret; }
                                -   virtual call(Member[] args)
                                    -   ret = this_p->fptr( ((TYPE1&)members[0]).get());
                            -   MyBigClass.call("+", {Integer(3)})
                -   생각을 해보자.
                    -   class Arith : public Type
                        -   Bind<Arith> operator+(Arith& rhs)
                            -   Bind<Arith> res = clone()
                            -   res.get()
                    -   class Integer : public Arith
                        -   Integer operator+(Integer& rhs)
                            -   return Integer(get() + rhs.get())
                -   4안
                    -   A + B가 있을때, 일단 A::+(B)를 시도 한다. 없으면 B::+(A)를 시도한다. 둘다 없으면 에러. 깔끔하며 단순하다. 그러면서도 대부분의 케이스에서는 동작한다. 설계도 단순하다.
                        -   덧붙여, 각 함수 호출에서 "없다"는 의미는 묵시적형변환이 동작해도 함수가 없다는 얘기다.
                    -   이 코드는 파서에 의해서 코드블록을 만들어낼때만 동작한다. 런타임에는 수행되지 않는다.
                    -   연산자 타입 추정과 함수 바인딩 우선순위에 의해서 묵시적 형변환이 일어나는 컨셉이 서로 영향을 미친다. 이걸 잘 정리해보자.
                        -   서로 영향을 미치지 않는다. 빌트인 타입에 대해서는 내가 다 만들어 놓을 것이며, 일반 타입의 경우 묵시적형변환은 upcasting에 대해서만 된다. 그러므로 괜찮다.
                -   v 5안
                    -   "클래스 확장" 기능을 통해서 이미 정의된 클래스에게 operator+()등을 넣을 수 있다.
                    -   묵시적 바인딩으로 다른 함수와 동일하게 동작되도록 한다.
                        -   인터프리터는 validation시, int + MyClass 가 있는 경우 정확히 int::operator+인 함수후보군을 뽑아내서 MyClass를 인자로 집어넣을 수 있는게 1개 있는 지 여부를 확인하면 된다. --> 묵시적바인딩을 참고하라.
                    -   모듈개발자는 클래스 정의시에 C++처럼 MyClass::operator+(Integer)을 정의하면 된다. operator+함수도 일반 함수와 동일하게 fptr로 지정할 수 있다.
                    -   그러나 Integer::operator(MyClass)는 모듈개발자가 어떻게 설정할 수 있지?
                        -   1안 의례 하는대로 friend 일반함수를 사용한다.
                            -   논리적으로 불가능하지는 않다. 다만 매크로는 "이 함수는 멤버함수 ptr가 아니라 일반함수 ptr다" 라는 걸 ㅇ라아야 한다.
                            -   v 1안 - 매크로를 다른거 쓰라고 한다. 2쌍을 제공한다.
                            -   2안 - SFINAE를 사용한다. 다만 함수명을 제외한 인자리스트와 반환형은 미리 정해져 있어야 하는 걸로 보인다.
                                -   모든 operator+-==<=>=<>!=*/%에 대해서 미리 만들어 놓아야 한다는 것이 된다.
                                -   그 외의
                                -   일반함수를 사용하고자 하는 경우가 또 있을 수 있을까?
-   Node간 연산시 타입 추정 알고리즘이 아마 필요 없을 것이다.
    -   A + B * (C / D + E * F) * G + H / I
    -   int + float * (char / bool + string * result) * float + string / char
    -   이러한 수식이 있을때, 최종적으로 나오는 타입은 무슨 타입인지 어떻게 아는가?
        -   1안. 2 pass를 돌린다.
            -   파서가 구성한다.
                -   +
                    -   +
                        -   A
                        -   *
                            -   *
                                -   B
                                -   +
                                    -   /
                                        -   C
                                        -   D
                                    -   *
                                        -   E
                                        -   F
                            -   G
                    -   /
                        -   H
                        -   I
            -   파서가 구조체를 타입 평가한다.
                -   각각의 2항 연산은 "연산자 동작컨셉" 에 의해 동작한다
                -   +
                    -   + --> string
                        -   A --> int
                        -   * --> string
                            -   * --> string
                                -   B --> float
                                -   + --> string
                                    -   / --> char
                                        -   C -> char
                                        -   D -> bool
                                    -   * -> string
                                        -   E -> string
                                        -   F -> result
                            -   G --> float
                    -   / --> error
                        -   H --> string
                        -   I --> char
            
        -   v 2안 --> 파서제네레이터가 판단해준다. 우리는 알거 없다.
-   월드 코드에서 연산자 우선순위 조정
    -   a + b * c 인 경우, b*c가 먼저 되어야 한다.
    -   GeneratorParser가 이걸 해줄 수 있다







#### 객체의_함수_접근이_이름만_가지고는_불가능하다_왜냐하면_오버로딩을_지원하기_때문이다

- 오버로딩 지원된다는 것은 함수식별이 "함수명 + 인자리스트"로 조합될때만 가능하다는 얘기가 된다.

- 따라서 world에서 함수를 식별하기 위해서는 "함수명(타입리스트)" 를 명시하면 된다.

  - 예) class A 
    - void foo()
    - int foo(int)
    - int foo = 5
  - A.foo(int).getName() // "foo"
  - A a
  - a.foo(void).getSignature() // "void foo(void)"
  - a.foo.getName() // compile 에러다.
  - a.foo.getClass().getName() // "int"
  - a.foo(int).getClass().getName() // "func"

- 고찰 내용

  - class A

    - void foo()
    - void foo(int)

  - a.foo.getName() // 이때의 foo는 어느 foo인가.

  - 그러면 사용자가 어떻게 2개 중 하나를 지정하도록 할 수 있을까?

    - 1안 인자리스트도 같이 써준다.

      - a.foo(int).getName()

      - 이건, foo(int)를 호출하고 나서 반환값을 getName() 한거로 오독될 여지가 있을까? foo(int)와 foo(int())와 foo(3)은 다르게 보일것이긴 하다.

      - a.foo().getName() 은 마치 foo()라는 함수호출 처럼 보이지 않는가.

        - a.foo(void).getName()로 사용하도록 유도한다.

      - a.foo(abc).getName() 이라는게 있다고 하자. 이때 abc는 Type일 수도, 변수일수도 있다. 문제는 없는가?

        --> 별도로 컨셉을 논의. 컨셉만 정해지면 문제는 없다. 

        - generating 단계에서 메소드의 내역이 확정된다. 
        - linking단계에서는 메소드의 내부가 scope를 update 해나가면서 확정해간다. 런타임환경과 동일하게 구성해야 제대로 binding여부를 탐지할 수 있기 때문에 scope를 같이 update하는 것이다.
        - scope의 우선순위는 
          - 타입, 전역
          - 객체의 멤버(메소드 + 변수)
          - Nested 밖의 지역변수
          - 현재 실행중인 지역변수
        - 순으로 접근이 이루어진다.
        - 식별자 중복시 어떻게 해야하는가는 별도로 생각해야할 문제이니 여기서는 패스하자.
        - 중요한것은 scope객체에 질의하면 "abc"가 무엇인지 명확히 알 수 있다는 것이며, 미리 정의된 컨셉에 의해서 무시하거나 계속 가거나를 선택해서 코드블럭을 적절하게 생성이 가능할것이다.

    - x 2안 저러한 것을 expression이라고 정의하자. 그리고 expression은 통째로 isCallable을 때리면 된다.

      - <variable> => prebuilt keyword가 아닌 것들
        숫자로 시작 ok 언더바, ?, #, $,@, %, & 사용가능 
      - <function> => <symbol>\( [<args>]* \)
      - <msg> => (<symbol> | <function>)
      - <msgs> => <msg>[.<msg>]*
      - <expr> => (<msgs> | <msgs> <oper> <msgs> | <msgs> <oper> )
      - <stmt> => (<expr> | <returns> | <fors>)
        statement란 keyword등을 사용해서 나오는 "값을 반환하지 않는" 것들 
      - **아니, 사람이 보더라도 저 foo가 foo() 인지 foo(int)인지 알 방법이 없다니까?**










###  객체의 정의
* 직접 정의 & 복제

* Prototyping 기반
* Origin 객체



#### 멤버변수 컨셉

- v 멤버변수는 Object에 속한것이냐 아니냐 기준으로 배열을 2개 만든다.

  - Object와 Method는 본격적으로 멤버변수를 다룬다. 멤버변수를 어떻게 구성할것인가는 생각외로 상당히 복잡한 문제가 되는데, 왜냐하면 const여부, static여부, private/public 여부, variable여부 등등 여러가지 요인들이 한번에 얽혀있기 때문이다.
    - [확정] 1. class - object 멤버를 구분해야 한다.
      - class에 속한것(메소드 + static variable)은 모든 object가 공유하는 것이므로 이것들은 모든 object가 생성될때마다 추가할 필요가 없어야 한다. 따라서 최소한 이둘은 반드시 구분할 필요가 있다.
    - \2. static 메소드 구현방법
      - 구현 알고리즘에 따라서 static 메소드는 일반 메소드와 별도로 구분할 필요가 있는가?
    - \3. public/private 
      - 얼핏 생각하면 외부에서 call()을 하는 경우에는 public 메소드만 호출가능해야 한다. 고로 private 메소드가 담길것과 public 메소드가 담길것이 구분이 되어야 하지 않겠냐는 것이다.
    - \4. const
      - 객체가 const화 되어있일때와 nonconst일때와 같은 메소드명으로 호출한다고 하더라도 다른 메소드가 호출되어야 한다. 즉 "caller의 const 또한 msg의 일부" 인 셈이다. 따라서 public/private와 마찬가지로 구분될 필요가 있다.
  - 그러나 문제는 저 4가지를 모두 채택할 경우, 멤버변수는 총 2^4 = 16개의 별도의 container에 담겨지게 된다는 것이다. 따라서 최적화를 고려해야만 하는 상황이다.
  - v 1안 굳이 구별할 필요가 없는 상황을 만든다.
    - const, public/private는 Object내부에서 걸러서 에러를 반환하도록 한다. 별도의 배열을 두지 않는다.  두는 이유는 "탐색시 빠르라고" 인데, 어짜피 최적화 과정이 들어가면 탐색 없이 함수를 특정할 수 있도록 해야 한다.
      - vtable 대신 Object.getMembers()[n] O(1)로 접근하게 된다.
  - x 2안 구별해야 하지만, 눈속임으로 구별하는 것처럼 만든다.
  - x 3안 16개의 container가 되더라도 속도가 낮춰지지 않게 하면 된다. 생성/실행시 퍼포먼스가 떨어지지 않는 방향으로 접근한다.
    - 갯수가 많아졌을때의 부담은 
      - \1. 바로 탐색이 느리다는것과
      - \2. 객체 생성시 부담이 생길 수 있다는 것이다.

- v 구성 및 객체생성

  - 시나리오
    - \1. 각 Class들은 부모의 메소드들을 copy한다. 이는 chain deep depth로 인한 퍼포먼스를 줄이기 위함이다.
    - \2. Object의 Members는 lazy하게 동작한다. 이때 Object는 getClass().getMembers()를 chain으로 가져와서 초기화한다.
    - \3. 각 Class는 프로세스 시작과 동시에 ClassTree 구축을 위해서 인스턴스가 자동발생한다. Class생성자에서 자동으로 initialize()를 실시한다. 단, Class::initialize() 안에서도 members를 구성하지는 않는다. lazy하게 간다.
    - \4. 만약 Class::getMembers()가 불려진 경우, getSuperClass().getMembers() 목록을 가져와 일단 clone한다. ClassTree 구축은 이미 끝났기 때문에 getSuperClass() 이때 한다고 해도 인스턴스만 생성한다. 그러나 이후에 호출되는 Members()는 SuperClass의 4번이 다시 반복되게 만든다.
    - \5. 그 후, T::onInitializeMethods()로 wrapping된 메소드 목록을 가져와서 append한다.
    - \6. T::onInitializeMethods() 안에서 Method객체가 생성된다. Method는 클래스가 아니므로 3번 과정이 반복되지 않는다. 결과적으로 T::onInitializeMethods는 TClass<T>::getMembers()가 불려지는 최초 1번만 cb된다.
  - 예외 시나리오
    - class Method {
      - const String& getName();
      - Method[] onInitializeMethods() {
        - v  getName()에 대한 Method를 만들어서 넘길 수 있는가? --> 넘기는 건 가능하다.
          - Method::getMembers() -> TClass<Method>::getMembers() -> Method::onInitializeMethods() -> Method newone(...) -> Method::Method(...)
          - 결론 : Method가 생성된 것이지, Member가 구성된게 아니기 때문에 재귀에 빠지지는 않을 것이다. 그리고 이 루프가 시작된 발발지점도 생성자에 의해서가 아니라 getMember()에 인한 것이다. 무한 재귀는 성립되지 않는다.
        - Method.get("getName(void)").get("getName(void)").get("getName(void)").get("getName(void)").get("getName(void)").get("getName(void)") 할시, getMember()는 여러번 구축되는가? 메모리 낭비가 되지는 않는가?
          - 하나씩 추려서 치환해가보자.
          - == TMethod<getName>().get("getName(void)").get("......");
          - TMethod<getName>은 Method의 일종이다.  그래서 get()은 getMember()를 호출하고, SuperClass인 Method::getMember()를 호출한다. Method::getMember()는 Class<Method>::getMember()를 호출하며, Class::getMember()는 이미 한번 초기화가 된 경우에는 저장된 멤버를 바로 리턴한다.
          - 즉, TMethod<getName>()에 담겨있는 TMethod<getName>()은 TClass<Method>::getMember()에 담겨있던 것을 TClass<TMethod<getName>>이 복제한 놈이다. 메모리 낭비가 아니다. 이는 TClass<T>에 T() 객체 한개가 들어있는 걸 생각하면 된다. 무한 루프 및 무한 재귀는 돌지 않는다.
      - }
    - };
    - Method.get("getName(void)").get("getName(void)") 시, 문제가 발생하는가?
      - == TNativeMethod<getName>().get("getName(void)")
  - class Object
    - friend class Class;
    - Chain _members;
    - virtual Container& getMembers()
      - return _members;
  - Class는 Array Memebers를 갖고 Array ObjectVariables를 갖는다. ObjectVariables는 Members를 chain 한다.
  - virtual Container Node::getMembers(); // invisible
  - TRefer<T> TClass::instantiate()
    - T& newed = *(new T());
    - _chainMembers(newd);
    - return TRefer<T>(newed);
  - class Class
    - void _chainMembers(Object& obj)
      - Chain& tweak = obj._members;
      - tweak.chain(getMembers());
      - tweak.chain(getObjectVariables().clone());
  - 파싱시에는 variable, function은 super의 것을 chain을 유지한다.

- 필요시 member라고 해서 variable과 function과 chain을 유지한 것을 값으로 생성해서 반환해준다. 값으로 내보내도 chain을 묶는것 뿐이므로 퍼포먼스 로스는 적다.

- 하나의 객체는 private variable, public variable 2종류를 갖는다.

- 클래스.instantiate()를 하게 되면 메타클래스의 variable을 복제해서 넣는다. 그리고 생성자를 호출한다. 객체의 variable은 chain되지 않은것을 복제했으므로 chain이 아니다.

- 객체가 함수를 사용할때는 chain되지 않은 함수의 것을 바로 사용하므로 역시 탐색시 로스는 없다.

  

#### 무엇인 member의 기준이 되는가? --> 메시지 스택이 전파될 수 있는가.

- 메시지 스택이 전파될 수 있는가? 그걸 허용하는가?
- class A
  - class B
    - void print()
      - a = 5;
- A.B.print 이걸 보자. 여기에는 3가지 메시지가 들어있다. {"A"}, {"B"}, {"print"} 그리고 각각은 stack으로 뒤에것은 앞에것에 영향을 받는다.
- 이것은 메시지가 전파되는 구조가 아니다. 각 메시지는 독립적으로 소비되지만, 메시지 스택은 공유되기 때문에 앞의 메시지는 뒤에 메시지에 영향을 끼치는 구조다. 
- 만약 Statement가 멤버라면 월드코드에서 누구나가 "a=5" 라는 statement에 접근할 수 있어야 한다.
- 위의 기준대로 각 개념들이 member인지 아닌지 따져보면,
- Statement : 아니다.
- **Method의 인자 : 맞다. method의 첫번째 인자가 무슨 타입인지 rtti로 알아내고 싶을때가 있기 때문이다.**
- **Method의 반환값 : 맞다.**
- **Method의 Method : 맞다.**
- **Method의 멤버변수 : 맞다.**



#### Object의_멤버변수_초기화_문제

- 문제정의 : Object가 Managed에서 생성될때는 TClass<T>::instantiate() 안해서 new T()로 객체를 만들고, 만든 T*->getMembers()로 Chain을 가져와서 chain(메소드.getMembers())하고, 메소드의 ObjectVariables()를 clone한걸 chain시키게 하는 동작을 함으로써 객체의 members 초기화가 완료된다. 이 과정은 쉽게 말해서 Native함수들을 Managed에 visible할 수있는 준비를 만드는 것이다. 그러나 Native에서 객체를 만드는 경우는 어떤가? Object 클래스는 부모클래스이기 때문에 이 생성자 안에서는 도대체 사용자 클래스인 자식클래스가 무엇인지 알 방법이 없다. 자식클래스의 생성자에는, 자식클래스가 사용자의 클래스이기 때문에 함부로 생성자의 코드를 작성할 수 없다. 방법은?
- v 1안 Lazy 초기화를 수행한다.
  - "Members에 접근은 반드시 getMembers()로만 수행해야 한다" 는 조건이 완벽하다면, 이 함수가 불려졌을때 Members가 비어있을 경우 메타클래스로부터 members를 가져와서 초기화한다.



#### 멤버변수 기초

- 고찰내용

  - 어떠한 변수를 생성해야한다는 정보를 누가 들고 있어야 하나?

    - \1. 생성자코드에 추가되도록 한다.

      - 아마도 자바에서 사용하는 방법일 것이다.하지만...

    - v 2. 클래스 자체가 변수도 들고있고, 클래스를 clone한다.

      - 클래스는 변수가 무엇인지 알아둘 필요가 있긴 하다. World에서 변수 접근, 변수에 할당은 모두 "메시지"로 취급한다. 함수나 변수나 구분은 할 필요가 없는 것이다.

      - 클래스가 함수를 담을 수 있다면, 구조상 변수도 담을 수 있는 잠재성이 있다.

      - 그럼, 그걸 어떻게 하는가?

        - v 1안
          - 클래스는 Node[] members; 를 갖게 한다. 그리고 여기에 Function이나 멤버변수가 들어가면 된다.
          - 이 Node가 일반 클래스인가, 아니면 데이터타입의 클래스(int, float, double, string ...) 인가를 구분짓는 것은 setter와 getter 메시지를 처리 할 수 있는가 아닌가다.
          - 클래스를 instantiate()를 하게 되면 T()를 생성하고 MetaClass가 가진 members중 Node[]만 복사해서 insert 시켜 주면 된다.
          - 임의 Node  a에게 메시지가 온 경우,  #메시지_전파_알고리즘 에 따라 scope의 관점에서 올라가면 된다.
            - 만약 객체소유의 관점에서 올라가면 멤버변수가 메시지_전파_알고리즘 에 반응해버린다. 
          - 문제점
            - 함수인 Member만 모아서 접근하는 건 쉬움. 이미 있으니까. 하지만 멤버변수인 Member들만 모아서 접근하는 방법은? for문을 도는 방법밖에 없다고 말하지는 말아줘.
              - 이러한 ContainerForContainer를 Chain이라고 이름을 붙였다. 이걸 통해서 해결한다.
              - 구체적인 설계는?
                - 1안 - 최대한 쪼갠다.
                  - 하나의 클래스는 private variable, private function, public function, public variable 4종류를 가직 있다.
                  - 파싱시에는 variable, function은 super의 것을 chain을 유지한다.
                  - 파싱이 끝나면 incarnate()를 통해서 원소를 복제하고 chain을 푼다. 이후로는 메타정보 injection이 불가능하다는 얘기다.
                  - 필요시 member라고 해서 variable과 function과 chain을 유지한 것을 값으로 생성해서 반환해준다. 값으로 내보내도 chain을 묶는것 뿐이므로 퍼포먼스 로스는 적다.
                  - 하나의 객체는 private variable, public variable 2종류를 갖는다.
                  - 클래스.instantiate()를 하게 되면 메타클래스의 variable을 복제해서 넣는다. 그리고 생성자를 호출한다.

      - 2안

        - 준비

          - 메타클래스는 Member를 2개 가지고 있음.  1개는 변수만 들어있는 Member이자 다른 1개를 super로 가리키는 것, 또 1개는 함수만 들어있는 Member. Member에는 함수와 멤버변수가 들어갈 수 있음.
          - 클래스 파싱될때 모든 함수를 먼저 함수Member에 넣음.
          - 그리고 멤버변수Member super를 함수Member로 지정함. 
          - 파싱된 멤버변수를 멤버변수Member에 넣음. 이제 멤버변수Member는 모든 멤버변수를 가지고 있음.

        - 결과

          - 메시지전파는 함수Member만 접근하면 됨. 문제없음.
          - 새로운 Node생성시, 멤버변수Member를 복제하여 새로운Node에 집어 넣으면 됨. 해당 Node는 독립적인 멤버변수를 가지고 있으며, 게다가 함수Member는 기존처럼 super로 가지고 있기에 메모리에 포함되지 않음.

        - 문제점

          

#### static변수는_어떻게_구현하는가

- Generating단계에서 class 객체를 추가하면서 members에는 static변수와 method만 담는다.
- WorldObject생성시 붙여지는 멤버변수는 별도의 const Members& getMemberVariables() const에 담겨지며 이것의 nonconst 버전은 friend 클래스들에게만 공개된다.
- ClassManager에 의해서 제공되는 class는 nonconst로 제공된다.
- 고찰내용
  - v 1안 일반 멤버변수는 class의 멤버가 아니다.
    - Class의 일반 변수는 world에 visible 해서는 안된다. 함수와 static 변수만 visible 해야한다. 
    - Generating단계에서 파싱을 하면서 class 객체를 추가하는데 이때 Class.member에는 Method와 static 변수가 nonconst로 접근할 수 있다. 멤버변수는 별도의 내부 members에 담겨지며, 이것들은 별도의 const Members& getMemberVariables() const 와 같이 접근해야 하며, nonconst로 접근할 수 있는 것은 일부 friend로 선언된 클래스들 뿐이다.
    - 대박이네.. 어제하루종일 고민한건데... 이렇게 간단히 풀리다니.
    - v 문제없어 보이긴하는데..시나리오로 검증해보자. 
      - C++ 관점에서
        - classManager로 nonconst인 Class를 얻을 수 있다.
        - class는 member인 method와 static 변수를 있는 그대로 제공한다.
        - 객체시 추가될 멤버변수는 const Members getMemberVariables()로 얻어온다.
      - world의 관점에서
        - member인 method와 static변수는 당연히 getMember()로 얻어 올 수 있다.
        - 원한다면 getMemberVariables()도 visible하게 할 수 있을 것이다.



#### 객체의 Member initializing 알고리즘

- Node는 member를 가지고 있다.
- 각 함수는 자신이 private 여부를 가지고 있다.
- ObjectType Class는 variable member와 function member, 그리고 Chain<T> member 3개를 가지고 있다. 이중 앞의 2개를 member가 chain하고 있다. function이 앞에, variable이 뒤에 속해있다.
- variable에 바로 push를 해도 알아서 잘 들어간다.
  - Container는 Attacher처럼 어떠한 타입에 대해서도 일단은 호출이 가능하고 AttachableType() 체크를 통해서 받아들일지 아닐지를 결정한다. 따라서 chain인 member도 일단은 push가 가능하다. push 할 원소를 앞의 chained 컨테이너와 뒤의 컨테이너에 각각 물어봐서 넣을 수 있다고 판단되면 그곳에 넣는다.
- 각 variable, function은 부모의 variable, function에 대한 chain이 아니다. 상속시, 부모의 함수를 push 하고 자신의 것을 넣는다.
  - 중복으로 인한 메모리를 낭비하는 이유는, 이게 퍼포먼스가 빠르기 때문이다.
- 객체를 생성하는 방법은 variable만 복제하는 것이다. 복제된 variable은 원본 function을 chain한 상태가 된다.
- 고찰내용
  - 클래스 문제점
    - factor가 많다. 
      - private-public 이냐
      - 멤버냐 function이냐
      - member
      - private-variable
      - public-variable
      - private-function
      - public-function
      - private-member
      - public-member
      - 하나의 컨테이너로부터 다양한 컨테이너를 뽑아내는 방법은?
      - 필수인 것들만 뽑아보자.
        - all-variable : 객체 생성을 위해서
        - all-function
        - all-member : 일괄 적용을 위해
        - public이냐 private이냐는 건 파서가 직접 판단해서 런타임 에러를 올려보내도록 한다.
        -  function이냐 variable이냐 를 구분하지 않을 방법은?
          - 이는 빠른 객체 생성을 위해서 필요했다. 객체 생성시에 variable을 복사해야 하기 때문이다.
          - Node는 member만 가지고 있고,
          - 클래스 & 객체는 변수member + 함수member 로 이루어져 있다. 이 2개는 member와 동기화 되는 거고.
        - member가 chain이며 function이 앞에 들어가 있는 상황에서  member.push(variable)를 하게 되면 어떻게 되는가?
          - 각 container는 어떠한 타입을 받을 수 있다는 정보가 있어야 한다. 기존 World는 이게 없었기 때문에 Container<T>는 있어도 ContainerBase 같은 건 있을 수 없었던 것이다. ContainerBase는 push(Node&)가 있어야 하며, 어떠한 타입에 대해서 연산이 가능한지를 알려주는 getPushableType() 같은 게 있어야 한다. 마치 Attacher 처럼.
  - 전역변수인지 아닌지는, 해당 object가 어느 scope에 속하는가에 따라서 정해질 뿐이다.
  - 상위 scope에서 객체를 접근할 경우 재귀적으로 접근이 동작하지 않는다.
  - 재귀적으로 할 경우 중복된 메시지수신이 존재했을때 순서에 의해서 수신자가 반응하게 되므로 예상치 못한 결과가 나오게 된다. 송신자는 접근시, 접근할 객체를 찾을 타겟을 정확하게 지정해야 한다.



#### Scope, 객체와 메소드 간의 메시지 전달 체계

- 상당히 까다로운 문제였다.
- \#Message는_name_thisptr_args를_모두_하나의_Array로_구성한다
- **thisptr은 Object와 관련이 없다.**
- **Method.call(msg)에서 Method가 static Method가 아니라면 msg 마지막에 thisptr를 넣어둬야한다.**
- CallStmt나 Method를 굳이 Native환경에서 쓰고 싶다는 변태적인 개발자는 직접 msg를 생성할때 args를 size+1한 뒤에 끝에다가 this로 사용할 object를 넣어둬야 한다. Method::run(msg)에다가 Method::run(thisptr, msg)로 하자는 의견도 있었다. 그러나 Method에는 StaticMethod도 나올 수 있으며 이 경우 thisptr는 완전히 필요없는 인자가 된다. Method라는 클래스에는 Static메소드도 포함된 상태이기 때문에 특정 자식클래스에서만 사용한는걸 공통클래스로 끌어올리는데는 조금 석연찮다.
- **Msg는 모두다 인자로써만 취급하기에 자신의 마지막 arg가 thisptr인지 아닌지는 알 도리가 없다. 메소드가 마지막 인자를 thisptr로써 취급하는 것 뿐이다.**
- **Scope.stack(Object&)는 ObjectSpace를 등록하며, scope의 localspace의 "this" 라는 변수를 만들어(이미 있다는 덮어써서) 주어진 object로 assign한다.**
- **Object는 call할때 scope에 대해서 아무런 동작을 하지 않는다. 그저 자신의 member들만 뒤진다.**
- **NativeMethod 역시 scope에 대해서 아무런 동작을 할 필요가 없다.**
- **StaticMethod는 Object관련된 scope 조작이 없다. LocalSpace만 add한다.**
- 왜냐하면 Method::stack을 보면 다른 모든것들은 scope에서 나오고 있기 때문이다. 
- 이 둘을 모두 scope에서 출발하도록, Method&origin도 그렇게 만들면 _stack의 args를 scope만 받도록 만들 수 있다. 
- 그렇게 되면 object와 method 모두 같은 함수인 _stack을 두도록 할 수 있다.
- 왜 msg에 뒀을까? 이유가 있을 것이다. --> #Message는_thisptr를_어떻게_다뤄야_할까
- **일반 nonstatic ManagedMethod는 외부로부터 this에 사용할 Object가 msg 뒤에 담겨있다는 걸 안다. nonstatic ManagedMethod는 this로 사용할 object를 꺼내서 scope.objectSpace.push() 한다. 함수가 끝나면 objectspace.pop()을 한다.**
- ManagedMethod가 자신이 static인지 아닌지 아는 방법은 isStatic()을 사용하면 된다.







#### 함수 디덕션. 코드를 보고 어떻게 무슨 오버로딩된 메소드인지 파악하는 가.

- 요구사항
  - 함수디덕션의 핵심은, expr에 담긴 argument들을, expr에서 호출하려고 하는 함수명세를 통해 도출된 함수후보군 중에서 가장 비슷한 함수의 parameter로 명시적 캐스팅을 묵시적으로시켜서 호출이 허용되도록 만드는 것이다.
  - 모든 명시적캐스팅들은 주어진 상황에 따라 묵시적으로 캐스팅이 될 수 없다. 오직 pretype 들에 대해서만 world가 미리 정의한 묵시적 캐스팅만 해당한다.
  - 여기서 핵심은 함수후보군을 찾아내는 것과, 그 후보군 중에서 가장 적합한 것 1개를 도출해 내는 과정과, 그 프로세스를 어느 클래스에서 가지고 있어야 하는 것 3가지다.
  - 가장 먼저 #묵시적_캐스팅-정책 이선결되어야 한다.
- 고찰결과 각 인자는 implicit casting(업캐스팅과 prebuilt 타입간의 제한된 casting)만 고려해서 가장 bestfit을 찾아내면 된다.
- 속도가 매우 중요하다. 캐스팅은 상당히 많이 사용되기 때문이다.
- .cast<T>는 묵시적캐스팅이다. 
  - world에서는 invisible하다. 
  - 빠르다.
  - 함수 deduction시 사용된다.
  - 다라서 Method 안에서 사용되는 캐스팅은 to()가 아니라 cast<T>다.
  - 묵시적 캐스팅은 업캐스팅과 기본제공타입의 명시적캐스팅이 있다. 
  - 기본타입의 명시적 캐스팅은 매우 빠르게 제공되어야 하므로 override를 사용해서 제공된다. (즉, 이 기본타입들은 생성자를 통해서 캐스팅을 공개하지않아도 된다는 것이다. 이 방법은 오래걸리니까).









##### deduction 함수 바인딩

- c++처럼, 함수의 signature와 정확히 일치 되지 않더라도 유도리있게 파서가 "이 심볼이지??ㅋㅋ" 하면서 매칭해주는 알고리즘이다.
- 고찰로 알아낸, 이 문제의 가장 포인트는, 
  - 묵시적 형변환으로 함수를 바인딩하는 것은 "**사용자의 의도와 실제가 달랐을 경우, 유도리있게 비슷한 걸 정해준다**"는 컨셉임을 잊지 말하야 한다. 이는 "형변환이 가능하다"와는 다른 얘기인것이다.
    - 예를들면 [float.to](http://float.to/)(string)은 가능하다. 하지만 그렇다고해서 foo(string) 함수에 사용자가 foo(3.5)로 호출하는 것이 용납되는 것은 아닌 것이다. 명시적으로 캐스팅을 해야하지. 이를테면,
      - foo(string)
      - foo(int)
      - foo(3.5)는 어디로 가야 하나? --> 정답은 foo(int)로 가야한다. 둘다 형변환은 가능하지만 묵시적변환은 int -> string은 동작하지 않아야 하는 것이다.
    - 하지만 foo(float) 함수를 foo(5)로 하는 건, 유도리 있게 해줄만 하다고 여겨지게 된다.
- 묵시적 형변환은 "계열" 을 기반으로 판단된다.
  - Numeric계열(int, char, float, bool)
  - 문자열계열(string)
  - custom계열(클래스 계층구조로 판정)
  - 계열이 다르면 묵시적 형변환은 일어나지 않는다.
- 알고리즘은 다음과 같다.
  - 파서는 foo(int, float)라는 코드를 봤을때 적절한 call 코드블럭으로 파싱해야한다.
  - 함수명 foo를 갖고 있는 현 scope의 모든 함수목록을 가져온다.
    - foo(char, string), foo(bool, result), foo(result, float), foo(int, float, string), foo(float, int)
  - 가져오는 도중 정확히 일치되면 그걸로 끝낸다. --> END
  - 차선책을 찾기 위해 본격적인 묵시적형변환을 통한 함수바인딩 로직에 들어간다.
    - 가져온 후보군 들을 탐색하면서,
      - 메소드들에게 parameter를 넘겨주고 실행가능한지 evaluate()하라고 한다.
      - int now = 메소드::evaluate(int current_most_low_evaluated_value) {
        - 인자 다르면 return -1
        - int sum = 0;
        - for 모든 Arguments {
          - sum += evaluated = Argument.evaluate(param[n]) {
            - String/Numeric::evaluate() {
              - if 같은 계열 아니면, return -1
              - return 0;
            - }
            - 기타 모든 계열(==custom::evaluate() {
              - if ! param.getClass().isSubOf(getClass()) return -1
              - return param.getSuperClasses().level - getSuperClasses().level;
            - }
          - }
          - if evaluated < 0, 탈락.
          - if sum > current_most_low_evaluated_value, 탈락. 더 볼것도 없다.
        - }
        - return sum;
      - }
      - if now < 0, 후보군에서 제거
      - if !now, 이 놈입니다. 잡아가세요.
    - if 남은_후보군.getLength() >= 2, 모호성의 오류
    - if ! 남은_후보군.getLength(), 함수가 없습니다. 에러.
    - return 남은_후보군[0];
- 위와 같이 하게 되면, 다음과 같은 상황에서도 모호성의 오류가 나온다.
  - void print(int, char, float) {} // 1
  - void print(float, float, int) {} // 2
  - print(3.5f, 3.5f, 3.5f);
- 얼핏보면 float이 일치된 갯수가 2번이 더 많으니까, 2번째 print로 가야하지 않냐고 생각할지도 모른다.
- 고찰 내용
  - World 함수 안에
    - foo()
    - foo(char)
    - foo(string)
  - 3개가 있을때 내가 foo(20440) 을 한 경우, 어떤 함수가 호출되어야 할지를 정하라는 것이다.
  - 1안 범용의 룰을 만들고 모든 타입에 대해서 적용시킨다.
    - 1안 아무런 호출도 하지 않아야 할까?
      - 그럼 foo(int)
        - foo(string)
        - foo(char)
        - 이 상황에서 foo(36452.5) 는 어떤가? 이래도 아무런 호출을 하지 않아야 맞는가?
        - 아니면 foo((int) 36542.3) 나, foo((int) grade) 를 앞에 붙여줘야 맞는가?
      - 다른 예는 어때?
        - foo(Parent)
        - foo(Child)
        - 에서 foo(GrandChild) 는 어떤가?
    - 2안 하니면 숫자와 가까우니까 char?
    - 3안 아니면 경우의 수가 가장 크니까 string?
  - 2안 축소화된 매우 알기쉬운 범용룰 1개를 만들고, 일부 타입에 대해서만 특수룰을 적용시킨다.




### 기본 타입
#### this, me
-   모든 코드는 함수 안에서만 실행된다. 함수는 항상 객체 안에만 있다. 따라서 모든 함수에는 this와 me 라는 기본 포인터가 2개 제공된다.
    -   this 는 C++의 this이다.
    -   me는 현재 Method를 지칭한다. 이는 Nested Method에서 사용될 수 있다.
-   식별자 탐색시 Scope 알고리즘대로 interperter LocalSpace가 이 식별자를 갖고 있는지, this가 갖고 있는지, me가 갖고 있는지, GlobalSpace가 갖고 있는지 총 4번 알아보게 된다.
    -   Scope라는 객체를 만들어서 이게 4가지를 다 들고 있게 하자.
    -   찾은 식별자가 2개 이상 존재할 경우 인터프리터는 모호성의 오류를 내뱉게 된다.
-   코드블럭이 완성되면 me 인지 this인지 local인지 인터프리터가 명시해두므로 탐색할 필요가 없게 된다.
-   this는 생략이 가능하다. 고로 다음의 코드는 모호성의 오류가 없다.
    -   class A
        -   void foo()
            -   getClass() // foo가 아니라 A가 반환된다.
            -   // foo(void).getName() 라고 해도 된다.
            -   // me.getName() 라고 해도 된다.







### Shareable

#### Shareable의 기본

- **고찰과정**

  - 변수를 생성하기 전에 그 클래스가 nonconst immutable이라면 파서는 객체를 바로 생성하고 이걸 owner나 scope에 등록한다.

  - 그 이외에는 파서는 새로운 객체를 가리키는 Reference를 만들고이걸 owner나 scope에 등록한다.

  - v World 내 구현

    - Occupiable은 상속되는가?

      상속된다. 상속이란 부모의 특성이 모두 물려받는 걸 의미하기 때문이다. 

      - 한번 "이 클래스는 immutable" 이야! 라고 선언하게 되면 이 클래스로부터 나오게된 모든 객체는 다 immutable이야 한다. 하지만 이를 클래스의 "상속"에 적용할 수 있는 문제인가?
        - 조합을 생각해보자. 
          - P는 부모, C는 자식
          - OK : P=mutable C=mutable
          - P=immutable C=mutable
          - X: P=mutable C=immutable
            - 이건 말이 안된다. 
            - 만약 이게 말이 되게 하려면 그냥 mutable이 아니라 immutable이 가능하나 mutable이 되지 않는 것이라고 해야 하나?
          - X: P=immutable C=immutable
            - C가 엄청나게 크기가 무거워진 게 될 수도 있다. 이것은 아니다.
        - 단순히 생각해보자.
          - Integer는 부모가 Type일 것이다.
          - Type은 immutable인가?
        - 용도적으로 생각해보자.
          - immutable의 용도는 값복사가 항상 일어나야 하는 객체가 필요하기 때문이다.
          - int a = b 라고 했을때 b와 별도의 a라는 값이 주어져야 하기 때문이다.
          - 왜 이런것인가? 이 질문이 아마 이 문제를 해결할 수 있는 가장 근본적인 물음이다. 이걸 답해야 한다. 왜이런것인가? 왜 이렇게 해야 하나?
            - 용도에 따른것이다. int, float은 다른 값을 참조하는 것보다 복사하는데 더 자주 사용된다.
            - 이것들은 작고, 가볍다. 단순하다. 그렇기에 원본의 값을 변경해야할 필요가 없다. 동기화를 필요로 하지 않는다. 어느 구조나 책임을 담당할 만한 부피가 아닌 것이다. 그저 작은 부품. 작은 부품에 지나지 않는 것들이다.
            - 자료형이라고 하는, "동작의 책임" 도 없으며, "다른 인스턴스를 관리" 하는 책임도 주어지지 않는 그저 자료형의 하나인것들이다.
            - 반례를 들어 반론한다
              - Object를 들어보자. 이것은 내부 멤버변수가 없다. 이것도 immutable인가?
                - ADT다. 객체 생성이 아예 안된다.
              - class Stream {
                - int fd;
                - initializeFileDescriptier();
              - };
                - 작은 사이즈를 지녔다. 하지만 책임이 존재한다. 함부로 복사가 일어나서는 안된다. 물론 그 사실은 개발자만 알 수 있다.
              - String은 데이터가 대개 크다. 하지만 자료형중 하나다. immutable인가?
                - 애매하다.
                - string a = "hello"
                - string b = a
                - a = "ok"
                - 이때의 b는무슨 값을 가지고 있을거라고 보는가?
                  - "hello"인가, "ok"인가.
              - IntegerArray {
              - } immutable인가?
                - 아니오. 매번 복사가 일어날 수 없다. 복사되는 매체인 원소는 공유되어야할 가능성이 있다.
      - 상속문제 --> occupiable은 상속으로 해결된다.
        - 현재는 occupiable을 개발자에 재량에 맞기자. 이다.
        - x 상속반대의견
          - 하지만 다음의 시나리오가 존재할 가능성이 없다면 추가적인 기능을 제공할 여지가 있다. 한번 재고는 해봐야 한다.
            - 자식이 occupiable이다. 부모는 occupiable 되는 경우가 있는가?
            - 자식이 sharable이다. 부모는 occupiable이 되는 경우가 있는가?
          - occupiable은 상속이 되어서는 안된다. 상속 금지! 왜? C#은 그렇게 하더라. int가 상속이 되어야 하는 이유가 무엇인가?
        - v 상속 찬성 의견 
          - int를 상속해서 sharable처럼 사용하고 싶은 경우는 무엇인가? 그렇게 하고 싶다면 int를 포함시켜버리면 되는 것이다.  **상속이란느 것은 부모의 속성을 전적으로 물려받는 것을 의미한다. 고로 int가 가지고 있던 occupiable 속성도 그대로 자식에게 물려지게 되는것이 당연한것이다.**

    - 어떻게 구현하지?

    - x 1안 Reference가 sharable 자체다

      - const 이슈 때문에 occupiable도 reference로 감싸여질 수 있다.

    - 2안 Class안에 이 정보가 들어있으며 Reference가 이걸 보고 동작을 판단한다.

      - **만약 Object = Target의 연산이 수행되어야 한다면, Target이 occupiable이건 sharable이건 어쨌든 할당연산(occupiable처럼 동작)이 일어나야 한다. native 관점에서는 애초에 share할수 있는 ptr가 없으니 당연한 것이다. 따라서 이 문제는 this가 reference일때만 발생하는 것이다.**

      - 고로 reference 안에서 이 객체가 occupiable인지를 판단해서, occupiable이면 get().operator=()로 redirection하는 코드가 적절하다고 볼 수 있다.

      - Reference는 TString<Object> 이므로, Object class 안에 isOccupiable()를 넣어두고, 이 정보는 TClass로부터 가져오게 하면 될 것이다.

      - OccupiableObject는 overriding으로 return true; 를 바로 반환한다.

      - isOccupiable()은 Node에만 속한 것이다.

      - isOccupiable()은 TClass도 갖고 있는다. 만약 TClass<T>의 T가 Node의 일종이 아니라면 항상 false가 나온다. default가 false란 얘기다.

      - isADT와 isOccupiable은 서로 다른 개념이다.

      - v Method는 occupiable인가?

        아니오. 대개는 sharable이라고 보면 된다. 그래서 isOccupiable()의 default는 false다 

        - Method* a, *b;
        - a = b; 가 될때 어떻게 되어야 한다고 보는가?
        - 당연히 sharable일 것이다.

  - v World코드 -> World 코드블럭 시나리오

    - 파서는 sharable이거나 const의 경우는 reference 감싸줘야 한다.

  - Native개발자의 경우

    - out





#### 멤버변수는_occupiable_멤버함수는_sharable_로_할_수_있을까?

- 그런 특성을 가지고 있는 것은 사실이다. 그러나 occupiable, sharable 로직을 객체 복제(메소드, 멤버변수의 복제)에 재사용하는 것은 안된다. 왜냐하면 occupiable, sharable 로직이 발동되려면 opearator=가 일단 호출이 되어야 하기 때문이다.
- 현재의 chain을 통한 자연스러운 컨셉(메소드는 공유, 멤버변수들은 operator=를 호출함으로써 occupiable, sharable 로직을 발동시키는 것)이 더 메모리나 퍼포먼스 적에서 이득이다. 
- 고찰내용
  - Method는 클래스에 소유한 것으로, 모든 Object들은 이 메소드를 공유하는 것이다. 반면 멤버변수는 객체마다 나오기 때문에 occupiable 특성을 가지고 있다. 
  - \#occupiable과_sharable 에서는 occupiable과 sharable이란 개념을 World에서 어떻게 구현할것인지를 정하고 있다. 이 구현물을 가지고 그대로 멤버변수와 멤버함수의 동작으로 재사용 가능할까?
    - 안된다.
    - occupiable과 sharable의 진정한 의미는 개체의 복사인 operator=가 일어났을때의 디폴트 컨셉이 무엇이냐는 것이지, 공유할 수 없다, 복제되어야 한다 같은 것이 아니다. 이를테면 객체D가 클래스로부터 생성이 되었다고 하자. 자, 그러면 sharable객체C는 클래스안에 들어가있는 객체C로부터 복제된 것이어야할까? 아니면 공유되어야 하는 것일까?
      - 복제가 되어야한다. 공유가 된다는 것은 단순히 static 변수를 의미할 뿐이다.
    - 그러면 객체D로부터 복제되어서 객체E가 나왔다고 가정해보자. E안에 있는 객체C는 객체D 안의 객체E 로부터의 복제품인가? 아니면 공유물인가?
      - 이거는 공유물이다. 
    - 즉, 객체의 복제가 일어났을때 복제인가 공유인가를 결정짓는 것은 sharable, occupiable이다. 왜냐하면 복제가 일어나면 멤버변수 객체에 한해서 operaort=가 일어나게 되니까. 
    - 이것은 객체가 생성되었을때 가지고 있어야 하는것과 클래스로부터 공유해야하는것과는 조금 다르다. 메소드는 처음부터 operator=과정을 거치지 않는다. Chain안에 포함되어있고 Chain이 복제될때 sallowcopy가 디폴트이므로.
    - 따라서 occupiable, sharaable 로직을 재사용하겠다는 것은 메소드들도 일단 operator=를 거치게 하겠다는 것이며 Chain을 사용하지 않겠다는 의미이기도 하다.
    - **고로, 재사용해봤자. 지금보다 더 로직이 복잡해지거나 메모리 낭비가 심해지게 될것이다.**





#### 객체를 생성하여 반환하는 native함수를 wrapping할때 사용자의 sharable, occupiable 부담을 덜어줄 수 있는 방법은?

- char* gen_xml_parsed(char* buf, char* path);
- 위 함수를 wrap하기 위해 사용자가 짜는 함수다.
- class XMLParser : Object
  - static void onInflacture(List<Method>& tray)
    - DECL(String parse(String path))
  - Reference parse(String& node) // BEST OK
    - char buf[65535] = {0, };
    - gen_xml_parsed(buf, [node.to](http://node.to/)<char*>());
    - return Reference<String>(new String(buf));
- 문제점
  - 사용자는 String이 sharable이기에 반환형이 Reference 라는 걸 반드시 알고 있어야 한다.
    - String& parse(const String& path) --> OK
      - return new String(buf);
    - 이렇게 대체할 수도 있지만 이 역시 sharable이라는 걸 알고, new를 써야 한다는 걸 알아야 한다.
- **답 : 문제 정의자체가 잘못되었다.** 
  - 반환형이 Reference던 String이던, String& 이던 상관없다. 어짜피 TNativeMethod는 반환한 값으로부터 Refer returned = cb(..)->to<String>()를 할것이기 때문이다.
  - 따라서 sharable인지 occupiable인지는 상관안해도 된다.





#### Refer

##### 복사연산을 어떻게 할가?

- \#occupiable_and_sharable 와 #Refer는_const를_정보를_가지고_있다. 로 인해서 이 문제는 상당히 어렵다.
- 요약
  - C++ 
    - Refer::Refer(const Node& rhs) // Node가 Refer일때는 Refer::Refer(rhs)를 실행한다.
    - Refer::Refer(const Refer& rhs);
    - Refer::Refer(bool isConst = false);
    - Refer::operator=(const Node& rhs); 
    - Refer::operator=(const Refer& rhs);
    - Refer::bind(const Node& rhs)
    - 를 가지고 있다. 즉, 타입이 설사 다르더라도 일단 시도는 하게된다.
    - 이는 WrdFrx은 기준 타입이 Node로, 구체타입이 뭔지 모르더라도 일단 동작하게끔 설계되었기 때문이다.
  - Refer와 Bind의 차이는 크게 2가지다.
    - \1. Refer는 const여부를 담고있으며 생성자에서 결정된다. 
    - \2. const A와 A는 다른타입이다. 따라서 한번 const Refer라면 죽을때까지 그 Refer는 const A만 물을 수 있다. 
  - World에서 const는 타입의 일부분이다. 고로, const Refer는 죽을때까지 const Refer이다. 그러나 const Refer<A>는 native에서, non const Refer를 const Refer로써 사용하고 있는 상태다. const를 벗기면 nonconst가 된다. 당연히.
  - nonconst는 const가 될 수 있다. 반대는 안된다. (이건 C++과도 동일하다)
- 검증
  - class A
  - class B : A,
  - 1
    - A a = B b // cmpl ok exe ok
    - Refer<A> a = Refer<B> b // compile ok, but exe ok.  
  - 2
    - B b = A a //comp err
    - Refer<B> b = Refer<A> a // compile ok, exe err
  - 3
    - A a = const A // cmpl err
    - Refer<A> a = Refer<const A> // cmpl ok, exe err
  - 4
    - const A a = A a // cmpl ok, exe ok
    - Refer<const A> a = Refer<A>; // cmpl ok, exe ok
  - 5
    - const A a = B b // cmpl ok exe ok
    - Refer<const A> a = Refer<B>; // cmpl ok, exe ok
  - 6
    - const Refer<A>는 World코드에는 존재하지 않는다.
    - const Refer<A> a = Refer<B> // cmpl err. const Refer<A>&이므로 operator=, bind() 전부 안되는게 정상이다.
  - 7
    - const Refer<B>는 World코드에는 존재하지 않는다.
    - Refer<A> a = const Refer<B> // cmpl ok, exe err
      Refer<A> a = Refer<const B>와 같다.

##### Method::run() const일때 ret인 Refer는 const REfer인가? 아닌가? 아니면 메소드는 신경쓸 상관없나?

- 신경쓸 필요가 없다. C++로 예를보면 아주 명료해진다.
  - class A {
    - B& getBFromSomeWhere() const { // case#1
    - ​     return B::getInstance();
    - }
    - A& operator=(const A& rhs); // case#2
  - };
- 아마도 이 질문을 한 의도는 case#2만 생각하고 한 것이다. 이 경우에도 Method는 신경쓸 필요가 없는데 반환형이 A&로 되어있다고 하더라도 거기에 담기는게 *this만 아니라면 아무런 문제될게 없기 때문이다.
- 그리고 *this를 담기지 못하도록 에러를 내뱉는 건 Method클래스에서 내뱉는게 아니라 파서가 해야 한다. const 메소드에서 this는 const A*가 되기 때문에 return (A*) this; 과 같은게 되버리며 A*에 const A*인 this를 넣으려고 했으므로 컴파일 단계에서 에러를 내뱉어야 한다. 
- 만약 컴파일단계에서 잡아내지 못하면 런타임시에 저 코드는 결국 null이 나가게 될것이다. nonconst Refer에 const를 넣으려 했기 때문이다.
  - 참고 -> #Refer는_const_T_캐스트가_되어야만_한다.





### 지정자
#,$,@,_



#### static

##### static의 기본

- World에서 static 함수는 앞에 share 키워드를 붙이면 된다. 일반인에게는 더 친숙할것이라 본다.

- 예제

  - class A
    - int age;
    - share int static_age;
    - int print(int a)
      - ...
    - share int static_print(int a)
      - int age
      - share int static_age = 5
      - ...
  - A a
  - A.static_age == a.static_age
  - A.static_print(2)
  - a.static_print(2)
  - a.print(5)

- 구현방법?

- 고찰내용

  - static 함수는 필요하다. --> random() 같은, 함수만 제공하고 싶은 경우가 있다. 

  - 일반 method와 구분이 되어야 한다. --> 기능적으로는 method처럼 써놓고 안에서 this를 사용하지 않는다면 문제될 것은 없지만 외부 사용자들이 보았을때 객체를 생성해서 method로 호출해야 하는지, 객체 없이 바로 호출 할 수 없는지 분간이 가야 하기 때문이다.

  - 1안 글자를 덧 붙인다.

    - 1-1안 static을 그대로 사용한다.
      - class MyModule
        - static int random()
          - return ... ...;
    - 1-2안 share를 사용한다.
      - class MyModule
        - share int random()
          - return .....;
        - share int age
        - int obj_age;
        - //int age --> 같은 클래스에 2개를 정의할 수 없다.
        - share int add(int new)
          - share int prev = 0
          - return prev += age + new
        - //share int add(int new) --> share를 적으면 에러다. 안에 객체의 변수에 접근하니까.
        - int add(int new)
          - return obj_age += new

  - 2안 글자를 덧붙이지 않고, 기호나 형태의 변형을 통해서 static이라는 걸알 수 있게 한다.

    - 2-1안 

  - 1안

    - 1 = static
    - 2 = keep (매 함수호출시마다 이 값을 공유하므로)
      - share를 쓰자는 안도 있었지만 static 멤버변수도 어떻게 보면 "공유" 자원으로 볼 수 있기 때문에 share와 혼동이 있을 수 있다.

  - *x 2안 키워드를 앞에 두는 방식이 아니라 클래스명을 두는 식으로 한다.*

    너무 선언문이 길어진다. 

    - 1 = int MyClass.static_value = 5
    - 2 = int Me.static_value;
      - 반대의견1 - 이 변수는 method에 속한 것이 아니라 블록문에 속해 있어야 한다. 그리고 블록문을 식별자로 지정할 수 있는 방법은 없다.
      - 찬성의견1 - c++도 static 변수는 메소드에 속하게 한다. 굳이 블록문에 한정할 필요가 있는가?







##### static정보를_어떻게_공개할것인가

- [v] 구현

  - [v] Method에만 isStatic 만들기
  - [v] c++ sfinae로 static 메소드인지 판단이 가능한가?
  - [v] 월드 method 정의 매크로로 자연스럽게 static func인지 판단이 가능하게 할 수 있을까? 다른 매크로를 또 만들게 하고 싶지 않다.

- 고찰내용

  - *1안*

    - Node
      - CompositNode

  - *2안 isStatic() const 함수는 this가 scope의 globalspace에 속해있는가, 혹은 메소드의 변수로써 박혀있는가 등으로 판단한다.*

    - 실행중이 아닌 Object라면 isStatic()여부를 알수 없다.

  - *3안 method에 대해서만 static 여부를 알린다. 즉, isStatic()을 묶지 말고 각 필요한 클래스 별로 별도로 가져간다.*

  - *5안 현 설계에 Node에 static을 둔다.*

    - 멤버변수의 static : 객체가 없어도 호출이 가능한 것.

      - *x ==> 객체에 속한 것이 아니라 class에 속한것*
      - **v ==> 실행 및 접근과정에서 this가 필요하지 않는 것.**
        - 이 점을 생각하고, Node에 isStatic() const를 두도록 한다.

    - 객체의 static : scope가 제한된 전역변수

    - static이란 msg로 call을 할때 msg안에 this가 필요한가 필요하지 않은가 이다. Node default로 true를 반환하도록 하자.

    - v Node에 static을 둘수 없다.

      답이 없다. 

      - c++ 적으로 알아낼 수 있는 방법이 없다.

      - 왜냐하면 native 사용자가 자신이 만든 클래스의 메소드 안에 static MyObject로 둔 경우, 이 객체는 절대로 isStatic()에서 true를 반환하도록 할 수 없다.

      - 이는 c++에서는 변수가 static인지 아닌지를 판정하는 것이 불가능하기 때문이다.

      - (static 함수는, visiblity를 위해서 함수명, 반환값, 인자리스트를 모두 알고있으므로 sfinae를 사용하면 static메소드인지 아닌지를 알 수 있다)

      - 따라서 모든 케이스에 대해서 static 여부를 반환하도록 할 수 없으며, 그렇게 오인할 수 있는 API를 만들어서는 안된다.

      - x 1안 만약 사용자가 Native에서 생성한 객체를 월드에 공개하고 싶을때는 추가적인 API를 사용해야만 한다고 제약을 건다면?

        너무 불편하다. 걍 제공하지 말자. 

        - 이 제약(메소드)안에서 static 여부도 같이 검사해서 값을 할당해주면 된다.
        - 그러나 이 static 문제만을 위해서 이렇게 제약을 거는 건 좀 그렇다. 혹시 다른 경우에도 이러한 제약이 필요한가? 생각해보자
          - static을 제외한다면 사용자가 멋대로 native에서 만든 객체를 world에게 반환값으로 넘겨줘도 문제는 안되는가?

  - [v] 6안 static의 의미를 세분화해서 그 중 100% 보장 가능한 것만 Node에 API를 둔다.

    - C++에서는 static이 여러의미로 쓰이는데
      - \1. 클래스 멤버에 대한 static : 이것은 이 멤버의 접근시 this가 필요없다는 의미이다.
        - 예) 클래스 static 멤버변수, static 멤버함수, static변수
        - 이 정보는 실행도중에 필요할 수 있다. this를 넣어야할지 아닐지는 programmatically하게 결정해야 할 수있기 때문이다.
      - \2. 함수 혹은 파일 translation unit안의 static 변수 : 이것은 이 변수가 여기서만 노출되는 전역함수라는 뜻이다.
        - 그러나 이 정보는 실행도중 참조할 이유가 아무것도 없다. 이정 보는 IDE에서만 사용하는 것이다. IDE에서만 노출되는 정보로 만들면 된다.
    - 위의 2가지 의미를 static 하나의 키워드로 묶는것은 다소 문제가 있어보인다. 월드에서 다음과 같이 지정하면 어떨까?
    - 1안 - method에 대해서만 static을 공개한다. 변수가 static인 것은 실행에 아무런 도움이 안되기 때문이다.
      - 정확히 말하면 이 메소드는 this필요로 한다 아니다를 판단하는 정보만 공개한다. 이는 실행할때 최적화에 도움이 된다. 필요하다.
      - Method에 isStatic() const를 추가한다.
      - [x] 변수가 static이건 말건 실행에는 중요하지 않다. 이런건 파싱할때 추가정보로써 IDE에서 참조가능한 형태로 전달한다.
        - 틀렸다. 멤버변수는 static인지 여부도 중요하다. native에서 만든 변수는 visible이 되지 않는다. 그러니 이건 패스. 하지만 월드코드상으로 만든 static 변수는 어떻게 되는가 말이다.







### 상수화 

#### const의 기본

- Java, python은 const를 지원하지 않는다. const가 없어도 사실 사용상에 문제가 없다. 실수를 줄여주기 위한 측면이나 동시에 귀찮은 존재가 되기도 한다.

  - java 같은 경우는 99, 05년도에 기능추가를 위한 논의가 있었으나
    - \1. 이미 넣기엔 너무 늦음
    - \2. 하위호환성
    - \3. c++ 처럼 모든 메소드 뒤에 const 붙어야 하니 불편하고 메소드가 더러워짐.
  - 으로 넣지 않게 되었다.

- World는 const를 지원한다.

  - default(= const 를 명시하지 않을때)가 auto를 의미한다. 이는 컴파일러가 판단하여 const인가 nonconst인가를 판단하는 걸 말한다.
    - 어짜피 validation을 위해서 이 메소드가 const인가 nonconst인가는 판단을 해야 하는 문제다.
  - nonconst 나 const를 뒤에 적으면 "사용자가 명시적으로 이 함수는 무엇이다" 라고 말한게 된다.

- side effect

  - 일반적인 언어라면 default를 auto로 하지 않을것인데, 왜냐하면 사용자가 "이 함수가 const인가?"를 알 수 있는 유일한 방법이 compile 이기 때문일 것이다.
  - 이것은 컴파일러와 사용자가 같은 대상물로 대화하는 것이 아니라, 사용자는 "코드"로 얘기하며 컴파일러는 "에러로그"로 답신하는 구조를 띄고 있기 때문이다.
  - 반면 월드는 코드가 핵심이 아니며, 코드가 프로그램이라고 생각하지 않는다. 코드는 어디까지나 대화의 한 수단일 뿐이며 프로그램을 만들기 위해 개발자가 편리하게 얘기할 수 있는 수단이다. IDE의 코드창은 개발자만의 대화공간이 아니며 개발자와 컴파일러가 함께 도와주고 서포트 해주고 채워나가며 프로그램을 만드는 공간이다.

- 문법

  - const MyType a = ... 에서 const는 a가 가리키는 객체가 const 라는 뜻이다. 
    - World는 ptr기반이지만, ptr const는 할 수없는 pointer만 존재한다고 생각하면 된다.
  - nonconst 인 reference는 const reference로부터 할당을 받을 수 없다.
    - const MyType a = ...
    - MyType b =  a **// compile 에러**
  - const를 그대로 사용한다. nonconst를 사용한다.
    - v 1안 const를 그대로 사용한다.
      - class A
        - void print(const int age, string msg) const
          - Console.out(msg + [age.to](http://age.to/)(string))
      - 그러나 nonconst를 명시할때는 어떻게 하는가? "nonconst"는 너무 길지 않나? 
        - 자주 쓰는 것도 아니고. 가끔 쓰는데다가, 영어권에서도 nonconst는 자주 사용하기도 하고. 이걸로 가자.
    - x 2안 ro와 rw를 사용한다.
      - class A
        - void print(ro int age, string msg) ro
          - Console.out(msg + [age.to](http://age.to/)(string))
      - 짧긴 하나, 되려 눈에 잘 들어오지는 않는다.
      - readonly로 보이는게 아니라 "로" 라고 보인다.

- Managed 개발자를 위한 World 구현

  - \1. 인터프리팅시
    - 컴파일러가 메소드를 파싱할때 이 메소드가 최종적으로 (non)const 여부를 결정한다. 
    - validation이 method.isConst() != 사용자가const로 명시 이면 에러를 내보낸다.
  - \3. World 코딩시
    - intelisense에 const 여부가 반영되며, const여부의 경우는 텍스트창에 메소드명의 색이 nonconst일때와 다르다.
  - \2. 실행시
    - **"일단은 호출은 ok, 호출안쪽에서 에러 체크"** 로 판단한다.
    - const를 위한 별도의 member는 가지고 있지 않는다.
    - native 메소드를 fptr로 갖는 Method는 매크로에 의해서 생성된다. 매크로는 자신이 물은 native 메소드가 const메소드인지를 탐지해야 한다.
    - const일 경우에는 Method.isConst() = true로 만든다. 그러나 c++ Method객체 자체는 절대 const가 되지 않는다.
    - Method에서 fptr를 호출할때 const를 메소드를 call()시, 고려해야 하는 조건은 크게 2가지다.
      - \1. const thisptr를 얻어와야한다.
        - --> const Object& caller = msg.getOrigin().get(); **// origin은 nonconst Binder다.**
      - \2. 반환값이 const 인경우, 최종적으로 Refer(isConst() = true)에 wrapping에서 넘겨줘야 한다.
        - --> return (caller.*_fptr)(msg.getArgs()[0], ....).to<const T>(); **// 반환값은 동일하게 Refer다. 다만 const가 앞에 붙었으므로 Refer.isConst()를 true가 될 것이다**
        - **// 모듈개발자는 반환형으로 T\* 같은 걸 넣으면 위의 코드는 빌드되지 못한다. --> 이건 TNativeMethod 같은 거 만들어서 T\*에 대해 클래스 템플릿 특화 시키면 될것이다**
    - 모든 World 동작은 call()로 이루어진다. 따라서 isConst()인데, call()가 불려진 경우에는 isConst() const가 대신 실행되어야 한다. 
    - Node는 bool isConst() const; 를 갖는다. Method, Object, Refer는 모두 isConst를 다루는 클래스들이다.
    - Method도 const를 여부를 가지고 있어야 한다. 이는 validation을 위한 것이다. c++의 Method객체는 const가 되든 말든 동작에는 아무런 영향을 주지 못한다.
    - 모듈개발자의 클래스의 멤버변수는 World에서는 visible하게 할 수 없기 때문에 모듈개발자에게 const는 메소드 일때만주의하면 된다.
    - Q. Thing::to(const Class& cls); 에는 사용자가 const Refer를 받고 싶어하는지의 여부가 포함되어있지 않다?
      - 1안 Thing이 const냐 아니냐에 따라서 Refer(isConst() = true)로 나갈건데, 이걸로는 부족한가?
        - 사용 시나리오로 생각해보자.
        - v Native에서 nonconst에서 const Refer로 만들때
          - 이건 const Object& casted = this; this->to(cls) 하면된다.
        - Managed에서 만든 const 객체에서 const Refer로 만들때
          - Managed

- v Managed 개발자가 Native모듈의 const를 어떻게 다루는가?

  - v 멤버변수를 다루는 경우 --> 당장은 모듈개발자는 메소드만 visible하게 할 수 있다.
  - v 메소드로 나오는 경우는
    -  TNativeMethod<const T> 나, Mashalling<const T> 특화를 통해서 해결할 것이다. 
    - World의 const 가 있건 없건 타입 자체는 항상 Refer가

- Native모듈개발자가 Managed의 const를 어떻게 다루는가?

  - const Refer& 로 Native에서 작성하는 것은 쉽게말하면 Managed객체를 한번도 const로 래핑하는 것과 동일한 것이다. native적으로 이것은 const로만 사용할 것임을 확정하는 것이다. 따라서 Managed객체가 실제로 const인가 nonconst인가 관계없이 항상 const로만 동작하게 된다.

  - 왜냐하면 Managed의 모든 객체들은 그 객체들이 nonconst이건 const이건 관계없이 항상 c++에서는 nonconst로 동작하기 때문이다.

  - 따라서 native에서는 const여도, World에서는 nonconst로 되는 경우도 있다.

  - 반대로 World에서는 const여도, Native에서는 nonconst로 사용하게 되는 경우도 있다. 

    occupiable도 const인 경우에는 refer로 감싸야만 한다. 

    - 예를들면 Object.isConst() == true인 경우, native에서는 이Object가 occupiable인 경우 nonconst로 가져올 수 있다, Refer가 없으므로.

    - 이때 Object의 native nonconst 메소드를 막 호출해주면 되게된다.

    - 실수는 막아야 한다. 어떻게하면 native에서도 world에서 정의한 const 객체에 const native객체로 접근하게 유도할 수 있을까?

    - v 1안 Occupiable도 Refer에 감싼다.

      - Refer는 퍼포먼스를 요구하며, occupiable, sharable 컨셉 변경이 필요하다.
      - isConst 면 get()시 null 나오며, get() const는 값이 제대로 나와야 한다. 
      - 따라서 마찬가지로 Refer::assign()에서 get()이 Null이면 바로 종료 하는 예외처리가 필요하다.

    - 2안 World의 객체를 native가 사용하려면 어짜피 타입캐스팅을 해야만 한다. 타입캐스팅to()는 refer를 반환하니까 이걸로 대체 가능하다.

      dynamic_cast를 사용자가 사용해서는 안된다. 

      - 시나리오

        - Node& one = ...;
        - Node& mem1 = one.getMember(3) // == one[3]
        - mem1.call(Msg("print")); // call로 보내면 안에서 const 예외처리를 해줄 수 있다.
        - MyObject& mine = [mem1.to](http://mem1.to/)<MyObject>();
        - if(mine.isNull())
          - return InvalidType.err("mine is const");

      - 그래. 그렇다. 만약 이 방법이외에 처음부터 구체타입(예, MyObject) 형태로 접근이 가능하다면 사용이 불가능하다. 이런 예는 없을까?

        있다. dynamaic_cast를 사용한 경우다. 아마도 limitation으로 남겨야 할 것이다. 

        - dynamic_cast나 c cast를 사용한다면?
          - MyObject origin(is_const = true);
          - Node& one = origin;
          - MyObject& my = dynamic_cast<MyObject&>(one); // ok
          - my.print();
          - // 원래는 밑에처럼...
          - TRefer<MyObject> get = [one.to](http://one.to/)<MyObject>();
          - if(get.isNull())
            - return;
          - TRefer<const MyObject> cget = [one.to](http://one.to/)<const MyObject>();
          - if(cget.isExist()) {
            - cget->print(); // err. print() is nonconst
            - const MyObject& out = *cget;
            - out.print(); // err. print() is nonconst
          - }
        - x 만약 Integer*를 들고 있는 native클래스가 런타임에 적당한 객체를 ptr에 집어넣는다면?
          - class MyObject {
            - Integer* age; // 멤버변수는 visible하게 할 수 없다.
            - Integer& getAge() { return *age; }
          - }
          - --> 런타임에 ptr를 멤버변수에 집어넣으려면 멤버변수를 알 고 있는 native가 해야 한다. native에서 Integer 타입을 dynamic_cast나 C cast를 하지 않는다면 to밖에 없다.

  - v 어떤 객체A의 멤버변수나, scope안에 있는 경우

    - native가 멤버변수를 꺼내려면 반드시 1번은 to를 써야한다.

  - 이미 native 가 자신의 모듈에 멤버변수를 추가하였다면 멤버변수는 일단 invisible하며 월드가 멤버변수릉 땡겨올려면 메소드의 반환형을 사용해야 하며 TNativeMethod는 Refer로 이걸 감싸서 넘겨준다.

  - 다시말하면 Native에서 만든 모든 occupiable은 사실상 refer로 쌓어있게 된다.

- 고찰내용

  - 1안 Refer와 Object 모두 isConst를 갖게 한다.
    - isConst는 Node에 속해 있어야 한다. 왜냐하면 우리는 Node 기준으로 작업을 하니까. 그렇지 않으면 동적캐스팅을 계속 써야 한다.
    - 왜 Object도 isConst가 있어야 하는가?
      - 그렇지 않으면 occupiable도 Refer를 둬야 하기 때문이다.
    - Object가 const일때 어떻게 되는가?
      - 모든것은 call()로 이루어진다. 따라서 call() 안에서 isConst()이면 call() const로 redirection 하면된다. 그러면 call() const는 isConst()가 true인 Refer를 반환할 것이다.
    - Method도 const 여부가 필요하다.
      - 단 Method 자체가 const 가 될 필요는 없다. (사실 상관은 없다. 어짜피 method에서 할 수 있는게 뭐가 있다고. 대부분은 그냥 fptr로 redirection하는게 전부잖아) 여기서 알수있다는 것은 Validation에 사용하기 위한 부분 뿐이다.
    - Native에서 const로 만든 객체가 있다. 이건 어떻게 Managed에서 const로 노출되게 할 것인가
      - const T& 가 반환형인 경우에는 METHOD 매크로가 TRefer<const T>(fptr의 반환값) 을 담아서 이걸 반환할것이다.
      - World에서는 모듈개발자가 클래스의 멤버변수를 visible하게 할 수 없다. 따라서 const 인 멤버변수를 어떻게 visible하게 할 것인가는 고려하지 않아도 된다.

- [v][v] const로 인해서 클래스 분할문제와 Native visible 문제
  - 포인터를 대신 하는 클래스들은, const 여부를 고려해야되기 때문에 같은 역할을 수행하는 2가지 버전(const 버전과 nonconst버전)으로 쪼개져야 하는 경우가 많다. 이때 World에서도 const버전과 nonconst버전을 2개다 제공해야하는가에 대해서 헷갈리기 시작한다. 
    - CIterator, Iterator, TWeak, TStrong, Refer, CRefer 등..
  - 결론 : visible 하게 되는 것은 World에서는 별도의 클래스로 구분 하지 않는다. --> #CRefer는_존재하지_않는다 참고
  - 왜냐하면 Node 클래스의 의의는 구체클래스가 뭔지 몰라도 사용할 수 있다! 라는 것이다. 그외의 클래스 계층을 타는 것들은 native에서만 유요한 것이며 Managed의 const와 native의 const가 불일치 되어 일어나는 문제가 없다. 그래서 이것들은 기존대로 계속 진행하면 된다.
- [v][v] Method의 const
  - native동작
    - Method도 const여부가 있다. 인터프리터는 월드코드를 읽고나서 validation을 통해 이 함수가 const인지 nonconst인지 검증하기 위해 자체적으로 판단해야 한다. --> #인터프리터는_어떻게_이_함수가_const인지_판단하는가
    - **따라서, Method는 isConst()인지 아닌지를 스위치로 onoff할 수 있으며, 이 값을 바꾸기만 하면 thisptr로 Object가 C++에서 const가 붙어서 나오는지 아닌지를 결정하게 만들어야 한다.**
      - Method는 _is_const 멤버변수를 갖는다. CREPL이 적용되면 인스턴스는 동일하되, 변경만 일어나는 경우도 있을 수 있기 때문에 CMethod 식으로 별도의 클래스를 만드는 건 적절치 않다.
      - Method가 isConst() == true일 경우, thisptr가 const Object& 로만 나와야 한다는 걸 의미한다.
  - world동작
    - 메소드의 const는 c++처럼 뒤에 적으면 된다. nonconst로 확정하고 싶으면 variable을 적으면 된다.
      - class My
        - void print(const int a, int b)
        - void print(const int a, int b) variable
        - void getAge() const
    - variable은 변수 앞에 붙여야 하나, 기본적으로 생략가능하다.
      - variable My mine = ...
      - My mine = ...
  - 1안
    - thisptr를 최종적으로 사용하는 곳은 어디일까
      - ManagedMethod -> scope.stack(msg.getTail()); // 여기에서 thisptr을 꺼내서 objctspace 갱신
      - NativeCaller에서 msg.args 로부터 implicit 캐스팅을 하려는 시점 --> 
    - if(Method::isConst())
      - 
- [][v] Method auto const 컨셉
  - 함수 뒤에 const나 variable을 적지 않으면 auto가 적용된다. auto는 컴파일러가 이 함수가 무엇인지 알아서 판단해서 적어주게 된다.
  - c++에서의 const는 컴파일시에 제어장치다. 즉 사용자가 컴파일 하기 전에 이함수가 const라는 걸 알고있어야 효과가 발휘된다. 그래서 c++에서는 auto const라는 걸 만들기에 적합하지 않다.
  - 그러나 World는 CREPL 기반이므로 빌드라는 것이 없고 "코드의 변경 == 소프트웨어의 변경" 이다. 즉각적으로 소프트웨어가 재구성되어야 하므로 사용자가 편집한 이 함수가 const인지 아닌지를 인터프리터는 ide에게  전달하고 ide는 이걸 intelisense 같은걸로 색으로 표시하여 개발자에게 보여줄 것이다.
    - 이게 가능한 이유는 "월드lang은 visual programming language로써, 그래픽 요소를 나타내줄 수 있는 프로그램(=툴)과 한 몸이다" 라는 방향성을 갖고 있기 때문이다.
  - 구현은 매우 단순하다. validation에서 어짜피 인터프리터는 함수가 정말 월드코드대로 const인지를 체크해야한다.(에러체크를 위해) 그 체크 결과를 그대로 Method.isConst()에 set 해버리면 된다.





#### CRefer는_존재하지_않는다

- CRefer가 존재하는 이유는 isConst()인 Refer는 Native사용자가 get() const 를 해야 한다는 걸 빌드타임에 강제하기 위함이다. 따라서 Refer와 다르게 CRefer는 get() const 만 갖고 있게 된다.
- 하지만 문제는 Native개발자가 접하는 클래스는 Refer가 아니라 Node다. 따라서 이 시점에서 구체클래스를 가져오는 방법은 to를 사용하는 것이며 설사 Node가 isConst()라고 하더라도 C++의 const는 아니기 때문에 to<T>() 함수가 호출 가능하고 반환값은 null을 가리키는 Refer가 된다. 즉 CRefer(혹은 const Refer)를 만들어봤자 결국 사용자는 to<T>()를 하고, 반환값이 null이 아닌지를 확인 한 후, null이면 to<T>() const를 다시 호출해야 하는 식으로 가야 한다는 것이다.
- 어짜피 CRefer로 구체클래스를 뽑아내지 않으면 빌트타임에 const 여부를 강제할 수 없다. 따라서 그럴바에야 차라리 CRefer와 Refer를 통합시켜서 클래스 1개라도 더 줄이는게 좋은 선택이라고 판단된다.

#### Refer는_const를_정보를_가지고_있다.

#### Refer는_const_T_캐스트가_되어야만_한다.

- 요구사항

  - //    TODO: const cast.
  - //        Refer는 알다시피 World의 const를 구현하는 핵심 클래스다.
  - //        Node& n = Refer(const T&..);
  - //        [n.to](http://n.to/)<T>(); // REJECT. return Refer(Null)
  - //        T& cast = n.toSub<T>(); // REJECT. cast.isNull() == true.
  - //        const T& cast = n.toSub<const T>(); // OK.
  - //        Refer& cast1 = [n.to](http://n.to/)<const T>(); // OK. cast1->isNull() != true
  - //    위의 코드가 가능하도록 해야 한다.
  - Refer<const T>().cast<T>()가 나오면 거절해야 한다.
    - 예) Refer<const Object>().cast<Object>()시 null된 Object가 나와야 함.
    - 예) 그러나 Refer<Object>().cast<const Object>()는 정상적으로 나와야 함.

- 참고 -> #명시적캐스트에서_다운캐스팅으로_반환된경우만_isConst함수가_영향력을_발휘한다. , #명시적캐스팅

- \1. Refer::to()에서 다운캐스팅이 되서 나올것 같으면 isConst 확인해서 null로 가도록함

- \2. Refer::toSub()에서 isConst() true면 null로 나감.

  



#### Node는 isConst()를 가지고있다. Method는 isConst() == true면 method에서 사용하는 thisptr가 const Object가 되어야 한다.

- Stmt는 msg를 구성할때 World코드상 const로 되어있다면 msg 맨 뒤에 Refer<const Object>()로 넣어두고, nonconst라면 msg 맨 뒤를 Refer<Object>로 넣어둔다. (Msg의 맨 뒤는 실행시마다 변경되는것이다)
- Method는 isStatic()이 false일 때만 msg 맨 뒤에서 OBject를 꺼내야 하는데, isConst()가 true면 cast<const Object>()를 한다. 만약 Stmt는 Msg 맨 뒤에 Refer<const Object>()로 넣어뒀는데 Method는 refer.cast<Object>()를 하게 되면 NullRefer가 나오게 된다. 이것은 Refer<const T>의 동작이다. --> #Refer_const_T_캐스트가_되어야만_한다
- Method는 가져온 object를 scope에 넣는다. stack(*Refer<Object>);
- 이후는 #Scope에_const_member만_넣어야_한다  를 따라간다.
- 참고로 Native환경에서 Method를 실행하고 싶은 경우에는 call(msg)혹은 run(msg)에 들어갈 Msg 맨 뒤에 Refer<Object>()로 thisptr를 직접 채워넣어야만 한다. 이런 시나리오가 많지 않을것으로 여겨지기 때문에 run(thisptr, msg) 같은 걸 만들어 주진 않을 계획이다.



#### const...뺄까?

* 코드가 너무 복잡해짐. 이 언어는 가볍게 배우고 빨리 실습해보고.. 이랬음 좋겠다.






### 프로그램 구조





### 컨테이너

#### 기본

[][v] Container 기본

- 요구사항
  - Range Based For 를 지원해야 한다.
  - Container는 Object이다.
  - Object만 담을 수 있어야 하는가? Array<int> 같은 건 바로 안되나? --> 안된다.
  - type T 특화는 어떻게 이루어지는가? --> 기존 to<T>, to() 조합해서 써라.
    - Weak<Node> get()을 하면 사용자가 귀찮아진다.
    - 귀찮지만 어쩔 수 없다. 여러 타입이 한 Array에 안에 들어가려면 감수해야 한다. 대신 이걸 cast하는 방법에 대해서 논의해보자.
    - v 1안 기존의 to<T>() or to(Class&) 를 조합해서 쓰라고 한다.
      - arr[3].to(Classizer<int>())    ||    arr[3].to<int>();
    - x 2안 to용 get을 만들어준다
      - arr.getT<int>(3);
  - 
  - 구체클래스에 대한 Container를 지정한 경우는 Weak, Bind에서 자유로워져야 하나? 아니면 모두 Bind에 묶인채로 쓰라고 해야 하나? --> 모두 Bind에 들어간다.Statement는 
- 논리의 정리
  - Container의 목적은 월드에서 사용하기 위한 목적이다. 이게 가장 중요한 점이다. 물론 World는 Native와 양쪽이 통해있으므로 이것도 고려해야 한다.
  - Array<int>는 안된다. 월드 목적이므로 Node이상부터 가능하다.
  - Element의 타입은 어디까지 허용되나
    - v 1안 Container의 원소는 무조건 Bind<Node>다. 자바스타일.
      - 월드에서 사용할 수있어야 한다. 파서가 코드블럭을 만들때를 생각해보자. 1번은 쉽게 가능할 것이다. Array객체를 만들기만 하면 된다.
        - 물론 Native에서는 사용자가 만든 Array로부터 타입T특화를 사용하는 방법이 난감할 것이다.
      - 2번이라면 인터프리터는 모든종류의 사용가능한 조합을 들고 있어야 한다? --> 그렇지 않다. 월드는 배열에 타입이 없다. 자바스타일이다. 따라서 Array<Bind<Node>> 만 사용한다는 것이다.
      - 만약 Native에서 Array<Integer> 같은게 있다고 하자. 월드는 이걸 인식할 수 있는가? 
        - 인식할 수 있다.
        - 하지만 이걸 사용할 수 없는게 Array에는 Integer외에도 다른 것도 공존할 수 있어야 하기 때문이다. 따라서 Array는 Bind<Node>가 맞다.
        - get(n).to(int) or arr[3].to<int>() 처럼 가야 한다. 
    - x 2안 사용자 정의에 따라서 native에서는 Array<Integer> 같은 것도 사용할 수 있게 하자
  - get()의 반환형은 Bind<Node>가 아니라 Node&가 된다. 왜냐면 항상 Element가 Bind<Node>이므로. 조금 편해졌을 것이다. 
- class Iteratable {
  - virtual const Result& move(int step) = 0; // step can be negative
  - virtual Node& get() = 0;
  - virtual bool isEnd() const = 0;
- }
- class Iteration : public Thing { // iteration is invisible
  - Iteration() {}
  - Iteration(Container& owner) : _cont(owner) {}
  - Container& getContainer() { return *_cont; }
  - Weak<Container> _cont;
- }
- class Iterator : public Object { // Iterator is visible
  - virtual const Result& move(int step) {
    - return _way->move(1);
  - }
  - This& next() {
    - move(1);
    - return *this;
  - }
  - This& operator++(int n) { return next(); }
  - This operator++() {
    - This to_return(*this);
    - next();
    - return to_return;
  - }
  - This& prev() {
    - move(-1);
    - return *this;
  - }
  - This& operator--(int n) { return prev(); }
  - This operator--() {
    - This to_return(*this);
    - prev();
    - return to_return;
  - }
  - bool operator==(const This& rhs);
  - bool isEnd() const {
    - if(_way->isNull()) return true;
    - return _way->isEnd();
  - }
  - bool operator bool() {
  - }
  - Node& operator->() { 
    - if(_way->isNull()) return nulled<Node>();
    - return _way->get();
  - }
  - Bind<Iteration> _way;
- }
- class Containable {
  - virtual const Result& insert(Iterator e, const Node& newone) = 0;
  - virtual Node& get() = 0;
  - ..
- }
- class Container : public Object, public Containable {
  - int _length;
  - template <typename E, typename Lambda>
  - const Result& each(Lambda onEach) {
    - for(Iterator e=getStart(); e ; e++)
      - E& casted = e->to<E>();
      - if(casted.isNull()) continue;
      - if(onEach(casted) == ConsumedSuccessful)
        - return ConsumedSuccessful;
    - return Success;
  - }
  - virtual Iterator getIterator(int n);
  - Iterator getStart() { return getIterator(0); }
  - Iterator getEnd() { return getIterator(_length); }
  - int getLength() { return _length; }
  - int getLastIndex() { return _length - 1; }
  - Node& operator[](int n) { return get(n); }
  - virtual Node& get(int n) = 0;
  - const Result& set(int n, const Node& rhs) { return set(getIterator(n), rhs); }
  - virtual const Result& set(Iterator e, const Node& rhs);
  - const Result& insert(int n, const Node& rhs) { return insert(getIterator(n), rhs); }
  - const Result& insert(int n, const This& rhs) { return insert(getIterator(n), rhs); }
  - 
  - virtual const Result& insert(Iterator e, const Node& rhs);
  - const Result& push(const Node& rhs) { return insert(_length-1); }
  - const Result& enq(const Node& rhs) { return insert(0, rhs); }
  - const Result& pop() { return remove(length-1); }
  - const Result& deq() { return remove(0); }
  - const Result& remove(int n) { return remove(getIterator(n)); }
  - const Result& remove(Iterator e);
- }
- class List : public Container {
  - **friend** class ListIteration : public Iteration {
    - ListIteration(List& owner) : Super(owner) {}
    - virtual const Result& move(int step) {
      - if( ! e) return NullPointerException;
      - List& list = getContainer().to<List>();
      - if(list.isNull()) return NullPointerException;
      - Datum* head = list._head;
      - if( ! head) return NullPointerException;
      - while(step) {
        - if(step-- > 0)
          - if( ! e) return AbortActionWarning;
          - e = e->next;
        - } else {
          - if(e == head) return AbortActionWarning;
          - e = e->prev;
        - }
      - }
      - return Success;
    - }
    - virtual bool isEnd() const = 0;
    - Datum* e;
  - }
  - struct Datum {
    - Datum* prev;
    - Datum* next;
    - Bind<Node> value;
  - }
- }
- 검색
  - wbool has(const T&) const;
  - windex find(const T&) const;
  - windex find([](const T& elem) {...});



#### deepclone() 이 있어야한다

- Container는 사실상 Array<TStrong<T>> 이기 때문에 그냥 clone() 하게 되면 같은 T를 공유하는 shallow copy가 된다.



##### Cell과 Array는 차이가 없다.

- Array는 Cell에서 remove, insert를 빼고, setElement로 대체한것이다. 와... 이걸 5년동안 눈치를 못채다니..









#### 시퀸스

##### Sequence 기본

- 기호 {} 를 사용한다.
- Sequence = {2*n+1 | 3...10}
- {n|3...10} == {3...10}
- {1...5} == {5}









#### 배열
##### 1
-   int[] a = {0, 1, 2} // Array는 length만 있다. size는 눈에 보이지 않음.
-   a[2] = 5
-   _//void(int)[4] a = {}_





#### Chain

##### 기본

- 배열1과 배열2가 있을때 이 둘을 chain해서 배열1의 원소와  배열2의 원소를 모두 가진것처럼 보이는 배열을 만들수 있어야 한다. 
  - 예) Chain a, b
  - a.chainFront(b)
  - b.push(5)
  - a.getLength() == 1 // O
  - a[0] == 5 // O
  - a.push(25)
  - a.getLength() == b.getLength() // X
  - a[0] = 27
  - b[0] == 27 // O
  - a.liberate(b)
  - a[0] // 25
- List건, vector건 모든 컨테이너에 적용되야 한다.
- chain에 push, pop을 하게 되면 적절한 실제 배열에 해당 명령이 내려가야 한다.
- Mutliple Container를 묶을 수 있어야 하며, Chain을 실질적으로는 Vector< Bind<Container> >로 봐야한다.
- 고찰 내용
  - 추가 아이디어
    - \1. incarnate() 함수를 사용하면 chain은 유지되지만 원소가 복제된다. 그렇게 되면 탐색시 O(n)의재귀 함수call을 하지 않아도 되게 된다?
      - origin의 원소가 변경되면 어떻게 되는가?
      - 그럴바에야 List l = chain1; 을 사용하게 해라. 이 기능은 필요가 없다.

- 요구사항
  - Container종류 상관없이 동작해야 한다.
  - 임의의 타입 T로 나올 수 있어야 한다
  - 속도가 가능한 빨라야 한다.
  - Container를 특정 ContainerChain 사이에 insert할 수 있어야 한다.
  - Controller를 상속해서 기능 추가가 가능해야 한다.
- 1안 Binder<Container>의 Array이다.
  - class Chain : public Array {
    - class Controller : public Containable { // World에 invisible해야 한다.
      - Controller() {}
      - Controller(Chain& rhs) : _owner(rhs) {} 
      - virtual const Result& insert(Iterator e, const Node& newone) { 
        - if( ! _owner) return NullPointerException;
        - return owner->Container::insert(e, newone); }
      - }
      - virtual Container& get(int n) { 
        - if( ! _owner) return NullPointerException;
        - return _owner->Super::get(n); 
      - }
      - //each는 get을 사용할 것이므로 추가 구현없이 정상적으로 Container를 each하게 된다.
      - Weak<Chain> _owner;
      - Translated translate(int index) {
        - Translated to_return;
        - int sum = 0;
        - Super::each([&to_return, &sum, index](const Element& e) {
          - int before = sum;
          - sum += e->getLength();
          - if(sum > index) {
            - to_return.index = index - before - 1;
            - to_return.cont = e;
            - return ConsumedSuccessful;
          - }
          - return KeepSearching;
        - });
        - return to_return;
      - }
    - }
    - Controller _controller;
    - Controller getController() { return _controller; } // World에 invisible해야 한다.
    - class _Iteratoration : pubilc Iteration {
      - ...
    - }
    - struct Translated {
      - int index;
      - Bind<Container> cont;
      - bool isEmpty() { 
        - return cont.isNull() || index < 0 || index >= cont->getLength();
      - }
      - Node& get() {
        - if(isEmpty()) return nulled<Node>();
        - return cont->get(index);
      - }
    - };
    - virtual Node& get(int n) {
      - return _translate(n).get();
    - }
    - virtual int getLength() {
      - int len = 0;
      - getController().each<Container>([&len](const Container& e) {
        - len += e.getLength();
        - return Success;
      - });
      - return len;
    - }
    - virtual const Result& set(int n, const Weak<Node>& rhs) 
    - virtual const Result& insert(int n, const Weak<Node>& rhs) {
      - Translated bean = _translate(n);
      - if(bean.isEmpty()) return NullPointerException;
      - return bean.cont->insert(bean.n);
    - }
    - Weak<Node> operator[](int index);
    - // each() 는 get()를 사용하므로 따로 조작할 필요없음
  - }





### Sharable & Occupiable







### Scope
라이프 사이클, GC

#### 

#### scope는 Node다.

- chain이 되어야 했기 때문에 결과적으로는 invisible한 Node가 되었다.
- get(n) get(string) 함수를 물려받을 것이다.
- call() 함수를 채워야 한다.
- v Node는 getMembers()를 채워야 한다. Chain은 어떻게 getMembers()를 채울까?
  - x 1안 return *this;
  - x 2안 Chain
  - v 3안 당연히 TClass<Chain>의 메소드들이 들어갈 것이다. 뭐가 문제인가. 배열원소를 접근하고 싶다면 Msg("get", {int=index})를 쓰라고 해라.

#### Scope의 초안

- 3개의 space로 이루어진다. GlobalSpace, ClassSpace, LocalSpace.
  - ClassSpace로 한 이유는 Object가 아닌 것도 ClassSpace에 멤버를 넣어야 하는 때가 있기 때문이다.
- class Scope : Chain
  - Array<Node> _globals;
  - Chain::Control& getControl()
- class Node
  - virtual call()
    - Chain::Control& con = Scope.getControl()
    - TStrong<Chain> classsp = con[1];
    - TStrong<Array> localsp = con[2];
    - con.set(1, _getMembers())
    - con.set(2, *Array::create());
    - // member를 찾아서 메시지 전달..
    - con.set(1, *classsp)
    - con.set(2, *localsp);
- class Object
  - // virtual call() --> Node와 동일. 이게 기본 컨셉이다.
- class Method
  - private windex _post(int n)
  - virtual call() // Method의 call은 기본컨셉(Node의 call)과 다르다.
    - if([msg.name](http://msg.name/)() == "execute") // 종말메소드인 execute는 이렇게 수동으로 처리해야 한다.
      - return execute(msg)
    - return Super::call() // Method가 msg를 bypass 하는 경우에는 어떠한 member도 scope에 추가하지 않는다. Method의 멤버가 추가되지 않으므로 재귀함수를 돈다고 가정했을때에 중복으로 scope에 등록되는 케이스는 발생하지 않는다. 요때는 기본컨셉(Method를 Node로써 다룸)으로 진행된다. ObjectSpace가 다빠지게 된다. 
  - execute(msg)
    - Control& con = Scope.getControl();
    - int n = Scope.getLength()
    - Scope.enq("me", *this); // me.getMembers()는 넣어서는 안된다. 어디까지나 this,즉 object의 것만 넣어야 한다. 그리고 원소는 반드시 [0] 부터 넣어야 최적화가 가능하다.
    - con.enq(getNestedMethods())
    - con.enq(getArguments())
    - _onExecute() // TODO: 여기는 bridge에 영역.
    - while(Scope.getLength() >= n) // TODO: 최적화
      - Scope.pop()
- 고찰 내용
  - 1안
    - 구성
      - Scope : Chain
        - public static const int GLOBAL = 0, LOCAL=2, OBJECT=1;
        - Array<Node> _globals;
        - Array<Chain> _objects;
        - Array<Node> _locals;
        - _sync()
          - getControl()[1].set(_objects[0]);
    - class ScopeControl : Chain::Control 로 제공.
      - insert, remove 는 ObjectSpace 자체를 제어한다.
        - insert(OBJECT, ...) 시 Chain 객체를 매번 생성하고, remove시에 Chain을 제거한다.
      - Chain& getLocal/Object/GlobalSpace() 제공한다.
      - getObjectSpace().getControl().push(members)는 ObjectSpace(정확히는 _objects[0])에 Space내의 것을 제어한다.
  - 2안
    - class Scope : Chain
      - class ScopeControl : public Control
    - Node::_precall(n)
      - n = Scope.getControl().push(getMembers())
    - Node::_postcall(n)
      - while(getLength() > n)
        - getControl().pop()
    - Method::_precall(n)
      - Super::_precall()
      - getControl() += NestedMethodMembers())
      - getControl() += getArguments()
    - //Method::_postcall(n)
    - Object::_precall(n)
  - 3안
    - class Scope : Containable
      - Array<Node> _globals;
      - TStrong<Chain> bean;
      - insert() / remove()
        - return bean.insert() / remove()
      - Chain::Control& getControl()
        - return bean.getControl()
      - Chain createObjectSpace()
        - Chain ret;

##### 지역변수-중복-되는-경우-scope는-어떻게-구현해야-하는가, 가능하면 블록문이 끝난 경우, 기존 심볼을 같은 인덱스에 위치하는 방법은?

- 변수와 메소드의 중복정의는 허용하지 않는다.

- 사용자가 헷갈릴 수 있다.

- 고찰 내용

  - @문제정의

    - class A
      - void(void) foo(int b)
        - int a = 5
        - Console.out(a) // -- 1
        - if(b > 5)
          - int a = 7
          - Console.out(a) // -- 2
        - else
          - int a = 10
          - Console.out(a) // -- 2
        - Console.out(a) // -- 3

  - 1과 2와 3의 인덱스가 같았으면 좋겠다. 어짜피 if 블록문 안쪽에서는 1번 a를 참조할 수 없으니, 자연스럽게 동작도 가능하며, 최적화시에 같은 인덱스를 넣으면 되니 더 편할 것이다.

  - 1안 각 변수가 복원 시킨다

  - 2안 블록문이 복원 시킨다

  - 3안 스코프가 복원 시킨다

    - 외부에서 스코프에 로컬 변수를 넣고자 하는 경우 2가지 방법밖에 없다.

      - \1. 인덱스를 지정해서 잠시 덮어쓰는 방법.

        insert(3, ....) 

        - 이 경우, 기존에 3번 인덱스에 있던걸 기억해 두고 있어야 한다.

      - \2. 그냥 맨앞에 추가 하는 방법

        pushHead(...) 

        - 이 경우, 그냥 원소를 넣으면 그만.

    - 이후, 블록문에서 "이 인덱스 이전으로 생성된 것들을 모두 pop!" 이라고 한다.



##### scope symbol 반환 알고리즘 초안

- Statement의 심볼 접근은 숨겨진 전역객체인 Scope를 통해서 해결한다. 
- Scope는 3가지로 구분해서 심볼을 관리하며 Stack 구조를 가지고 있다.
  - GlobalSpace : 전역 공간이다. Scope가 소유한다.
  - ObjectSpace : 현재 메소드를 소유하는 객체의 멤버들이 들어있다.(메소드 + 멤버변수) 그때그때마다 객체의 member를 chain 시켜놓는다.
  - LocalSpace : 현재 수행중인 메소드, 블록문에서 지정한 지역변수들이 여기에 임시로 들어가게 된다. Scope가 소유한다. int border가 있으며, 이것은 [x, length-1] 까지 이 함수에서 접근가능한 심볼의 범위를 나타내는 int 값 x를 담고 있다. 메소드가 이것을 placeBorder(int newborder)로 지정하고, Statement는 getVisibleElement()로 이 지정된 범위에서만 심볼을 찾아서 사용한다. 
  - 컴파일러가 최적화되면 getElement(index)를 바로 사용한다.
- 알고리즘은 다음과 같다.
  - Scope {
    - Members global;
    - Members local;
    - Chain<Array<Node>> members;
    - Scope() {
      - members.chain(global);
      - members.chain(local);
    - }
  - } Scope가 생성되면서 기본 built-in 전역변수, 프로그램 전역변수들이 global에 push 된다.
  - Statement가 실행되면, 최종적으로 Method가 msg를 받는다. Method.call("()")이 되면 이를 "execute()"로 번역된다. 메소드는 setArgument로 받은 인자리스트를 넣어두고, Method.execute()가 호출한다.
  - Method.execute()이 불려지면 현재 Scope.ObjectSpace 주소가 thisptr가 일치하는지 본다. 아닐 경우에만 Scope.ObjectSpace의 현재 주소를 보관하고, thisptr의 member를 대신 넣어둔다. getBorder()로 현재 값을 확인하고 placeBorder(length-1)을 지정한다. 그리고 블록문.execute()를 부른다.
  - class Method : public BlockStatement 로 되어있다. 블록문은 Statement들을 갖고 있으며, call(), execute()가 가능한 것을 말한다.
  - 블록문.execute()이 되면 Scope의 LocalSpace의 length를 기억하고 statements.execute()한다.
  - 그리고 Statement들은, 지역변수를 정의할때 Scope의 localSpace에 직접 push하도록 코드를 작성한다.
  - 블록문은 Statements들이 모두 끝나면 앞서 기억해둔 LocalSpace.length까지 pop을 시켜준다.
  - Method.execute()는 블록문.execute()가 끝나면 placeBorder(이전에 기억하던 lenght)로 되돌리고 보관하고 있던 ObjectSpace 주소로 원복시킨다.
  - Closure는 execute시에 placeBorder()를 하지 않는 BlockStatement다.
    - class BlockStatement : public Statement
    - class Closure : public BlockStatement
    - class Method : public Closure
  - 파서는 코드블럭을 생성할때, 메소드 안에 메소드는 closure로 인식해서 코드블럭을 만든다.
  - 같은 클래스 메소드A에서 메소드B를 호출하는 경우는? --> OK
  - 클래스A::메소드A에서 클래스B::메소드A를 호출하는 경우는? --> OK
  - 메소드의 메소드를 실행시키는 closure의 경우는 어떻게 되는가? --> OK
- 고찰 내용
  - World코드의 이 식별자가 무슨 심볼과 매치되어야 하는가. 무슨 심볼에게 이 함수호출을 보내야 하는가를 정하기 위해서는 지역변수목록, 전역변수 목록, 클래스멤버 목록을 다 알 고 있어야 한다. 이와 같은 작업을 수행해주는 (= SymbolTable) 걸 Scope라 한다. 어떻게 설계할지를 논의해보자.
  - 힌트
    - \1. IDE 편집모드에서는 scope 객체가 필요하다. 최적화가 된 build 된 실행모드에서는 scope가 필요없다.
    - \2. 되도록이면 World는 편집모드인지 실행모드인지 알 필요가 없었으면 좋겠다.
    - \3. 퍼포먼스는 중요하다. 매 getMember() 마다 Scope객체를 만드는건 너무 시간이 오래 걸린다.
    - \4. 소스코드의 변경은, 즉 Scope 객체의 변경을 의미한다. 편집모드에서는 Scope는 매번 변경되게 될 것이다.
  - 1안 compile, validate, execution 시에 scope를 만들어가면서 파싱한다.
    - Scope는 실행시에 "a" 란 식별자에 접근하려는 코드가 있을때 실제로 이 변수를 반환하는 객체다. 이는 compile 과정에서 코드블럭에 "어떠한 객체에게 이 메시지를 전달해야 하는가"를 따지는데 사용된다. 
    - Scope는 3종류가 있다. 
      - \1. GlobalSpace라는 객체. 프로그램 시작전에 전역변수가 여기에 담긴다.
      - \2. LocalSpace라는 객체. Method에서 생성된 지역변수 + 전달받은 thisptr + Arguments 들이 여기에 생성되어 놓여진다. Class는 LocalSpace의 borderline을 그어놓고, 그 이후에 추가되는 것들만 검색되게 한다. Class 파싱이 끝나기 직전에는 LocalSpace의 borderline을 취소한다.
      - \3. Object Space. Object의 members 들. 객체 생성과 동시에 만들어진다.
    - 프로그램 실행과 동시에 GlobalSpace값을 추가된다.
    - 그리고 이는 메소드를 파싱하면서 지역변수 목록을 메소드에 추가하게 되는데, 이때 LocalSpace에도 추가한다. 
      - 지역변수 목록은 메소드의 멤버가 될 수 없다. 그렇게 되면 메소드 외부에서 지역변수에 접근할 수 있도록 되어버릴 것이다.
    - 단, LocalSpace는 구현이 좀 독특하다.
      - Class는 msg가 넘어오면 LocalSpace의 구성물을 잠시 꽁쳐두고 비워놓는다. (LocalSpace는 구성물을 꽁처두는데 최적화되어 퍼포먼스 loss가 발생해서는 안된다. swap(Stack&) 이런거 만들어 놓으면 될것이다.)
      - Method가 msg를 받으면 LocalSpace의 index를 기억한다. to()로 생성해낸 인자리스트를 LocalSpace에 박아넣고, Statements를 돌린다. 이 과정에서 지역변수를 만드는 Statment는 당연히 LocalSpace에 인스턴스를 넣어놓는 코드가 될것이다.
      - Method가 종료되면 아까 기억했던 index까지 LocalSpace를 pop한다. LocalSpace는 Stack의 특성을 띄면 될것이다.
    - 만약 Nested Method가 실행된 경우는?
      - class MyClass
        - int a
        - void foo(int b)
          - int c
          - void boo(int d)
            - int e
          - boo(c)
      - MyClass cls
      - cls.foo()
      - 먼저 cls.foo가 먼저 실행된다. MyClass::call()이 수행되면 LocalSpace의 구성물을 지역변수로 swap시키고 비워놓는다.
      - 다음foo()가 수행된다. 현재 LocalSpace의 length를 확인한다. == 0
      - 그리고 인자리스트를 to()로 생성하여 LocalSpace에 쑤셔넣는다. 모든 메소드의 인자1은 반드시 thisptr, 즉 cls 변수가 들어있다.
      - 다음 boo(c)가 수행된다. boo는 Method인 foo 안에 있는 것이다. 이는 코드블럭으로는
        - msg {
          - name = boo
          - args = {cls, c}
        - } 와 동일하다.
      - 인터프리터는 코드의 boo가 Nested Method, 즉 foo함수의 boo임을 알 수 있다. 그러므로 msg를 수신하는 주체를 foo Method로 설정한다.
        - 여기서 Method는 클래스다. 단, 값을 가질 수 는 없다. 왜냐하면 Method는 World에서 Unique 속성을 갖기 때문이다. (static이라면 이론적으로는 가질 수 있을 것이다)
      - boo::call(msg)가 수행된다. LocalSpace length를 확인한다. == 2
        - boo()함수의 수행한다.
      - boo()가 끝나면 아까 기록했던 length가 되도록 pop한다. [현재 length 3이므로 pop() 1번 하게 됨]
      - foo()가 끝난다. 아까 length가 되도록 pop한다. [pop() 2번해서 length 0이 됨]
      - MyClass1::call()이 끝난다. MyClass1은 아까 지역변수로 swap해둔 LocalSpace를 교체한다. 
    - 고찰내용
      - 파서는 World코드로 지역변수의 정의를 보면 Function.stack에다가 지역변수 명세를 추가한다. 지역변수의 순서는 상관이 없다. 
      - scope는 multiple chain이다. 맨 위부터 Stack공간(Function의) -> 클래스(thisptr)의 all member 공간 ->전역변수 공간 으로 3개가 chain된다.
        - 메소드 안에서 다른 객체의 메소드를 호출한 경우는, 이것만으로는 해결되지 않는다.
          - class MyClass
            - void foo()
              - do-something...
          - class MyClass1
            - MyClass cls
            - void boo()
              - cls.foo()
          - result main()
            - MyClass1 c1
            - c1.boo()
          - 위의 알고리즘대로라면, 이렇게 된다.
            - \1. MyClass1, MyClass Class 객체가 각각 만들어지고, method, 변수 정보가 각각 member에 들어가게 된다.
              - ClassManager[1]에 있을, MyClass1을 예를들어보면
                - methods[0] = boo()가 들어있으며
                - variables[0] = Object(MyClass()) 가 들어있다.
                - members는 methods, variables를 link해서 members[1] == variables[0]과 같다.
            - \2. 프로그램이 실행되기 전에 전역객체가 만들어지고 Scope.전역공간에 등록된다. 이 코드에서는 비어있다. result main() 메소드가 생성되면서 
            - \3. 이 코드에서는 언급되지 않았지만 main메소드가 객체가 생성되면서 메소드마다 가지고 있는 stack공간[0]에 지역변수 c1이 Object(MyClas1)으로 생성된다.
            - \4. main이 실행된다. 메소드의 stack공간이 Scope.지역공간에 push 된다. 결과, Scope는 클래스공간은 null이므로 전역공간 + main지역공간으로 이루어지게 된다. 따라서 Scope[0] = "c1"만 들고있는 1개 짜리 공간일 것이다.
            - \5. MyClass c1를 하게되면 ClassManager["MyClass1"].instantiate()가 되고, 이는 Object(MyClass1)를 만들면서 members가 MyClass1.methods를 link시키고, variables = MyClass1.variables에서 깊은복사하고, members는 variables를 link시킨다. 그러면 새로 만들어진 c1객체는 methods는 클래스의 것을 사용하되, variables는 클래스에서 복제된 자신만의 것을 갖는 상태로 출발하게 된다.
            - \5. c1.boo 가 수행된다. 이는 객체, c1으로 일단 메시지가 가는 것이다. c1은 Object, 객체. Object는 자신에게 msg가 왔을 경우, 클래스공간을 release하고 자신의 members를 link시킨다. (이미 자신이 등록되어있으면 무시된다). 결과 Scope는 [0] = c1, [1~n] = c1의 members로 이루어진 상태가 된다. 그리고 Scope에서 boo Method를 찾아서 반환한다.
            - \6. 반환된 boo의 "()"가 수행된다. 이는 Method::call(args)와 같은 것이다. Method는 msg가 왔을 경우, 
            - 문제점
              - 객체에 msg가 가지 않은 상태에서 함수에게만 msg가 가게 된다면 클래스공간이 업데이트 되지 않은 상태에서 지역공간에만 메소드stack공간이 추가될 것이다. 이게 가능한가?
              - 지역변수는 미리 만들어둔다? 그러면 초기화되지 않았는데 참조해버리는 경우는 어떻게 되나?
                - Stack공간::getElement()
        - Chain::find(T& needle) // 각각 탐색 함수호출을 내린다.
          - for e in _subs
            - if found = e.find(needle)
              - return found
      - Function은 execute("")가 되면 자신의 stack을 복제하여 scope의 stack 공간에 넣는다. (chain의 각 원소는 Bind<T>로 되어있다). 그리고 함수를 실행한다. 
      - 파서가 만들어놓은 코드 블럭이 담긴 Function의 실행부는, 함수 호출의 집합으로 이루어져있다. 함수호출은 3가지 값이 필요한데, 인자, 함수, thisptr 이다. 함수는 시스템에 유일하게 1개이므로 그냥 바인들로 문제없고 인자, thisptr은 그때그때 함수호출마다 "어느 객체가 thisptr인 함수호출인가" 에 의해서 변경되게 된다.
      - 이런 상황에서 퍼포먼스 최적화를 위해 최적화된 Bind을 정의한다. 이 Bind는 기존 Bind<T>의 일종이다. 처음 실행하면 cache값을 확인해서 -1 처럼 되어있다면 scope객체에 접근해서 주어진 이름으로 심볼을 찾아서 가지고 온다. 찾으려던 심볼이 확인되면 cache의 값을 scope의 인덱스로 업데이트하고 Bind는 심볼을 반환한다. 다음 접근요청이 들어오면 scope[cache]로 바로 심볼을 가져오고, 검증이 실패되었을때만 scope["foo"]처럼 심볼을 재 탐색해서 cache를 업데이트한다.
        - 결론적으로 scope["foo"] 와 같은 로드가 많이 걸리는 탐색작업을 "최초 1번"으로 제한 할 수 있다.
        - 게다가 IDE에서 런타임에 코드가 수정되어도 자동으로 동기화가 이루어진다.
  - 2안 compile, validate에만 scope가 필요하며, 이때 각 함수 안에서 재귀적으로 생성한다.
    - 먼저, "어떠한 객체에 이 메시지를 전달해야 하는가" 라는 것은 코드에만 dependent하다. 다시말해서 코드가 fix되면 이 정보를 갱신할 필요가 없다. build가 완료되면 optimized된 바이너리코드가 나오고 이 상태에서는 더 이상 편집이 불가능하다는 것이므로 optimization을 할때 "어떠한 객체에 이 메시지를 전달해야 하는가"도 같이 최적화 시키면 실행시에는 이 값을, scope를, 업데이트할 필요가 없게 된다.
    - 하지만 validate시에 이 부분을 정해버리면 편집상 문제가 생긴다. 왜냐하면 이 작업은 부피가 좀 큰 작업이고 소스코드가 한창 변경중인 상황에서 매수정시마다 scope를 생성하여 조회하여 매칭을 시켜봤자 좀 있다 다시 수정될 가능성이 있기 때문이다. 실행할지도 모를 모든 코드에 대해서 이러한 작업을 수행하는 것은 부담스럽다. 따라서 실행속도가 늦어지더라도  IDE모드에서는 optimization을 하지 않고 실행시점에서 늦게 scope를 하나 두고 매칭을 지속적으로 시켜가는게 좋다.
      - 그 얘기는 WorldInterpreter는 이것이 실행모드인지 편집모드인지 알 고있어야 한다는 것 처럼 보이는데?
        - 1안 IDE모드에서는 scope를 사용해서 매칭하는 함수를 넣고, optimization에서는 이 함수 대신 직접 target 을 가리키는 걸로 대체함으로써 최적화 시킨다.
          - 이 말은 Node::getMember(const String& name) 이거 안쪽에서 Scope를 통해서 찾아내야 한다는 걸 의미한다.
          - 포인트는 1. 실행모드에서는 scope는 불필요한 데이터이다. 2. 재귀적으로 구성시켜야 한다. 3. 인스턴스별로 그 값이 달라야 한다.
          -  어떻게 구현할까?
            - 1안 lazy-초기화를 사용한다.
              - 각 인스턴스는 요청을 받을때 member에다가 동적으로 값을 scope 쑤셔넣는다. scope의 기반이 되는 것은 owner로부터 받는다. 이 말은 owner(클래스, 혹은 메소드) 가 누구인지 알 고있어야 한다는 것이다. 
              - owner에 대한 정의와 컨셉이 필요하다.
              - Scope Node::createScope() {
                - Scope scope = getOwner().createScope();
                - scope.chain(getMembers());
                - return scope;
              - }
              - 매번 Scope값이 생성,채워져서 들어간다. 엄청난 퍼포먼스 loss가 예상되는데.
  - 3안 1안의 최적화 및 개선안
    - 실행모드시에도 scope를 채우거나 빼내어가면서 실행을 한다. 모든 Statement들을 이 scope로부터 심볼에 접근하는 걸 대 원칙으로 한다. 
      - IDE 모드(즉, 코드를 text를 input으로 보내어 compile, validate가 일어나는 과정) 에서는 코드의 변경이 많기때문에 getMember(String& name) 을 사용할 것이며, 이 함수는 scope에서 string 비교로 심볼을 찾는다.
      - 실행모드에서는 Interpreter가 getMember(String& name)을 getMember(int index)로 최적화시킨다. **따라서 Scope는 매 실행시마다 항상 동일한 인덱스가 나오도록 해야한다.**
      - Scope는 3개의 space로 이루어져있다.
        - \1. LocalSpace
      - 메소드에서 같은 클래스의 다른 메소드를 부르는 경우, 만약 "지역변수는 LocalSpace에 선언될때마다 들어간다" 라는 것이면 
        - \1. 매번 객체생성해야한다.
        - \2. LocalSpace에 push, pop을 해야 한다. 매 메소드마다. 이건 꽤나 큰 loss일 수 있다.
      - 만약 메소드가 LocalSpace를 각각 들고 있고, 여기에 지역변수들이 이미 들어있다면 어떨까? push, pop은 인스턴스를 빼고 넣는게 아니라 단순히 이 원소를 사용한다 사용하지 않는다는 표시만 하는 거라면.
      - 지역변수는 블록문이 있다면 중간에 소멸되기도 해야 한다.



#### Scope에서 멤버 중복제거

- 재귀메소드를 호출한다고 하자. 그러면 Method::getMembers()가 계속해서 쌓일 것이다. 어떻게 해결할까?
- 쌓이지 않는다. 
- x 1안 me로 접근 한 경우에만 Method::getMembers()가 쌓인다. 
  - Method에는 이 Object에 대한 것 + 메소드 인자 + "me" 변수 만을 채워놓는다.
  - 메소드가 재귀호출되면 me 변수는 중복되어서 local에 들어갈 수 있다. scope는 [0]부터 탐색해서 중복무시하고 가장 먼저 매칭되는 것만 반환한다.
  - "만약 한 Space에서 2가지 이상의 식별자가 발견되면 모호성의 오류가 발생된다." 이거 때문에 me도 중복되어서는 안된다. "this" 도 마찬가지다.
- 2안 this, me만 특별 취급한다. 
  - Object는, 자신이 등록되면 this, me를 scope에 setThis(), setMe()로 얻어놓는다.
  - Scope는 저 함수가 불려지면, 
    - if(it.isExists())
      - if(_this.isBinded()
        - _this.bind(it)
      - else
        - _this.bind(it)
        - _this_n = locals.push(_this)
    - else
      - _this.release();
      - locals.pop(_this_n); 을 한다.
  - Node::call()은
    - origin = Scope.getThis();
    - Scope.setThis(*this);
    - ...
    - Scope.setThis(origin)을 한다.
- 1-2안 1안으로가되, me, this에 대해서만 모호성의 오류를 내지 않는다.
- **고찰을 통해 알아낸 팩트**
  - \1. me의 위치는 고정되있지 않다. me가 추가되고 지역변수가 추가되고나서 nested method가 불려진 상황이라면 me는 scope에 맨 위라고 보장할 수 없다.
  - \2. 설계상 me는 반드시 scope 안에 있어야 한다. 별도의 변수로 제공되는 예외취급되어서는 안된다.
  - \3. Method::call()과 NestedMethod::call()에서의 scope 제어 코드가 다르다.
  - \4. LocalSpace도 ObjectSpace처럼 bind, release가 가능해야 한다.
    - class Method // == NestedMethod
      - call()
        - if msg == execute
          - execute()
        - else
          - return 
      - execute()
        - n = scope[2].getLength()
        - scope[2].push(args)
        - scope[2].push(getNestedMethods())
        - scope.updateMe(this)
        - onExecute() // --> Object.call() or Method.call()
        - while(scope[2].getLength() > n)
          - scope[2].pop()
    - class ??Method : Method
      - call()
        - TStrong<Space> origin = scope[2];
        - scope[2].set(**new Space()**);
        - Super::call()
        - scope[2].set(origin);
    - class StaticMethod : Method
      - virtual onExecute()
        - // msg에서 this를 가져오지 않는다.

#### 중첩메소드 지원과 그때의 scope의 컨셉

- 중첩메소드는 잠깐 scope에 등록되고 사라지는, Object의 메소드중 하나이다. Method에 속한 Method가 아니다.

- scope에 보이고 빼는 건 자신이 정의된 소유자Method가 담당한다.

  

#### Scope는 Reversed-Stack, 클래스멤버는 Stack으로 구성해야 한다.

- Scope는 새로운 심볼이 [0]에 들어가는 Stack이어야 하며,
- 클래스멤버는 새로운 멤버가 뒤에[n] 들어가는 Stack으로 들어가야 한다.
- 고찰내용
  - Scope는 인덱스가 해당 함수 내에서만 블록적으로 확정적이다. 그렇기에 그 블록을 인덱스 맨 앞으로 위치시킨다면 항상 확정적인 상태를 만들 수 있다.
  - 반면 클래스의 멤버는 그 클래스, 그 클래스가 상속받은 부모클래스들까지 모두 확정적이다. 그러므로 뒤에 위치시키는 것도 가능하다.



#### 인터페이스 공개 - 외부에서 scope객체를 얼마나 접근가능해야 할까?

- native, managed 포함하여, scope의 존재자체를 몰라야 하며, 간접적으로 이를 조작해서도 안된다.(예, c++에서 변수 정의하는 Stmt를 지역변수로 임의로 하나 만들어서 바로 실행)
- 고찰내용
  - v 변수를 멋대로 추가하거나 제거해서는 안된다? --> Validation실패는 허용되지 않는다. 안된다.
    - Stmt는 execute()가 되면 변수를 추가할 수 있다. 제거는 메소드에 의해서 처리된다. 설사 여기서 scope를 막아놓는다 하더라도 변수를 정의하는 Stmt를 하나 만들어서 execute()를 때려버리면 scope에 들어가게 된다.
    - 제거만 못하게 막아놓는다 하더라도 scope는 [0]부터 가장 먼저 매칭된 것을 보내주므로 (모호성의 오류가 없다. 그건 클래스에서만 있지) 사실상 로직을 바꾸는 결과가 된다. 만약 이걸 하는 경우 validation한 결과와 정말 실행한 결과가 불일치 하게 된다.







#### Scope의 실행모드(바이너리 직접 실행)과 IDE편집 모드시의 차이점

- 가장 중요한 것은 월드 자체는 현재 바이너리 실행모드인지 알아서는 안된다는 것이다. 똑같이 Statement를 실행할 뿐이지만 최적화Statement에서는 get(name)를 사용하지 않음으로써 속도가 개선될 뿐이다.
- 따라서 실행모드와 IDE모드라는 것은 엄연히 존재하지 않는며, 구분하지 않는다. 여기서는 편의상 임시로 사용하는 용어다.
- scope는 양쪽 모드에서 항상 구축이 되어야 한다. 그래야 지역변수가 참조가 될 수 있다. 
- 단, 바이너리 최적화가 이루어지면 scope.get("변수이름") --> scope.get(n)으로 탐색속도가 올라가는 것 뿐이다.
- 고찰내용
  - 가장 중요한 것은 월드 자체는 현재 바이너리 실행모드인지 알아서는 안된다는 것이다. 똑같이 Statement를 실행할 뿐이지만 최적화Statement에서는 scope를 사용하지 않음으로써 scope 구현이 빠지게 되어야 한다.
  - 1안 - scope에 reg, unreg도 눈에 보이지 않는 statement로 대체한다?
  - 2안 - scope객체는 "실행모드"임을 catch해서, 이때는 reg, unreg를 비운다.
  - v 3안 - scope는 실행모드에서도 필요한것이다?
    - 왜냐하면 지역변수가 어디에 있게 되는가? 바로 scope이지 않는가. scope가 유일하게 지역변수가 visible한 장소이기 때문이다. 실행모드에서 최적화되는 것은 scope.getMember("string") --> scope[n]으로 되는 부분인 것이다.





#### Scope에_const_member만_넣어야_한다.

- validation이 실제로 scope가 어떻게 구성되어있는가로 판단하기 때문에  Method가 OBjectSpace를 update할때 Object가 const면, const 멤버만 ObjectSpace에 넣어야만 한다.
- *1안 chain을 잘 구성해서 const 멤버만 모아둔 chain을 또 만든다. 그리고 이걸 바로 반환한다.*
- v 2안 const member를 따로 구성하면 로스가 너무 심하다. 그래서 멤버는 그냥 다 들어가고, 실행직전에, 혹은 stmt나 어딘가에서 이걸 위한 exception handling을 끼워넣는다.
  - scope는 어짜피 Object에 종속적으로 될 수 밖에 없다. 따라서 scope에 object를 stack할때 const로 stack했는가 nonconst로 stack했는가를 기억했다가, 외부에서 objectspace에 접근할때 member가 nonconst라면 에러를 내뿜도록 하면 어떨까?
  - Node::isConst()를 사용하면 된다.
  - scope는 stack(const Object&) stack(Object) 2개를 만든다. 그리고 TWeak<Object>와 TWeak<const Object> 2개를 둔다. 이렇게 2개를 두는 이유는 const 또한 타입의 일종이기 때문에 C++에서는 하나의 타입 A를 둬서 const, nonconst 겸용으로 바인더를 쓰게끔 할 수가 없기 때문이다.
  - stack안에서는 const Object이면 TWeak<const OBject>를 bind()하고, TWeak<Object>.release() 하는식으로 한다.
  - 이후, 외부에서 scope[""] 나 scope.get("name")으로 멤버를 접근하려고 하는 경우에, 외부에서 주입된 Object가 const인지 nonconst인지를 알수 있으므로, 이를 고려해서 접근하도록 만들 수 있다.
- *3안 const를 위한 별도의 배열을 object 마다 하나씩 만든다. 메모리는 증가하지만 object space 삽입시 로스는 없다.*







#### Scope의 LocalSpace 알고리즘 최적화

- IDE 모드일 경우

  - getMember(const String& name)으로 Scope객체에서 심볼을 찾는다. 따라서 Scope의 LocalSpace에 지역변수가 들어만 가있으면 된다.
  - 지역변수 생성시 LocalSpace에 변수를 push하며, 함수가 끝나면 Method는 LocalSpace를 release() 해버리면 된다. (자기껏만)
  - 블록문이 끝나면 LocalSpace의 해당 element만 release된다. 
  - LocalSpace는 Array<Bind<Object>>가 된다. (Reference나 Object가 올 수 있다.

- 실행모드일 경우

  - 컴파일러는 코드를 완전히 분석, 실행하여 이 시점에서 생기는 지역변수가 몇번 index의 LocalSpace에 들어가는지 파악해야 한다. 
  - 그렇게 되면, 
    - 지역변수를 생성하는 Statement는, push가 아니라 setElement를 쓰도록 해서 탐색 속도를 낮추고 메모리 점유를 줄일 수 있다.
    - 심볼 접근시 문자열 비교가 아니라 getElement(index)로 하면 더 빨라진다.
  - 그 이외의 블록문이 끝나면 LocalSpace에서 remove하는 것, 함수가 끝나면 Method는 LocalSpace를 release() 해버리는 것(자기껏만)은 동일하다.

- 고찰내용

  - 메소드에서 같은 클래스의 다른 메소드를 부르는 경우, 만약 "지역변수는 LocalSpace에 선언될때마다 들어간다" 라는 것이면 
    - \1. 매번 객체생성해야한다.
    - \2. LocalSpace에 push, pop을 해야 한다. 매 메소드마다. 이건 꽤나 큰 loss일 수 있다.
  - 만약 메소드가 LocalSpace를 각각 들고 있고, 여기에 지역변수들이 이미 들어있다면 어떨까? push, pop은 인스턴스를 빼고 넣는게 아니라 단순히 이 원소를 사용한다 사용하지 않는다는 표시만 하는 거라면.
  - 지역변수는 블록문이 있다면 중간에 소멸되기도 해야 한다.
    - 최적화가 되었을때 인덱스는 항상 유지가 되어야 한다. getMember(index)로 접근할 것이기 때문이다. scope에서 배열은 고정되어야 하며, 원소들은 삭제가 일어나서는 안된다. 
    - LocalSpace[n].release(); 를 하도록 한다.
    - 블록문이라는 클래스를 만듬으로써 해결한다.
  - x 1안 Array로 member를 구성해둔다. 그리고 리사이클한다
    - 지역변수의 소멸/생성보다 확실히 미리 잡아둔 뒤에 init하는 편이 빠르긴 하다.
    - init을 하면 안되는, 반드시 생성자를 거처야만 하는 케이스가 있을까?
      - C++이 아니라는 점을 되새겨 보자. init이 수행되는 타겟은  결국 Object다.
      - 개발자가 Object에서 상속받은걸 모듈로 만들기 때문에 생성자를 그대로 사용하면 안될 것이다. 생성자는 1번만 호출 되는 것이며, 생성자를 대신할 월드만의 API인 onConstruct()  인걸 overloading해서 사용해야 한다.
      - 사용자가 만들어놓은 모듈안에 있는 Object를 onConstruct()된다고 하자. 무엇이 발생해야 하는가?
        - Object의 모든 멤버변수들이 초기화되고, 사용자의 생성자함수가 불러져야 한다. 문제는 모든 멤버변수를 월드는 모른다. 사용자는 생성자 대신 이걸 써야 한다.
        - 레퍼런스 초기화가 안된다. 이건 limitation으로 걸 수 있다.
        - 복사생성자는?
          - 1안 그것도 만든다.
          - 2안 대체가 불가능한지 검토 한다.
        - 직접해보면서 검증하자.
          - class MyModule : public Object {
          - private:
            - String* msg;
            - DirectX9Device* device;
          - public:
            - const Result& construct() {
              - msg = 0;
              - device = 0;
            - }
          - }
        - 1안 construct()를 만든다.
        - x 2안 release()로 대체가 불가능한가?
          - release는 원래 있는 걸 재사용하는 것이다. construct라는 메소드를 만들지 않아도 된다.
          - 명시적으로 생성자를 호출할 수는 없다. 근데, 이게 진짜 단점은 아닐 것이다. 원래 그런것이다.
          - msg = 0 같은 케이스는 release에서 대체가 불가능하지....않나?
            - 어짜피 생성자에서 msg = 0으로 된다.
          - 복사생성자는 어떻게 되지?
            - int a = b;
              - Object::assign(obj);
            - MyChildModule b;
            - MyModule a = b;
              - Reference::assign(ref);
                - return binder->assign(ref);
          - 예제
            - class MyModule : public Object {
              - MyModule() : msg(0), device(0) {}
            - public:
              - const Result& release() {
                - if (msg)
                  - delete msg;
                - msg = 0;
                - if (device)
                  - device->ReleaseDevice(0, 0, 0, 0)
                - device = 0;
              - }
            - }
          - --> 고찰을 통해서 지역변수 리사이클은 폐지되었다. 이는, 사용자가 C++ 클래스나 메소드 안에서 지역변수를 만들때는 "생성자 이벤트"를 월드에서 호출할 방법이 없다. 사용자가 클래스를 정의할때 생성자에 "내가 최종 구체클래스라면, 생성자이벤트를 호출하라" 라는 걸 만들 수 밖에 없다. 
          - --> 혹은 사용자는 소멸자 코드를 "진짜 ~소멸자()"와 "release() 함수 안에서 state를 통해서 소멸자여부를 판단해서 수행하는 것"  2개로 나누는 방법도 있으나, 이것도 사용성이 번거롭기는 마찬가지다.
    - Container
    - Cell : Container
    - TCell<Node> : Cell
      - getElement에서는 캐스팅 하지 않음. insert, remove에서만 실시함.
  - v 2안 Array로 멤버를 구성한다. 리사이클은 하지 않는다.
    - IDE모드냐 최적화모드냐에 따라서 동작이 변한다. 
    - IDE 모드일 경우
      - getMember(const String& name)으로 Scope객체에서 심볼을 찾는다. 따라서 Scope의 LocalSpace에 지역변수가 들어만 가있으면 된다.
      - 지역변수 생성시 LocalSpace에 변수를 push하며, 함수가 끝나면 Method는 LocalSpace를 release() 해버리면 된다. (자기껏만)
      - 블록문이 끝나면 LocalSpace의 해당 element만 release된다. 
      - LocalSpace는 Array<Bind<Object>>가 된다. (Reference나 Object가 올 수 있다.
    - 실행모드일 경우
      - 컴파일러는 코드를 완전히 분석, 실행하여 이 시점에서 생기는 지역변수가 몇번 index의 LocalSpace에 들어가는지 파악해야 한다. 
      - 그렇게 되면, 
        - 지역변수를 생성하는 Statement는, push가 아니라 setElement를 쓰도록 해서 탐색 속도를 낮추고 메모리 점유를 줄일 수 있다.
        - 심볼 접근시 문자열 비교가 아니라 getElement(index)로 하면 더 빨라진다.
      - 그 이외의 블록문이 끝나면 LocalSpace에서 remove하는 것, 함수가 끝나면 Method는 LocalSpace를 release() 해버리는 것(자기껏만)은 동일하다.

- LocalSpace는 어떻게 관리되는가?

  블록문 으로 해결한다. 

  - 1안 Scope에서 Unique로 관리. 이경우 메소드는 Scope를 사용하는 관계가 된다.
    - 1안 메소드는 시작전에 esp를 저장하듯이 pop을 해야 하는 index를 알고 있어야 한다.
    - 2안 Cell로 구성한다.
      - LocalSpace를 Cell<Bind<Node>>로  구성한다.
      - 블록문이 끝나면 setElement(index, NULL)로 만든다. Cell이라도 sort는 일어나지 않는다.
      - Method가 끝나면 Method는 처음 시작시 알아둔 LocalSpace의 length로 복원한다.
  - 2안 매 메소드호출에서 

- 더 최적화할 수 있다.

  - Statemenet의 심볼이 LocalSpace인지, 어느 객체의 것인지 정해놓으면 더 빨라질 수 있다.
  - LocalSpace::pop()은 심볼을 진짜 삭제하는 것이 아니라 





#### scope에서의 식별자 검색과 모호성의 오류의 기준

- 인터프리터는 파싱하면서 식별자를 Scope에게 질의한다. 
- Scope는 LocalSpace, ObjectSpace(me, this), GlobalSpace 3개의 영역을 갖고 있고, 각 영역에 식별자와 매칭되는 객체를 찾을때까지만 탐색한다.
- 만약 LocalSpace에 객체를 찾지못하면 ObjectSpace에 질의하고, ObjectSpace에서도 찾지못하면 GlobalSpace에서 질의한다.
- 만약 한 Space에서 2가지 이상의 식별자가 발견되더라도 블록문 안에 있는 경우에는 예외적으로 허용되기때문에 존재할수 있다.
- 따라서 블록문기준으로 중복을 체크하던가 아니면 validation에서 이걸 처리해야 한다.
- 시나리오
  - class MyClass
    - int a
    - int b = 1
    - void foo(int aa)
      - int b = 2
      - void foo(int a1)
      - foo(b)
        - // b는 LocalSpace에 있으므로 ObjectSpace의 a는 탐색하지 않는다. 값은 2이다.
        - // 그러나, this.foo(aa) 도 매칭되지만 me.foo(aa)도 매칭된다. 같은 ObjectSpace이므로 모호성의 오류가 발생된다.
        - void _koo()
          - do-somthing...
        - void _goo()
          - _koo() // 에러. _koo는 me._koo()가 될텐데, me는 _goo이며 아무런 nested method를 갖고 있지 않다. _koo()는 foo()가 갖고 있다.
  - MyClass cls
  - cls.foo()
- 1안 space별로 별도로 가져간다. 
  - GlobalSpace  & ClassSpace : isConsumable(msg) 가 2개 이상 있으면 안됨
  - LocalSpace : 있어도 됨. 맨 앞에거 기준으로 찾음.
  - Scope의 space는 container로 구성되어있으며 global과 classspace는 각각 container가 다르다(array vs chain) 따라서 이 둘을 합칠 수는 없으므로 별도의 class space라는 걸 만들지는 않는다. scope.validate()를 하거나 별도의 경로로 scope가 감지하도록 한다.









#### Scope_중_지역변수와_함수명의_충돌문제 

- 지역변수는 a.foo 처럼 접근하는 것이며 함수는 a.foo(void)로 접근하는 것이다. 표기가 다르므로 충돌이 일어나지 않는다. --> #객체의_함수_접근이_이름만_가지고는_불가능하다_왜냐하면_오버로딩을_지원하기_때문이다 참조.

- 단, 앞으로 Deduction을 지원하는 경우에는 함수명만 가지고 사용할수 있어야한다. 만약 이걸 지원한다면 애로사항이 생길수 있다.

- 고찰 내용

  - c++에서는 지역변수와 함수명이 같을 경우 어떻게 할까. 사용법이 다르기 때문에 코드상에 모호해지는 케이스는 없다.

  - 반면 변수명과 클래스명은 모호해질 수있기에 이것은 100% 에러일 것이다. 또한, 반면 변수명끼리는 겹처도 무시를 해주지 않는가. 대표적으로 블록문안에서의 중첩된 변수명의 경우. 어떤때는 중복이라며 에러를 내보내야 하고, 어떤때는 중복이라도 그냥 가야한다. 이 컨셉을 정해야 한다.

    





### 복제 상속
접근자  오버라이딩






### 확장

#### 1
-   이미 존재하는 클래스A에 메소드, 멤버변수를 추가하는, 클래스의 내용물을 add 하는 기능이다. 주로 연산자 오버로딩을 정의할때 사용한다.
-   import kukullza.print
-   class COut
    -   COut operator+(COut rhs)
        -   ...
-   class MyMyModule
    -   MyMyModule()
        -   ...
    -   Node to(Class cls)
        -   Node casted = [super.to](http://super.to/)(cls)
        -   if(casted) return casted
            -   --> return if([super.to](http://super.to/)(cls))
        
        -   if(cls == COut)
            -   return COut(age);
    -   MyMyModule +(MyMyModule rhs)
        -   ....
-   class COut extend kukullza.print
    -   COut operator+(MyMyModule m)
        -   return COut(m.age)
    -   Node to(Class cls) //--> compile에러. print.Cout 은 이미 to가 있을 수 있다. 그 경우 MyMyModule(Cout) 생성자를 이용해야 한다.
        -   ...
-   COut + MyMyModule() // ok
    -   1. COut.+ 후보군을 모두 뽑는다.
        -   +(COut)
        -   +(MyMyModule) 2개.
    -   2. 정확히 MyMyModule을 받을 수 있는 +()가 있으면 그걸로 한다.
    -   3. 만약 없는 경우 인자가 캐스팅 될 수있는지 따진다.
        -   만약 extend from을 안했다면 MyMyModule이 COut이 될 수 있는가. 캐스팅이 되는가. 캐스팅은 to를 통해서 이루어진다.
        -   COut(MyMyModule)이 define이 되어 있다면 MyMyModule --> Cout이 가능한 상태가 되므로 호출될 수 있다.
    -   4. 가능성이 여러개만 모호성의 오류가 나온다.
-   MyMyModule + Cout // ok
-   MyMyModule m1 = COut() // ok
-   COut c1
-   MyMyModule m1 = (MyMyModule) c1
-   extend from이 의미는 확실한데 너무 길다. 한 단어로 줄여본다면? --> 걍 extend로 하자.
-   파서가 어떻게 원본을 읽지 않은 상태에서 extend를 만났을때 원본을 먼저 읽도록 유도할 수있는가?
    -   먼저 읽도록 유도는 불가능하다. 이러면 C++ include의 동작과 동일하기 때문에 결국은 무한순환재귀 오류가 생겨버린다.
    -   Generating단계외 linking단계를 2개로 만들어 2pass로 ClassStackingUp 알고리즘으로 해결한다. --> #클래스_Generating과_상속문제
-   예전에는 넣지 말자고 생각했었다. 그 이유는...
    -   이 기능은 장점보다 단점이 매우 많아 지원 하지 않기로 결정되었다. 근거는 다음과 같다.
    -   장점이 희박하다. 개발자가 임의클래스A의 코드를 알지 못하며, 클래스의A의 멤버변수와 함수를 접근하거나 사용할 수 없어야 하며, 부득이하게 자신의 코드를 클래스A가 속한 컴포넌트에 주입시킬 방법이 없거나, 원 개발자가 마련해 두지 않을때 아주 제한적으로 사용이 가능하다. 단, 이렇다하더라도 주입한 코드가 기존의 로직에는 영향을 미치지 않는다.
        -   왜냐하면 주입할 클래스의 코드를 모른다는 전제조건이 있기 때문이다. 코드를 안다면, 그 코드에 바로 수정을 하면 된다. 모르기 때문에 이 기능이 필요한 것인데, 모른다는 것은 기존 함수나 멤버변수를 호출 할 수 없다는 것과 동치다. 따라서 의존성을 주입하는 것이 아니라 단순히 "완전히 기존 로직과 분리된" 로직을 투명한 벽을 사이에 둔 채 추가하는 것" 뿐이다. 설사 추가하였더라도 기존의 로직은 추가한 로직을 호출할 방법이 없으므로, 사실상 서로 영향을 미치지 못한다.
    -   고찰해보면 오버라이딩을 가로채는 용도 + 외부에서 호출하는 용도(이를 테면 operator+(int))로만 사용이 가능하다.
    -   오버라이딩을 가로챈다는 것은 기존 OOP에서도 가능하다. 하지만 이걸 제한두지 않고 문법을 통해서 보다 편리하게 해준다는 것은 마치 이러한 OOP룰을 어기는 걸 권장하는 듯한 늬앙스를 갖기 쉽다. 개발자가 만들어둔 클래스 집합은 하나의 컴포넌트로써, 말하자면 잘 가꿔진 정원과 같은 것이다. 이걸 수정하는 건 상당한 리스크를 동반하며 일반적으로 속속들이 잘 구현을 꿰고 있을때 가능하다. 그렇게 되려면 코드를 다 알 고 있어야 할 것이다.
    -   고찰내용
        -   어디서든 이미 만들어진 특정 클래스의 메소드 구성을 추가할 수 있다.
        -   그 형식은 클래스를 선언/정의하는 것과 똑 같다.
        -   컴파일 타임에 확정되므로, World의 정적 에러 체크는 논리적으로 작동가능하다.
        -   실제 코드는 분산되지만 소프트웨어의 브라우징은 비주얼로 이루어지기 때문에 마치 처음부터 한 곳에 정의된것처럼 보여지게 할 수 있다.
        -   덮어쓰는 것은 안된다. 어디까지나 추가만 가능하다.
            -   덮어쓴다는 의도는 사실 중복정의로, World 입장에서는 선후관계를 알 수 없다.
        -   예제
            -   ///////// 외부 모듈에서 가져온 것들 ///////////////
            -   class Person
                -   result eat() { Console.out("Do Nothing!") }
                -   string name = ""
            -   class Student
                -   Student()
                    -   name = "Chales"
            -   //////////////////////////////////////////////////////
            -   // 여기서부터 개발자의 World 코드
            -   class Student
                -   result eat() // 외부 모듈의 클래스에 eat를 오버라이딩함.
                    -   // 만약 외부모듈에 eat()이 있었다면 여기에서 에러가 발생한다.
                    -   Console.out("Let's eat!")
            -   class Main
                -   result main(String[] args)
                    -   Student std
                    -   std.eat() // --> Let's eat!이 나온다.
        -   문제점은 없을까? 물리적으로는 가능한데, 논리적으로 맞을까?
            -   대체 무슨 장점이 있는가?
                -   오버라이딩을 가로챈다.
                    -   c++에서는 이럴때 클래스를 상속해서 오버라이딩 하는 게 정석이다.
                        -   class MyStudent : public Student
                            -   result eat()
                                -   Console.out("Let's eat!")
                        -   result main(String[] args)
                            -   MyStudent std
                            -   std.eat()
                    -   만약 모듈A가 이미 잘 동작하고 있을때 그 중에서 특정 함수의 기능만 살짝 추가하고 싶은 경우가 있을 수 있다. 그러나 모듈A의 코드를 볼 수는 없다. 그리고 추가하고 싶은 함수는 모듈외부에 드러나지 않고 내부에서 사용되는 것들이다(이를테면 Logger) 내부소스를 변경하지 않고 코드만 변경하고 싶다면?
                    -   이럴때 사용할 수 있지 않을까?
                        -   하지만 함수가 정의되어있지 않아야 한다는 제약이있다. 따라서 매우 드문것이다. 그런 케이스는.
                -   멤버변수를 조작할 수 있다.
                    -   함수를 넣을 수 있다는 건, 그 함수 안에서 멤버변수들을 조작할 있다는 것이다. 이는 장점과 동시에 단점이 된다.
                    -   사실상 접근제한자를 무시할 수 있는 방책이 생긴것이다.
            -   쉽게 중복정의가 되버릴 수 있다.
                -   모듈A를 가져왔다.
                -   거기에서 오버라이딩을 하고 싶어서, B클래스에 추가했다.
                -   모듈B가 필요해서 가져왔다.
                -   그런데 모듈B에서도 A모듈의 B클래스에 함수를 추가하고 있던 것이다.
            -   Namespace 가 중요해보인다.
                -   그냥 class Student라고 적으면 안되겠지. 모듈A안에있는 Student라는 걸로 인식되어야 한다.
                -   이건 namespace 를 정의하는 문제와도 닮아있다.
            -   유효성이 깨진다.
                -   클래스는 책임을 중심으로 돌아간다. 접근제한자를 둔것은 그것을 막기 위한 것이다.
                    -   그렇지 않다. 사실상 friend를 하건, Java reflection을 하건, 상속을 하건 해서 하려고하면 얼마든지 피할 수 있다.
                -   접근제한자의 의미는 "다른 개발자들이 무엇을 집중해야 하는지"에 달려있는 것일 뿐이다.
                -   정리하면 유효성은 깨질 수 있다. 그리고 World는 어떻게 설계하든 그것을 막을 수 없다. 그것은 개발자의 역량에 달린 것이며, 우리가 할 수 있는 것은 개발자들이 그러한 것을 하고 있을때 최대한 개발자로 하여금 "내가 잘못된 것을 하고 있구나" 라는 감각을 주는 것 뿐이다.
                -   함수를 만들어서 집어넣는 것은 그러한 감각에 둔하게 느껴지지 않는가?
                    -   리플렉션에 비해서.








### 제네릭







### 오버라이딩 재지정 연산자






### 프로퍼티







### 클로저

#### 중첩메소드를 람다로 발전 시킬 수 있는가?

- 생각해보니, 이는 특별한 기능이 아니었다. 그냥 반쪽자리 람다에 불과하다.
- **이는 "지역 변수는 메소드가 미리 생성해놓고 있어야 할까 아니면 그때그때 생성해야 할까"를 해결하기 위한 것이다.**
- x 1안 변수 정보없이 공유한다
  - class A
    - foo()
      - void _nested()
        - cout << age // 이 age가 실제로 무슨타입인지 전혀 알 수 없다.
      - _nested() // 빌드에러
      - {
        - int age = 5
        - _nested() 
      - }
      - {
        - float age = 3.5
        - _nested() // 타입 확정이 무너진다. 
      - }
- 2안 이제 람다 문법과 설계가 정해졌다
  - class A
    - void print(int age)
      - void print(int newage) // err
      - void _print(int newage)
        - set(newage)
        - Console.out("age = " + _age)
      - void set(int age)
        - _age = age
      - int _age = 0
      - return print(int) // err





#### 중첩 메소드 개념 기본

- 중첩메소드에 대해

  - 중첩메소드는 메소드에 소속되지 않는다. 단지 scope 적으로 잠깐 visible하고 마는 것이다. 이는 함수 내에서 reuse를 높이고, 함수내에서만 사용되는 함수, 그 밖에서는 몰라도 되는 함수로 구분지으므로써, readailbity를 높이고자 하는 것이다.
  - 코드상으로는 Method가 별도의 배열로 갖고 있으며 Method가 scope에 members를 등록하고 나서 이 중첩메소드들을 그 위에 얻고, 지역변수를 얻는다.
  - 따라서 호출 우선순위는 ObjectSpace 보다 위이며, LocalSpace보다는 아래다.
  - 외부 개발자(Native포함)나 외부 클래스, 모듈에서는 절대 중첩메소드를 접근이 불가능하다.

- Method는 LocalSpace에서 관리되므로 Ownee Method에서 owner 메소드에서 선언된 지역변수를 참조 할 수 있다. == closure 

- 고찰내용

  - MyFoo f1

  - f1.print()

    - // Msg(Msg(Msg(scope, "get", "f1"), "get", "print(void)")), "execute", {})

  - f1.print(void).getName()

    - // Msg(Msg(Msg(scope, "get", "f1"), "get", "print(void)")), "getName", {}) 일때...

  - v getName()도 메소드다. 그렇다면 getMethod.getMethod.getMethod.getMethod.... 도 가능한거 아니냐.

    무한 루프 없음. 증명됨. 

    - World는 메시지 기반.
    - 메소드는 msg를 직접 처리할 수 있는 무언가이다. Object는 target으로 이용되거나 msg를 전달할뿐 자기가 msg를 처리하지는 못한다.
    - Object.getMembers()를 하면 class.getMembers()를 가져와서 이걸 chain하여 자기 변수들을 추가(class.getVariables().clone()) 한다.
    - Class.getMember()가 처음 불려지면 T::onInitializeMethods()를 불러서 초기화한다.
    - 위의 상황에서 생각해보면 쉽게 답이 나온다.
      - class MyFoo : Object
        - void print();
      - MyFoo my; // 이시점에서는 아무런 초기화도 일어나지 않음.
        - my.getMember() 호출 --> getMember가 처음 호출이니 getClass().getMembers()를 불러서 chain시도 --> TClass<MyFoo>().getMembers()가 처음 불러진 경우 MyFoo::onInitializeMethods() 호출 --> MyFoo::onInitializeMethods()는 Super::onInitializeMethods() += Method<print>() 를 append해서 반환함. --> TClass<MyFoo>는 독자적인 Method<print>() 객체를 갖게 됨 --> MyFoo 객체는 TClass<MyFoo>의 멤버를 chain함. 즉 MyFoo가 갖고있는 Method<print>는 TClass<MyFoo>의 것임. TClass<MyFoo>가 갖고 있는 Method::getName() Method객체도 TClass<MyFoo>만의 것임.
      - my.getName(void).getName(void) 를 한 경우
        - my.getName(void)는 사실상 TClass<MyFoo>가 독자적으로 갖고있는 Method(getName)를 반환함. --> .getName(void)를 하면 이 Method(getName)은 처음으로 getMembers()가 불러졌으므로 TClass<Method>::getMembers()를 호출함 --> 결과적으로 TClass<Method>에 독자적인 Method<getName>()객체가 들어가게 됨. 
      - 여기서 이 반환값에 다시 .getName(void)가 호출한다면? 
        - TClass<Method>::getMembers()에 들어있는 Method<getName>은 getMembers가 호출된 적이 없으므로 TClass<Method>::getMembers()를 호출 함 --> 결과 자기자신이 들어있는 Members를 chain함.
        - 도식화하면 이런거임
        - Method::getMembers() --> TClass<Method>::getMembers()
        - TClass<Method>::getMembers() "HAS" Method()
      - **결론: slave가 생성하면서(하고나서) owner의 ptr를 갖는 것은 흔히 있는 것이다. 재귀적 무한루프는 발생하지 않는다.**
    - 실용적으로 접근하기
      - 재귀적 참조 문제
        - 설명
          - class Foo
            - void print()
              - ..
          - Foo f
          - f.print(void).getName().getName().getName()..... 이게 되면 안된다?
        - 구현이 가능한가?
          - 호출의 관점 --> ok
            - f.print(void).getName()은 Method::getName()인 "print(void)"가 나온다. 이는 정확히 말하면 f.print(void).getName(void).execute 인 셈이다.
          - 초기화의 관점
            - class FooObject : Object
              - FooObject()
                - Super()
            - class Object
              - Object()
                - 
            - class TClass<Foo>
              - TClass<Foo>()
                - Super()
            - class Class
              - Class()
                - initialize();
              - initialize()
                - _methods = Super::getClass().getMethods();
                - _methods += onInitializeMethods()
            - }
            - class Method : Source
              - onInitializeMethods(arr)
                - Super::onInitializeMethod(arr)
                - arr += Method(getName) // Class<Method>는 Method(getName)를 가짐.
              - const String& getName()
            - class Foo inherit Object
              - onInitializeMethods(arr)
                - Super(arr);

  - v WorldLang에서 중첩메소드를 어떻게 구현할까?

    - foo()
      - v getName() --> 자, 이거는 foo.getName()이냐, Me.getName()이냐?
        - x 1안 this다가 기준이 되어야 한다.
          - 일반적인 메소드에서도 생략의 기준은 this이지, method자체가 아니다. 일례로 메소드 안에서 getClass()를 하면 Object의 클래스가 나와야지 메소드의 클래스가 나와서는 안된다는 것이다. 마찬가지로 중첩메소드에서도 기준은 this이기 때문에 중첩메소드를 호출하려면 앞에 me를 붙여야 한다.
          - 예)
            - class My
              - void foo()
                - string _get()
                  - return "hello world"
                - result _print(string msg)
                  - return Console.println(msg)
                - me._print(me._get())
                - _print(me._get())
              - void _print(string msg)
                - return Console.println("msg = " + msg)
        - v 2안 중첩메소드도 me. 없이 바로 호출되게 한다.
          - 예)
            - class My
              - void foo()
                - string _get()
                  - return "hello world"
                - result _print(string msg)
                  - return Console.println(msg)
                - _print(_get())
                - this._print(_get())
                - getName()
                - me.getName()
              - void _print(string msg)
                - return Console.println("msg = " + msg);
          - **이 관점은, 중첩메소드는 Method에 속한 것이 아니라 scope의 관점에서 일시적으로 Object에 추가되었다가 빠지는 것**. 라고 보는 것이다. 즉 중첩메소드는 Method의 멤버가 아니다. 단지 Method는 별도의 중첩메소드용 배열을 들고 있다가 자신이 scope에 등록될때 이 배열을 localspace에 얻는것에 불과하다. 따라서 이 메소드에 들어온 순간에만 중첩메소드들이 visible해진다. 
          - 각 중첩메소드들의 소속은 어디까지나 Object이다. 따라서 저 중첩메소드들만 LocalSpace 영역에 살짝 올라간다.
          - 충돌을 방지하기 위해서 중첩메소드는 private다. 즉 앞에 _를 붙이게 된다. 그러면 getName() 을 중복 정의해서 충돌되지는 않을 것이다. 이는 사용자가 public 메소드를 메소드 안에 정의하게 하는 것을 의례 사용하지 못하도록 막으려는 것이다. 중첩메소드는 어디까지나 "요 함수 내에서만 작게 쓰이고 싶어" 를 위해서 나온것이지, 외부 함수까지 메소드 안에 쓰게 되면 foo.print.getAge() 처럼, 메소드의 의의가 사라지게 된다.
          - 그리고 이는 C++의 중첩클래스와 완전히 궤를 같이한다. scope의 문제로 만드는 것이다. scope를 제외하면 외부에서 이 함수를 접근할 방법이 없으며, 순간적으로 사용되고 그 외에는 사라진것 처럼 보인다. 작은 scope 내에서 반복 작업을 reuse하는 용도로만 사용되며, 메소드 안에 속한 메소드가 되지 않게 한다.
      - v Native 개발자가 중첩메소드를 다루는 시나리오는?
        - C++에서는 중첩메소드를 사용할 수 없으므로, Managed에서 만든 중첩메소드를 Native에서 다루는 시나리오만 검토하면 된다.
        - 요지는, 중첩메소드는 NodeTree에 안보인다는 것이다. 따라서 엄밀히 말하면 Native 개발자는 중첩메소드에 접근할 수 없다.
      - v Native에서 call을 사용한 경우라면 어떨까?
        - 이 경우도, Managed 개발자가 작성한 로직에서만 중첩메소드가 사용되므로 폐쇠적으로 완전하다. 외부자(= Native 개발자)가 간섭할 수 없다. (Method 객체를 얻어서 뭔짓을 하면 되긴 할것이다)
    - string getName()



#### Delegator와 closure는 다른 것이다. 

- Delegator는 메소드들을 가리키는 것. closure는 지역변수를 내포할 수 있는 메소드. 2개는 별개의 클래스가 되어야 한다.



#### Delegator의 기본

- Delegator는 Method의 일종이며, 동시에 Method의 proxy이다.

- Delegator는 sharable이며, 사용자는 주로, Refer<Delegator>의 형태로 사용하게 된다. (Proxy의 Proxy)

- 고찰내용

  - Delegator는 단순히 method를 가리키는 것. static과 instance 2종류가 있다. capture된 delegator는 캡쳐 기능이 탑재된 delegator. 역시 static과 instance 2종류가 있다.

  - [v] 문제 2 - World 문법적으로 각 Delegator는 static여부, 인자가 동일하지 않으면 서로 할당이 이루어져서는 안된다.

    - 예)
      - void(void) a
      - void(int) b
      - void A.(int) c
      - a = b = c // 모두 컴파일 에러가 나야 한다. 
    - 다시말하면 인자타입과 static여부 자체가 하나의 타입으로 다뤄줘야한다. 어떻게 할까?
    - Delegator& a;
    - Delegator& b = a; // 이거 되야 하나 안되야 하나?
    - StaticDelegator a1;
    - StaticDelegator b1 = a1; // 이건 되야 하나 안되야 하나?
      - **당연히 안되야 정상이다. a1이 어떤 메소드를 가리키는 뭔지알고 교체하는가? 이건 마치 이런거다.**
    - [v] 1안 StaticDelegator::operator=(rhs)에서 rhs와 자신의 getParams()가 동일하며 static여부가 일치한 경우에만 _origin을 교체한다. closure여부는 고려하지 않는다.
      - operator=(rhs)는 assign(it)으로 결국 간다. assign(it)은 Refer<Delegator>::assign(it)이 호출되게 되어있다.
    - [x] 2안 Delegator들은 모두 operator=()를 막는다. 필요하면 c++개발자보고 clone()을 사용하라고 하라.
    - [x] 3안 그냥 풀어준다. C++ 대로 설계한다.

  - [] 문제3 되는건 컴파일시에 world문법상에서는 delegator들의 연산을 막아야 한다는 점이다.

    - void(void) a
    - void(void) b = obj.print
    - void A.(void) c
    - c = b 에러
    - a = c 에러
    - a = b ok
    - 이걸 컴파일타임에 할 수 있어야 한다. 즉 월드문법에서 중요시 생각하고 있는 건 타입리스트 + staitc여부 2개이다. closure는 고려하지 않는다는 걸 알 수 있다. 사용자의 입장에서 생각하고 있는 것이다.
    - [] 어떻게 할까?
      - [x] 1안 wygiwys로 간다. 
        - [] static딜리게이터는 어느때건 closure화될 수 있으며 반대도 가능하다. 이말은 static딜리게이터는 closure 화되는 코드를 담고 있거나, 이걸 외부에서 주입할 수 있다는 것이다. 이대로 c++코드도 따라간다.
          - 이건 어떻게 할까? 중요한건 코드가 아니라 멤버변수다.
          - 캡처를 하려면 다량의 멤버변수를 요구하게 된다. Object Refer 1개와 캡쳐한 로컬스페이스 Array 1개. 막대한 비용이 든다. 이걸 매 static delegator마다 탑재하게 하자고?
        - 월드 코드에서 사용자가 딜리게이터에 closure냐 static딜리게이터냐를 결정하는 건 rhs에서 object의 유무로 판단된다.
          - class A
            - void print()
          - A a
          - void(void) fptr1 = A.print (그냥 static delegator)
          - void(void) fptr2 = a.print (클로져)
      - [v] 2안 Delegator::assign() 재정의
        - 같은 타입일뿐만 아니라 getParams()가 완전히 동일해야만 할당이 이루어지도록 한다.
        - 월드 컴파일러는 

  - [x] 1안 Delegator > InstanceDelegator > Closure 순으로 상속

    - Delegator
      - // Method에 대한 Refer
      - InstanceDelegator
        - // thisptr를 method에서 추출해서
        - Closure

  - [] 2안 Delegator Slice 패턴

    유일하게 구현 가능한 안이지만, 너무 구현이 더럽다. 다른 방법은 없을까? 

    - class Delegator : public TRefer<Method>, public Methodable
      - Delegator(Params&, bool is_static, Pattern& new_pattern)
      - Delegator(const Method& method) : _params(method._params), _is_static(method._is_static), _patt(InstancePattern) {}
      - Delegator(This& rhs) : _is_static(rhs._is_static), _params(rhs.params), _patt(rhs._patt) {}
      - TStrong<Params> _params; *// 월드컴파일러(=WC)는 Method의 것을 복제시킬것인지, 아니면 새로운 Params를 넣어줄 것인지 정할 수 있음. 생성자에서 주입되며, 주입되면 2번다시 변경안됨.*
      - virtual const Params& getParams() { return *_params; } *// WC는 변경할 수 있음.*
      - virtual Refer to(const Class& cls) {
        - if cls.isSubOf(Method) 
          - return *this;
        - return Super::to(cls);
      - }
      - virtual assign(Thing& it) {
        - Method& casted = [it.to](http://it.to/)<Method>().get();
        - if(casted.isNull() || casted.getParams() != getParams() || isStatic() != it.isStatic())
          - return FAIL
        - if(Super::assign(it))
          - return FAIL
        - if(it.isSubOf(This))
          - Delegator& casted = it
          - _patt = casted._patt;
      - }
      - TStrong<Pattern> _patt;
      - bool _is_static;
      - virtual run(Msg& msg)
        - return _patt(this, msg);
      - virtual isStatic() { return _is_static; } *// Node::isStatic() { return false; }*
      - *// isStatic이 true이면 InstanceDelegator라는 뜻이 된다.*
      - virtual bind(Node& method) {
        - Method& casted = node.cast<Method>();
        - if casted.isNull() || isStatic() != casted.isStatic() || getParams() != casted.getParams()
          - return FAIL
        - if(Super::bind(method))
          - return FAIL
        - *// 메소드를 바인딩한다는 것은 closure가 아니게 되는 것이다.*
      - }
      - virtual Delegator capture(Scope& scope) *// from Methodable*
        - return *this;
      - class Pattern
        - ...
      - class StaticPattern
      - class InstancePattern
      - class ClosurePattern
    - }

  - [x] 3안 Delegator와 Refer<Delegator> 패턴

    Refer<Delegator>도 params를 들고있어야 하므로 Params는 총 3개가 된다. 실패. 

    - class Binder
      - bool isBindable(const Node& obj) = 0;
    - class Refer
      - virtual bool isBindable(const Node& obj) {
        - return obj.isSub(_cls);
      - }
      - virtual assign(Thing& it) {
        - if( ! isBindable(it))
          - return FAIL
        - ...기존코드...
      - }
    - class Delegator : public Method
      - *// Params에 Thisptr를 넣고 is_static을 false로 가져가면 InstanceDelegator가 나오게 된다.*
      - Delegator(Params&, bool is_static)
      - Delegator(const Method& method) : _params(method._params), _is_static(method._is_static) {}
      - Delegator(This& rhs) : _is_static(rhs._is_static), _params(rhs.params), _patt(rhs._patt) {}
      - TStrong<Params> _params; *// 월드컴파일러(=WC)는 Method의 것을 복제시킬것인지, 아니면 새로운 Params를 넣어줄 것인지 정할 수 있음. 생성자에서 주입되며, 주입되면 2번다시 변경안됨.*
      - virtual const Params& getParams() { return *_params; } *// WC는 변경할 수 있음.*
      - TRefer<Method> _method;
      - *// delegator.assign(another_delegator)만 지원한다.*
      - *// delegator.assign(method)를 하고 싶다면 bind를 사용하라. assign은 같은 obj에 한해서만 지원이 되니까.*
      - *// isStatic이 true이면 InstanceDelegator라는 뜻이 된다.*
      - bool _is_static;
      - virtual isStatic() { return _is_static; } *// Node::isStatic() { return false; }*
      - virtual bool isConsumable(msg) {
        - if(_method.isBinded())
          - return _method->.isConsumable(msg);
        - return false;
      - }
      - virtual Refer run(Msg& msg)
        - if( ! isBinded())
          - return Refer();
        - return get().run(msg);
      - virtual isBindable(Node& it) const {
        - if( ! Super::isBindable(it))
          - return false;
        - const This& casted = (const This&) it;
        - return casted.isExist() && it.getParams() == getParams() && isStatic() == it.isStatic();
      - }
    - class Closure : public Delegator {
      - Chain _captures;
      - virtual Refer run(Msg& msg) {
        - if ! isBinded()
          - return Refer;
        - swap captures
        - Refer ret = get().run(msg);
        - swap origins
      - }
    - }



##### Delegator의 capture 컨셉

- TEST
  - class A
    - void foo()
      - int a=3  // a가 주석처리되면 err
      - void _b()
        - _a() // ok
      - void _a()
        - print(a)
      - if a==5
        - int a = 11
        - _b() // 3이 찍힌다.
- Closure는 정의와 동시에 지역변수와 메소드를 바인딩한다.
  - 정의된 이후, 내부에서 참조하는 변수/메소드와 동명의 다른 식별자가 등장한 경우에도, closure는 정의된 시점의 바인딩을 따라간다.
- 고찰내용
  - [v] Closure는 지역변수 참조가 가능한 중첩메소드.
    - *[x] 만약 #지역변수-중복-되는-경우-scope는-어떻게-구현해야-하는가 이걸 동일한 인덱스가 나오도록 해결할수 있다면 closure는 캡쳐가 필요없게 된다. 왠냐하면 closure가 소지한 STMT들이 항상 언제 호출되건 동일한 scope[index]의 지역변수를 참조해버리면 되기 때문이다.*
      - [v] 반론 - 멤버변수 vs 지역변수로 총돌되는 경우는 여전히 안될 것 같다. 이런 상황을 봐라.
        - class A 
          - int a = 3
          - void foo()
            - Console.out(a) *// 1*
            - int a = 5
            - Console.out(a) *// 2*
        - 1과 2는 당연히 결과가 다르며, 1의 a의 scope[인덱스]와 2의 a의 인덱스는 설사 *#지역변수-중복-되는-경우-scope는-어떻게-구현해야-하는가* 이걸 해결한다 해도, 풀리지 않는다.
    - [v] 지역변수 중복 문제
      - 문제정의 : closure는 함수. 함수내에서는 여러개의 변수를 둘 수 있다. scope당 1개. closure가 변수 a를 바인딩하는 경우, 이 a는 뒤에 여러개가 나올 수 있다. 이때 어떻게 world는 동작해야 하는가?
      - [v] 1안 closure 정의 == closure의 바인딩. 즉, 처음 정의시 등장한 a만 그대로 쭉 사용하게 된다.
    - [v] 함수는 뒤에 나온걸 미리 사용할 수 있다. 그러나 변수는 그렇지 못한데?
      - 예)
        - class A
          - void foo()
            - int a  // a가 주석처리되면 err
            - void _b()
              - _a() // ok
            - void _a()
              - print(a)
      - [v] 왜 a가 주석처리되면 err인가. _a는 뒤에 나와도 괜찮은데?
        - 변수는 함수내에서 사용된다. 함수는 절차적으로 수행된다. 따라서 변수의 정의는 "시간"이 중요해지기 때문이다. 시간에 의존되기 때문에 변수를 바인딩하려면 그 변수가 미리 나와야 한다. 이건 당연한 것으로 다음 예제를 보면된다. world만의 특징이 아니다.
          - class A
            - void foo()
              - print(str1) // err. str1이 존재하지 않는다.
              - str str1 = "hello" // str1의 값은 함수내의 "시간"에 의존된다.
              - boo() // boo함수는 유일하기 때문에 boo는 호출이 된다.
            - void boo()
            - 





#### 메소드는_어떻게_캡쳐가_이루어지는가_캡쳐_문법

- 문제 정의 
  - \#람다메소드 에 의하면 결국은 closure가 지원이 되려면 일반메소드가 thisptr등을 모조리 싸안고 내적화 되어야 하며, 그것을 trigger하는 방법이 필요하다.  크게 3가지 방법으로 나뉘어진다.
    - \1. API화 시키며, 사용자에게 이 것을 강제하는 경우
      - 예) class A 
        - void foo(int a, bool b)
      - A a
      - void(int, bool) closure1 = a.foo.capture(a)
    - \2. API로는 만들지만, 특정 상황이라면 syntactic sugar처럼도 동작하게 한다.
      - 예) class A
        - void foo(int a, bool b)
      - A a
      - void(int, bool) closure1 = a.foo // 실제 코드블럭은 a.foo.capture(a)로 변형한다.
      -  // 문제는 어떻게 이렇게 만들것인가? 와 모든 시나리오를 찾아낼 수 있는가? 
- [v] 1안 외부 API로 두고, syntactic sugar로는  제공한다.
  - \#closure_syntactic_sugar
  - Method는 Object에 속한것이 아니다. Class에 속한 것이며 Object들은 Method들을 간접적으로 공유해야 한다. 이거는 fix된 사실이다.
  - 그런데 특정시점에서만 Method를 Object에 속한 것처럼 사용하고 싶다는 것이다. 여기까지는 좋다.
  - 문제는 특정시점이 순간이 아니라 경우에따라서는 늘어지게도 될 수 있어야 한다.
    - 예) Method fp = a.foo
    - ....do something...
    - fp.capture() *// Method.to<Delegator>()가 가능하려면 결과적으로 이렇게 인자를 받지 않는 capture를 정의할 수 있어야 한다.*
    - 예2) Method fp = .....;
    - ....do something at c++....
    - fp.capture();
  - 따라서 이거는 말이 되지 않는다. 순간적으로 Object에 속한것은 그나마 이해할 수 있어도 간격이 늘어나서도 Object에 속한 것이 유지가 되어야 한다면 Method*를 가지고 있는 수 밖에 없다. 그렇다고 늘어난 간격에서의 capture()는 허용되지 않고 오직 .으로 받고 나서 순간적으로만 capture()사용이 허용된다면 이것도 사용상에 문제가 있게 된다. 사용자는 capture()를 할때마다 매번 이걸 기억하고 있어야 한다. 또한 눈에 보이지 않는 의존성(시간에 대한)이 존재하게 되며 눈치채기 힘들다.
  - 대책
    - capture(Object&) 가 되어야 한다. 그리고 call(Msg) Msg에는 반드시 Thisptr가 들어가야만 한다. 다만 매번 월드코드에서 이렇게 작성하면 귀찮기 때문에 syntactic sugar를 추가한다. 그렇게 되면 월드코드로 부터 생성된 Expr 내부에서 위의 귀찮은 This를 넣는 작업이나 capture()안에다가 this object를 넣는 작업들을 대신하게 될 것이다.
    - Native 사용자들의 경우 Object에서 Method를 꺼내서 그 Object를 넣은 Msg를 만들어서 다시 Method에 떤지는 일련의 과정들이 매우 귀찮을 것이므로 이를 위한 편의함수 run(Msg&)를 Object에 넣어둔다. 코드는 이렇게 될 것이다.
      - Result& Object::run(Msg& msg) {
        - Method& m = getElement(msg).cast<Method>();
        - if(m.isNull())
          - return nulled;
        - msg[0] = *this; // Msg의 0번째 요소에 thisptr를 담는다. #Msg의_0번째_위치에_Thisptr를_넣는다 참고
        - m.run(msg)
      - }
- *[x] 2안 문법의 일반화를 유지하기 위해 어떻게든 Method.to<Delegator>()를 가능하게 한다.*
  - Method::to<StaticDelegator>()가 가능하도록 하겠다는 것이다.
    - object.call(getElement)를 한 경우, object는 
    - void(int, bool) = a.foo 
  - 개념적으로 접근하자. 
    - 메소드는 Object의 것이 아니다. 다만 일시적인 상황에서만 Object가 누구인지 연관성을 가질 수 있다. 그리고 그 경우는 앞에 . 을 찍히는 경우이다.
      - 예1) a.foo --> 이 경우 foo는 a가 누구인지 일시적으로 알게 된다.
      - 예2) a.foo(5) --> foo와 a는 서로 관련이 없으나 이 경우에만 foo는 자신을 호출한 객체가 a 임을 알 수 있어야 한다.
      - 예3) void(int) fp = a.foo
      - fp(5) --> 객체정보가 없으므로 호출 될 수 없다. "." 이 메소드에 붙어서 효력을 볼려면 연속적으로 .이 찍힌 상황에서 메소드에게 최종 액션이 취해져야만 한다.
    - .은 이러한 의미를 갖고 있는데 반해, 현재 . 을 구현하는 방법은 msg 뒤에 thisptr를 붙이는 방법으로 오직 예2만 만족을 시키는 상황이라는 게 문제의 핵심이다. 다시 말하면 예1도 만족시킬 수 있는 . 을 구현하는 새로운 알고리즘을 만들어버리면 이문제를 해결 할 수 있다.
  - *[x] 1안 .이란 object.call()과 정확하게 시점이 일치한다. 이 시점에서 scope에다가 object를 등록해버린다.*
    - 문제는 이경우 scope에 등록된 object를 언제 해제시켜주느냐가 관건이된다. 시나리오를 여럿 생각해봐서 문제는 없는지 생각을 해봐야 한다.
    - 시나리오 검증
      - *[x] 문1*
        - 문제정의
          - [0] void A.(int) fp = a.foo
          - [1] fp(55)
          - [2] a.foo(55)
        - *[x] 1안*
          - 위의 코드를 AST로 풀면,
            - CallExpr { this <= Cstr로 생성된 객체.
              - .caller= defineDelegatorExpr --> 요때 MethodCstr 그러나 this는 갱신되지 않음.
                - .caller= "",
                - .msg={ "cstr"
                  - args="void", "int"
                - }
              - }
              - .msg={ "operator="
                - .args= CallExpr { --> this <= a object.
                  - .caller= callExpr {  --> this=null(scope가 this를 제거)
                    - .caller="scope"
                    - .msg={ "getElement"
                      - .args="a"
                    - }
                  - }



#### Delegator와_Method의_관계

- \#월드문법 참고
- *[x] 1안 Delegator도 메소드의 일종으로 한다.*
  - 메소드란 -> 어떠한 방법으로든 주어진 인자를 통해서 아웃풋을 내뱉는 액션, 즉 execute를 가지고 있는 Object.  Delegator도 메소드의 일종이다. proxy로 하고는 있다만 메소드이긴 하다. 
  - *[x] Native FRX에서 Method <- Delegator(or ConsumableMethod) 순으로 상속구조가 잡히는 것처럼 월드코드로부터 파싱된 MgdMethod나 Delegator나 모두 메소드의 일종이며, World코드 상에서 void(int) a를 Method b인 b에 할당하는 게 올바른 코드가 되는 걸 설명할 수 있게 된다.*
    - --> Delegator는 메소드가 아니다. Refer가 Object가 아니듯이 말이다. Delegator는 Method와 동일한 인터페이스를 갖고는 있지만 Method 특유의 고유성(stmt를 가지고 있는 등)을 지니지 못하며 흉내만 낸다.
- *[x] 2안 Object가 run()가지게 되었으므로 Delegator를 Object 밑에 둔다.*
  - Object
    - Method
    - Delegator
      - StaticDelegator
      - MethodDelegator
  - [x] Delegator는 Object 인가? Delegator클래스만의 고유한 메소드가 있는가?
- *[x] 2-1안 Object가 run()가지게 되었으므로 Delegator를 Object 밑에 둔다.*
  - Object
    - virtual Result& run(Msg& msg);
    - Method
      - MethodImpl(가칭?)
        - NativeWrapper
        - MgdMethod
      - Delegator
        - StaticMethodDelegator --> 더 좋은 이름은 없을까? 너무 길다
        - MethodDelegator 
- [v] 3안 Delegator를 TRefer<Method>로 만든다.
  - 이는 Delegator의 요구사항인, "정의는 호환되지 않게, 사용은 호환되게"를 반영한 것이다.
  - Node
    - Refer
      - TRefer<Method>
        - Delegator (ADT) : public Methodable
          - vector<TWeak<Class> > _types; // [0] = ret, [1] = object, [2] = params...
    - Object
      - Method
        - Closure
          - LocalSpace
          - Bind<Object>
  - TEST [Native]
    - Delegator d = Method(..).capture(); // staticcatpure를 시도한다.
    - if( ! d) *// == d.isBind()*
      - return NotBind; // method는 nonstatic
    - d->run(args); *// Delegator::run() --> Method::run()으로 간다.*
    - *// d->run(args)에서 d는 nonstatic인지 static인지 중요하진 않다. 사용에 obj를 필요로 하지 않는다.*
    - *// d는 static이건, nonstatic이건 꼭 필요한 만큼의 데이터를 가지고 있다.*
    - d.getParams() *// d의 params는 d 의 생성자로 넣어진다. Bind로 원본을 가리킬 뿐이다. 용량이 절약하고 있다.*
    - d.bind(AnotherMethod); *// 만약 AnotherMethod.getParams()가 d의 getParams()와 다를 경우 에러가 된다.*
    - d->runs(args) *// d가 만약 InstanceMethod일때는 args에 반드시 thisptr가 들어가있어야 한다. 사용자는 이것을 바로 알기가 어려운데...? -->* #모든-것을-요청할-수-있다-그러나-동작을-보장하진-못한다. 참고
    - d.bind(new Closure()); // Delegator는 static인지 nonstatic인지 closure인지 신경쓰지 않는다.
    - d.bind(A::getClass().getMethods()[1]); *// err. 실행은 되나, thisptr가 처음에 지정한 클래스가 아니므로 reject 된다.*









#### 람다메소드 (즉, Closure)

- [v] 전역변수는 어디서나 접근 가능하므로 별다른 조치를 하지 않아도 closure에서 접근이 가능하다.
- [v] 멤버변수는 ObjectSpace는 그 자체가 shallowcpy되므로 이 역시 똑 같다.
- [][v] 컴파일러는 어떤 외부 변수들을 closure가 참고하는지 알아내서 생성할 closure객체에 주입해야 한다.
  - 어떻게 알아내는가?
  - 1안 C++처럼 직접 사용자가 코드로 명시
  - [v] 2안 알아서 적당히 유추 -> scope 참조 알고리즘
    - scope 참조 알고리즘은 이름 중복이 된 경우 가장 최근에 정의된 걸 따라 가는 것이다. 이름 중복은 scope가 다를때만 허용된다. 같은 scope라면 이름이 중복되어서는 안된다. scope는 블록문을 기준으로 나뉘어진다.
    - 또 이 목록(참조할 외부변수 목록)은 컴파일시만 사용하는 것이다. 왜냐하면 컴파일이 완료되면 expr은 직접 vector<int>로 참조할 scope[n]을 다 들고있을 것이기 때문이다. 이 목록을 Closure가 또 들고 있을 필요는 없다. closure는 localspace 목록(정확히 말하면 closure가 가지고 있는 코드(=expr)에서 참조하는 외부변수에 대한 목록)만 가지고 있으면 된다.
      - 정리하면, "참조할목록" 은 컴파일에만 사용하므로 제외
      - "참조한 목록"은 현재 바인딩을 의미하므로 실행시 꼭 필요하므로 포함.
- [][v] capture시 로컬변수 바인딩 문제
  - class A
    - void foo()
      - void _boo() *// closure*
        - print(a)
      - int a = 3
      - _boo()
      - a = 5
      - _boo()
      - if 1
        - int a = 15
        - _boo()
      - _boo()
  - 1 // C/++       -> 3 5 15 5
  - 2 // Python/JS -> 3 5 15 15
  - 2안으로 따라간다. 1안은 너무 WorldFrx 코드가 지저분해진다. 
  - 변수, 함수의 중복정의는 일체 허용하지 않는다. 고로, block scope라는 건 없다. BlockStatement는 scope를 갖는데, 이는 지역변수가 아니라 static이나 closure를 위한 것이다.
  - 정의부는 실행부보다 먼저 나와야 한다.
  - delegator가 capture()로부터 생성되는 시점에 capture이루어진다.
  - 링킹 최적화후
  - closure 및 delegator 정의부:
    - 해당 closure의 코드를 컴파일하면서(링킹이 아님) 사용하는 외부지역변수(member변수가 아니다)의 목록(localspace) 에 넣는다.
    - 그리고 해당 expr에 localspace[n==방금insert된 index] 을 참조하도록 바꿔준다. 
    - 만약 컴파일 전이라면 localspace["변수명"]
  - 실행부: 
    - 해당 closure가 들고있는 "capture 희망목록"에 접근할 수 있어야 한다.
    - 그 목록에 현재의 scope에 있는 것들을 줄 수 있는 지 확인한다. 안되면 링킹에러다.
    - 정의부에서 추려낸 지역변수 목록들만 capture 뜨는 명령어 ( Method.capture(1,5, 10) )를 사용해서 delegator를 만들도록 stmt를 정의한다. 
    - 컴파일최적화 전이라면 Method.capture("변수명1", "변수명2", ...)
- [x][x] *closure 원격 native 생성 문제*
  - *[x] Native환경에서 원격지에 있는 closure() 해서 그걸 원격지의 객체 중 하나의 Refer에 할당한 경우, 이때 생성된 closure는 실제 동작과는 다르게 된다. 어떻게 하면 좋을까?*
    - 이해가 안간다. 뭐가 문제인가?
- [][v] closure의 생성자의 인자리스트에 scope를 명시해야 하는가?
  - closure는 생성되는 순간 scope를 반드시 참조해야 한다. 생성자에 인자로 두면 명시적으로 이걸 드러낼 수 있다. 다만 귀찮아질 것이다.
  - [v] 1안 네
    - 로컬 스페이스는 scope에 속한 것이며 각 object마다 고유의 것이 아니다. 
    - 종속관계는 가능한한 드러내는 게 좋다.
- TEST Driven Development
  - TEST#1
    - class A
      - void(void) foo(int b)
        - void _boo()
          - Console.out(a)
        - int a = 5
        - _boo() *// "5" 출력*
        - if(b > 5)
          - int a = 7
          - return _boo *// Closure->Delegator 시에 capture 발생*
        - else
          - int a = 10
          - return _boo
    - A a
    - a.foo(6)() *// "7" 출력*
    - void(void)(int) fptr = a.foo *// InstanceMethod->StaticDelegator이므로 capture발생.*
    - fptr(3)() *// "10" 출력*
    - void(void)A.(int) foptr = a.foo *// InstanceMethod -> InstanceDelegator*
    - a.foptr(10)() *// "7" 출력*
  - TEST#2
    - class A
      - void(void) foo(int b)
        - *//void _boo()*
          - *//Console.out(a) --> 이 시점에는 아직 a가 정의되지 않았으므로 에러.*







### 예외처리






### scope확장













## 구현과 디자인

### backbone

#### prefix는 NE_ 대신 WRD를 사용한다.



#### Msg

##### Msg클래스는 WRD_CLASS를 써야한다.

- Thing에서 상속받은 구체클래스다.
- instantiate()는 반환형이 Instance부터 가능하다. 
- **[v] 1안 값으로 반환하는 경우에도 전방선언은 유효하다.**
  \#include <iostream> using namespace std;  // A.hpp class B; class A { public:     B foo(); };  // A.cpp class B { public:     int age; };  B A::foo() {     return B(); }  int main() {     A a;     a.foo();     return 0; }  // compile ok. 



##### Msg의_마지막_위치에_Thisptr를_넣어야_한다?

- 결론
  - 2안 thisptr은 배열에 넣지 않는다. 모든 Msg는 별도의 TStrong<Object> thisptr라는 멤버변수를 갖게 된다.
- 고찰내용
  - Msg Args의 첫번째 위치에 넣는 방법도 생각해볼 수 있겠지만 그래서는 안된다. 이유는 이렇다.
    - \1. thisptr는 도중에 변경된다. 런타임에서만 확정된다. 
    - \2. 아무 생각없이 thisptr를 msg에 넣게 되면 msg가 resize가 일어나면서 매번 퍼포먼스 로스가 발생한다.
    - \3. 그러므로 thisptr를 msg에 넣어야하는 주체인 Expr인 Msg를 만들면서 미리 thisptr를 넣기 위한 여분의 공간을 1개 끝에 더 만들어서 넣는다. 그리고 Expr은 이 부분을 실행시킨다.
  - 고찰을 통한 요구사항 추출
    - \1. args와 thisptr가 하나의 배열에 같이 담겨져 있어야 한다. 다시말하면 thisptr또한 arg로써 다뤄줘야 한다.
    - \2. static메소드에 thisptr가 포함된 msg가 들어가도 동작이 가능해야 한다. 즉, static 메소드는 args와 thisptr가 서로 구분이 가야한다. thisptr는 args의 일부로써 취급받지만 때로는 평범한 arg와는 선을 그어야 한다.
    - \3. 런타임에 thisptr가 추가되거나 set 될 수 있다. 이때 resize가 발생하지 않도록 해야 한다.
    - \4. 사용자는 Msg를 Object.run()에게 던질경우, 이 결과가 InstanceMethod에게 도달할 것인지,  static메소드에게 갈것인지 몰라도 되야 한다. 따라서 Msg는 런타임에 thistpr가 추가될 수 있게 된다.
  - [x] 1안 thisptr도 배열에 넣는다. 
    - thisptr 조차 하나로 arg로 판단하므로 static메소드는 thisptr가 없으면 에러를 내뱉는다. 
    - 마찬가지로 InstanceMethod도 thisptr가 없으면 에러가 된다
    - 사용자는 Object.run(Msg)를 보낼때 미리 이 Msg는 thisptr를 필요로 하는지 아닌지를 알고 있어야 한다. 안 그러면 resize가 발생한다.
      - Msg는 기본적으로 항상 thisptr을 위한 size+1를 만들어놓는 다면?
        - 되기야 하겠지. 하지만 근본적으로 배열에 하나로 담았을때의 merit이 없다는 걸 알게되었다. 2안 참조. 그리고 resize+1 하는 것보다 차라리 그럴바에야 물리적으로는 다른 멤버변수로 나뉘어져 있어도 가상적인 배열에서는 하나로 묶여져있게끔 하는 것도 방법이 될 수 있다.
    - [x] 1안 thisptr을 배열의 앞에 넣는다.
      - 만약 thisptr가 앞에 있게 된다면 이 msg가 static 메소드에 도달한 경우 에러가 발생하게 된다. 무슨 말이냐면 굳이 앞에 넣을 거라면 내가 msg를 보낼 메소드가 static인지 아닌지를 매번확인해야 한다는게 된다.
        - [v] 반론: 그 말은, 보낼 메소드가 static인지 아닌지 상관없이 일단 thisptr 넣고 보겠다는 이야기로 들린다. 그러나 생각해보자. 만약 static 메소드에 thisptr를 넣어서 보내게 된다면 static 메소드는 이걸 thisptr가 아니라 추가된 인자로써 받아들일 것이다. 결과적으로 함수 호출이 실패된다. 왜냐하면 static메소드 입장에서는 자기가 알지 못하는 인자가 뒤에 하나더 붙어있는 것이기 때문이다.
        - 이 말은 managed에서의 메소드 호출은 항상 이 함수가 static인지 , 어떠한 인자를 가지고 있는지를 if-else,로 판단해야 한다는 것이다. 사용자가 항상 이렇게 판단해서 올바른 msg를 구성해서 보내야지만 메소드가 호출된다.
        - 또한 일반 메소드들은 별다른 언급및 코드가 없어도 인자리스트 맨 앞에 thisptr가 들어가있게 만들어야 한다.
        - [x] Object.run(Msg)를 하는 경우에는, 알아서 thisptr를 넣도록 했었다. 만약 thisptr를 args[n]으로 바꾼다면 native 환경에서 Object.run()을 하는 경우에는 사용자는 static인지 아닌지 구분을 할 필요가 없게 된다.
          - [v] 그러나 이 편의방법을 사용하는 경우, 어쨌거나 args.resize()가 일어날 가능성이 있다. 이걸 막기 위해서는 처음부터 Object.run()을 호출하기 전에 사용자는 static인지를 확인 한 뒤, static이 아닐 경우에는 resize(args.size() + 1)을 해야만 하는 것이다.
  - **[v] 2안 thisptr는 배열에 넣지 않는다.**
    - 모든 메시지는 thisptr을 소유한다. 특별취급한다. args에 들어가지 않는다. 모든 Msg는 thisptr 만큼 메모리가 늘어난다.
    - 이 방법을 택한 근본적인 이유는 thisptr를 배열에 넣게 됨으로써 가지는 merit이 없기 때문이다. 
      - thisptr가 배열에 들어가게끔 하는 이유는 뻔하다. 인자의 하나로써 일반적인 로직 하나로 해결하겠다는 것. 
      - 주된 사용처는 Method에서 인자리스트가 제대로 들어있는지 to<T>()를 통해서 validation을 하는 곳일 것이다. 
      - 하지만 thisptr가 워낙에 특이한변수이다보니 이곳에서조차, thisptr일 경우에는 thisptr->func(args)처럼 특수한 처리를 해줘야만 한다. 
      - Thisptr != Object& 이다. args 배열은 Object&라는 관점에서만 바라보기 때문에, thisptr로써 주어진 object&인지, 인자로써 주어진 object& 인지 구분이 쉽지 않고, 대부분의 상황에서 이 구분을 필요로 했다. 다시말하면 그 일반적인 로직의 다양성이 적다는 것이다. (기껏 하나의 배열로 합쳐봤자 쓸데가 없다는 얘기)
      - 되려 분리시켰을때의 편의성이나 static/instance메소드를 특정하지 않고도 메소드를 보낼 수 있는 점등 장점이 더 많다.



##### Msg의인자는Method에const로넘어가면안된다

- \#복사연산_시나리오 를 참고.
  - 요약하면 Refer는 생성시에 const 여부가 결정되며, const 타입의 일부이므로 한번 const Refer이면 계속 const Refer여야 한다.
- 일반적으로 생각했을때는 msg의 내용이 변하면 안된다고 볼것이다. 그러나 msg가 처리되는 시나리오와 method로 넘어가는 과정, refer클래스와 const 정책을 모두 고려하면 const로 가면안되고, 각 인자가 const Refer인지 아닌지를 정하게끔 해야 한다.
- 먼저 const 정책문서를 보면 알겠지만 Refer는 2가지 형태의 const를 갖는다. 하나는 native에서만 들어나는 const고, 하나는 managed,nateve모두 들어나는 const인, isConst()다. 둘중 하나라도 const가 되어있다면 get() const를 호출했을때만 유의미한 값이 나온다. const를 결정하는 것은 사실상 Refer클래스가 담당하는 것이며, 원본은 const가 아니라도 Refer는 그것을 const 취급할 수 있다. Refer는 const여부는 생성자에서 정해지며, 소멸될때까지 const는 계속 유지된다. 따라서 const라는 건 궁극적으로는 const ptr라고 불러야 한다.
  - class A 
  - class B : A
  - Refer<A> a = new B()
  - const Refer<B> b // b는 C++적인 const만 적용되어있다. b.isConst()는 false다.
  - const Refer<A>& a1 = a; // ok
  - b = a1; // err. b는 c++ const객체이므로 assign이 안된다.
  - Refer<B> b1 = (const B*) new B();
  - b1.isConst() // true
  - b1 = a1; // B가 sharable인가 occupiable인가 따라 다르다. 
- occupiable sharable 문서를 또 보면 알겠지만 isOccupiable은 metaclass에 저장되어있고, pretype을 제외하면 사용자 클래스는 모두 sharable이다. occupiable이냐 sharable이냐의 동작상 차이는 오직 Refer클래스에 복사생성 및 operator=()에만 존재한다. sharable이면 Refer객체인 rhs를 그대로 복사하며(isConst()여부도) occupiable이면 deepcopy를 시전한다. 그것뿐이다.
- msg의 args는 Node에 대한 배열이다. 이 Node에는 다른 expr이 들어갈 수도있고 Integer가 그대로 박혀있을 수도 있다. 후자를 프로그래밍 언어에서는 리터럴상수라고 한다. **리터럴상수로 된 경우는 얼마나 메소드를 수행하던 그 인자값이 항상 동일해야한다.**
- 메소드는 주어진 인자를 최종적으로 cast()함수를 사용한다. cast의 반환값은 refer로, 바로 반환이 가능한 케이스(업캐스팅, 다운캐스팅)은 Refer객체를 바로 만들어보내고, 그게 아닐 경우는 생성자를 호출하여 객체를 복사한다.
- 이 문제가 생각하기 까다로운 이유는 2가지 상태값을 갖는 4가지 팩터들을 각각 모두 고려해야하기 때문에 총 16가지 케이스가 나오기 때문이다. 4가지 팩터는 앞서 설명한 1. const인가 2. occupible인가 3. 메소드안에서 write를 하는가 4. 인자가 리터럴상수인가
- 먼저, 본격적으로 시나리오들을 검토하기 전에 요구사항들을 추려보겠다.
  - \1. 모든 케이스에서 가능한가 아닌가를 따지는 것이 아니다. 어떤 케이스는 연산이 불가능해야한다. (예, 인자를 const로 줬는데 메소드는 write를 하는 케이스) 이 경우, 불가능하다는 것이 사용자에게 고지(컴파일에러등)될 수 있으면 문제는없다.
  - \2. 다른 프로그램과 비교했을때 예상범위 내의 결과가 나와야 한다.



##### Message는_name_thisptr_args를_모두_하나의_Array로_구성한다

- Message안에 mutable로 들어간다.
- \#Method는_ThisPtr이_꼭_필요하다_어떻게_얻을_수_있을까  참고
- 모든 Object는 call()안에서 expr.thisptr이 비어있다면 자신의 것으로 채워넣고, call()이 끝나기 직전에 다시 비워놓아야 한다.
- me는 항상 자신으로 갱신 한다.
- 고찰내용
  - 핀포인트 물음
    - Method는 Object에게 소유한 것인가? Class에게 소유한 것인가?
    - Object 소유가 아니라면 과연 Method가 thisptr를 반환할 당위성이 있는가?
    - Object 안에 멤버변수인 Object는 과연 Object의 소유인가?
  - 고찰을 통한 팩트 도출
    - \1. thisptr가 필요한 순간은 Object에서 Method로 call을 redirection 하는 순간일 뿐이다. 왜냐하면 Method는 Object에 속한것이 아니며, call()은 인자리스트가 fix되어있기 때문에 Method에게 Object자신의 thisptr를 전해줘야만 하기 때문이다.
    - \2. Method의 thisptr는 실행중인 상태에서만 조회가 가능하다. 당연히 왜냐하면 Method는 모든 객체의 것이니까.
    - \3. 콜스택에 함수가 들어가있는 모든 함수는 자신의 thisptr를 알려줄 수 있어야 한다.
      - 예) A함수 실행 -> 안에서, B객체의 C함수를 호출한 상황일때, C함수 안에서 A함수의 getObject()를 했을때 
  - v 1안 모든 Message 객체는 .thisptr라는 멤버변수를 두고 거기에 담아둔다. 
    - 반대의견
      - Message는 Expression이 하나씩 소유하고 있음을 생각해보면 답이 나온다. Expression은 Method가 가지고 있으며 Method는 시스템에 1개다. Expression도 한개다. 고로 그 안의 Message도 한개다. 그런데 thisptr는 클래스는 같아도 여러개의 객체가 나오므로 Message에 넣어질 thisptr는 여러개가 된다. 따라서 모든 Message마다 thisptr를 갖고 있는 것은 낭비일 것이다.
      - 만약 World에서 Object가 아닌 Method.getName()을 한다고 해보자. 이 알고리즘이 제대로 될것인가?
        - Method도 Object이다. 따라서 Expr이 처음 call로 전달되기 직전에 만나는 Object가 자신의 thisptr를 채워넣으면 된다.

시나리오

- 작성
  - IDE에서 사용자가 메소드를 작성한다. 컴파일되고 Wrd는 이 메소드가 static인지 아닌지, 인자는 뭐가 필요한지 알게된다. IDE에게 그것을 고지하고 IDE는 인식한 뒤, 사용자에게 그것을 고지한다. 사용자가 잘못된 인자를 Method에 넣거나, 일반메소드를 static메소드처럼 사용한 경우, IDE는 그것을 컴파일러에게 넘기고, 컴파일러는 CREPL로 이걸 처리하면서 에러를 뿜어낸다. 사용자는 에러를 보고 올바르게 고친다. 사용자가 제대로 작성한 메소드호출 코드를 작성하면 Wrd는 메소드를 호출하기 위한 msg를 생성할때 이 Method가 static이 아니라는 사실을 알게된 순간 첫번째 element를 this를 위해 추가로 size+1하여 생성하고 앞에서부터 인자를 채워넣는다. (this는 맨 뒤에 위치하게 된다) 
- 실행
  - Managed
    - Wrd는 Object에 먼저가서 사용자가 어떤 member를 가져가길 원하는지 질의해서 찾아낸다. 그리고 methodcallstmt는 msg 인자 맨 뒤에 caller(= this)를 넣고 Method.call(msg)을 수행한다. 수행이 끝나도 msg 맨 뒤의 thisptr는 그대로 유지한다.
  - Native
    - 사용자는 들고있는 Method가 isStatic()으로 확인 한 후, Msg를 생성하여 인자를 채워넣고 Method에 대한 Object를 맨 뒤에 넣은 뒤, call(msg)를 호출하거나
    - call(thisptr, msg) 버전을 호출한다.

- 고찰내용
  - Msg는 const가 되어서는 안된다. --> #Msg의인자는Method에const로넘어가면안된다
  - 따라서 모든 msg 마다 추가적은 thisptr를 담아야한다는 메모리감소만 감수한다면 이렇게 할 수 있다. 장단점을 비교해보자.
  - 장점
    - this도 msg의 한 인자로써 일반적으로 취급할 수 있다는 점
    - this를 method에 주입하는 방법이 밖으로 들어났으므로 native에서도 Method에다가 호출이 가능하다는 점
  - 그럴 필요가 있는가?
    - Msg가 전달될때 첫번째 인자는 thisptr이 되어야 할까?
  - 1안 Message : public Array {
    - [0] : thisptr
    - [1] : name
    - [2] : arg[0]
    - [3] : arg[1]....
    - 그러나 이렇게 하면 getArguments() 같은 걸 만들 수 없다. 고로 Chain이 되어야 하며, 추가적인 비용으로 될 것이다.
  - 2안 그대로 유지한다.
    - class Message
      - string name
      - TStrong<Node> thisptr
      - Array args
  - 실패한다. 애초에 msg에 thisptr가 들어갈 수 없다.
    - v Msg는 외부에서 주어지는 것이다. 그러니 call(const Msg&) 로 들어갈 가능성이 있다?
      - 모듈안에서 인자의 값이 수정되어야하는 경우는 어떠한가?? 예를들면
        - class MyModule : public Object {
          - Integer& foo(Integer& origin) {
            - origin++;
            - return origin;
          - }
        - }
        - class Wrapper : public Func {
          - void execute() {
            - thisptr->fptr(args[0].to<Integer>()); // args[0]에는 Expr이 들어있을것이고, 그것은 scope["origin"] 을 수행할 것이다.
          - }
        - }
      - 따라서, 모듈안에서 인자가 수정되는 경우에도 msg자체가 변경되는 것은 아니다. 따라서 call(const Msg&)는 정당한 설계라고 봐야 할것이다. 따라서 msg안에는 thisptr가 들어가서는 안된다.
  - 단점
    - 메모리 사용량 증가

##### 메시지를 받을 수 있는 모든 것은 World에 visible 하다.

- 모든 것은 객체다. 하지만 World에서 더 중요한 것은 Message다.

- Message란 함수호출을 위한 의지를 의미한다. 

- 객체는 함수와 자기의 변수를 가지고 있다.

- Object는 객체다. 고로 함수가 존재하고 메타클래 Class<Object>는 각 함수에 대한 Function을 가지고 있으므로 이걸 통해서 호출이 가능하다. 

- 하지만 Object 자체는 메시지를 받을 수 없다. 

- 이말은, World 개발자는 Object의 함수를 간접적으로 사용하는 것은 가능할지라도(Class<Object>().call("")을 통해서..) Object를 직접 Reference로 가리키던가 Node화 시키는 것은 불가능하다는 것이다.

- 클래스, 함수도 Message를 받을 수 있다. 그러므로 World개발자가 조작할 수 있다.

  - class A

    - void foo(int b)

  - A.foo.getName()

  - A a

  - a.foo(3) // a.foo.call("foo", [int(3)]) 의 축약버전이다.

    

##### 하위 Node로의 매시지 전파

- World로 call("foo", {Integer(5)}) 가 들어왔을때, 이걸 해독하여 foo(int)를 호출할 수 있도록 해주는것이다.

- Node::call(string name, args[])

  - for m in members
    - if m.getName() == foo
      - m에게 나머지 messgage를 맡긴다.
      - 만약 message가 foo.getName() 일 경우에는 m의 getName()이 호출되는 것이다.

- 월드 코드 "foo[0].getManager().getName()" 가 있을 경우, 어떤식으로 진행되는가?

  - 파서가 코드블럭을 만들어내면 끝나는 작업이다.
  - foo, [0], getManager (), getName () 이렇게 끊는다. 
  - Statment[]를 생성한다.
    - Statement6
      - Statement5
        - Statement4
          - Statement3
            - Statement2
              - Statement1
                - this
                - "foo"
              - "[]"
              - {0}
            - "getManager"
          - "()"
        - "getName"
      - "()"
  - 위의 statement가 실행한다" --> 안되면 에러, 되면 반환형이 손에 쥐어질 것이다.

- 메소드 또한 Class의 일종으로, Method를 가질 수 있다. 따라서 World코드 마지막에는 Method.call() 대신 Method.execute()를 하지 않으면 무한 재귀를 돌게 된다.

- 인터프리터는 파싱한게 함수호출임을 알 수 있으며, 마지막에는 반드시 Method.execute(msg)로 끝날 수 있도록 코드블럭, 즉 Expression을 구성해야한다.

- 고찰내용

  - call("()") 로 체크한다는 것인데, 이게 redirect하는 native함수는 무엇인가? 만약 그게 만약 execute()라면 World코드로 call("execute")를 한경우는 어떻게 되는가

    - World에서 작성한 함수는 C++에서 호출하려면 "World"의 방법대로 호출해야 한다.
      - 즉 call("execute")를 하면 ExecuteFunction()이 실행된다는 것이다.
    - 논리적으로 불가능하지 않다. 다만 Native개발자는 "()"와 매칭되는게 execute라는 사실을 인지하고 있어야 한다.

  - 재귀가 발생한다

    - Method는 객체가 되어야 한다. 이게 나중에는 함수포인터 내지는 콜백으로 기능하게 될 것이기 때문이다. Reference(Method) 같은게 반드시 있어야 한다.

    - 하지만 그렇게 되면 문제가 되는데 Method에도 함수가 존재하게 될 것이고, execute()는 메소드를 실행시킬 함수가 될 것이다. 그렇게되면 메소드를 실행하는 순간 Method->executeMethod->executeMethod->...가 반복되게 된다.

      - 1안 종말메소드 를 만든다.

        - 종말메소드는 객체가 아니다. 주어진 인자를 무조건 사용해서 동작1개를 수행한다.
        - 이들은 일반적인 method와 다르게 주어진 msg를 판독하는 기능이 존재하지 않는다.
        - 문제점
          - 이후 TClass<T> 매크로로부터 생성되는 모든 메소드들은 자신 안에 Member로 또하나의 종말메소드들을 다 갖게 되버린다.
          - 그리고 함수가 실행되는 절차도 길어지게 된다.

      - 2안 위와 같은 문제를 야기시키는게 execute 뿐이라면, 해당 코드만 특화시킨다.

      - v 3안 재사용된 종말메소드

        - Method 클래스에 execute를 종말메소드로 만든다. 종말메소드는 일반적인 메소드 클래스와 달리 어떠한 자식Node도 없다.

        - execute종말메소드는 call()시, msg를 판독하지 않고, 바로 execute(Args&)를 부른다.

        - Native함수가 실행되는 최소시작점은 execute(Args&) or execute() 다.

        - 매크로로 expand된 클래스들은 execute(Args&)를 override해서 주어진 인자들을 풀어서 최종 메소드로 redirect 하는 코드를 만든다. --> _onExecute(Integer&, String&)

        - 장점

          - 종말메소드는 구현파일 안쪽에 감출 수 있다.

          - 기존 로직 수정이 거의 없고 예외처리가 존재하지 않는다.

            

##### Msg의인자는Method에const로넘어가면안된다

- \#복사연산_시나리오 참고
- \1. Native(Wrd Frx)에서는 const Refer나 Refer<const T>나 동일하다.
- \2. nonconst -> const 는 ok이지만 const -> nonconst는 안된다.
- 고로, const msg&로 넘어오게 되면 msg의 모든 인자에 대해 to<T> const()만 써야 하며, const Refer로만 받을 수 있다.











## 코딩 컨벤션














## 작성 예제