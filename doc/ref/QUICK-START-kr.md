# Quick Start in KR 

```wrd
// don't need to import sys.cons.

def app
    main() void
        sys.cons.out("Hello world!")
```


# 변수와 표현식

* 정의시, type은 항상 뒤에 옵니다.

```wrd
str1 := "message" // 변수의 정의
str1 = "wow" 
bool1 := false
flt1 := 3.5 + 3
char1 := 'c'
int1 := 15

toInt := int1 as flt64 // casts int as 64bit float.
```


# 흐름 제어
```wrd
msg := "hello"
for ch in msg
    c.print("ch=$ch") // ch=h ch=e ch=l...

n := 0
for ++n < 3
    if sum in 1..0 // reversed range.
        sum += n
    elif sum == 2
        sum -= n
```


# 컨테이너

```wrd
intArr := {1, 2, 3}
floatArr := {1.5, 2.5, 3.5}

seq := 2..4
seq.len == 3 // true
for n in seq
    c.print(intArr[n])

pair1:= intVal;"banana"
pair1.key == 3.5
pair1.val = "money?"

map := {pair1, 2.5;"apple"} // mas as float[str]

sys.cons aka c // typedef
c.print("how many apple do you have = $map['apple']") // "how many apple do you have = 2.0"
```


# 함수

* 함수는 본문이 있는 소괄호로 정의합니다.
    * 반환형을 없어도 된다는 얘기입니다.
    * 함수명이 없어도 된다는 얘기입니다.
    * 인자가 없어도 된다는 얘기입니다.
* 함수 안에서라면 인자타입이 없어도 됩니다.
* 정의시, 역시 type은 항상 뒤에 옵니다.

```wrd
getLen(b int...) int // ... means varidic argument
    sum := 0
    for n in b
        sum++
    return sum

getLen(b int) // return type is deducted to 'int'
    sum := 0
    return sum

(b int) // ok. but never got called.
    sum := 0
    return sum
    
fun := () // == returns closure refering <nameless function>() str.
    return ""
fun()

setClickListener((v): v.onClick())

// getLen(b int) --> err. if context is missing, this should be regarded to a function call.

foo(useless int...) int = null // 'null' declares that this is abstract method def.
likeFptr := foo // foo can be used as a type.
likeFptr() // foo is abstrat. Exception occurs.

likeFptr = getLen // ok to assign.
lifeFptr() == 0 // true
```


# 객체정의

```wrd
sys.cons aka c

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

# 표현식기반

```wrd
max := if isGood := false // max as int
    c.out("never reach here.")
    c.out("and returns the last expr to outside of block")
    -1 
else: c.out("or use \"ret\" keyword"): ret 10

if isGood: return; // never reach here

val := for n in 0..max // "for" returns last expr while it loops.
    n
val == 10 // true
```


# 프로퍼티
```wrd
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

# closure

```wrd
def app
    func() int = null // abstract method.

    foo() func // returns a function.

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


# exceptions

```wrd
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

* 결과: you will see this sentence

# all preserved keywords

## syntax

def from with if elif else ret return continue switch import pack aka as try on in for 
 
## primitive types

int int8 int16 int32 int64 flt flt32 flt64 str bool char void err obj null

## predeclared objects

me it null super

## operators

. _ + - / * % += := == === -= /= *= ^ %=
! ^ & | !! ^^ && ||
[] ...  () ++ ** -- // /* */ : => -> ,
