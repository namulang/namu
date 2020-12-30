# type

## worldlang은 타입이 존재한다.

## type은 worldfrx에 type, ttype<T> 와 같은 컴포넌트로 구현된다.

## type은 monostate다.

## type은 C++의 RTTI를 제공한다.

* 부모 클래스 판단
* "is" 메소드가 여기서 구현

## type은 메소드콜의 인자의 verification에도 사용된다.

## type은 nativeType과 mgdType 2종류로 상속된다.

## mgdType은 origin객체를 반환할 수 있다.


## aka

* 식별자의 별칭을 만들 수 있다.

    <원본식별자> aka <별칭이름>

### 정의와 동시에 aka를 쓰는 경우 문법이 조금 생소할 수 있다.

```go
def person obj() 
    callback() void aka c

    callback(whatever flt) void = null aka c2

    callback(whatever str) void
        doSomething()
        ...
        return (lamb,da) -> str aka l
            ....
    aka c3

aka p
```

* 정의는 식별자를 대신한다.
* 따라서 정의가 모두 끝나고 난 뒤에 aka가 나와야 한다.
* 그러나 정의는 대부분 개행을 가지고 있다.
* 그러니 개행이 끝나고 정의블록문의 시작했던 indent 앞에 바로 aka가 나오면 된다.
* 블록문이 없는 정의라면 바로 이어서 같은 라인에 aka가 나온다.

## type을 정의하면 그것의 unique object가 그 type이름에 대신들어간다.

* 메소드도 마찬가지다.

## type에 대고 생성자를 호출하면 unique obj의 복제가 아니라 type의 복제가 된다.

## class란 native type 을 의미하며 meta 모듈에 의해 관리된다.

## meta module

* 별도의 기반 모듈로써 native의 reflection을 담당한다.
* world에서 제공하는 메타 API의 backend 에 해당한다.

### unregister를 지원해야 한다.

* C-REPL 지원을 위해서 native 모듈도 붙었다가 떼어졌다가 된다.
* 따라서 native class 정보 또한 시스템에서 제거될 수 있어야 한다.

### 타입의 연관정보는 모두 meta 모듈에 의존한다.

### 매크로를 통해서 meta class를 생성할 수 있어야 한다.

* 이경우 프로그램이 시작하기 전에 자동으로 register를 한다.
* unregister는 자동으로 할수 없다.

### 사용자가 정의한 metaclass 객체를 생성/등록 할 수도 있어야 한다.

* 상속 기반이 아니라 객체 기반이어야 한다는 것이다.
* 물론 unregister도 가능해야 한다.
