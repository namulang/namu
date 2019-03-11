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
| char   | 정수         | unsigned  | 16bit | 0      | 2                                  |
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
        console.out("hello world!"[-9999999~4] + "boy aged " + pow) // str은 UTF-16 인코딩
        // Sequence: x~y 로 표현하며 [x, y)의 범위를 가짐.
        // str[-9999]는 0으로 예외처리.
        // str[99999999]는 str의 length-1로 예외처리.
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
        // 블록문 생략:
        // 블록문은 구문의 집합이며, 중괄호로{} 표현한다.
        // 원칙적으로는 항상 중괄호를 사용해야하나, 편의를 위해서 멤버(변수와 메소드)내에서
        // 중첩적으로 정의된 블록문에 한해서는 중괄호를 생략할 수 있으며, 이를 권장한다
        // (반대로 말하면, 클래스와 외부 메소드, 외부 멤버변수의 정의에는 반드시,
        // 중괄호가 들어가야 한다.)

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



##### 객체와 라이프 사이클

```cpp
import console

class Plant {
	int _age = 5
	Plant() {
        console.out("constructor. age=" + age)
		age = 20
    }
    // 인라인 지정자inline-specifier:	<keyword has blockstmt>: stmt
    // 	":" 는 inline 지정자(specifier)로써,
    //	뒤에 stmt 1개를 블록문 없이 사용 가능.
    ~Plant(): console.out(name + " destructor")
    str name = "herb"
    int getName(): return name
    void #test(Plant p, str new_name): p.name = new_name
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
			
			// p1이 소멸된다.			
			// GC(a.k.a GarbageCollection):
			//	모든 객체(int, str의 primitive 변수 포함해서)는 refcount 기반의 제한적인 GC에
			//	의해 해제된다.
			//	제한적인 이유:
			//		1. 다음의 java 코드는 worldlang으로 구현할 수 없다.
			//			in java)	new Daemon(); // 자바는 ref 없이 생존할 수 있다.
			//		2. GC의 한번쯤은 들어봤을, 유명한 원형-참조circular reference 문제.
			//			(현재 limitation. 해결방안 생각중)

		else: console.out("no") console.out("p.age is " + p.age)
		// 인라인 지정자 뒤에 바로 다음 구문을 붙여쓰고 있다. 유효한 문법이다. 권장 안하나, 허용한다.

		Plant.test(Plant(), str("5.5")) // 이름-없는-객체nameless object 를 생성가능하다.
		console.out("end of program")
	}
}

/*	결과:
	constructor. age=5
	constructor. age=5
	chickery destructor
	p.age is 20
	constructor. age=5
	5.5 destructor
	end of program
	herb destructor
*/
```



##### null & void

```cpp
import console

class app {
    int _age
    void returning_void() {
        // void:
		//	1. void로 정의된 값은 모든 종류의 값을 받아들이고, 동시에 무시한다.
		//		e.g) ret1은 void로 반환값에 할당이 시도되나, 반환값에 변화는 없다.
		//	2. 단, 사용을 명확히 하게 위해 명시적으로 void로 변수 정의하면 에러로 판단한다.
		//		e.g) void abc // 컴파일 에러.
		//	3. void로 선언된 값에 대한 묵시적인 할당연산만 예외적으로 허용한다.
		//		e.g) 	int foo(): 3 가 있을때,
        // 				void main() {
        //					// return foo() // 명시적 int를 void로 반환하면 에러다.
        //					foo() // 결과적으로 void에 int를 반환하지만, 유효한 문법으로 처리.

        // 묵시적 void 반환:
		_age = 35 // 이 코드는 void ret = _age = 35와 같다.
    }
    void main() {
        returning_void()
    
        class Person {
			int age
            str name
            str say() {
            	console.out("actually we don't those stmts in that block of \"if\"")
            }
        }	
        // null: 선정의 객체
        // 변수에 값이 존재하지 않는 경우 null로 정의할 수 있다. 다음의 규칙을 따른다.
        //	1. null은 primitive 타입을 제외한 모든 타입의 객체에 할당될 수 있다.
        //	2. primitive 타입의 경우에는 null은 각 타입의 기본값으로 변환되어 할당된다.
        //	3. 2번의 경우, 명시적으로 할당한 경우 컴파일 경고로 판단한다.
        int age = null; str name = null; Person p = null // age, name은 경고
        console.out("age=" + age + ", name=" + name) // age=0, name=
        //	4. null이 할당된 객체는, 메소드가 수행 안되고 바로 null을 반환한다.
        //	5. null로 할당된 객체를 사용한 경우, exception으로 catch할 수 있다. (추후 서술)

        str ret = p.say() // ret == null
        // int ret1 = p.say() // 반환형이 다르므로 컴파일 에러.
        wow(p)
        wow_short(p)
        wow(p = Person())
        wow_short(p)
    }
    void wow(Person p)
    	if p == null    		
    		return
    	console.out(p.say()[3])
    }
    void wow_short(Person p): console.out(p.say())
}

// 결과:
//	age=0, name=
//	u
//	actually we don't those stmts in that block of "if"
```



##### sharable & occupiable

| 타입명                                       | Occupiable / Sharable |
| -------------------------------------------- | --------------------- |
| int, str, bool, char, float, byte, res, void | O                     |
| int[], str[int]                              | S                     |
| ()                                           | O                     |
| class                                        | S                     |
| 사용자 Class                                 | S                     |

```cpp
import console

//	Sharable & Occupiable:
//		sharable과 occupiable은 할당연산시 원본인가, reference를 할당하는가만 다르다.
//			sharable:	(by reference) 	말그대로 할당된 변수들 끼리 같은 원본을 참조한다.
//			occupiable:	(by value)		각각의 변수들은 독립적인 원본을 따로 소유한다.
//
//		*) immutable & mutable과는 다르다. occupiable이라고 해도, 데이터를 변경할 수 있다.

class Person { // 사용자가 정의한 class는 모두 sharable.
    int _age = 5
    int getAge(): age
    float _grade = 3.5
    float getGrade(): grade
    void setGrade(float new): grade = new // implicit 할당인 void = float 은 무시된다.
}

class app {
    void proxied(Person p, str name, float grade, float[3][str] list) {
        p.setGrade(age*grade) 		// Sharable 	외부의 Person객체에도 영향을 미친다
        name = "Sissel from Norway"	// Occupiable
        grade *= 2					// Occupiable
        list["vector_x"] = (0.1, 0.1, 0.1)
    }
    void main() {
        Person p()
        str name = "unknown"
        float grade = 3.0
        float[3][str] list = [([0.1, 0.0, 0.0], "vector_x"),
        					  ([0.0, 0.1, 0.0], "vector_y")]
		proxied(p, age, grade, list)
    	// ... 3개 구문 뒤에 붙이면 구문을 자를 수 있다.
    	// ... 뒤에 공백whitespace이 오면 안된다.
    	name[0]="I"; name[1]="m" // name은 occupiable과 관계없이 const 아니므로 변경 가능.
		console.out("p.getGrade()=" + p.getGrade() + ", name=" ...
			+ name + ", grade=" + grade) 
 		console.out("vector_x:" + list["vector_x"][0] + ", " + ...
 		list["vector_x"][1] + ...
	list["vector_x"][2]) // 0.1, 0.1, 0.1
    }
}

// 결과:
//	p.getGrade()=15, name=Imknown, grade=3.000000
//	0.1, 0.1, 0.1
```



##### node & var

```cpp
import console

class app {
	int foo(? unknown) {
		// node:
		//	? 는 node 라는 타입으로 동적바인딩DynamicTyping or DuckTyping 된다.
		unknown += "world!"	// node 타입이 포함된 구문은 binding validation이 되지 않는다.
							// 런타임에 에러가 판별된다.

		console.out(unknown) // 결과가 return 된다.
	}
	void main() {
		// var: 타입유추TypeInference로 컴파일타임에 타입을 결정해준다.
		//	python, c++11 표준의 auto와 동일하다.
		var ret1 = foo("hello") // var == int
		foo(3) // int -> str 묵시적형변환이 될 수 없다. 컴파일은 되나, 런타임 에러가 된다.
		
		bool success = false
		var ret = if success: 35 else: "wow" // 결과에 따라 success나 35 혹은 "wow" 중 하나가 반환된다.
		// int ret = if success: 35 else: "wow" // 컴파일 에러.
												// 묵시적 str -> int를 요구하는 부분이 있다.
		
		// ret의 타입은 ?(node)다.
		// 35와 "wow"를 모두 포함할 수 있는 타입은 node 뿐이다.
		ret1 = ret 	// ret는 node 이므로 validation은 무시된다.
					// success가 false일 경우, int = str 이 되므로 런타임에러가 된다.
	}
}

/* 결과:
	helloworld
	<런타임 에러로 프로그램 종료>
*/
```



##### Containers

```cpp
import console

class app {
    void tuple() {
        //	튜플: (<표현식expr>, ...)
        //	튜플은 각각의 타입으로 정의된 값들을 묶어놓은 특이한 컨테이너.
        //	사용자는 이 컨테이너 자체를 접근하여, iterate 불가능하며, 오직 worldlang
        //	인터프리터만 컨테이너 자체를 다룰 수 있다. (즉, worldlang 개발자는 튜플타입 변수를
        //	만들 수 없다)
        //	단, worldlang개발자는 "statement 는 expression #2 규칙" 에 의해,
        //	튜플에 들어갈 원소에 이름을 붙여서 이를 직접 다룰 수 있다.
        //	(튜플에 들어간 각 원소는 sharable 속성을 무시된다.)
        //
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
    void sequence() {
    	// 시퀸스: <정수> ~ <정수>
    	// 범위를 나타내기 위한 컨테이너. 튜플과 동일하게 사용자는 이 컨테이너 자체를 접근하여,
        // iterate 불가능하며, 오직 worldlang 인터프리터만 컨테이너 자체를 다룰 수 있다.
        // ~ 기준으로 한쪽이 없는 경우, 극대(int의 양의 최대값)와 극소(int의 음의 최소값)를
        // 나타낸다.
        int sum = 0
        for int n in 1~3
        	sum += n
        	
       	str msg = "hello world"
       	console.out(sum + msg[5~])
    }
    void conversion() {
    	// 본래 다룰 수 없는 튜플과 시퀸스 컨테이너를 다음과 같이 변환하면 다룰 수 있음.
    	//	튜플은 임의의 타입으로 정의된 변수의 집합:
    	?[] tup = (0, "banana")
    	
    	//	시퀸스는 시작과 끝, int 2개로 변환 가능.
    	int[] sequence = (int start, int end) = 3~7
    	sequence[0] = 10
    	if sequence[0] != start
    		console.out("diff: sequence[0]=" + sequence[0] + ", start=" + start)
    		// "diff: sequence[0]=10, start=3"
    	str[] seq1 = ("wow", "hello", 1234) // 배열은 튜플을 받아들임.
    	//int[] seq2 = (1234, "1234") // 컴파일에러. str -> int는 implicit 캐스팅이 되지 않음.
    	int[] seq2 = (1234, (int) "1234") // ok.
    	?[] tup = (1234, "1234") // ok
    	int[] seq3 = tup // 컴파일 ok, 그러나 런타임 에러
    	
    	str msg = ""
    	for (str e, int n) in seq1 // 튜플과 배열은 사실 맵이며, 맵은 (값 1개)와 (값1개, 키1개) 에 대한 for-in을 지원한다.
    		msg += e + seq2[n] // if n >= seq2.len: n = seq2.len-1
    	console.out("seq1=" + msg) // "wow1234 hello1234 12341234"

		//	단, node로 취급하기 때문에 에러 사전 탐지 불가.
		//	(자세한 내용은 추후 서술한 node 항목 참조.)
    	for ? e in tup
    		console.out(e) 	// "0"
    						// "banana"
    }
	void main() {
		tuple()
		if 1
			(str x, str y) = map(1, "Jae-in")
			console.out("x=" + x + ", y=" + y) // "x=4, y=apple"
			
		// console.out("x= " + x + ", y=" + y) // 에러
		array()
		sequence()
		conversion()
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
	3 world
	diff: sequence[0]=10, start=3
	0
	banana
*/
```



##### 인터페이스 상속

```cpp
import console

class app {
    // 중첩클래스(nested class)
    class Plant {
        str getName(): "Plant"
        int _age = 1
        int getAge(): _age
    }
    // 상속inheritance:	class <파생클래스> -> <기반클래스>    
    //	기반 클래스baseclass의 인터페이스를 물려받는다.
    //	->는 상속UML Generalization 기호에서 착안했다.
    //	함수 명세signature가 같은 경우 overriding으로 판단한다. (= Java)
    //	함수명과 인자리스트(즉, header) 까지만 일치할 경우, 메소드 은닉hiding 된다.
    class Leaf -> Plant {   
        str getName(): "Leaf" // overriding
        float getAge(): 3.5 // 반환형이 다르므로 은닉이다.
    }
    void main() {
        Plant p()
        if 1
            p = Leaf()
       	console.("name=" + p.getName() + ", age=" + p.getAge())
    }
}

// 결과: name=Leaf, age=1
```




##### 상수와 캐스팅

```cpp
import console

class Animal {
    // 상수: # <타입>
    // prefix 중 하나로, #로 표현한다. (# 기호가 딱딱함과 고정됨을 연상시키기 때문이다.)
    //	1. 타입 앞에만 붙을 수 있다. (다시말하면, Refer 항상 교체될 수 있으며, 이를 문법적으로
    //	   방지해주지 않는다.)
    //  2. prefix를 같이 표기하는 경우, 순서를 지켜야 한다. $#_ 순으로 표기한다.
    //  3. void에 #을 붙일 수 없다.
    str #getName(): "unknown" // const 메소드.
    #int _age = 1
    int getAge(): _age
   
    #int $#_foo() {} // "static const private method returning const int."
    // void #$_foo1() {} // 컴파일에러: Rule#2 위반
    void foo1() {}
    // void setAge(int new): age = new // 컴파일에러: age는 const 이다.
    void #walk(): console.out(age + "yo " + getName() + " walked.") // getName()이 const메소드가 아니었다면 에러였다.
}
class Beaver -> Animal {
    #str #getName(): "Beaver"
    void #walk() {
        super.walk() // super는 기반클래스(Animal)로 캐스팅된 this를 의미한다.
                    // "Animal super = this" 가 이미 선언된 것과 같다.
        console.out("Beaver's finding a seashell.")
    }
}

class app {
    int main() {
        #Animal[] anims1 // an array to constant Animal.
        Animal#[] anims2 // an constant array to Animal.

        // anims1[0].setAge(5) // non-const 메소드에 접근한다. 컴파일 에러.
        // Beaver beav = anims1[0] // 컴파일에러. 묵시적 형변환에 downcasting은 포함 되지 않는다.
        // Beaver beav = (Beaver) anims1[0] // 컴파일 에러. const -> non-const로 형변환 안된다.
        #Beaver beav = (#Beaver) anims1[0]
        #Animal anim = anims2 // non-const -> const 로는 묵시적 변환된다.
        // beav.setAge(5) // beav 는 const 다.
        beav.walk()
       
        #Animal#[#str] map = [(beav, "beav")] // a constant map holding const Animal as value distinguising with const string.
        // map["anims2"] = Animal() // 컴파일에러. map은 const 이다.
        #Animal[#str] map2
        map2["anims1"] = Animal() // Rule#1: Value는 const타입이나, refer는 const가 아니다.
        // map2["anims1"].foo() // #Animal로 non-const 메소드를 호출했다.
        console.out(map["anims1"].walk())
    }
}
/* 결과:
1yo Beaver walked
Beaver's finding a seashell.
1yo Beaver walked
Beaver's finding a seashell.
*/
```



##### 클로저

```cpp
- 블록문의 구체적인 룰 소개
  class와 그 직통 멤버(외부 메소드outer method, 멤버변수)는 반드시 중괄호 사용한다는걸 비교해서 재확인
  그 멤버 안쪽은 중괄호 무시 권장
```



##### 인터페이스 확장

```cpp

```



##### 노테이션

```cpp
- @는 syntactic sugar.
- 일일이 외워야 한다. 알면 편하다. 몰라도 된다.
```



##### 프로퍼티

```cpp

```



##### 메타



##### res와 익셉션



##### Blockstmt 는 클로저



##### try-catch는 클로저로 동작한다



## 설문

이쪽에서 짧게 진행해주시면 됩니다.



## 끝

하고싶은 말이 더 많이 있지만 worldlang에 대한 주요 내용에 대한 소개는 여기까지만 해야할 것 같네요.

이 프로젝트에 관심있으시면 github(url) 한번 둘러보세요.



시간 내주셔서 다시한번 감사드립니다.

