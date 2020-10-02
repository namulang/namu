# scope

## scope은 3종류로 분류한다.
* global scope 은 전역변수와 모든 origin객체가 놓여진다.
* object scope 은 객체 1개에 대한 멤버들이 등록된다.
* local scope 은 메소드 실행 도중에 발생하는 객체들이 등록된다.

## 모든 객체는, 자신이 메소드를 처리할때 scope을 갱신하려고 한다.

## 일반 객체는 자신이 가진 member로 object scope을 교체하고 localscope을 비운다.

## 메소드는 local scope을 추가한다.

## 메소드는 실행 도중에 변수의 정의가 나오면 local scope에 추가한다.

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
