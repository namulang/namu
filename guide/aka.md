# aka

* 식별자의 별칭을 만들 수 있다.

    aka (<path>|<defexpr>) '->' <alias-id>

* path는 '.' 으로 이어지는 식별자다.
* defexpr은 함수정의, 변수 정의, 객체 정의 등이 해당된다.

## 축약 형태

    aka <path>

## 정의와 동시에 aka를 쓸 수 있다.

```namu
aka sys.console

aka def person from obj() 
    aka callback() void -> c
    aka callback(whatever flt) void = null -> c2

    callback(whatever str) void
        console.print("")
        doSomething()
        ...
        return aka (lamb,da) str
            ....
            ->l

        aka (lamb, da) -> str
            ....
        ->l2

        return aka ((labm, da) -> str
            ....
        ) -> l3 // ok.
-> p
```

## aka도 expression 이다.

```namu
foo(aka (view): view.show() -> lambda, 33)
/*  or,
aka (view)
    view.show()
-> lambda */
foo(lambda, 33)
```
