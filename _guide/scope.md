# scope

## scope은 개념적으로 3종류로 분류한다.
* object scope 은 객체 1개에 대한 멤버들이 등록된다.
    * world에서는 가장 바깥 공간에 pack 객체가 있다. pack 또한 obj 이므로 전역공간이 별도로 존재하지 않는다.
* local scope 은 메소드 실행 도중에 발생하는 객체들이 등록된다.

## 그러나 구현에서는 영역을 구분하지 않고 frame안의 1개의 chain에 몽땅 넣는다.
* 따라서 frame에 들어가는 scope의 순서가 중요하다.
* pack 넣고, filescope 넣고, obj넣고, localscopes 넣는다.

## 모든 메소드는 실행하기 전에 넘겨받은 thisobj 로 scope을 갱신하려고 한다.

## 객체는 자신의 object scope을 교체하고 localscope을 비운다.

## interpret 과정은 origin 객체의 generation 과 bind&verify 가 별도의 phase로 구성되어 있다. 
* 따라서 객체의 메소드를 정의할때 안에 구현에서 아직 나오지 않은 다른 origin객체나 메소드를 사용하더라도 문제가 없다.
* 메소드의 localscope은 런타임에 생성되니 제외한다.

## this
* objscope에 접근하는 키워드다.
* 기본적으로 scope에 들어가 있다. this는 이름 충돌시에 사용한다.

## scope와 이름충돌
* 개념적으로 본다면 동일한 레벨의 indentation 내에 같은 심볼이 있으면 컴파일 에러로 판단한다.
* 이를 구현하는 방법은 frame에 담긴 element가 가진 name과 args 가 중복되면 에러로 판단하는 것이다.
    * 이 검사는 verify 단계에서만 실시한다.

```namu
def sample
    foo(n int) void
        foo := 5 // ok
        aka foo -> boo // ok
        aka foo -> koo // ok
        aka foo -> foo // err. 'foo' is on same scope, local scope, already.
            with boo
            n := it++ // err. n is on local scope. duplicated.
            $n := it // err. static n var is on local scope too.
            aka $b := it -> n // err. 'n' is on local scope already.
```

## 하나의 scope에 복수의 subs()가 할당되어야 하는 경우에는 ndeepChain을 넣는다.
* frame은 1개의 chain만 갖는다.
* 이름 충돌 rule에 의해서 frame(== chain)의 각 container가 중복체크를 하는 단위가 된다.
* 각 container가 indentation level을 표현하는 것이며  안에만 동일한 name + args 가 없으면 중복을 피하게 된다.
* 이 frame에 scope을 넣을때 scope에 여러 container를 한 묶음으로 할당해야 하는 경우가 생긴다.
    * e.g. 상속을 하지 않는 객체의 subs()는 2개의 container가 chain으로 묶여있을 것이다.
    *      그러나 이 2개가 frame에 들어갈때는 한 묶음으로 들어가야 한다.
    *      이경우 ndeepChain(subs()) 로 묶어서 ndeepChain 한개만 frame에 add한다.
    * e.g. A객체가 B로부터 상속한 경우, A와 B는 개념적으로 같은 이름을 가질 수 있다.
    *      따라서 frame에 들어갈때는 각 container가 shallow cpy 되서 들어간다.

## func는 이름만 같을 뿐 아니라 인자리스트까지도 같아야 같은 충돌로 간주한다.
* 반환형은 제외한다.

## with

```namu
<indent>
    with <identifier> (, <identifier>)*

    [<expr>]*
<dedent>
```
* 식별자가 있는 경우 블록문을 실행하는 동안 식별자의 scope을 현재 scope보다 상위로 chain에 push 한다.
* with가 사용된 scope이 어디냐에 따라서 구현이 살짝 달라진다.

## with는 항상 사용된 indent level의 최 상단에 놓여져야 한다.

## with가 어디에 사용되었느냐에 따라 구현이 다르다.
* filescope에서 사용된 경우 filescope에 추가된다.
    * filescope에 with의 내용을 추가한 후 pack을 가리키도록 한다.
* with가 메소드 안에 사용된 경우는 withBlockExpr 이라는 별도의 객체로 정의한다.
    * 해당 객체는 새로운 array를 생성해 localscope에 add하기 직전에 with를 실행해서 가져온 객체의 subs()도 하나의 array로 묶는다.

## scope는 chain을 reversed 하게 구성한다.
* reversed 하게 chain을 엮으면 stack처럼 사용할 수 있기 때문이다.
    * reversed라는 것은 chain의 head가 항상 최근에 넣은 container를 가리키게 한다는 것이다.
* scope는 STACK (FILO) 메카니즘을 가지므로 scope의 추가와 삭제가 다음과 같이 된다.

```namu
// 추가:
newChain.link(scope.head)
scope.head.bind(newChain)

// 삭제:
scope.head.bind(scope.head.next)
```

* 게다가 head부터 탐색해가므로 localscope부터 순차탐색하게 되는데, 이것은 언어spec에서 가장 indentlv
  이 깊은 symbol이 먼저 택해진다는 규칙과 잘 맞는다.
 
## 같은 pack 내에서의 객체들은 서로 with를 하지 않아도 된다.
* 같은 pack scope에 있으니까.

## with는 와일드 카드를 지원하지 않는다.

## with는 콤마를 지원한다.

## with가 import를 대신한다.
```namu
// mymodule:
def person()
    foo() void
        print('hello world!')

main() void


// app.namu:
mymodule.person.foo() // ok

with mymodule
person.foo() // ok
```

## 블록문은 indentation으로 표현한다.
```namu
b := foo()
    a := koo()
    a.doSomething() // 'a' destoryed
print(b)
```

## 블록문에 with를 한경우 해당 블록문에만 with가 적용된다.
* with는 현재 최상단 scope에만 영향을 주기 때문이다.

## with 는 statement 다.
```namu
if (b := foo()) > 2
    with b, c := koo()
    // (with b) + 5 -> err
    // with b + 5 -> err
```

## 메소드 안에서 임시 생성하는 모든 것들은 local scope이다.
* 메소드의 parameter list
* 반환값
* 메소드 실행중 생성되는 local 변수

## node 기본적으로 sub를 접근할 수 있는 다음 API를 제공한다.
* 식별자명, 타입과 인자리스트를 모두 받는 것이 원본 API가 된다.
```namu
// 정상이면 ret.val로 접근, 2개 이상 hit하면 ret.err에 hit한 sub가 모두 들어있다.
get<T=node>(name str, types Type[]) ret<ref>
get<T=node>(name str, type Type...) ret<ref>
gets(name str) ret<ref[]>
```

## sub를 찾을때 null일 인자를 넣는것과, 빈 인자리스트를 넣는 것은 다르다.
```namu
get("anyName") // anyName인 객체를 찾는 것이다.
get("anyName", {}) // anyName() 를 찾는 것이다.
```

## 블록문 내의 변수의 scope는 항상 indent depth에 의해 판단된다.
* 다른 언어에 비해 expression 기반인 namu 는 변수의 scope을 생소한 케이스가 몇개 있다.

```namu
if val := foo()
    val++
print(val)
```

* val은 if 문 내에서 정의되었지만 indent level은 print(val) 구문과 동일하다.
* 따라서 if 블록문 밖에서도 접근이 가능하다.

```namu
for n in arr
    print(n)
print("finally n was $n")
```

* 마찬가지로 foo 문 내에서 정의된 n은 for 문 바깥에서도 접근이 가능하다.
* 따라서 다음과 같은 코드는 에러다.

```namu
for n in arr
    print(n)

//for n in arr2 // err: n은 이미 정의한 적이 있다.
//    print(n)

for n2 in arr2 // ok
    print(n)
```
