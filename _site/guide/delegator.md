# delegator

## 메소드를 정의하면 그것이 곧 delegator로 사용할 수 있다.

```go
cb(msg str) void = null // just interface. can't call this function directly.
cb2(msg str) void: ret // returining void. it's accessible.
foo(msg str, @cb) void
    cb(str)
```

## func과 nested func은 delegator를 생성하는 API를 각각 다른 방법으로 제공한다.
* 일반 func의 경우 특정한 objscope에 대해서 scope capture를 하면 된다.
* 반면 nested func의 경우 outer func의 localscope 까지 모두 capture가 되어야 한다.
    * nested func은 outer func 안에 있는 상황이기 때문에, 모든 시나리오에서 이 nested func에 접근하려면 이미 outer func의 S, NS가 scope에 올라간 상황이 된다.
    * nested func은 이 outer func의 scope에 크게 의존하고 있는 특수한 문법이므로 capture가 될때에도 outerscope 위에 자신의 것이 capture가 되어야 한다.
* 일반 func과 nested func은 모두 delegate() Delegator 를 제공하며, nested Func은 이것을 override 해서 localscope도 capture가 되도록 만든다.
* implicitCast(type) 혹은 as(type) 에서 func이 들어온 경우에는 현재의 stackframe으로부터 호출자 frame을 [1] 로 추출하여 thisobj로 eval 한 다음에 수행한다.
    * 단순히 stackframe[1] 알고리즘으로는 native 환경에서 주의 깊지 못한 개발자가 잘못 호출하면 stackframe이 엉망이 된 상태에서 호출자 frame을 유추하지 못할 수 있다.

## 메소드에 접근하는 expr은 Delegator로 캐스팅 될 수 있다.
* 객체를 통해 func에 접근하는 경우:
```go
def person
    sayHello(name str) void
func := person.sayHello

DeclExpr("func", FuncType(sayHello), AccessExpr(AccessExpr(scope, "person"), "sayHello"))
```
    * 이 경우 DeclExpr은 AccessExpr(AccessExpr(scope, "person"), "sayHello").cast(FuncType) 을 시도한다.
    * Func.as() 혹은 Func.implicitCast(funcType) 이 되면서 delegator가 나오게 된다.

* 객체의 명시적인 접근 없는 경우:
```go
def person
    sayHello(name str) void
    foo() sayHello
        return sayHello

        ReturnExpr(AccessExpr(scope, "sayHello"))
        // 구현상으로는 위의 케이스와 동일하게 AccessExpr이 담당하는 걸 알 수 있다.
```

## Delegator가 생성될때 scope 캡처가 발생한다.
* scope 캡처를 위한 chain 1개와 func에 대한 ref 1개를 갖는다.

## 메소드에 this는 값으로 접근했을때의 this이다.
* 임의의 객체를 통해서 메소드에 접근하였고 그것이 값으로써 다른 변수의 할당될때 해당 변수는 delegator로 정의된다.
* delegator로 메소드가 값을 넣을때 delegator는 메소드 접근시 사용한 this를 capture해 놓는다.
* 클로져는 현재의 local scope 까지 capture하므로 delegator에서 구현이 하나 더 추가된 것이다.
* delegator는 메소드가 호출되기 직전 capture한 scope를 load한다.
* 메소드가 끝나면 scope를 원상복구 시킨다.

```go
def person
    sayHello() void
        sys.out("hello world")

p := person()

arr := [p.sayHello, person.sayHello]
arr2 person.sayHello[] // 타입으로 접근한 것이므로 this는 무시된다.
arr2 = arr

for fn in arr2
    fn() // 사용시 this를 필요로 하지 않는다.
```
