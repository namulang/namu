# container

## array, map, tuple 3종류를 기본 제공한다. 

## 자바처럼 arraylist의 버금가는 활용도를 제공한다.

* 자바는 기본 배열은 어느순간 잘 안쓰게 되고 확장성 있는 arraylist를 사용을 자주한다.
* 효율성을 버리고, 타입을 일원화하는데 초점을 맞춘다.

## container는 생성자 문법이 통용되지 않는다.

* "[", "]" 를 통해서 별도로 생성자처럼 사용한다.

## container는 unique object가 존재하지 않는다.

* unique object에 접근하는 것처럼 문법을 작성하면 실제로는 텅빈 container를 만드는 것이다. 
* container는 생성자가 없기 때문이다.

## array

### 문법

    [((value) (, value)*)*]

* type deduction으로 값의 타입을 보고 어떠한 배열인지를 유추한다.
* 텅빈 배열을 만들 수 있다.

```go
arr := str[] // arr is refer to str array.
arr2 := str[]() // empty arry to str.
arr = arr2
arr.len // 0


arr := ["wow", "hello", 1] // obj[]
foo(strs str[]) void
    for e in strs
        sys.out(e)
foo(arr) // err
foo(arr as str[]) // casting err

arr2 := str[]
for e in arr
    arr2.add(e as str)
foo(arr2)
```

### 배열의 index는 0을 제외한 양수여야 한다. 

### add, del로 배열은 size가 고정되어 있지 않다.

### 접근시 []로 접근한다.

* arr[5]
* 접근시 O(1)에 해당한다.

### 비어있는 원소가 없다.

* arr[2], arr[4]은 되지만 arr[3] 을 하면 exception 이 발생하거나 하진 않는다.
* 물론 원소로써 null이 들어가 있을 수는 있다.

### 원소들은 모두 같은 타입이다.

### 배열을 범위를 벗어나면 runtime 에러가 발생하고 프로그램이 종료한다.



## typelist

* typelist은 여러개의 서로 다른 타입들이 container로 존재하는 것이다.

### 문법

    ((value) (, (value))*)*

### 사실 사용자는 typelist을 마음껏 다룰 수 없다.

* typelist을 정의하는 부분은 정해져 있다.
    * 다중 할당 문법
    * 메소드의 인자리스트
    * 어떠한 문법의 일부
* 사실 , 로 여러개의 값 혹은 타입을 넘기거나 다루는 모든 것을 편의상 타입리스트이라고 하는 것 뿐이다.

### typelist는 단독으로 있을 수 없다.

* 계속 말하지만 정해진 위치에서만 사용이 가능하다.

```go
b, c := 1, 5 // 단독으로 있을 수 있다면, 이것은 마치 3개짜리 list로 보이기 시작한다.
```

### 멀티 반환값을 가진 메소드 정의하기

```go
def app
    foo() int, float, char on err =>

    main() void
        a, b, c on res := foo()
```




## sequence

* array의 일부 기능만 가지고 있는 제한된 컨테이너다.

### 문법

    (include number) .. (include number)

* 예제
```go
arr := [1, 2, 3]
for num in 1..arr.len
    sys.out("$num,")
// 1,2,3,
```

### 원소마다 메모리를 점유하지 않는다.

### operator [, ]를 지원하지 못한다.

* 대신 get(n)을 지원한다.
* operator[]를 지원하지 못하는 이유는 operator[]는 반환형E가 immutable이어도 mutable처럼 만들어주는 특이한 메소드이기 때문이다.
```go
ar := [1, 2]
ar[0] = 3 // int는 immutable이지만 3으로 변경되어야 한다.
```

### seq 클래스가 이 문법을 구현한다.

### seq는 당연히 제네릭이다.

### seq는 그외에도 step을 받는 생성자들이 있다.

* 직접 seq 객체를 생성하면 이 값을 채울 수 있다.
* seq도 반환할 수 있게 된다.

```go
foo(s int, e int, s step) seq<int> // int만 step 이 있다.
    return seq<str>(s, e, s)

for n in foo(5, 1, -2)
    .......
```

### seq<str>은 생성자 인자에 step이 없다.

### iterator를 내보낼 수 있어야 한다.

### has(elem E) bool를 지원한다.

### step이 얼마인지, start, end는 얼마인지 외부에서 seq객체로부터 알 수 있어야 한다.

### a..b에서 a가 더 작은 경우 reverse로 동작한다.

* step은 항상 1 혹은 -1이다.

### a..b 문법은 seq의 인자 2개짜리 생성자를 부르는 syntactic sugar다.
```go
sys.cons.out("$4..2.step")

```

### ".." 문법은 반환형에 사용할 수 없다.

* 반환형에는 값이 아니라 타입이 와야 한다.
* 2..4 로 사용하면 이것은 타입이 아니라 값이다.
* 반환하고 싶다면 seq를 사용하라.



## pair

### 문법

    (value) : (value)

* 키와 값을 갖는 1개의 쌍이다.

### key, val 로 각 member에 접근한다.

arr := "name": 3
arr.key
arr.member



## map

* hash다.

### 문법

    [((pair) (, pair)*)*]

### element가 떨어진 배열 처럼 사용할 수 있다.

### for 문에 넣으면 pair가 나온다.

```go
map := ["banana": 1, "apple":3]

for pair in map
    sys.out("$pair.key:$pair.val")

for v in map.vals
    sys.out("value=$v")

map.keys
```


## container 간 캐스팅은 container가 가진 타입 T에 대해서만 지원해야 한다.

* 원소에 대해서 casting을 해서 변환을 하면 안된다.
* 그것은 캐스팅이 아니라 변환(conversion)에 해당한다.


## 복잡한 컨테이너 문법

```go
def app commonMyApp
    res, res2 => foo(arr int[], cache base[str], key str) int[][str], base[str] on err
        return int[][str](), base[str]() on myErr

    main() void
        if a, b on res := foo(null, null, null)
            return

        age := a["wow"][3]
        baseWas := b["wow"]
```



## chain

* native에서만 사용하는 container다.
* 다른 알고리즘이나 container를 대신 사용해도 무방하다.
* 배열1과 배열2가 있을때 이 둘을 chain해서 배열1의 원소와  배열2의 원소를 모두 가진것처럼 보이는 배열을 만들수 있어야 한다.
* List건, vector건 모든 컨테이너에 적용되야 한다.


## container는 known worldlang class 이다.
* 순수 c++ 로 작성된 것은 native영역에만 존재하거나 극히 일부분의 managed 영역 객체에 한한다.
* managed 영역에 실재하게 되는 인스턴스가 순수 c++로 작성되는 것을 최대한 피한다.
* managed 영역에 존재하게 하는 가장 확실한 방법은 world언어로 작성하여 pack로 import 시키는 방법이다.
* 이 방법에서 벗어나서 managed 영역에 존재한다는 것은 예외적인 상황을 의미하므로 이러한 상황을 피하는 것이다.
* container 또한 별도의 world언어로 작성된 pack로써 import되어 시스템에 들어간다.
* 그러나 interpreter는 특정 문법이 동작하려면 container의 존재를 알 수 있어야 하며, node가 container 인지 아닌지 등을 알 수 있어야 한다.
* 그러므로 predefined library로써 프로그램 파싱전에 반드시 import 된다는 걸 언어 스펙으로써 보장한다.
* unique한 string을 주어졌을때 이걸로부터 특정 클래스의 TMeta를 접근할 수 있는 방법이 제공된다.
    * 이 방법은 어디서건 어느때에건 호출 할 수 있어야 한다.
    * interpreter는 이걸 사용해서 container의 meta클래스를 얻어올 수 있다.
    * interpreter는 이걸 사용해서 container의 객체를 생성하거나 상속관계를 verify 할 수 있게 된다.
* 이 string은 alltime unique해야 하며, 로케일, 지역, 언어, 재부팅, 시간변경, 단말 변경에 관계없이 동일한 unique 한 값을 정의할 수 있어야 한다.
