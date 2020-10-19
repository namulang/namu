# Exception handling

## try - catch를 사용하지 않는다.

## 메소드는 err를 반환한다는 것을 문법으로 간략하게 표현하게 한다.

```go
def customErr err
     customErr(): super("customMsg")

def app
    foo(val int) void on customErr
        if val < 0: return customErr

    boo() foo

    main() void
        val on res := boo()(5)
```

## 반환형으로 err 타입을 명시할 수 없다. 그럴 경우 void를 적는다.

## err을 받지 않으면 경고처리 된다.

* 할당 연산자에서 err을 받지 않으면 값이 할당연산자의 최종 값이 된다.
* 할당 연산자에서 err까지 받으면 err값이 최종 값이 된다.

```go
foo(val int) int on err
    ....

if a := foo(5) // if a가 0이 아니라면
if a on res := foo(5) // if foo(5)에서 err가 나왔다면
if !(a on res != foo(5)) // if foo(5)에서 err가 나오지 않았다면
if on res := foo(5) // if foo(5)에서 err가 나왔다면
```

## on으로 반환할 수 있다.

```go
def app
    foo() int on err
        return 55 on customErr
```

## 에러는 handling 하지 않아도 경고가 아니다. 단순히 반환값 중 1 개일 뿐이다.

## exception이란 없으며 모든 것은 런타임 에러, 즉 F/C로 이어진다.
