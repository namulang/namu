# Exception handling

## try - catch는 사라진다. 에러는 단순히 또 하나의 반환값이다.

## on 키워드는 유일하게 메소드에서 multi value return을 하게 해준다.
* on 키워드를 제외하고 multi value가 되는 경우는 없다.

## on 키워드는 err 값을 반환한다.
```namu
foo() str on permErr

got := retVal on someErr := foo()
// got == permErr
```

## worldlang은 예외처리시 하나의 코드 라인에 대해서만 체크한다.
* excpetion handling은 범위체크를 지원하면서 예외코드와 실행코드를 분리시키자는 의도다.
* 그러나 실제로 개발자들은 exception 안쪽에서도 예외처리를 종종한다.
* 따라서 어짜피 안될바에야 C 처럼 하나의 라인에 집중하게끔 한다.

## 보통 on으로 받은 에러는 when 으로 처리한다.

## 예제
```go
def customErr err
     customErr(): super("customMsg")

def app
    foo(val int) void on customErr
        if val < 0: return customErr
        // return; 과 같다. 에러가 아니라면 굳이 on 으로 반환을 하지 않아도 좋다.

    boo() foo

    main() void
        val := boo()(5) // okay. 그러나 exception이 발생하면 F/C
        when val on res := boo()(5)
            // doSomething() // try on 사이에는 다른 expr이 와서는 안된다.
            customErr, permErr // res == customErr || res == permErr
                sys.cons.out("$it")
                sys.cons.out("customErr")
                // break를 넣을 필요가 없다.

            else // == default
                ....

        return // when이 다 끝나면 일반 구문이 와도 된다.
```

## 반환형으로 err 타입을 명시할 수 없다. 그럴 경우 void를 적는다.

## err을 받지 않으면 에러처리 된다.
* 할당 연산자에서 on을 사용하지 않으면 값이 할당연산자의 최종 값이 된다.
* 할당 연산자에서 on으로 err까지 받으면 err값이 최종 값이 된다.

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

## on으로 반환받을때 값이나 err 둘 중 1개를 생략할 수 있다.
```namu
def someErr err
foo() int on someErr // on 반환받을때가 아니다. 고로 생략할 수 없다.

f := foo() // err: on 은 반드시 명시해야 한다.

f1 on := foo() // ok
on res := foo() // ok

if f1 on := foo() // on은 err 값을 반환한다. 여기서는 if f1 이 아니라 if <err of foo()> 가 된다.
    print("err occurs! f1 was $f1")
    return

if ! f2 on := boo()
    print("res value of boo() said that it has no error.")
else
    print("error! f2=$f2")
```
