# specifier

## protected accessor는 멤버 식별자 앞에 _ 를 붙인다

* __를 두번 쓴 경우는 맨 앞의 _만 포함된다.

## func 내에서 정의된 static 요소들(func, origin, static variable)은 제한된 protected를 지닌다.
* func 외부에서는 이 sub nodes 들에 접근하지 못한다.
* 중첩메소드는 이 func의 요소들에 접근할 수 있다.

## 접근제한자의 구현
* 구현 상으로는 모든 sub에 접근이 가능하다.
* 그러나 interpreter는 컴파일타임에 verify 하고 에러를 내보낸다.
* 특정 요소가 protected인지 public인지 판단은 getName()[0] == '_' 으로 한다.
* protected 일 경우, 접근을 해도 되는지 여부는 node.isAccessibleFrom(obj) 로 체크한다.
    * node가 일반 객체일 경우에는 isAccessibleFrom(thisObj)는 thisObj와 node가 동일한 pack에 속해 있다면 true다.
        * node.getType().getModule() 로 얻어올 수 있다.
    * node가 중첩메소드일 경우에는 thisObj == func.origin로 비교 한다.

## class 앞에 _를 붙이면 packaged 가 된다.

* 동일한 패키지 안에서는 접근 가능하다.
* 여기서 접근이 차단되는 것은 unique 객체를 의미한다.
* 복제된 객체라면 packaged 접근자라고 하더라도 외부에서 가져갈 수 있다.

## -> 재지정 연산자

* 문법:
    ((identifier)* ->)* (method signature) (->)*
* -> 는 메소드 signature 앞에 올 수도 있고 뒤에 올 수도 있다.

### ->가 메소드 앞에 오면 super를 먼저 call 한다.

* 1: -> 앞에 아무것도 적지 않으면 super를 실행하되 반환값을 보존하지 않는다.
* 2: -> 앞에 식별자를 적으면 super의 반환값이 그 식별자에 담긴다.
* 만약 2번을 사용하고자 하는데 on err 도 반환하고 있었다면 try를 앞에 적어줘야 한다.

```go
def boy person
    // 1:
    -> sayHello(msg str) int
        return 0 // super의 반환값은 사용하지 않는다.

    // 2:
    -> sayHello(msg str) float on err
        return doSomething()

    // 또는

    try res -> sayHello(msg str) float on err
        on nullErr: return nullErr
        on outOfBoundErr: return outOfBoundErr

        return doSomething()
```
### -> 가 뒤에 오는 경우는 super한 결과를 반환한다.

```go
def boy person
    explainMe() void
        doSomething()
        return me.super()
  
    // 또는 

    explainMe() void ->
        doSomething()
 ```
