# variable

기본 제공 타입은 기본자료형(primitive data type)과 선정의 타입 (pretype) 2종류로 나뉘어집니다.

기본 자료형은 총 7 종류이며, pretype은 밑에서 얘기하겠습니다.

| 타입명 | 종류         | 표현 범위 | 크기  | 기본값 | casting 우선순위(낮은쪽 -> 높은쪽) |
| ------ | ------------ | --------- | ----- | ------ | ---------------------------------- |
| int    | 정수         | signed    | 32bit | 0      | 4                                  |
| float  | 실수         | signed    | 32bit | 0.0    | 5                                  |
| str    | 문자열       | .         | .     | ""     | 6                                  |
| bool   | true / false | .         | .     | false  | 2                                  |
| char   | 정수         | unsigned  | 16bit | 0      | 3                                  |
| byte   | 정수         | signed    | 8bit  | 0      | 3                                  |
| res    | 결과         | .         | .     | rok    | 1                                  |

```cpp
import console

def app // 객체 app
	age = 0 // app의 변수, age.
    void   main   (   )  // whitespace 무시
        age=0 // 지역변수 age와 member변수와 이름 중복 허용
        ++age++ *= 2 // age == 4
        // 연산자 우선순위 존재함.
        // 다음 연산자 지원 : += -= /= %= <= < > >= = == != --

        pow = age^2 // => age*age == 16
        console.out("hello world!"[-9999999~4] + "boy aged " + pow) // str은 UTF-16 인코딩
        // Sequence: x~y 로 표현하며 [x, y)의 범위를 가짐.
        // str[-9999]는 0으로 예외처리.
        // str[99999999]는 str의 length-1로 예외처리.
        // int + str시, implicit 캐스팅 우선순위(3vs5)에 따라, int->str casting


// 결과: hellboy aged 16
```


## 이름 중복을 허용한다.
```java
def A
	def B := A
		void say()
		void foo()
			say() // A.B.say()와 A.say()가 충돌하고 있다.

	void say()
```
local scope을 우선하는 것이다. local scope이란 즉, 해당 메소드가 정의된 클래스를 우선하는 것으로, 해당 클래스를 작성중일 개발자가 그러한 클래스나 메소드가 있다는걸 가장 잘 알고있다. 그러니, 대부분의 의도또한 local scope에 있는걸 사용하려는 것일 것이다.

## 전역변수는 .<변수명> 으로 접근한다.

## 여러개의 변수를 동시에 정의 가능하다.

* 튜플을 이용하면 가능하다.
