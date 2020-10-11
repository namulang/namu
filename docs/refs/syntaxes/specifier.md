# specifier

## protected accessor는 멤버 식별자 앞에 _ 를 붙인다

* 접근할때는 _ 는 이름에 포함되지 않는다.
* __를 두번 쓴 경우는 맨 앞의 _만 포함된다.

## => 재지정 연산자

* 문법:
    * ((identifier)* =>)* (method signature) (=>)*
* => 는 메소드 signature 앞에 올 수도 있고 뒤에 올 수도 있다.
* 앞 뒤 모두 올 수는 없다.
* 앞에 올때는 => 앞에 식별자를 두면 해당 변수에 me.super(args)의 결과가 담긴다.

```go
def boy person
    ret on res => sayHello(msg str) on err
        sys.out("ret=$ret res=$res")

    explainMe() void=>
   
if ret on res := boy.sayHello("wow")
    doSomething()
 ```
