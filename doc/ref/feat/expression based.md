# Expression based

## 대부분의 keyword는 expression으로 평가된다.

## ret 는 expression의 값을 도중에 반환한다.

## if 도 expression으로 취급한다.
```namu
flag := true
val := if flag
    ret 3
else
    ret 5
```

* else를 명시하지 않은 경우 해당 타입의 기본값이 할당된다.
    * primitive 라면 0 혹은 ""이 할당되며, 커스텀 타입이라면 null이 들어간다.

## for 도 expression으로 평가된다.
```namu
arr := [1, 2, 3, 4]
lastElem := for e in arr
    if e == 4: ret e * 5
    print(e)
lastElem == 20
```

## def 도 expression으로 평가된다.
```namu
def myObj
    say() void = null

foo(object myObj) void
    object.say()    

foo(def helloObj() myObj
    say() void
        print("hello world"))

/*
foo(def helloObj myObj // 이 경우 origin 객체이므로 호출이 불가능하다.
    say() void
        print("hello world")
)
*/
```

## expression으로 판정시 반환형은 ret 키워드로 판단한다.
```namu
arr := [1, 2, 33, 44]
a := for e : arr
    if e > 22: ret e
    if e == 44: ret e as str
```
* ret e 는 int 이며 ret e as str 는 str 로 반환한다.
* int와 str의 공통 타입은 obj 가 된다.
* a 는 obj 타입이다.

## ret 가 없는 블록문은 void로 판단되며 다른 ret 타입을 우선한다.
```namu
a := if e < 2
    ret e * 2 // int로 유도된다.
else
    print("else") // void로 유도된다.
```
* a는 void + int 최종적으로 int 타입이며 e >= 2일때는 a에 int의 기본값이 할당된다.

### note: 왜 ret를 꼭 사용해야 하는가?
* 위의 예제에서 마지막 줄에 print("else") 에서 사용자는 아무런 값도 반환하고자 하지 않았다.
* 하지만 만약 print의 시그내처가 print(msg str) str[] 이었다면, a는 최종적으로 str[] + int => obj
  로 유도되고 만다.
* 문제는 사용자가 정의한 a 변수에는 타입이 명시되지 않기 때문에 사용자는 int라고 생각할 가능성이
  높다는 데 있다.
* 또한 print가 외부 라이브러리였으며 version 업데이트로 print의 반환형이 바뀌었을때, 위와 같은
  많은 예제들에서 에러가 발생할 것이다.

## ret가 없는 경우 expression으로 받으면 에러가 된다.
```namu
a := if flag // err: a에 할당될 블록문에 어떤 라인에서도 ret를 찾지 못했다.
    22
else
    if doSomething()
        30
    else
        44

a := if flag // ok:
    22
else
    if doSomething()
        ret 30
    else
        44
```
