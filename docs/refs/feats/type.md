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

