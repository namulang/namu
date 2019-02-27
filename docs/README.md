# worldlang 개요 & 설문

## 서론

먼저 수고를 들여 이 문서를 열람해 주신것에 감사의 말씀 올립니다. 

저는 변두리에서 *world*라는 프로그래밍 언어를 만들고 있는데, 이에 대한 피드팩을 받고 싶어서 이 문서를 만들었습니다. 



## 진행 순서

무엇보다 제가 시간을 많이 가져가면 안될것 같네요. 간단한 아이디어 소개와 문법들을 15분에 소개하고 있으며, 이에 대한 설문이 약 3분 진행됩니다. 모든 설문은 무기명으로 진행되며 답에 시간이 오래걸리는 주관식은 최대한 배제하였습니다.



그럼 먼저 이 언어의 특징부터 소개하고나서, 문법을 알려드릴께요.



## 철학

### 빠른 개발이 되려면 더 빨리 실패해야 한다.

##### Context based REPL

##### 항상 디버깅 상태에서 개발



### 인터프리터도 한명의 개발자.

##### 인터프리터는 프로그램의 구조를 온전히 런타임으로 이해한다.

##### 인터프리터가 개발에 참여한다.



### 텍스트를 입력하는 것만이 코딩은 아니다

##### UI를 통한 코딩

##### doc 문서 자동 생성



## syntax

### before start

### 특징

##### 간단한게 최고다.

###### 어려운 개념은 감춘다

당연히, 포인터,

###### 코드라인 줄이기.

offside-rule

###### 등장요소를 재사용하자.



##### 강한 피드백

###### Validation.

(= Typescript, Java, C#)

###### Strong typed.



##### 모든것은 객체다.



##### 예외를 혐오하자

###### 일관성을 갖자

이곳에서 되면 여기서도 이렇게 하면 될까? 싶으면 되야 한다.



### spec

##### 항상 시작은 Hello world 로부터.

```cpp
import Console // import로 모듈을 가져옴

/*모든 프로그램은 진입점을 위한 app을 정의 필요*/
class app
    void main() //int main(), void main(str[] args), int #main(str[] args)도 ok.
        Console.out("hello world\n") // python처럼 off-side rule (= indentation으로 블록문)

// 결과: hello world
```



##### 변수정의와 기본 연산자

기본 제공 타입은 기본자료형(primitive data type)과 선정의 타입 (pretype) 2종류로 나뉘어집니다.

기본 자료형은 총 6 종류이며, pretype은 밑에서 얘기하겠습니다.

| 타입명 | 종류         | 표현 범위 | 크기  | 기본값 | casting 우선순위(낮은쪽 -> 높은쪽) |
| ------ | ------------ | --------- | ----- | ------ | ---------------------------------- |
| int    | 정수         | signed    | 32bit | 0      | 3                                  |
| float  | 실수         | signed    | 32bit | 0.0    | 4                                  |
| str    | 문자열       | .         | .     | ""     | 5                                  |
| bool   | true / false | .         | .     | false  | 1                                  |
| char   | 정수         | unsigned  | 8bit  | 0      | 2                                  |
| byte   | 정수         | signed    | 8bit  | 0      | 2                                  |

```cpp
class app    
    void   main(   ) // whitespace 무시
        int age=0 // 지역변수 age와 member변수와 이름 중복 허용        
        ++age++ *= 2 // age == 4
    	// 연산자 우선순위 존재함.
    	// 다음 연산자 지원 : += -= /= %= <= < > >= = == != --

        int pow = age^2 // => age*age == 16
        Console.out("hello world!"[0:4] + "boy aged " + pow) // ':'은 범위 연산자.
    	// 범위 연산자: x:y 로 표현하며 [x, y)의 범위를 가짐.
        // int + str시, implicit 캐스팅 우선순위(3vs5)에 따라, int->str casting

// 결과: hellboy aged 16
```



##### 키워드

```cpp
class app
    void main()
        int age = 21
        //    keyword는 메소드와 달리 사용시 () 를 쓰지 않는다.
        int sum = 0
        if age > 20
			age > 20 & age < 20? // ? == if
				Console.out("can't reach here")
            
            int sum = 0 // 허용된 중복 정의
            for int n in 1:5 // 1부터 5까지
                sum += n
                
            Console.out("sum=" + sum)
        else if age == 20
            sum = 0
        if age > 21 | sum // | 는 or연산. sum이 0이 아니면 true로 판단
        	Console.out("sum=" + sum)
/* 결과:
sum=15
sum=15
*/
```



##### 접근자와 메소드



##### 객체와 라이프 사이클



##### 상수와 캐스팅



##### mutable



##### node



##### Pretype: Containers



##### Pretype: void & null



##### 인터페이스 계승



##### 인터페이스 확장



##### 메타



##### 클로저



##### res와 익셉션



##### statement 는 expression



##### Blockstmt 는 클로저



##### try-catch는 클로저로 동작한다



## 설문

이쪽에서 짧게 진행해주시면 됩니다.



## 끝

하고싶은 말이 더 많이 있지만 worldlang에 대한 주요 내용에 대한 소개는 여기까지만 해야할 것 같네요.

이 프로젝트에 관심있으시면 github(url) 한번 둘러보세요.



시간 내주셔서 다시한번 감사드립니다.

