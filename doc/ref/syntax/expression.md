# Expression

## 기존 언어의 statement 중 상당 수가 expression 기반이다.

* 객체의 정의, 메소드의 정의, 변수의 정의, if, for 등

## 모든 블록문은 마지막 라인을 자동으로 반환한다.

```go
def app
    foo() bool
        age := 35
        isYoung := if age < 25
            true
        else
            false

    main() void
        res := foo()
        sys.term.out("res=$res")

// result: false
```

## Worldfrx를 통해서 expression 객체를 pack에서 조작해서는 안된다. (invisible)

## if-else 에서 양쪽 블록문 안에서의 값으로 수렴한다.

```go
res := if 3 < 5
    "wow" // str type
else
    [person("boy"), person("girl")] // arr type

// res는 str과 arr 모두 가능해야 한다.
// str과 arr를 모두 포함할 수 있는 타입은 node 밖에 없다.
res is node // true
```

## expression과 statement는 구분이 필요하다. 모든 statement가 expression인건 아니다.

* 대표적으로 import 를 들 수있다.
* 문법의 추가로 또다른 예가 생길 수 있다.
