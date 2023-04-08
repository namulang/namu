# variable declaration
## 문법
* <identifier> <type> (:= expr)*
```go
n int
grade flt32 := 3.5
objs str[]? := ["why", "so", "serius?"]
```

## type deduction을 지원한다.

* <identifier> := expr

```go
n := 4
grade := 3.5
objs := ["why", "so", "serius?"]
```

## null ref declaration

* mutable 타입에 한하여 null인 reference를 쉽게 정의할 수 있다.

```go
def myObj
    ...
obj1 := myObj // myObj 유니크 오브젝트를 ref에 넣었다.
// 다음 4개의 ref는 모두 동일한 코드이다.
obj2 := null as myObj // obj2는 myObj? 로 유추되며 null이 할당된다.
obj3 myObj? := null
obj4 := myObj?
obj5 myObj?

int1 := int // Unique오브젝트가 존재하지 않으며 immutable인 경우 int(0)의 객체가 복제되어 할당된다.
int2 := int? // error. immutable은 ref를 만들 수 없다.

arr := [] // arr은빈node[] 객체가 할당된다.
arr1 := null as myObj[] // arr1은 myObj[]의 refer이며 null이 할당된다.
arr2 myObj[]? := null // 위와 같다.
arr3 := myObj[]? // 위와 같다.
arr4 := [myObj?] // myObj의 null을 1개 가지고 있는 myObj[] 배열이 arr4에 할당된다.
arr4.len == 1 & !arr4[0] // true
```
