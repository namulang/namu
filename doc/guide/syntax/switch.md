# switch

## 요점
* 2개의 form이 존재한다.
* primitive 변수와 enum에 대해서만 switch을 사용할 수 있다. 일반 클래스는 지원 하지 않는다.

## 문법
```world
switch expr
    (<number> | <string> | <boolean>) [, (<number> | <string>)]*  <-- #1
        // if expr.operator==() 로 번역
    range                                                         <-- #2
        // range.has(expr) 로 번역
```

* 2가지 form을 지원한다.
* #1 form의 경우 if it == <something> || 과 같은 표현으로 간주한다.
  여기서 switch에 질의되는 expr의 타입은 비교되는 <something> 보다 구체타입이어야 한다는 걸 알 수 있다.
  이것은 == 자체가 이렇게 동작하는 것이다.

## verification
- range의 타입과 expr의 타입이 서로 호환가능해야 함.
    예) 2..3.has(2.5) 는 true다. (float -> int)
    그러나 2..5.has("3") 는 verification err가 되어야 한다.

- expr의 타입은 op==를 지원하는 타입이어야 한다.
