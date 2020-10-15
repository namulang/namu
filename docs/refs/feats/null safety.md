# null safety

## exception handling의 한 종류이다.

## 모든 타입은 nonnull이다.

* 메소드 반환값이 평가되는 line을 제외하고는 100% 모든 값은 null이 존재하지 않는다.
* world는 함수 호출 직후, exception에 대해 명시하지 않으면 에러로 간주한다. null또한 exception이다.

```go
try b := boo(5)
    as nullExcept: return

try k := koo(boo(foo()))
    on nullExcept:

// b, k는 non null이다.
```

* 기존 프로그래밍 언어에서 null을 반환해야할 상황에서 월드 개발자는 다음 중 1개를 해야 한다.
    * 나머지 코드를 무시하고 리턴한다.
    * err를 반환한다.
    * 다른 값으로 대신 채운다.

## 편의를 위해 safe navigation을 제공한다.

* 문법: "?."
* 멤버의 반환에 대해서만 사용이 가능하다.

```go
boo(3)?.sayHello()

// 2:
try b := boo(3)
    on nullErr: return
```

## nullable 타입을 지원하지 않는다.

* null이 있을 수도 있는 타입을 지역변수건 메소드인자건 메소드반환이건 변수로 정의할 수 없다.
* null과 정상값이 같이 혼재하는 멤버를 만들수만 있는 것이다.
* 고로 property나 메소드의 반환형에 "?"이 들어갈 수 있게된다.

```go
def app
    name := "wow"? // err
    name := str? // err

    foo() void?
    foo() int?
    foo() int on nullErr // 위와 같은 코드
    foo() int? on outOfBoundErr
    foo(msg str?) int? // err
```

## 프로퍼티에 ?를 묘사한 경우, get()에 그 nullErr를 반환하는 코드가 반드시 1번은 나와야 한다. (verification error)

```go
def my
    name str? // err

    n := 0
    name str?
    // | name str on nullErr
        @get()
            return if ++n % 2 == 0: "wow": else: nullex
```
