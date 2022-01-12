# func 

## Func는 일반 객체와 다른, 확장이 불가능한 builtin 객체다.
* 메소드 또한 객체로써 취급한다. 그러나 일반 객체와는 다음과 같은 항목에서 다르다.
    * 그러나 메소드의 메소드는 고정된 항목들이며 메소드로부터 확장하거나 extend가 불가능하다.
    * 메소드가 제공하는 메소드는 RTTI 관련 항목이다.
    - 메소드는 Object가 아니므로 객체마다의 멤버는 가질 수 없으나 공유멤버는 가질 수 있다.
* 다음은 일반 객체와의 공통점이다.
    * 메소드는 객체이므로 메소드에 대한 참조를 만들 수 있다.
    * 메소드는 블록문을 가지고 있다.
    * 메소드의 정의는 expr 으로 취급한다.

## 모든 메소드는 객체에 속해있다.
* static 클래스는 존재하지 않는다. static 메소드 역시 존재하지 않는다.
* static 변수는 존재한다.
* 메소드가 정의되면 해당 scope에 static member로써 추가된다.
    * 메소드 안에서 메소드가 정의되면 메소드의 static member로써 추가된다.
- Exception 핸들링또한 Nested Func를 통해서 돌아간다.

## 다형성을 기본적으로 제공한다.

## 메소드의 sub nodes는 이름앞에 "_"를 붙이지 않더라도 private 접근제한자를 갖는다.
* 외부에서 호출할 수는 없다.
* 문법상에서 유일하게 사용되는 private다. 

## 클래스 계층
* Func는 Object와 동작이 상이하나 Node의 일종인 것은 맞다.
* Func는 BlockExpr를 1개 소유한다. 

## 특정한 인자타입리스트에 대해서 실행이 가능한지를 판별하는 메소드를 제공한다.
* interpreter는 bind&verify 에서 모호성 오류를 검증하기위해 인자리스트를 처리할 수 있는 곳인가를 반드시 짚고 넘어가야 하기 때문이다.
* 인자를 묵시적 변환을 거쳐서 처리가 가능한지를 반환해야 한다.
* func을 갖는 obj는 소유한 func의 인자리스트 처리가능 여부와 함께, 처리 우선순위를 계산해서 가장 높은 순위 1개를 get()의 반환값으로 넘긴다. 모호성 오류가 발생한 경우에는 2개 이상이 나오게 된다.

## method의 인자 deduction 우선순위
* 묵시적 변환이 일체 없이 타입이 정확히 일치하면 우선순위 0
* 변환이 불가능하면 우선순위 음수
* 묵시적 변환이 한번이라도 사용되었다면 우선순위 1이 된다. 
    * 묵시적 변환이 몇번 발생했는지는 중요하지 않다.

## func에 thisptr도 함께 전달한다.
* 객체는 this를 수신하면 object scope을 this의 것으로 교체한다.

## 메소드ptr는 Ref에서 상속한 Delegator로 사용한다.
* Ref는 type 이라는 별도의 Object로 verify를 한다.

## 각 함수 객체는 FuncType 이라는 type을 1개씩 갖는다.
* 함수는 FuncType 이라는 별도의 클래스로 verify를 한다.
* FuncType은 하나의 Type으로는 불가능하고 인자와 반환형을 통해서 verify 한다.
* 반환형과 인자타입리스트가 동일하더라도 함수가 다르면 다른 FuncType 객체가 나온다.
* native에서 템플릿을 사용하여 함수의 type을 가져올 수 없다. functype은 인스턴스별로 unique 하다.
* FuncType.isSame(type)은 인자리스트와 반환형이 동일하면 true를 반환한다.

## 메소드 정의 문법
* 메소드 메소드명과 인자리스트를 함께 적는다. 인자리스트는 반드시 type declaration이 포함되어있어야 한다.
```go
def person
    sayHello(name str, age int) res
```

## 기본값은 지원하지 않는다.
* deduction이 복잡해서 그렇다. 나중에 지원할 수도 있다.
* 지원하게 된다면 아래와 같은 문법이 가능해진다.
```go
def person
    sayHello(name := "defaultName", age int := 5.5) res
```

## 메소드 식별문법
* 만약 메소드명 만으로도 식별이 가능하다면 인자리스트를 생략할 수 있다.

```go
person.sayHello
```

* 그 이외의 경우에는 인자리스트를 모두 적어줘야 한다.
```go
person.sayHello(a1 str, anyName int)
```

* 뒤에 반환형이 없다는 것으로 메소드의 정의와 구분한다.

### 빈 메소드일 경우는 void를 넣는다.

```go
def person
    sayHello() = null
person.sayHello(void)
```

* void는 이 경우를 제외하고 void는 값으로 넘길 수 없다.

## 특수 메소드

* 앞에 @ prefix를 붙일 경우, 괄호를 붙이지 않아도 메소드로 인식한다.
* @가 붙어도 되는 메소드명은 정해져있다.
    * @ctor, @get, @set, @as

## 비어있는 메소드

* 메소드가 비어있을 경우 기본값을 내보낸 것이다.

## 인터페이스 메소드
* 뒤에 = null을 적은 메소드는 호출이 불가능하다. 인터페이스로 사용된다.
* overriding 혹은 type으로써 사용된다.
* 구현시 함수객체는 정상적으로 생성된다.
* Null이 할당된것과 같다.
* 접근은 가능하다.
* RTTI 메소드도 호출할 수 있다.
* 복제 혹은 메소드 호출은 안된다.

```go
def person
    someCallback() void
        return
    someCallback2() void // 위와 동일하다.
    aInterface() void = null

person.someCallback2()
person.aInterface() // err
person.aInterface.name // ok
```

## 메소드ptr를 정의하는 문법

* 인터페이스 메소드를 정의하는 것으로 메소드 ptr의 타입을 정의 하도록 한다.

```go
def person
    someCallback(p person) int = null
    delayCall(fn someCallback) void
        fn(this)

def app
    _callback(p person) int
        ret sys.csol.print("p.age=$p.age")

    main() void
        person.delayCall(_callback)
```

## 메소드를 ptr에 넘길 경우, 클로져 처럼 동작한다.

* object scope가 캡처되서 FuncRef에 기록된다.

## 멤버함수 ptr 라는건 없다.

* 메소드를 갖는 클래스가 다르더라도 signature만 동일하다면 호출이 가능하다.

```go
aka -> sys.cons

def person
    aka do() void = null -> d
    do(@d)
        d.do()

def boy()
    do() void: cons.out("shopping!")

def girl()
    do() void: cons.out("exercise hardly!")

def app
    main() void
        person.do(boy.do)
        person.do(girl.do)
```

## 식별자 바인딩은 매번 get("identifier-name")을 넣음으로써 매번 검색한다.

* optimization 과정이 끝날 경우, 이 과정은 상수타임에 끝나도록 한다.

## 메소드를 생성자처럼 사용하면 메소드가 생성되는 대신에 메소드호출이 된다.

## 메소드의 구현
* 객체와 달리 메소드는 scope이 항상 동적으로 구성된다.
* func객체가 생성되는 시점에서 pack scope을 깔고 자신의 shared chain을 구성해놓지 않는다.
* S(shared sub chain)과 NS(non shared sub array)가 obj 처럼 존재한다.
* 메소드 내에서 정의된 static 객체, origin 객체, 함수객체가 S chain에 generation 단계에서 추가된다.
* 로컬변수, 인자리스트는 NS에 정의된다.

## 메소드의 실행 알고리즘
* thisobj와 인자리스트가 넘어온다.
* thisobj로 objscope을 교체한다.
    * thisobj는 pack scope까지 이미 가지고 있으므로 stackframe이 ptr를 1개 바꾸기만 하면 된다.
    * stackframe은 이미 있던 scope(= frame)을 stack에 넣고, 새로운 frame을 만들어 넘어온 thisobj의 scope으로 갱신한다.
    * 이렇게 하는 이유는 외부에서도 stackframe의 목록을 접근할 수 있어야 하는 요구사항이 때문이다.
    * 새로 추가된 frame의 chain에 func의 S를 push하고 NS를 deepcpy한 뒤 push한다.
    * 메소드를 실행한다.
    * stackframe을 pop 한다.

## func도 origin 을 가지고 있다.
* func 객체는 시스템내 유일하게 1개가 파서로부터 생성되서 origin객체에 붙어있게 된다.
* func.origin에는 이 origin객체를 가리키게 된다.

## func는 blockExpr가 아니며, blockExpr를 aggregation으로 가질 뿐이다.
* blockExpr의 종류는 일반과 withBlockExpr 2 종류가 있다.

## func과 obj는 같은 부모로 구성할 수 있다.
* 둘 모두 chain, S chain, NS array 3개가 필요하다.

## func을 run() 하는 메소드는 func에만 정의되어 있다.
* native world frx은 node 타입을 기반으로 동작하기때문에, 메소드 호출을 위해서는 캐스팅이 필요하다.

## 중첩메소드는 상위 메소드의 local scope을 공유한다.
* 중첩메소드의 정의 시점 보다 이후에 나오는 outer func의 로컬변수는 참조할 수 없다.
```go
def person
    foo() void
        age := 12
        koo(val int) int
            sum := val + age
            return sum + nextYear // err: nextYear가 없다.
        nextYear := 1
        // koo의 정의가 여기에 있었다면 에러가 발생하지않는다.
        koo(5)
```
* 명백히 말하면 실행시점에서의 바인딩을 체크해야 하나, 그렇게 되면 실행시점마다 바인딩을 체크해야 한다. if 등으로 branch 까지 고려하면 복잡도가 늘어나므로 제한을 두었다.

## 중첩메소드는 outer func의 sub를 모두 접근 가능하다.
* 메소드의 sub는 private로 되어있지만, 중첩메소드는 접근 할 수 있다.

## 중첩메소드의 실행 알고리즘
* 실행시 obj scope을 교체하지 않는다.
    * 따라서 실행시 outer func의 scope이 들어간 상태에서 실행이 된다. outer func의 local변수에 접근이 가능한 것이다.
* 이미 있는 chain에 자신의 S, NS를 각각 얹는다.

## 중첩메소드에서 참조하는 상위 메소드의 local variable은 중첩메소드가 정의되는 코드보다 먼저 등장해야한다.

