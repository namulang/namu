# when

## 요점
* 2개의 form이 존재한다.
* primitive 변수와 enum에 대해서만 when을 사용할 수 있다. 일반 클래스는 지원 하지 않는다.

## 문법
```world
when expr
    (<number> | <string> | <boolean>) [, (<number> | <string>)]*
        // if expr.operator==() 로 번역
    range
        // range.has(expr) 로 번역
```

## verification
- range의 타입과 expr의 타입이 서로 호환가능해야 함.
    예) 2..3.has(2.5) 는 true다. (float -> int)
    그러나 2..5.has("3") 는 verification err가 되어야 한다.

- expr의 타입은 operator==를 지원하는 타입이어야 한다.
    primitive 타입만 operator==를 제공하므로 일반 클래스는 여기서 걸러진다.
