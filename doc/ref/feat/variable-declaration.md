# variable declaration
* 약식과 정식이 존재한다.

## 정식
```go
n int := 55
obj myObj? := myDerivedObj()
```

## 약식
```go
n := 55
obj := myDerivedObj()
```

## 함수 파라메터의 약식
* 일반 약식과 다르게 함수 파라메터는 좀 더 기호가 추가되어야 한다.
```go
foo(/*약식*/n int, obj myObj?, n2 int := /*기본값*/55)
```
* 함수 약식 선언은 함수 signature 밖에서는 절대로 사용할 수 없다.
    * 띄어쓰기만을 기준으로 약식 문법이 이루어져 있기 때문에 밖에서 사용하는 순간 다른 문법과 많은 충돌을 일으키기 때문이다.
* 정식은 함수 파라메터에서도 사용이 가능하다.

## null ref declaration

* mutable 타입에 한하여 null인 reference를 쉽게 정의할 수 있다.
```go
def myObj
    ...
obj1 := myObj // myObj 유니크 오브젝트를 ref에 넣었다.
obj2 := null as myObj // obj2는 myObj? 로 유추되며 null이 할당된다.
obj3 myObj? := null // 위와 동일하다.
obj4 := myObj? // 위와 동일하다.

int1 := int // Unique오브젝트가 존재하지 않으며 immutable인 경우 int(0)의 객체가 복제되어 할당된다.
int2 := int? // error. immutable은 ref를 만들 수 없다.


arr := [] // arr은빈node[] 객체가 할당된다.
arr1 := null as myObj[] // arr1은 myObj[]의 refer이며 null이 할당된다.
arr2 myObj[]? := null // 위와 같다.
arr3 := myObj[]? // 위와 같다.
arr4 := [myObj?] // myObj의 null을 1개 가지고 있는 myObj[] 배열이 arr4에 할당된다.
arr4.len == 1 & !arr4[0] // true
```
