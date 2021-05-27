# scope

## scope은 3종류로 분류한다.
* object scope 은 객체 1개에 대한 멤버들이 등록된다.
    * world에서는 가장 바깥 공간에 pack 객체가 있다. pack 또한 obj 이므로 전역공간이 별도로 존재하지 않는다.
* local scope 은 메소드 실행 도중에 발생하는 객체들이 등록된다.

## 모든 메소드는 실행하기 전에 넘겨받은 thisobj 로 scope을 갱신하려고 한다.

## 객체는 자신의 object scope을 교체하고 localscope을 비운다.

## interpret 과정은 origin 객체의 generation 과 bind&verify 가 별도의 phase로 구성되어 있다. 
* 따라서 객체의 메소드를 정의할때 안에 구현에서 아직 나오지 않은 다른 origin객체나 메소드를 사용하더라도 문제가 없다.
* 메소드의 localscope은 런타임에 생성되니 제외한다.

## this
* objscope에 접근하는 키워드다.
* 기본적으로 scope에 들어가 있다. this는 이름 충돌시에 사용한다.

## scope와 이름충돌
* 동일한 scope에 내에 같은 심볼이 있으면 컴파일 에러로 판단한다.
    * 런타임에는 verify 하지 않는다.

```wrd
def sample
    foo(n int) void
        foo := 5 // ok
        foo aka boo // ok
        foo aka koo // ok
        foo aka foo // err. 'foo' is on same scope, local scope, already.
        with boo
            n := it++ // err. n is on local scope. duplicated.
            $n := it // err. static n var is on local scope too.
            ($b := it) aka n // err. 'n' is on local scope already.
```
* func는 이름만 같을 뿐 아니라 인자리스트까지도 같아야 같은 충돌로 간주한다.
    * 반환형은 제외한다.

## with

```wrd
with <identifier> (, <identifier>)*
```
* 식별자가 있는 경우 블록문을 실행하는 동안 식별자의 scope을 현재 scope보다 상위로 chain에 push 한다.
* with가 사용된 scope이 어디냐에 따라서 구현이 살짝 달라진다.
* with는 항상 사용된 indent level의 최 상단에 놓여져야 한다.
* filescope에서 사용된 경우 filescope에 추가된다.
* 메소드 안에서 사용된 경우, 현재 localscope에 추가된다.

## with는 현재 scope에 id.subs()를 add한다.
* remove를 따로 하지 않는다.

## 같은 pack 내에서의 객체들은 서로 with를 하지 않아도 된다.
* 같은 pack scope에 있으니까.

## with는 와일드 카드를 지원하지 않는다.

## with는 콤마를 지원한다.

## with가 import를 대신한다.
```wrd
// mymodule:
def person()
    foo() void
        print('hello world!')

main() void


// app.wrd:
mymodule.person.foo() // ok

with mymodule
person.foo() // ok
```

## 블록문은 indentation으로 표현한다.
```wrd
b := foo()
    a := koo()
    a.doSomething() // 'a' destoryed
print(b)
```

## 블록문에 with를 한경우 해당 블록문에만 with가 적용된다.
* with는 현재 최상단 scope에만 영향을 주기 때문이다.

## with 는 statement 다.
```wrd
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
```wrd
// 정상이면 ret.val로 접근, 2개 이상 hit하면 ret.err에 hit한 sub가 모두 들어있다.
get<T=node>(name str, types Type[]) ret<ref>
get<T=node>(name str, type Type...) ret<ref>
gets(name str) ret<ref[]>
```

## sub를 찾을때 null일 인자를 넣는것과, 빈 인자리스트를 넣는 것은 다르다.
```wrd
get("anyName") // anyName인 객체를 찾는 것이다.
get("anyName", {}) // anyName() 를 찾는 것이다.
```

## 블록문 내의 변수의 scope는 항상 indent depth에 의해 판단된다.
* 다른 언어에 비해 expression 기반인 wrd 는 변수의 scope을 생소한 케이스가 몇개 있다.

```wrd
if val := foo()
    val++
print(val)
```

* val은 if 문 내에서 정의되었지만 indent level은 print(val) 구문과 동일하다.
* 따라서 if 블록문 밖에서도 접근이 가능하다.

```wrd
for n in arr
    print(n)
print("finally n was $n")
```

* 마찬가지로 foo 문 내에서 정의된 n은 for 문 바깥에서도 접근이 가능하다.
* 따라서 다음과 같은 코드는 에러다.

```wrd
for n in arr
    print(n)

for n in arr2 // err: n은 이미 정의한 적이 있다.
    print(n)

for n2 in arr2 // ok
    print(n)
```
