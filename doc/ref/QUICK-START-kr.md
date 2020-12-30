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
intArr := [1, 2, 3]
floatArr := [1.5, 2.5, 3.5]

seq := 2..4
seq.len == 3 // true
for n in seq
    c.print(intArr[n])

intVal, floatVal := 2, 3.5 // , for list

tup1 := intVal:"banana"
map := [tup1, floatVal:"apple"] // mas as float[str]

sys.cons aka c // typedef
c.print("how many apple do you have = $map['apple']") // "how many apple do you have = 2.0"
```


# 함수

* 정의시, 역시 type은 항상 뒤에 옵니다.

```wrd
getLen(b int...) int // ... means varidic argument
    sum := 0
    for n in b
        sum++
    return sum

foo(useless int...) int = null // abstract method def.
likeFptr := foo
likeFptr() // foo is abstrat. Exception occurs.

likeFptr = getLen // ok to assign.
lifeFptr() == 0 // true
```


# 객체정의

```wrd
sys.cons aka c

def base
    _realAge := 0 // "_" means protected

    age := int // all member variables are property.
        @get: realAge + 1
        @set: realAge = it  // it refers the parameter of this method which has a single parameter.

    @ctor(newAge int)
        realAge = newAge
        c.out("constructor(int)")

    @ctor(): c.out("constructor()")

    say() str? // returning value can be assigned to null.
        c.out("age=$age")
        return null

def derive base

    @ctor(int new) // ctor does nothing but calls super()

    // overrided
    say() str? => // derive.say() print "derive.say" before calls super's one.
        c.out("derive.say!")

b1 := base(1) // b was created from "base" object.
b1.say() // "age=2"
derive.say() // there is no class. all of them are object, too.
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
        got => @get
            sys.cons.out("this will return $got")
            return got

def myObj2
    age := 22
        @set=>: cout("age.@set")
        _@get=> // @get returns value of age.

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
    int func() = null // abstract method.

    foo() func // returns a function.

        $cnt := 0 // $ means "static" which only can be prefix of a variable.

        arr := int[]
        for (n := 1) < ++cnt
            arr.add(n)

        getLenFrom() int // a nested method like a closure.
            arr.len // all of expr always returns last expr to outside.

        ret getLenFrom

    main() void
        foo()() // == 1
        foo()() // == 2
```


# exceptions

```wrd
def app
    safeNavigation() void
        getActivity()?.getAppContext()?.getResources()?.getString(1) // safe navigation

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

def with if elif else ret return break continue aka as try on in for 
 
## primitive types

int int8 int16 int32 int64 flt flt32 flt64 str bool char void err obj null

## predeclared objects

me it null super @set @get @ctor

## operators

. _ + - / * % += := == === -= /= *= ^ %=
! ^ & | !! ^^ && ||
[] ...  () ++ ** -- // /* */ : => -> ,
