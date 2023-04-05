# closure

## 월드에서는 중첩메소드를 delegation한 것이 closure다.

## closure는 지역변수를 포함한 변수의 lifecycle을 capture하여 지연시킨다.

```go
def app
    cb(msg str) str = 0

    sayHello(msg str) cb
        firstLetter(from str) str
            return from[0] + msg
        return firstLetter

    main() void
        cb := sayHello("ell")
        sys.out("res=$cb('hello')")
```

## delegation의 파생클래스로써 구현된다.

* object scope만 capture하는 delegation 구현을 기본적으로 수행하며
* local scope 까지 수행한다.

## 최적화를 한다면 closure 에서 실제로 참조하는 외부 변수들만 capture하도록 할 수 있다.
