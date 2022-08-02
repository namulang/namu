# for

## for문은 2가지로 사용한다.
* for <booleanexpr> 과 for <iterator> in <collector> 다.
* for문은 var가 true를 의미하면 루프를 지속한다. null은 0을 의미하며 0은 false를 의미한다.

```cpp
for <var>
    ...
for true
    ...
for is_success
    ...

for null
    ...
for false
    ...

a = Obj()
for a
    a = null
```

## for in은 별도의 문법이다.
* <var>의 getiterator()를 호출하여 가져온 뒤, 자동으로 next를 호출한다.

## for 문 condition 부분에 정의한 변수는 최초 1번만 정의되고 다음 부터는 할당으로 간주한다.
```namu
foo() int
for isTrue := foo()
    doSomething()
```

* 위의 코드는 사실 다음과 같다.
```namu
isTrue int
for isTrue = foo()
    doSomething()
```
