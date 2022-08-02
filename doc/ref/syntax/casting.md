# casting 

## Casting은 3 종류가 존재한다.
- Native에서의 dynamic cast
- worldlang ast를 대상으로 한 묵시적 형변환
- worldlang ast를 대상으로 한 명시적 형변환

## 명시적 형변환
  - 월드의 형변환은 1가지 문법으로 100% 대체가 가능한데, as() 함수다. as 함수는 다음과 같은 순서로 우선순위를 갖는다.
    - 사용자가 정의한 캐스팅코드
    - 거기에 없으면 클래스 계층상 구체클래스타입을 원하는 경우(= RTTI)
    - 거기에도 없으면 실패. 끝.
  - 1, 2번은 모두 WorldFrx 안에 탑재되어있어야 한다.
  - Node에 정의된 virtual Refer as(Class&) 함수가 실질적인 형변환을 수행한다.
  - Native환경에서는 타입이 구체적으로 나와야 편하기 때문에 TRefer<T> as<T>()도 제공한다.

## native 언어의 지역변수는 명시적 캐스팅이 안된다.
```c++
void main() {
    Int val(5);
    val.as<Flt>()
}
```

## native 환경에서 지역변수도 바인딩 된다.
* smartptr 같은 바인딩은 본래 HEAP에 속한 인스턴스에 한해서 동작한다.
* 그러나 native 환경에서 사용자가 개발할 때는 local 변수나 HEAP에 속한 변수도 모두 한 데 넣고 범용적으로 처리할 경우가 있다.
```c++
ref* getArray() {
    static Int staticInt(22);
    static ref cache[] = {
        new ref(new Int()),
        new ref(&staticInt) // smartptr라면 heap에 있는 변수가 아니므로 binding 이 불가능하다.
    };
    return cache;
}

void main() {
    ref arr[] = getArray();
    for (auto e : arr) {
        if (!ref.get("val"))
            return;
    }
}
```
* 이를 위해서 world에서 적용하는 binding API는 로컬변수에 대한 바인딩도 지원한다.
* 로컬바인딩은 Weak만 지원한다. 다음의 기능을 제공한다.
    * Binding 여부를 알려줄 수 있다.
    * Binding 했던 인스턴스가 사라졌다는 걸 알려줄 수 있다.
    * Binding 유지는 할 수 없다. (Weak)

## as함수의 반환형은 Bind 다.

* Bind 클래스는 Strong과 Weak 모드 양쪽으로 동작 가능한 클래스다. namu frx 에서는 대부분 이 Bind 클래스로 나갈 것이다.
* 상황에 따라서 Weak일 수도 있으며 Strong 일 수도 있다.
* 이는 로컬바인딩으로 나가는 상황을 고려한 것이다.
* Strong로 나간걸 Weak로 받을 수 있다. Bind로도 받을 수 있다.
* Weak를 Strong으로 받을 수 없다. Bind로는 받을 수 있다. 타입체킹을 해야 한다.

## 묵시적캐스팅

ast를 대상으로 해서 부모클래스로의 캐스팅 + 일부 primitive 변환이 해당된다.

묵시적 캐스팅의 의의는 함수 디덕션 과정 (참고로 함수디덕션은 단순히 함수호출을 의미하는게 아니다. World는 모든 것이 msg의 송수신, 즉, 함수로 보기 때문에 생성자 생성과 연산자, if 같은 keyword까지 포함한 모든 것을 의미한다)에서 주어진 인자로 이 함수를 호출 할 수 있는 지를 판단하기 위해 타입의 교량역할을 하는 것이다.

## built-in type에 대한 묵시적 형변환 목록

- built-in 타입들에 대해서 최소한의 묵시적형변환을 지원해준다. 그 이외에는 직접 개발자가 캐스팅을 코드에 명시해야 한다.
- 사용자가 작성한 타입을 부득이 다른 타입으로 변환한다는 것은 World가 적절한 타입으로 변경해준다는 걸 의미한다. 여기서 "적절함" 이란 일종의 AI를 의미한다. AI를 넣을 수 없다면 그걸 대신 할 수 있는 대중의 합의점에 해당하는 데이터가 필요로 해진다.
- 형변환 테이블에는 비슷한 그룹군이 담겨있다. 우선순위는 존재하지 않는다.
  - 원칙
    - 작은것은 큰것으로 흘러가는 것이 원칙이다. 그러나 사용성을 위하여 몇가지 예외를 둔다. (int -> float, char -> int, int -> string)
    - 예외적으로 숫자 그룹군끼리는 서로 호환된다.
    - 대부분의 built 타입은 string으로 묵시적 변환될 수 없다.
  - int --> float, char, bool
  - float --> int, bool
  - char --> float, int, bool
  - bool --> int
  - result --> string, bool

* 예외적으로 0과 null은 false로 변환 될 수 있다. 0 이외의 값은 true다.

## str은 묵시적캐스팅에 해당하지 않는다.

산술연산인 int, char, byte, 등만 해당된다.
자바와 같은 방법이다. str도 포함되면 모호성 오류가 너무 많다는 걸 알았다.
단, 자바처럼 str + int 식의 + 에 한해서만 묵시적 캐스팅을 지원해 줘야한다.

## 메소드 호출시 인자에 대해서는 묵시적 변환만 이루어진다.

이 말은, 어떤 메소드를 호출해야 하는지 바인딩을 선택하는 과정에서 묵시적 변환으로 판단해야 한다는 것이다.
캐스팅의 주체는 객체 자체가 해야 한다. 따라서 메소드 호출을 담당하는 객체는, 각 인자들에게 해당 타입으로 변환이 가능한지를 질의한다.

## 연산자 우선순위는 파서에 의해서 구현된다.

## 캐스팅 문법

    <expr> as <identifer>
    <expr> as? <identifier>

* 모든 변수는 캐스팅의 타입으로 사용 가능하다.
* as에서 casting이 실패하면 런타임 에러가 된다.
* as?에서 casting이 실패하면 null이 들어간다.

## as의 알고리즘
* as는 매우 기본적인 func이므로 node가 갖는다.
* is도 같이 제공해야 한다.
* native 환경에서는 as<T>가 더 편할 것이다. 같이 제공한다.
* as 안쪽에서는 각 class 안쪽에서 type에 대해 적절한 bind가 나가도록 구현한다.
    * is 와 짝이 맞아야 한다.

## is

    <expr is <identifier>

* casting이 가능하면 true, 불가능하면 false가 나온다.

```cpp
def A
    bla bla...

def B A

a := B()

b := a as b // err. b는 아직 정의되지 않았다.
b := a as B
b := a as B() // err.

get() A
    return B()

b2 := get() as a as B as b // (b) ((B) ((a) get()))
```

## 상수를 명시적 캐스팅에 이용해서는 안된다.

```cpp
a := 35 // ok
a1 := 35.5 as int // ok
a2 := a as 35.5 // err
```

* 착각하지 않도록 하자. 상수도 묵시적 변환은 이루어진다.

## 묵시적 형변환으로 다른 타입이 되어 setter 메소드에 넘겨도 괜찮다.
* 다음의 시나리오를 보자.
```cpp
def a()
    print(msg str) void
        msg += "msg = "
        c.out(msg)
    print(msg flt) void

a.print(35) // err
a.print(35 + "") // "msg = 35"
```

* 35는 string으로 형변환 되지 않는다. 너무 많은 모호성 오류가 나오기 때문이다.
    * 만약 array 같은 것이 묵시적형변환이 된다고 했다면 문제가 더 심각했을 것이다.
* str에 대한 + * - / 등의 산술 연산으로 인한 타입유추는 str를 지원한다.

## 커스텀 명시적 캐스팅은 as 를 오버라이딩 해서 지원한다.
* 임의 타입에 대해서 다른 타입으로 명시적 변환이 가능하도록 하려면 @as를 오버라이딩한다.

```go
def base
def my base
    name := ""

    @as str
        sys.term.out("as")
        ret name 
    @as int
        ...

base1 := my() as base
base1 as str // as
base1 as int
base1 as my

## upcasting의 알고리즘
* 구현상 문제가 되지 않는다. 다음 예제를 놓고 시나리오를 분류해보면 명확해진다.
```go
def A
    foo() void: sys.out("A")
    boo() void

def B
    foo(int) void: sys.out("B(int)")
    boo() void: syhs.out("B.boo()")

a A := B()
a.foo(5) // 에러
(a as B).foo(5)
a.boo() // B.boo가 나온다. 당연하다.
```
    * boo()와 같이 파생과 부모에서 signature가 같다면 이건 override가 된다. 문제 없다.
    * 부모에는 없고 자식에게는 있는 거라면 업캐스팅은 부모만 다루기 때문에 문제가 되지 않는다.
    * 부모에는 있고 자식에게만 없는 경우는 존재하지 않는다.

## downcasting의 알고리즘
* 문제가 되는 것은 downcasting 이다.
* 컴파일 시점에서는 항상 캐스팅이 성공한다고 가정하고 verify 한다.
* 런타임에 실제로 캐스팅이 실패한 경우 Exception을 내보낸다.




