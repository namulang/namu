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
```go
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

```go
with <identifier>*
    <expr>+ 
```
* 식별자가 있는 경우 블록문을 실행하는 동안 식별자의 object scope을 현재 this object scope보다 상위로 chain에 push 한다.
    * local scope보다 상위다.
* 그리고 블록문을 실행하기 전에 새로운 localscope을 chain에 push 한다.
* 블록문을 실행한다.
* 실행이 끝나면 pop()을 2번 한다.
* with 안에 with가 있을 수 있다.

## 메소드 안에서 임시 생성하는 모든 것들은 local scope이다.
* 메소드의 parameter list
* 반환값
* 메소드 실행중 생성되는 local 변수

## node 기본적으로 sub를 접근할 수 있는 다음 API를 제공한다.
* 식별자명, 타입과 인자리스트를 모두 받는 것이 원본 API가 된다.
```go
// 정상이면 ret.val로 접근, 2개 이상 hit하면 ret.err에 hit한 sub가 모두 들어있다.
get<T=node>(name str, types Type[]) ret<ref>
get<T=node>(name str, type Type...) ret<ref>
gets(name str) ret<ref[]>
```

## sub를 찾을때 null일 인자를 넣는것과, 빈 인자리스트를 넣는 것은 다르다.
```go
get("anyName") // anyName인 객체를 찾는 것이다.
get("anyName", {}) // anyName() 를 찾는 것이다.
```
