# 메소드

## Method는 일반 객체와 다른, 확장이 불가능한 builtin 객체다.
* 메소드 또한 origin 객체로써 취급한다. 그러나 일반 origin객체와는 다음과 같은 항목에서 다르다.
    * 그러나 메소드의 메소드는 고정된 항목들이며 메소드로부터 확장하거나 extend가 불가능하다.
    * 메소드가 제공하는 메소드는 RTTI 관련 항목이다.
    - 메소드는 Object가 아니므로 객체마다의 멤버는 가질 수 없으나 공유멤버는 가질 수 있다.
* 다음은 일반 객체와의 공통점이다.
    * 메소드는 객체이므로 메소드에 대한 참조를 만들 수 있다.
    * 메소드는 블록문을 가지고 있다.
    * 메소드의 정의는 expr 으로 취급한다.

## 모든 메소드는 객체에 속해있다.
* static 클래스는 존재하지 않는다. static 메소드 역시 존재하지 않는다.
* static 변수는 존재한다.
* 메소드가 정의되면 해당 scope에 static member로써 추가된다.
    * 메소드 안에서 메소드가 정의되면 메소드의 static member로써 추가된다.
- Exception 핸들링또한 Nested Method를 통해서 돌아간다.

## 다형성을 기본적으로 제공한다.

## 중첩 메소드를 외부에서 호출할 수는 없다. (invisible)

## 중첩 메소드의 accessor가 protected, public 이건 동작에는 차이가 없다.

## 클래스 계층
* Method는 Object와 동작이 상이하나 Node의 일종인 것은 맞다.
* Methods는 블록문의 한 종류로 볼 수 있다. Block문은 Statement의 한 종류다.
  따라서 Node <-- Expr <-- BlockExpr <-- Method 의 상속구조가 된다.

## Msg를 어떠한 member가 처리할 수 있는지를 탐색해서 member[]를 반환하는 메소드가 있어야 한다.
* 바로 call을 해버리면 곤란하다. 왜냐하면 interpreter는 validation에서 모호성 오류를 검증하기위해 이 msg를 받을 수있는 곳이 1곳인가를 반드시 짚고 넘어가야 하기 때문이다.
* 메시지의 인자를 묵시적 변환을 거쳐서 처리가 가능한지를 각 member가 반환해야 한다.
* 각 member는 처리가능 여부와 함께, 처리 우선순위를 계산해서 반환한다.

## method의 msg 처리 우선순위
* method deduction에서 사용하게 된다.
* 묵시적 변환이 일체 없이 타입이 정확히 일치하면 우선순위 0
* 변환이 불가능하면 우선순위 음수
* 묵시적 변환이 한번이라도 사용되었다면 우선순위 1이 된다. 

## 메소드에 thisptr는 전달하지 않는다.
* 객체는 msg를 수신하면 object scope을 자신의 것으로 교체한다. 따라서 thisptr를 전달하지 않고도
  scope를 조회하면 자연스럽게 객체의 member를 호출할 수 있게 된다.
* 모든 메소드는 객체에 속해있으므로, 메소드에 전달되는 msg는 항상 객체에 먼저 전달된다.
* 람다 메소드도 예외가 아니다. 람다는 자신이 capture 하고 있는 object + local scope으로 교체를 해버린다.

## 메소드ptr는 Ref에서 상속한 FuncRef로 사용한다.

* Ref는 type 이라는 별도의 Object로 verify를 한다. 하지만 함수는
하나의 Type으로는 불가능하고 인자와 반환형을 통해서 verify를 해야한다.
단순히 Ref를 통해서 Verify 하기가 힘든다.

## 메소드 식별문법

* 메소드 메소드명과 인자리스트를 함께 적는다. 인자리스트는 반드시 변수명이 함께 있어야 한다. 인자리스트가 빈 메소드라면 void를 넣는다.
'''go
def person
    sayHello(name str, age int) res

person.sayHello(name str, age int)
'''

* 만약 메소드명 만으로도 식별이 가능하다면 인자리스트를 생략할 수 있다.

'''go
person.sayHello
'''

## 비어있는 메소드

* 메소드가 비어있을 경우 호출이 불가능하다. 이는 인터페이스를 정의한 것이다.
* void를 반환하는 경우라도 return문 1개는 있어야 한다.
* 비어있는 메소드라도 메소드 호출만 불가능 할 뿐, 접근은 가능하다.

'''go
def person
    someCallback() void
        return
    someCallback2() void

person.someCallback()
person.someCallback2() // err.
person.someCallback2.name
'''

## 메소드ptr를 정의하는 문법

* 비어있는 메소드를 정의하는 것으로 메소드 ptr의 타입을 정의 하도록 한다.

'''go
def person
    someCallback(p person) int
    delayCall(fn someCallback) void
        fn(this)

def app
    _callback(p person) int
        ret sys.csol.print("p.age=$p.age")

    main() void
        person.delayCall(_callback)
'''

## 메소드를 ptr에 넘길 경우, 클로져 처럼 동작한다.

* object scope가 캡처되서 FuncRef에 기록된다.

## 식별자 바인딩은 매번 get("identifier-name")을 넣음으로써 매번 검색한다.

* optimization 과정이 끝날 경우, 이 과정은 상수타임에 끝나도록 한다.

## 메소드 hiding 되지 않는다.


## 메소드를 생성자처럼 사용하면 메소드가 생성되는 대신에 메소드호출이 된다.

## 메소드 정의시 뒤에 = 0을 붙이면 해당 메소드는 abstract 이다.

* Null이 할당된것과 같다.
* 접근은 가능하다.
* RTTI 메소드도 호출할 수 있다. (유일하게 일관성없이 동작하는 부분 중 하나)
* 복제 혹은 메소드 호출은 안된다.
