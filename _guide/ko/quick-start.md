---
layout: guide
title: quick start for developer
toc: true
toc_label: "to next-point..."
lang: ko
---

## 개발자를 위한 빠른 가이드 문서입니다.

* 척하면 척하고 알죠.
* 자세한 내용을 알고 싶으면 기본 가이드를 참고하세요.

## 변수와 타입

* 시작은 우리의 `Hello world` 가 아닙니다.
* namulang 에서 타입을 명시적으로 표현할때는 항상 타입을 식별자 뒤에 표현합니다.
* 변수를 정의할때도 다음과 같이 합니다.
```go
value1 int // 뒤의 int가 타입이죠.
```
* 초기화를 해서 변수를 정의할 수도 있는데, 그럴때는 `:=` 기호를 사용합니다.
```go
value1 int := 42
value2 := 42 // 그런데 보통 초기화구문을 넣을때는 타입을 생략합니다.
```
* 다음 타입을 기본 제공합니다.
```go
str1 := "message" // str
bool1 := false // bool
flt1 := 3.5 + 3 // flt
int1 := 15 // int
// void는 변수로 정의할 수 없어요.
char1 := `c`
byte1 := 12
```
{% include embed_src.html src='
main() void
    str1 := "message" // 변수의 정의
    str1 = "wow"
    bool1 := false
    flt1 := 3.5 + 3
    int1 := 15
' id='2' %}

## 함수 호출과 정의
* 함수명과 소괄호를 사용해서 함수호출을 표현합니다.
```go
foo(a, b, c)
```
* parameter 목록과 Tuple과 반환형, Block문이 정의된 것을 함수라 정의합니다.
```go
foo(a int, b flt, c char) void
    print(a + b + c) // print문은 기본 제공되는 함수로, 화면에 값을 출력합니다.
```

* 블록문은 위처럼 항상 Indentation 레벨로 표현합니다. (전문용어로 offside-rule이라고 합니다.

## 흐름 제어
* 흐름제어로 `if`와 `for`를 사용할 수 있습니다.
```go
msg := "hello"
for ch in msg
    c.print("ch=" + ch)
// 결과: 'ch=h ch=e ch=l ch=l ch=o'

n := 0
while ++n < 3 // while 뒤에 bool 식을 넣으면 해당 bool이 true일 동안 반복됩니다.
    if sum in 1..0
        sum += n
    else if sum == 2
        sum -= n
```

## String Template
* StringTemplate도 지원합니다.
```go
print("ch=$ch") // 1 
print("ch=" + ch) // 2
```
* 2 구문은 서로 같은 결과예요.

## Scope

* 항상 Indentation 레벨로 scope를 표현합니다.
* 식별자 이름이 동일해도 scope이 다르면 중복정의 에러가 아니예요. 이 점은 어떠한
상황에서도 적용됩니다.

```go
val := 0 // 1
if val == 0
    if val > 0
      val := val/*1에서 만든 val입니다*/ + 5
      print("val=$val") // 5가 출력되요.
      // 5의 값을 가진 val을 담은 scope은 이제 사라집니다.

print("val=$val") // 1에서 만든 val입니다, 0이 나오겠죠.
```

* ':'는 블록문을 붙여서 쓸 수 있어요.
* `;` 는 다음줄과 같은 블록문에 있다는 의미입니다.

```go
if val == 0: print("1"); print("2") // 1

if val == 0 // 2: 위의 1과 같은 결과입니다.
  print("1")
  print("2")
```
* `:`를 응용하면 이렇게도 쓸 수 있는데요,
```go
if val == 0: if val > 0: print("ok") // `:`를 2번 했어요.
  else: print("no") // 이 else는 indent를 1번 했죠? 그래서 두번째 if에 대한 else예요.

/*
풀어쓰면 이런 코드가 됩니다:

if val == 0
    if val > 0
        print('ok')
    else
        print('no')
*/
```

## 컨테이너
* namulang은 배열, map, pair, sequence를 기본 제공합니다.
```go
intArr := {1, 2, 3} // 각 원소의 Literal 표현식으로 타입 추론합니다.
floatArr := {1.5, 2.5, 3.5}

seq := 1..3 // 시퀸스는 `..` 으로 표현합니다. startInclusive .. endExclusive
입니다.
seq.len == 2 // true. 1, 2가 seq에 포함됩니다.
for n in seq
    c.print(intArr[n]) // "23" 이 출력됩니다.

<< 채우기>>
pair1 := intArr[2]"banana" // ';' represents a pair. and a pair contains 'key' and 'val'.
pair1.key == 3.5 // false
pair1.val = "money?"

map := {pair1, 2.5;"apple"} // map as float[str]

aka sys.cons ->
c.print("how many apple do you have = $map['apple']") // "how many apple do you have = 2.0"
```

## 표현식기반

* namulang은 표현식기반 언어입니다. 무슨 말이냐면, 정의문을 제외하고는 값을
반환할 수 있어요.
```go
isGood := true
max := if !isGood
    print("1")
    print("2")
    -1 // 블록문은 마지막 표현식을 반환합니다.
else: print("3"); 10
// max는 int 타입이고, -1 아니면 10의 값을 가지죠.

val := for n in 0..max // "for"는 배열을 반환합니다.
    n
val.len == 10 // true 입니다.
```





* 제가 언급한 함수 정의에 함수명이 없다는 점을 눈치채셨나요?
* 함수명을 적지 않으면 람다함수를 정의할 수 있어요.

```go
runLambda(val1, (a, b)
  a + b
)
```


closure도 동일합니다.

```go
closure(n int) int = null

if val > 0
    callClosure(c closure, n int) void
        c(n)

    callClosure((n int) int
        return n + 5
    , 22) // watch the comma. it's align to the indentation of 'callClosure' function call.
          // which means that it's belongs to the call as one of argument.
          // if the comma has been attached to the end of 'return' statment inside function,
          // it has totally different meaning.

    /* callClosure((n int) int
        return n + 5, 22)
    ',' is belongs to the line which has 2 indentation level. so it exists as one of term of
    'return' statement.
    now 'callClosure' function is returning two integer, n+5 and 22, and is not valid syntax
    in namulang. */

    callClosure((n): switch n: 22, 23: doSomething(), 23) // ok
    // in above statement, comma was also used to represent the case statement, but it's not
    // ambigious because every case statement has at least one statement.

    callClosure((n): switch n: 22, 23: doSomething()
    , 23) // err. newline should not exist when you put ':' to represent a block statement.
```


## 객체정의

```go
aka sys.cons -> c

def base // base is incomplete origin object
    _realAge := 0 // "_" means protected

    age int // this property don't have a value.
        get(): realAge + 1
        set(new int): realAge = new // it refers the parameter of this method which has a single parameter.

    age2 := 0 // this property has value.
        get(old int): return old + 1 // getter should accepts 1 argument holding the value.
        set(new int) int: return new

    age3 := 0 // convenient way.
        get: return it + 1
        set: return it

    me(newAge int)
        realAge = newAge
        c.out("constructor(int)")

    me(): c.out("constructor()")

    say() str? // returning value can be assigned to null.
        c.out("age=$age")
        return null

def derive(1) from base // derive is complete origin object

    me(new int) // ctor does nothing but calls super()
        super(new)

    // overrided
    say() str? 
        c.out("derive.say!")

def derive2(2) from base(22) // you can call constructor of superclass.
    // this 'derive2' is like a static variable of other languages.

b1 := base(1) // b was created from "base" object.
b1.say() // "age=2"
derive.say()
derive.say() // now, "age=2"

// derive.realAge // can't access private member at outside.

msg1 := "hello" // string is also a object.
msg2 := "hel" + "lo"
msg1 == msg2 // true
msg1 === msg2 // however, they aren't same object.
```


## 프로퍼티
```go
def myObj
    age := 22 // age as int. it has value 22. but is also property.
        get
            sys.cons.out("this will return $it")
            return it 

def myObj2
    age := 22
        set(new int) int: cout("age.$new")
        _get // get is normally returning value of age but isn't accessible from outside.
        // same as, '_get(old int) int: return old'

def app
    main() void
        with myObj
            age // == 22
            age = 5
            age // == 5

        myObj2.age = 10
        if myObj2.age == 10 // compile err. it's protected.
```

## closure

```go
def app
    func() int = null // abstract method.
    // when you declare a func, the func can be also used as a type.

    foo() func // returns a function matching the signature of 'func' function.

        def cnt() from 0 // origin object can be shared and exist as only one instance during the process.

        arr := int[]
        for (n := 1) < ++cnt
            arr.add(n)

        getLenFrom() int // a nested method like a closure.
            arr.len // so, arr can be captured.
                    // all of expr always returns last expr to outside.
        ret getLenFrom // the capturing of arr variable occurs at here. (when assigning value to a closure)

    main() void
        foo()() // == 1
        foo()() // == 2
```


## exceptions

```go
def app
    safeNavigation() void
        activity?.appContext?.res?.getString(1) // safe navigation

    exceptionHandling() int on nullErr, ioErr // specifying that returns err with value.
        try Resources res = getActivity().getAppContext().getResources()
        on nullErr: return it // throw.
        on ioErr: return -1 on it

        return err("unknown")

    foo(val int) int
        return val

    main() void
        safeNavigation()

        // try is available when calls method specified errs with "on" keyword.
        try val := foo(exceptionHandling())
        on err: ret handling()

        if val == -1
            try val = foo(exceptionHandling())
            on err:
                sys.cons.out("you will see this sentence.")
                return
```

```
결과: you will see this sentence
```

## all preserved keywords

### syntax

def from with if elif else ret return continue switch import pack aka as try on in for 
 
### primitive types

int int8 int16 int32 int64 flt flt32 flt64 str bool char void err obj null

### predeclared objects

me it null super

## operators

. _ + - / * % += := == === -= /= *= ^ %=
! ^ & | !! ^^ && ||
[] ...  () ++ ** -- // /* */ : => -> ,
