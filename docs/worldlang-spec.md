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
..
..







## 개념

### Prototyping 기반
### Origin 객체
### 정적 타입
### C-REPL

..







## 문법과 알고리즘

### Hello World




### 연산자
우선순위




### 흐름 제어



### 변수
상수/변수의 의미 / 캐스팅




### 메소드
* 정의, 호출, 캐스팅을 사용하고 있는 점





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
    -   GeneratorParser가 이걸 해줄 수 있다.






###  객체의 정의
직접 정의 & 복제








### 기본 타입
#### this, me
##### 1
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







### 지정자
#,$,@,_







### 상수화 (const...뺄까?)
* 왜?
	* 코드가 너무 복잡해짐. 이 언어는 가볍게 배우고 빨리 실습해보고.. 이랬음 좋겠다.






### 프로그램 구조






### 컨테이너
#### 배열
##### 1
-   int[] a = {0, 1, 2} // Array는 length만 있다. size는 눈에 보이지 않음.
-   a[2] = 5
-   _//void(int)[4] a = {}_







### Sharable & Occupiable







### Scope
라이프 사이클, GC







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







### 예외처리






### scope확장












## 코딩 컨벤션














## 작성 예제