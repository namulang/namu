# specifier

## protected accessor는 멤버 식별자 앞에 _ 를 붙인다

* 접근할때는 _ 는 이름에 포함되지 않는다.
* __를 두번 쓴 경우는 맨 앞의 _만 포함된다.

## ==> 재지정 연산자

* 문법:
    ((identifier)* ==>)* (method signature) (==>)*
* ==> 는 메소드 signature 앞에 올 수도 있고 뒤에 올 수도 있다.

### ==>가 메소드 앞에 오면 super를 먼저 call 한다.

* 1: ==> 앞에 아무것도 적지 않으면 super의 반환값을 그대로 반환한다.
* 2: ==> 앞에 식별자를 적으면 super의 반환값이 그 식별자에 담긴다.
* 만약 2번을 사용하고자 하는데 on err 도 반환하고 있었다면 try를 앞에 적어줘야 한다.

```go
def boy person
    // 1:
    ==> sayHello(msg str)
        ....

    // 또는

    res ==> sayHello(msg str)
        return res



    // 2:
    ==> sayHello(msg str) float on err
        return doSomething()

    // 또는

    try res ==> sayHello(msg str) float on err
        on nullErr: return nullErr
        on outOfBoundErr: return outOfBoundErr

        return doSomething()
```


### ==> 가 뒤에 오는 경우는 super한 결과를 반환한다.

```go
def boy person
    explainMe() void
        doSomething()
        return me.super()
  
    // 또는 

    explainMe() void ==>
        doSomething()
 ```
