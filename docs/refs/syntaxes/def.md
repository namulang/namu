# Definition of object

## 프로토타이핑 기반

* 새로운 객체를 정의할 수 있고, 그 객체로부터 복제를 정의할 수 있다. (프로토타이핑 상속의 기본 조건)
* 새로운 객체를 origin 객체라고 한다.

## 프로토타이핑을 하는 이유

* 가장 큰 이유는 class라고 하는 개념을 덜 수 있기 때문이다. 이는 문법에서 몇가지 개념을 덜수 있게 해준다.
    * static 메소드, static 변수
    * class 라는 문법, class는 객체가 아니라는 구분

* 그러나 동시에 프로토타이핑은 2가지 단점이 있다.
    * 전역변수로써 생긴다. 의존성이 겉으로 드러나지 않는다.
    * 어느샌가 원본이 훼손되어 있는 경우 디버깅이 매우 어렵다.

## 생성자는 2벌을 준비한다.

* 기본 생성자는 origin객체가 최초로 접근되어질때 호출된다.
* 이는, origin객체들 간에 순서를 정해주지 않으면 상호 의존 문제가 발생할 수 있기 때문이다.
* 객체 자체는 이미 만들어져 있다.
* 복사 생성자는 원본의 복제 객체가 나올때 호출된다.

'''go
def person
    name str
    @ctor
        name = "I'm unique"
    ctor()
        name = "ctor"
    ctor(src person)
        name = src.name()

def app
    main() void
        person.name // I'm unique 
        person.name = "hello"

        person().name // "ctor"
        person.clone().name // hello
'''

## origin 객체

* origin객체는 컴파일러로부터 생성되며 생성된 후에는 사용자는 절대로 접근이 불가능하다.
* origin객체가 생성되면 이로부터 복제된 객체 1개 시스템에 의해서 생성되며 이를 unique객체라고 한다.
* unique객체는 origin객체의 이름을 부여받으며 사용자는 unique객체에 접근할 수 있다.

## @ctor은 unique 객체의 생성자다.

* 1번만 불려질 것이며
* unique객체에 접근하려고 하는 순간 호출된다.
* 프로퍼티의 기본값은 처음부터 할당이 되어있다.
* @ctor()은 origin 객체의 복제시 호출된다.

## unique 객체는 lazy하게 시스템에 의해서 복제된다.

* 접근하는 순간 복제된다.
* Generic unique 객체를 위해서이기도 하다.

## unique 객체는 복제되지 않는다.

* 프로토타이핑은 원본이 객체이므로 원본이 쉽게 훼손될 수 있으며 그걸 눈치채기가 어렵다.
* 따라서 기존의 로직들이 훼손된 원본에 의해서 다른 결과를 만들어 낼 수 있다. 이것은 장점이기도 하고 단점이기도 하다.
* unique 객체를 복제하기 위해서 문법을 작성하면 실제로는 unique 객체의 원본인 origin객체로부터 복제된다.
* 따라서 unique객체로부터 복제를 하더라도 항상 초기상태의 값으로 객체가 생성된다.

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
* 내부적으로 public member와 private member 2종류가 존재하며 이 들을 chain으로 묶은 배열이 존재한다.

## 객체의 variable은 생성자에서 새로운 객체로 할당되어야 한다.

'''go
def person
    name str
    name1 := "world"

    person()
        name1 = org.name1()

person.name = "hello"
p1 := person()
p2 := person()

p1.name === p2.name // true
p2.name === p2.name // false
'''

* 월드는 복제될때 모든 member에 대해서 얇은 복사를 자동으로 수행한다.
* 그리고 나서 생성자를 호출한다.
* "org"는 origin 객체를 가리킨다.
* "this"는 이 복제본 객체를 가리킨다.

## 상속

* 문법은 다음과 같다.

    def <this-identifier> <identifier>

## 객체는 package 안에 존재한다.

'''go
package org.worldlang.example

def example1
    ....

* namespace 라는 것은 없다.

## 중첩 origin 객체

* 중첩 origin 객체 public으로 될 수 있다.
* origin 중첩 객체는 origin객체를 owner로 삼는다.
* owner의 origin 중첩 객체는 복제 객체로부터 참조하는 origin 중첩객체와 동일한 객체이다.

```cpp
def test
    name := ""

    def in
        koo() void: c.out("name=$name")

    foo() in
        ret in()

def app
    main() void
        test.in.koo() // name=
        test.name = "wow"
        test.in.koo() // name=wow

        new := test()
        // test.in = new.in -> err. in은 ref가 아니다.
        new.name = "new"
        new.foo().koo() // name=new

        test.in.koo() // name=wow
        new.in.koo() // name=wow

        nested := new.in // ok
        nested1 := new.in() // ok
```

## 중첩 객체는 object scope에 등록할때 owner것을 먼저 등록 한다.

* owner와 중첩객체 통째로 context switching 될 수 있다.

## 중첩 객체는 복제될때 현재 object scope의 owner를 내부 참조자에 할당한다.

* 즉 scope은 object scope이 2개 이상 들어갈 수 있어야 하며 어떤게 owner인지 분간해야 한다.

## 기본적으로 제공하는 메소드

* obj 상속받은 객체라면 다음의 메소드를 기본 제공한다.
    * ctor(), ctor(rhs), clone(), get(), set()
