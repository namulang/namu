# property

## 프로퍼티는 setter와 getter를 함축하는 객체다.

* 외부에서 이 객체에 접근하고, 새로운 참조값을 할당할때에 불려지는 setter와 getter에 대한 이벤트를 처리 할 수 있는 객체다.
* worldlang 문법적으로는 모든 객체는 정의시 setter, getter를 함축한다. 그렇게 보여진다.
* setter/getter에는 그것이 속한 객체의 object scope가 없는 상태에서 메소드가 실행된다.
* setter/getter는 유일하게 static 메소드 처럼 동작하는 메소드다.

```go
name1 := ""

def objA
    name := ""
    name1 := "hello"
        @get=>
        @set
    
    @get: ret name as objA // err. getter에서는 getter가 속한 객체(objA)의 object scope가 없다.
    @set(new): ret name1 as objA // ok
```

## get() / set()을 갑자기 추가해도 다른 코드는 전혀 변경이 없어야 한다.

```go
def app
    name := "hello"

    main() void
        sys.out(name)
```

* 위 코드에서 name에 @get, @set을 둬서 프로퍼티로 만들어도 main() 코드 변경이 없어야 한다.

## 프로퍼티를 정의하려면 객체 정의(복제 혹은 origin)후 블록문에 넣으면 된다.

* 일반 메소드를 복제 객체 정의의 블록문에 넣을 수는 없다. 오직 프로퍼티 관련만 가능하다.

## 프로퍼티라고 해도, 객체는 값을 가지고 있다.

* 단순히 proxy로써 동작하는 게 아니다. 참조값을 가지는 동작위에 overriding을 한거라고 보면 된다.

## get, set은 특수 메소드다.

* 특수메소드는 앞에 @ 를 붙이며, 별도의 명시가 없어도 고유의 인자리스트를 생략하도록 한다.

## getter/setter를 생략할 경우, 기존 값이 그대로 나간다.

* 막고 싶다면 앞에 _ 를 붙인다.

```go
def objA
    name1 str
        @get=>
            sys.term.out("good!")
        @set: sys.term.out("you can call but never change")

    name2 := "can't call set()"
        @get
        _@set

objA.name1 = "wow" // --> try 'objA.name1 = "wow"' but not worked.
objA.name1 // good!
objA.name2 // never change
objA.name2 = objA.name1 // err.
```

## 임의 타입 T에 대해 setter/getter가 존재하면 T에 대한 ref는 setter/getter를 호출한다.

* T는 getter, setter가 있건 말건 절대로 변경하지 않는다.
* T를 참조할 Ref는 T가 setter/getter가 있을 경우 그 메소드를 찾아내서 사전에 호출하는 방식이다.

## 프로퍼티가 아닌 객체가 프로퍼티를 추가하더라도 하위호환성은 지켜진다.

* 일반 복제 객체가 이후 프로퍼티로써 변경된다 하더라도 다른 코드는 일절 변경이 없어야 한다.

## 프로퍼티는 origin객체를 대상으로 할 수도, 복제 객체를 대상으로 할 수도 있다.

```go
def person
    _name := "wow"

    name1 str
        @get: person.name // origin객체.name
        @set: name = new // 복제객체.name
``` 

## 프로퍼티 오버라이딩

* 프로퍼티 또한 오버라이딩 할 수 있다.
* 프로퍼티가 소유한 메모리는 고정되고 @get, @set 메소드만 오버라이딩 된다.
* 공변을 허용하므로 타입이 일치하지 않아도 된다. 변수명이 일치해야 한다.
