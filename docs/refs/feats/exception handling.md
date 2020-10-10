# Exception handling

## try - catch를 사용하지 않는다.

* try catch는 하는 역할이 많다.
    * 여러 종류의 에러를 반환값에다가 추가로 전달한다.
    * 범위에 걸쳐서 에러를 찾게 한다.
        * 그러나 대부분은 exception이 발생하는 부분은 1부분에 불과하다. 나머지는 불필요하게 범위를 설정한 것이다.
    * exception이 처리되지 않을 경우 unwinding이 된다.

* 익셉션의 단점은
    * 로직과 예외처리가 완전히 분리되지 않는다.
        * 로직안에 다른 예외처리를 넣는 경우도 부지기수다.
    * 문법이 장황하다.
        * 블록문이 2,3개씩 들어가야 하며 블록문 마다 키워드, 메소드형태의 시그내처, 괄호 등
    * 프로그램의 동작이 일반적이지 않다.
        * 메소드처럼 보이지만 그 안에서 return하면 함수 자체가 종료된다.
        * 익셉션을 처리하지 않을 경우, 상위로 전파된다. 그게 잘 눈에 보이지 않는다.
    * 잘못 짤 수 있다.
        * global exception을 만들어버리면 모든 에러를 다 흡수해버린다. 눈에 띄지 않게 된다.
    * 예외처리 부분이 길어지면 오히려 코드에 집중을 못하게 된다.


## err라는 타입을 빌트인으로 제공한다.

## 메소드는 err를 반환한다는 것을 문법으로 간략하게 표현하게 한다.

```go

def customErr err
    customErr(): super("customMsg")

def app
    foo(val int) void on err 
        if val < 0: return customErr

    boo() foo

    main() void
        val on res := boo()(5)
```

## 반환형으로 err 타입을 명시할 수 없다. 그럴 경우 void를 적는다.

## err를 받으려면 on 키워드를 쓴다. on err 메소드에 대해서만 가능하다.

* err를 받는 용도로 사용된다. 문법은
    <identifier> on <identifier>

## on은 왼쪽의 lhsexpr과 동일한 우선순위를 갖는다.

## on으로 반환할 수 있다.

```go
def app
    foo() int on err
        return 55 on customErr
```

## on은 반환형으로 res을 반환한다.

```go
if val on res := foo(-5) // res가 null이 아님. 즉 에러라면.
    ....
```

## 빌트인 err들을 제공한다.

## err는 exception 처럼 unwinding이 되지 않는다.

```go
def app
    main() void
        koo(boo()(5), 22) // boo()(5)에서 err가 발생했지만 잡아낼 수 없다.
```
