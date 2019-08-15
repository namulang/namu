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



#### static

##### 1

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





### 상수화 (const...뺄까?)
* 왜?
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