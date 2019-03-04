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
import console // import로 모듈을 가져옴

/*모든 프로그램은 진입점을 위한 app을 정의 필요*/
class app { // 블록문(Block stmt)는 중괄호 사용
    //	블록문시 여는-중괄호는 stmt의 뒤에 넣음
    /*	잘못된 예)
    		class app
    		{   
   	*/

    // 블록문 안의 코드들은 반드시 들여쓰기(indent) 필요함
    int main() { // 진입점
        return console.out("hello world\n")
    }
} 	// Indent가 중요하기 때문에 한줄에 여러개의 }를 붙일 수 없음
	// 잘못된 예) }}

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
import console

class app {
	int age = 0
    void   main   (   ){  // whitespace 무시
        int age=0 // 지역변수 age와 member변수와 이름 중복 허용
        ++age++ *= 2 // age == 4
        // 연산자 우선순위 존재함.
        // 다음 연산자 지원 : += -= /= %= <= < > >= = == != --

        int pow = age^2 // => age*age == 16
        console.out("hello world!"[0~4] + "boy aged " + pow) // ':'은 범위 연산자.
        // 범위 연산자: x:y 로 표현하며 [x, y)의 범위를 가짐.
        // int + str시, implicit 캐스팅 우선순위(3vs5)에 따라, int->str casting
    }
}

// 결과: hellboy aged 16
```



##### 키워드와 논리연산자

```cpp
class app {
    int main() {
        int age = 21
        int sum = 0
        if age > 20 { // 원칙은 블록문시에도 항상 {, }를 사용하나,
            if age > 20 & age < 20 // 함수 내의 블록문은 {, } 생략을 권장.
                Console.out("can't reach here")
            
            int sum = 0 // 허용된 중복 정의
            for int n in 1~5 // ~는 1부터 5까지를 의미함. [1, 5)
                sum += n
                
            Console.out("sum=" + sum) // "sum=10"
        } else if age == 20 // } 뒤에 다음 stmt 가능.
            sum = 0
        if ! (age == 21) | sum // |는 or연산. sum이 0이 아니면 true로 판단
            Console.out("sum=" + sum)
        elif ! sum // == else if
            Console.out("can't reach here")
            return -1 // 함수 종료. 반환

        int bit = 2            
        Console.out(bit || 4) // "6"
        // ||, &&, ~~ 비트 연산자
        return 0
	}
    // import console // 에러.
}

import console // 외부 scope 이면, 어느 위치에든 선언 가능.


/* 결과:
sum=10
sum=10
6
*/
```



##### statement 는 expression

```cpp
class app {
    // 구문statement와 표현식expression:
    // 프로그래밍 언어에서 구문이란 코드의 각 라인을 말하며,
    // 표현식은 특정한 값을 반환할 수 있는 식별자가 조합된 식을 뜻한다.
    //	e.g in c++)	foo(3); 			// 표현식이므로, 동시에 구문이다.
    //				void func(int age); // 구문이다.
    //				class A;			// 구문이다.
    //
    // world는 문법을 간결하게 하기 위해 모든 구문은 표현식으로 정의한다.
    // 이를 위해 2가지 규칙이 있다.
    //	1. 모든 블록문을 갖을 수 있는 키워드는 블록문의 마지막 라인을 밖으로 반환한다.
    //	2. 모든 타입 선언은, 동시에 정의이며, 정의된 식별자는 해당 범위scope내에서 유효하다.
    int foo(int age) {
        5 // #1 규칙. return이 없어도 ok.
    }
    void boo(class declared, bool success, int age) { // class도 int와 같은 타입의 한 종류.
    	// ... class의 인터페이스는 차후 설명
        
        // bool -> str시 "true" | "false"
        console.out(success + ", age=" + age) // true, age=20
        
    }
    void main() {
        int age = foo(0) // age=5
        bool success = if age // always true.
            console.out("at if blockstmt")
            true
        else
            false
        console.out("success=" + success)
        foo(class inner { 	// #2 규칙. 클래스의 정의. 클래스 자체를 foo함수로 넘긴다.
            				// worldlang은 클래스또한 하나의 타입으로 다룬다. (추후 서술)
            void print() {
             	console.out("app.main.inner.print")
            }                
        }, if success // if의 블록문 2개중 하나의 마지막 라인이 foo함수로 넘겨진다
           	bool(true)
        else
        	bool ok(false) // #2 규칙.
        , int local_age = 20)
		// local_age와 inner는 main 함수 내에서 사용 가능하다.
        console.out(local_age) // 20
        // console.out(ok) // 에러. ok는 이미 else 블록문이 끝남과 동시에 소멸되었다.
    }
}

/* 결과:
	at if blockstmt
	success=true	
	true, age=20
	20
*/
```



##### 접근자와 메소드

```cpp
import console

class app {
    // prefix _는 private를 의미. 정의와 동시에 초기화도 ok.
    // 접근시에는 _grade가 아니라 grade
    float _grade = 3.5
    // 3.5처럼 . 포함된 리터럴상수는 float으로 간주.
    int age // 접근자(accessor)는 public. 초기화 표현식이 없을 경우, 각 타입들의 기본값이 assign.
    void main() {
        app.double(grade) // static 메소드 double 호출.
        Console.out("age=" + age + ", grade=" + double(grade)) // scope(app) 생략 가능
    }
    
    // prefix #은 static 메소드를 의미.
    // 함수간 선언 순서에 종속되지 않음. _double() 호출보다 정의가 나중에 나와도 ok.
    int #double(float val) { // 인자리스트에 #, _ prefix는 붙일 수 없음.
        float #mul = 0
        mul++
        return val*mul // 리터럴 상수 int -> float -> int로 implicit 캐스팅
    }
}
// 결과: age=0, grade=10.5
```



##### Containers

```cpp
import console

class app {
    void tuple() {
        //	튜플: (<표현식expr>, ...)
        //	튜플은 각각의 타입으로 정의된 값들을 묶어놓은 특이한 컨테이너.
        //	사용자는 이 컨테이너 자체를 접근하여, iterate 불가능하며, 오직 worldlang
        //	인터프리터만 컨테이너 자체를 다룰 수 있다. (즉, worldlang 개발자는 튜플 변수를
        //	만들 수 없다)
        //	이를 이용해 다른 객체에 값을 편하게 전달해주는 용도.
        (3, "apple") // 각 원소의 타입이 모두 다름.
        class Person { // innerclass.
        	int a = 0
        	str name = ""
        	float grade = 2.5
            void print(): console.out(name)
        }
        Person p = (1, "Donald")			;p.print() // "Donald"
        // ;은 다음 stmt를 이어서 서술 가능.
        
        p() = (float age=3.0, str msg="Jung-un")
        // 변수 정의 또한 표현식이므로 튜플내에서 사용 가능.
        // 정의된 변수는 해당 scope 내에서 유효. (사용된곳이 블록문 안쪽이면,
        // 해당 블록문이 종료까지 유효.)
        // 튜플과 할당연산의 경우, 객체의 소유한 멤버와 순서대로 할당.
		// 	p.a = (int) age
		//	p.name = msg
        p.print() // "Jung-un"
        
        msg = "Denis Trillo"  // 튜플age, msg는 현 scope내에 접근.
        p.print() // "Jung-un"
        // p.name과 msg는 별도의 인스턴스.
    }
    (int, str/*변수명 생략*/) map(int age, str name) { // 사실, 이것도 튜플이며, 함수호출도 튜플이다.
    	//	맵: <타입>[<타입>]
        int[str] dict = [(3, "apple")] // 리스트를 통해 초기화 된다.
        dict.push(3, "apple") // 런타임 에러
        dict["apple"] = 4
        dict["banana"] = 5
        
        for (int x, str name) in dict // dict의 원소들인 튜플을 (x, name)으로 된 튜플로 복사
        	console.out("x, name=" + x + ", " + name)
        	
       	return (dict["apple"], "apple") // 복수개의 값을 튜플로 반환
    }
    void array() {
		// 배열: <타입>[<크기>]
        // 문법을 보면 알겠지만, 배열은 사실 맵의 특수한 종류 중 하나. ("[]" 안 int가 생략된 맵)
		int[3] arr
		for int n in ~3 // ~3은 0에서 2까지
			arr[n] = n	// c.f) arr[2] = 2
		arr[3] // 런타임 에러
		
		for int n in [0, 1, 2] // [x, y, z, ...] 은 배열의 상수 표현식
			console.out(n)
		
        arr.push(5)
        arr[3] == 5 // true
        
        int[] arr2 = arr // 크기 생략 가능
        arr2 != arr // true
        arr2.isSame(arr) // true
	}
	void main() {
		tuple()
		if 1
			(str x, str y) = map(1, "Jae-in")
			console.out("x=" + x + ", y=" + y) // "x=4, y=apple"
		// console.out("x= " + x + ", y=" + y) // 에러
		array()
		
	}
}

/* 결과:
	Donald
	Jung-un
	Jung-un
	x, name=4, apple
	x, name=5, banana
	x=4, y=apple
	0
	1
	2
*/
```



##### Pretype: void & null



##### 객체와 라이프 사이클

```cpp
import console

class Plant {
	int _age = 5
	Plant() {
        console.out("constructor. age=" + age)
		age = 20
    }
    ~Plant() {
    	console.out(name + " destructor")
    }
    str name = "herb"
    int getName() {
    	return name
    }
}

class app {
	void main() {
		Plant p() // Plant 객체 정의

		if 1
			Plant p1() // Plant 객체 정의
			p1.getName() == p.name // "herb" == "herb"
		
			Plant p2 = p1
			p2.name = "chikery"
			p1.getName() == p.name // "chikery" == "chikery"
			
		console.out("p.age is " + p.age)
		console.out("end of program")
	}
}

/*	결과:
	constructor. age=5
	constructor. age=5
	chickery destructor
	p.age is 20
	end of program
	herb destructor
*/
```



##### 인터페이스 상속

```cpp

```




##### 상수와 캐스팅

```

```



##### mutable



##### node



##### 





##### 인터페이스 확장



##### 메타



##### 클로저



##### res와 익셉션



##### Blockstmt 는 클로저



##### try-catch는 클로저로 동작한다



## 설문

이쪽에서 짧게 진행해주시면 됩니다.



## 끝

하고싶은 말이 더 많이 있지만 worldlang에 대한 주요 내용에 대한 소개는 여기까지만 해야할 것 같네요.

이 프로젝트에 관심있으시면 github(url) 한번 둘러보세요.



시간 내주셔서 다시한번 감사드립니다.

