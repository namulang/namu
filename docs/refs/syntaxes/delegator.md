# method delegator

## 메소드를 정의하면 그것이 곧 delegator로 사용할 수 있다.

```go
cb(msg str) void // or = 0
foo(msg str, @cb) void
    cb(str)
```

## 메소드 정의시 뒤에 = 0을 붙이면 해당 메소드는 abstract 이다. (method.md 참고)

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
