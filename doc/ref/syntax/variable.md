# variable

| 타입명 | 종류   | 표현 범위 | 크기  | 기본값 | cast (asc order) | literal const |
| ------ | ------ | --------- | ----- | ------ | ---------------- | ------------- |
| int    | 정수   | signed    | CPU   | 0      | 4                | 1234          |
| flt    | 실수   | signed    | CPU   | 0.0    | 5                | 1234.0, 1.3   |
| str    | 문자열 | .         | .     | ""     | 6                | "1234"        |
| bool   | 논리식 | .         | .     | false  | 2                | true, false   |
| err    | 결과   | .         | .     | N/A    | 1                |               |

```cpp
import console

def app // 객체 app
	age := 0 // app의 변수, age.
    main   (   )     void // whitespace 무시
        age:=0 // 지역변수 age와 member변수와 이름 중복 허용
        ++age++ *= 2 // age == 4
        // 연산자 우선순위 존재함.
        // 다음 연산자 지원 : += -= /= %= <= < > >= = == != --

        pow := age^2 // => age*age == 16
        console.out("hello world!"[-9999999~4] + "boy aged " + pow) // str은 UTF-16 인코딩
        // Sequence: x~y 로 표현하며 [x, y)의 범위를 가짐.
        // str[-9999]는 0으로 예외처리.
        // str[99999999]는 str의 length-1로 예외처리.
        // int + str시, implicit 캐스팅 우선순위(3vs5)에 따라, int->str casting


// 결과: hellboy aged 16
```

## int, flt은 뒤에 8의 배수로 byte를 64까지 붙일 수 있다.

* int8, int64
* flt8, flt32

## 서로 다른 scope에서의 이름 중복을 허용한다.
```java
def A
    say() void: ret
    foo() void
        say() void
        say() // say()가 stackframe에 2개 존재한다. 
```
* 가까운 scope을 우선하는 것이다. 여기서는 메소드 안에 정의된 say()를 우선하는 것으로, 해당 클래스를 작성중일 개발자가 그러한 클래스나 메소드가 있다는걸 가장 잘 알고있다. 그러니, 대부분의 의도또한 local scope에 있는걸 사용하려는 것일 것이다.

## 전역변수는 .<변수명> 으로 접근한다.
* moduleScopeAccessExpr로 번역될 것이며 이 Expr은 stackframe에서 가장 밑에 있는 frame을 찾아서 탐색한다.

## 여러개의 변수를 동시에 정의 가능하다.
* 튜플을 이용하면 가능하다.
