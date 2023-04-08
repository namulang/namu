# def

## 프로토타이핑 패턴에 기반을 둔 클래스 기반 상속

* 새로운 객체를 정의할 수 있고, 그 객체로부터 복제를 정의할 수 있다. (프로토타이핑 상속의 기본 조건)

## 프로토타이핑을 하는 이유

* 가장 큰 이유는 class라고 하는 개념을 덜 수 있기 때문이다. 이는 문법에서 몇가지 개념을 덜수 있게 해준다.
    * static 메소드, static 변수
    * class 라는 문법, class는 객체가 아니라는 구분

* 그러나 동시에 프로토타이핑은 2가지 단점이 있다.
    * 전역변수로써 생긴다. 의존성이 겉으로 드러나지 않는다.
    * 어느샌가 원본이 훼손되어 있는 경우 디버깅이 매우 어렵다.

* worldlang은 CREPL을 달성하는 것이 가장 중요한 언어다. 동시에 사전에 에러를 많이 찾아야 하므로 정적언어가 되어야 한다.
* 따라서 동적으로 구성을 변경할 수 있으면서도 정적언어를 띌수 있어야 했기에 프로토타이핑 기반으로 구현을 하되 문법은 클래스 기반으로 보이게 된다.
* 또한 클래스라는 개념을 1개 없애서 좀 더 단순하게 만들 수 있다.
    * 모든 것은 객체다. 그런데 def 시 생성을 하지 않으면 디버깅을 위해서 접근을 막은 것에 불과하다.

* 위의 특성은 대개 동적 언어에 부합하는 특성이다. 정적언어를 띄는 world에는 어울리지 않는다.
* 그래서 origin, type, clone 3가지로 해결한다.

## 클래스처럼, 때로는 프로토타입처럼 사용한다.
* world에는 클래스가 없다. 모든 것은 객체다.
* origin 객체는 def 를 통해서 정의되는 객체로 사용자는 절대로 origin 객체의 데이터를 변경할 수 없다.
* origin 객체의 메소드를 호출할 수 있으나 이것은 언어 spec 상에서 약속된 일부 RTTI 관련 메소드 뿐이다. origin 객체로부터 복제객체를 생성할 수 있다.
* origin 객체의 불변성과 복제를 통한 사용은 클래스를 떠올리게 한다.
* def를 하면서 동시에 그 타입으로 unique 객체를 완성 할 수 있다.
* unique 객체는 mutable 한 객체로써 worldlang spec상 unique와 origin은 별도의 객체다.

```go
def Person
    age := 5
Person.age // 에러

def person()
    age := 5

person.age = 3 // unique객체.age == 3
p := person()
p.age != person.age // true
p2 := person(person)
p2.age == person.age // true
```

## 생성자는 outer scope에 속한 특수한 static func다.
* 생성자가 외부에 놓여질때 타입이름으로 놓여져야 한다, "@ctor"이 아니라.
* type Person의 생성자는 Person에 있는 것이 아니라 Person의 origin를 갖고 있는 객체가 소유한다. (대부분은 pack일 것이다)
* 이는 모호성 오류를 해결하기 위해서이다. 다음 예제를 보자.
```go
def A
    @ctor(int)
def B A
    @ctor()
a A := B(5)
```
* 만약 생성자가 객체에 속한 것이라면 생성자는 당연히 상속된다. 그러므로 B(5)는 옳은 문장이 되어야 한다. 그러나 데이터의 무결성이 엉망이 된다.
* 생성자를 밖에 둔 경우에만 B 객체에 접근없이 B(5)를 호출할 수 있게 된다.

## origin 객체

* origin객체는 컴파일러로부터 생성되며 생성된 후에는 사용자는 절대로 접근이 불가능하다.
* def 에 명시하면, origin객체가 생성될때 이로부터 복제된 객체 1개가 시스템에 의해서 생성되며 type name에 바인딩 된다. 이를 unique객체라고 한다.
* unique객체가 명시될때 생성자의 인자를 다양하게 줄 수 있다.

## unique 객체는 intepreting 3 phase인 initialize 단계에서 eval 된다.

## unique 객체는 복제된다.

## 생성자는 origin 객체를 복제하는 것이다.

## 복사생성자는 임의의 객체를 복제하는 것이다.

## 프로토타이핑이라는 것이 숨겨진다.

* 전부 복제를 기반으로 동작한다. 그러나 문법으로만 봐서는 class 기반 처럼 보이게 된다.
* unique객체에 생성자를 호출하면 origin객체로부터 객체가 나온다.
* 복제를 하고 싶다면 clone()을 호출한다.

## 멤버는 동적으로 구성한다. 이후 최적화를 통해 정적으로 만든다.

* 디버깅 모드에서는 멤버는 동적으로 구성된다.
* 멤버는 WorldFRX 외부에서는 변경할 수 없다.
* 최적화 과정 중에, 이 멤버를 정적으로 구성하는 게 포함되어 있다.

## 멤버는 Chain 자료구조로 구성된다.

* 겉보기에는 1차원 배열처럼 보이므로 간결한 API를 제공한다.
* 유동적으로 배열의 내용을 구성할 수 있으며 원본의 배열 내용이 변경되어도 추가 비용없이 동기화된다.
* 탐색에 O(n)의 비용이 소모된다.
* shared sub chain 1개와 all subs chain 1개 non shared sub array 1개 총 3개로 구성된다.

## origin 객체의 정의 알고리즘

* obj는 NonShared array와 Share chain과 subs Chain 3개를 가지고 있다. (물론 더 있다)
* chain 자료 구조는 add 된 container 갯수와 관계없이 일정한 복잡도와 퍼포먼스를 낼 수 있다. 이를 위해서 단방향 linked list의 Node처럼 구현된다. (list가 아니다)
* origin 객체를 정의 할때 다음의 알고리즘으로 작성한다.
    * 파서 혹은 native 언어에 의해서 작성된다. 다음은 mgd origin obj에 대해서만 적용된다.
    * 파서는 origin 객체를 생성해야 하므로 new MgdObj()를 통해서 만들어 낸다.
    * origin객체 생성시, 중첩객체 여부를 고려하지 않는다. 상속만 고려한다.
    * generation 단계
        * interpreting의 첫 1 phase인 generation단계에서도 어떠한 이름을 가진 객체가 부모인지는 Type에 바인딩 시킬 수 있다.
        * 파서는 scope가 객체를 접근하는 족족, origin객체가 없을 경우 그 자리에서 origin과 Type객체를 만들 도록 lazy한 getter를 들고 있어야 한다.
        * origin객체를 생성하면서 인자로 미리 작성해둔 Type 객체를 생성자의 인자로 넣는다.
        * Type 객체는 어떤 origin 객체가 부모인지 기록되어 있다.
    * verify&bind 단계에서는 상속을 처리한다.

## 복제객체의 생성
* 생성자를 호출하면 origin객체의 복제를 만드는 작업을 한다. 이는 클래스에서 객체를 만드는 것과 비슷하다.
* 다음의 과정으로 진행한다.
    * 생성자를 호출하기 위해 2 종류의 인자가 필요하다.
        * 1. 복제하려는 origin 객체
        * 2. 생성자 인자
    * origin객체는 생성자가 알고 있다.
    * 복사 생성자라면 "2. 생성자 인자"에 this로 넘어온다.
    * 생성자에서는 다음과 같이 된다.
        * nativeClone을 한다.
        * origin객체로부터 _type이 복제되고
        * S chain은 shallowcpy
        * NS는 deepcpy 된다.
        * 생성자 코드를 실행한다. 
* native객체일 경우에는 단순히 가상복사생성자를 처리하면 된다.
* clone() 메소드 사용하면 native이건 mgd 이건 복제가 완료된다. (native 환경에서도 mgd객체를 복제할 수 있다는 뜻이다)

## 기본생성자
* 흔히 하듯, 생성자를 명시하지 않으면 기본생성자가 추가된다.
* 복사생성자를 명시하지 않으면 복사생성자가 추가된다.

## 상속

* 문법은 다음과 같다.

    def <me-identifier>(<constructor call>)* <expr>

* 상속시 부모 클래스가 오는 자리에 expr이 올 수 있다.
```namu
foo() A
   return .....
def B foo()
```
* 상속 단계에서 expr의 output Type으로 진행 한 후, 초기식 단계에서 expr을 직접 수행하여 결과를 assign 한다.

* 상속은 verify&bind 단계에서 진행한다.
    * 2PASS에서는 생성된 origin객체는 자신의 type에 기록된 부모객체로부터 상속을 수행한다.
    * 부모객체는 다음과 같은 모양새를 갖는다.
    * 부모의 S chain은 global scope이 포함되어 부모의 부모클래스들의 모든  상속된 최종 Shared 가 들어있다.
    * 부모의 NS array는 조상과 부모 자신의 모든 NS nodes가 1개의 배열에 들어있다.
    * 부모의 chain은 이 S와 NS가 chain으로 묶여있다.
    * 먼저 부모의 S를 앞에 새로운 배열을 담은 S chain을 this에 할당한다.
    * 파서는 Schain의 첫번째 배열인 이 새로운 배열에 메소드와 static 변수등을 넣을 것이다.
    * 부모의 NS arr를 deepcpy해서 this에 push 하면 상속 완료.

## origin객체의 초기화
* 3phase initialization 에서 origin 객체도 초기화 된다. 이때 다음 요소가 eval 되어야 한다.
    * origin 객체의 부모클래스의 expr
    * origin 객체의 sub variable의 기본값

## 객체는 보통 pack 안에 존재한다.

```go
pack org.worldlang.example

def example1
    ....
```

* namespace 라는 것은 없다.

## me는 scope에 들어갈 때 Object scope에 속한 것처럼 register 된다.

* 예를들어 MyObject 라는 객체가 있을 경우, MyObject 객체는 object scope에 자신을 등록할때 me를 MyObject scope에 넣어둔다.
* 그리고 편의를 위해서 local space에 me를 MyObject.me로 redirection 되도록 한다.
* 따라서 다음과 같은 코드는 모두 같은 것이다.
```go
foo()
me.foo()
MyObject.me.foo()
```

## 기본적으로 제공하는 메소드

* obj 상속받은 객체라면 다음의 메소드를 기본 제공한다.
    * ctor(), ctor(rhs), clone(), get(), set()

## typelist 정의

* 단순히 encapsulation만을 사용해서 원하는 타입의 객체들을 하나의 객체로 묶으려면 다음과 같이 해야 한다.
```namu
def person
    name str
    age int
    weight flt

person.name
person.age
person.weight
```

* 이와 같은 성격의 객체를 typelist라고 정의하며 다음과 같이 축약할 수 있다.
```namu
def person -> name str, age int, weight flt

person.name
person.age
person.weight
```

* 만약 @type 선언 문법을 사용하면 더 줄일 수 있다.
```namu
def tempVal -> @str, @int, @flt
foo() tempVal: tempVal("Chales", 35, 89.5)
ret := foo()
c.out("value1=$ret.str, val2=$ret.int")
```
