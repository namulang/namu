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

## try - on

    try (expr)
        on (errType)
        ..
        ..

* 예제
```go
def app
    foo() int
    boo(n int) bool on nullErr, err ==> 
        if n < 0
            return nullErr
        else
            return err

    koo(n bool)

    main() void
        b := boo(5) // err

        try b := boo(5)
            as nullErr: return

        try k := koo(b := boo(foo())) // try - on
            on nullErr:
                ....
                ,,,
                k = ...
                // err. b = ... 가 없다.

            on err:
                return
            // 2개 모두 적어야 한다.
```

## try에서 수행중 발생한 모든 에러를 on 중에 하나와 매칭해서 처리한다.

## try-on vs try-catch

* tryon은 한줄에 포커스를 맞춘다. (한 메소드 콜이 아니라) 여러줄에 걸쳐서 예외처리를 하면 예외처리에 들어갈 라인도 같이 길어진다. 이는 try-catch가 예외처리와 로직을 분화하는 방식이 마음에 안들어서 그런것이다. 예외처리와 로직을 분리가 어렵다.
    * 전통적인 if 예외처리와 try-catch의 예외처리 방식이 이질적인데 개발자들은 2가지 모두 사용한다. 그래서 한가지 방식으로 예외처리 방식을 합치고자 한 것이다.
* try-on은 예외를 처리하지 않으면 경고로 취급한다. 
* 처리되지 않은 예외는 즉각 런타임 에러다.
* try-on은 명시가 없으면 예외를 밖으로 던지지 못한다.

## 한줄의 에러는 한번에 처리할 수 있다.

* 도중에 err가 발생하면 나머지 동작은 중지된다.
* 블록문 안쪽이 아닌 변수 정의에서 try를 한 경우 Err가 발생하면, 이 값에 별도의 동작을 할당하지 않으면 에어로 간주한다. (verification error)
* 여러줄은 안된다.
* 여러개의 err가 동시에 on에 도착하는 일은 없다.

## 빌트인으로 exception 객체를 제공한다.

## 새로운 exception 객체를 생성해서 반환할 수 있다.

```go
def app
    def myErr err
        msg := ""
        myErr(msg str)
            this.msg = msg    
            
    foo(msg str) void on err
        return myErr(msg)

    main() void
        try foo("wow"): on myErr:
            myErr.log() // "wow"
```

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

## on은 왼쪽의 lhsexpr과 동일한 우선순위를 갖는다.

## on으로 반환할 수 있다.

```go
def app
    foo() int on err
        return 55 on customErr
```

## 에러는 handling 하지 않으면 경고 처리한다.

## 처리 되지 않은 에러는 즉시 F/C로 이어진다.
