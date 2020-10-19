# Quick Start KR 

```wrd
import sys.cons aka c
def app
    main() void
        c.out("Hello world!")
```


# 변수와 표현식

```wrd
str1 := "message" // 변수의 정의
str1 = "wow" 
bool1 := false
float1 := 3.5 + 3
char1 := 'c'
int1 :+= 15

toInt := int float3 // casts float to int.
```


# 흐름 제어
```wrd
msg := "hello"
for ch in msg
    c.print("ch=$ch") // ch=h ch=e ch=l...

sum := 0
for n in 2..3
    if sum <= 0
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

(intVal, floatVal) := (2, 3.5)

map := [intVal:"banana", floatVal : "apple"] // float[str] type.
c.print("how many apple do you have = $map['apple']") // 2.0
```


# 함수

```wrd
int getLen(int a, int b)
    sum := 0
    for n in [a, b] 
        sum++
    retfun sum

int foo(int.. useless) // does nothing
likeFptr := foo
likeFptr() == null

likeFptr = getLen // ok
```


# 객체정의

```wrd
def base
    _realAge := 0 // protected
    age := prop from int
        @get(): realAge + 1
        @set(int new): realAge = new

    @ctor(int newAge)
        realAge = newAge
        c.out("constructor(int)")

    @ctor(): c.out("constructor()")

    int say()
        c.out("age=$age")
        return 0

def derive from base

    @ctor(int new) // ctor does nothing but calls super()

    // overrided
    int say()=> // derive.say() print "derive.say" before calls super's one.
        c.out("derive.say!")

b := base(1) // b was created from "base" object.
b.say() // "age=2"
b = derive // there is no class. all of them are object, too.
b.say()

// derive.realAge // can't access private member at outside.

msg1 := "hello" // string is also a object.
msg2 := "hel" + "lo"
msg1 == msg2 // true
msg1 === msg2 // however, they aren't same object.
```


# 표현식기반

```wrd
isGood := false
max := if isGood
    c.out("never reach here.")
    c.out("and returns the last expr to outside of block")
    -1 
else: c.out("or use \"ret\" keyword"): ret 10

val = for n in 0..max // for returns last expr while it loops.
    n
val == 10 // true
```


# 프로퍼티
```wrd
def myObj
    _realAge := 22
    age := prop propOfRealAge from int
        @get(): ret realAge
        @set(int new)
            cout("age.@set")
            realAge = new

def myObj2
    age := prop from int(22)
        @set=>: cout("age.@set")

// myObj's age will do exactly same actions to what the 'age' from myObj2 will.
```


# closure

```wrd
int func()
func foo() // returns a function.
    $cnt := 0 // $ means "static" which only can be prefix of a variable.

    for n in 1..cnt++ // "++" priority precedes to ".."
        out arr := int[]() // define a empty int[]
        // out puts variable out of "for" block.
        arr.add(n)

    int getLenFrom() // this is a method in a method.
        arr.len // all of expr always returns last expr to outside.
                // and it can access local variable at outer method.
    ret func 

f1 := foo()
f2 := foo()

len1 := f1()
len2 := f2()
len1 == 0 and len2 == 1 // true
```


# exceptions

```wrd
getActivity()?.getAppContext()?.getResources()?.getString(1) // safe navigation

with
    @warn(rNull) // catches rNull exception and just print logs.
    Resources res = getActivity().getAppContext().getResources()
    res.getString(1)
    @res(rOutOfBound ex) // res also caches exception but does nothing.
        c.print("ex=$ex")
        ex.calls.print()
        retfun ex // throw.
actitivty := Activity null // assign null.
activity.getAppContext() // this occurs rNull exception but no catch, F/C occur.
```


# all preserved keywords

## syntax

def from with if elif else ret retfun retif retfor again out prop import aka
 
## predefined

int float str bool char void this me got node null super @set @get @ctor @dtor

## operators

. <casting> $ _ + - / * % += := == === -= /= *= ^ ! %= :+= :-= :*= :%= %= :/= 
[] ..  () ++ ** -- // /* */ : => -> 
