# Exception handling

## try - catch 대신 try-on을 사용한다.

## try - on은 하나의 코드 라인에 대해서만 체크한다.

* excpetion handling은 범위체크를 지원하면서 예외코드와 실행코드를 분리시키자는 의도다.
* 그러나 실제로 개발자들은 exception 안쪽에서도 예외처리를 종종한다.
* 따라서 어짜피 안될바에야 C 처럼 하나의 라인에 집중하게끔 한다.

## 메소드는 err를 반환한다는 것을 문법으로 간략하게 표현하게 한다.

```go
def customErr err
     customErr(): super("customMsg")

def app
    foo(val int) void on customErr
        if val < 0: return customErr

    boo() foo

    main() void
        val := boo()(5) // okay. 그러나 exception이 발생하면 F/C
        try val := boo()(5)
        // doSomething() // try on 사이에는 다른 라인이 와서는 안된다.
        on customErr
            sys.cons.out("$it")
            sys.cons.out("customErr")
        on err // on은 이어서 여러개 와도 된다.
            .....

        return // on이 다 끝나면 일반 구문이 와도 된다.
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
