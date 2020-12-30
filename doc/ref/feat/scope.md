# scope

## scope은 3종류로 분류한다.
* global scope 은 전역변수와 모든 origin객체가 놓여진다.
* object scope 은 객체 1개에 대한 멤버들이 등록된다.
* local scope 은 메소드 실행 도중에 발생하는 객체들이 등록된다.

## 모든 객체는, 자신이 메소드를 처리할때 scope을 갱신하려고 한다.

## 일반 객체는 자신이 가진 member로 object scope을 교체하고 localscope을 비운다.

## 메소드는 local scope을 추가한다.

## 메소드는 실행 도중에 변수의 정의가 나오면 local scope에 추가한다.

## scope는 외부에서 제네릭객체에 접근한다는 사실을 판별해야 한다.

* 제네릭 객체에 접근하려고 하고 있으며, 그 generic 객체가 아직 없다면 새로 unique객체를 만들어야 하기 때문에.
* 혹은 generic 객체에 접근할때의 이벤트를 외부에서 cb을 받을 수있게 하거나.
* generic의 unique객체를 만들때에는 일단 unique객체를 scope에 낑겨넣고 verfiication을 돌린다.
    * 다시 scope에 질의해서 무한 루프를 도는 걸 막아야 하기 때문이다.
    * verification이 실패시 넣었던 객체를 다시 지운다.

## 일반 객체는 정의를 scan 하는 과정과 verify 하는 과정 2PASS를 돌린다.

* 따라서 객체의 메소드를 정의할때 안에 구현에서 아직 나오지 않은 다른 메소드를 사용하더라도 문제가 없다.

## 메시지는 메시지를 처리하는 주체를 소유한 객체에게 전달된다.

```cpp
def a
    void print()
    void foo()
        print()
```
* 여기서 print() 는 this.print() 와 같은 것이다. print()를 소유한 객체는 foo 메소드가 아니라
  a 객체다.
* a 객체는 일반 객체이므로 자신이 가진 member인 print와 foo를 object scope에 등록한 후 local scope을 비운다.

## 위의 알고리즘을 따르면, 중첩 메소드도 해결된다.
```cpp
def a

    void foo()
        a := 35

        void print()
            a++
            b++ // err

        b := 5
        print()
```

* print()를 소유한 객체는 foo 메소드다. 따라서 foo 메소드는 localscope을 하나 추가한다.
  print()안쪽에서 a 에 대해 접근이 가능하다.
* 참고로, b는 중첩메소드가 정의되는 시점에는 아직 정의되지 않았다. 따라서 접근이 안된다.



## this

* global scope에 접근하는 키워드다.
* global scope는 기본적으로 scope에 들어가 있다. this는 이름 충돌시에 사용한다.

## me

* 실행중인 메소드다.
* RTTI 관련 메소드가 기본적으로 제공된다.
    * me.name
    * me.super(....)

* 메소드를 생성자처럼 사용하면 메소드가 생성되는 대신에 메소드호출이 된다.


## with

* with (식별자)* 블록문
* 블록문을 실행한다.
* 식별자가 있는 경우 블록문을 실행하는 동안 식별자의 object scope을 현재 this object scope보다 상위로 올린다.
    * local scope보다는 상위가 아니다.
* with 안에 with가 있을 수 있다.

## scope와 이름충돌
* 동일한 scope에 내에 같은 이름이 있으면 컴파일 에러로 판단한다.
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

## 메소드가 소유한 subnodes와 메소드 안에서 생성하는 모든 것들은 local scope이다.
* 메소드의 parameter list
* 반환값
* 메소드 실행중 생성되는 local 변수
* 메소드의 static variable
* 메소드가 기본 제공하는 Method 클래스의 메소드들
