# worldlang 개요 & 설문

## 서론

먼저 수고를 들여 이 문서를 열람해 주신것에 감사의 말씀 올립니다. 

저는 변두리에서 *world*라는 프로그래밍 언어를 만들고 있는데, 이에 대한 피드팩을 받고 싶어서 이 문서를 만들었습니다. 



## 진행 순서

무엇보다 제가 시간을 많이 가져가면 안될것 같네요. 간단한 아이디어 소개와 문법들을 15분에 소개하고 있으며, 이에 대한 설문이 약 3분 진행됩니다. 모든 설문은 무기명으로 진행되며 답에 시간이 오래걸리는 주관식은 최대한 배제하였습니다.

##### 

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

/*모든 프로그램은 진입점을 위한 app이라는 객체 정의가 필요*/
app
	int main(): console.out("hello world\n")

// 결과: hello world
```



##### 변수정의와 기본 연산자

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

app // 객체 app
	int age = 0 // app의 변수, age.
    void   main   (   )  // whitespace 무시
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


// 결과: hellboy aged 16
```



##### 객체의 기본

```cpp
import console

// 객체 확장 문법:
// <Opt:원본객체> <인터페이스 복사될 객체>
// 		<Opt:객체의 확장 인터페이스>
//		<Opt:객체의 확장 인터페이스2>

A // 객체 A를 정의한다. 원본객체는 생략되었다. 고로, 이 객체는 무scratch에서 출발한다.
	void print() // 객체 A는 print() 라는 메소드를 갖게 되었다.
    	c.out("hello world. I'm " + age + " years old.") // print의 구현
   	int age = 0

A B // 객체 B를 정의한다. A의 인터페이스를 물려받는다.
	void say() // 거기에 say() 메소드를 확장했다.
    	c.out("and you?")

app
	void main()
    	A a1 // A 객체로부터 인터페이스를 모두 물려받는다.    
    	B b1
    	b1.age = 5

    	c.out("a1' age is " + a1.age) // a1's age is 0
    	c.out(b1.age) // 5

		A.age = 20
    	A C // 메소드 안에서 새로운 객체를 만들 수 있듯,
    		// 새로운 객체를 만들면서 인터페이스 확장도 당연히 가능하다.
    		void wow()
    			say()
				print()
    	C.wow()
    	// 단 C는 지역객체이므로 메소드 밖과 시그내쳐signature에서는 사용할 수 없다.

/* 결과:
	a1's age is 0
	5
	hello world. I'm 20 years old.
	and you?
*/
```



##### 키워드와 논리연산자

```cpp
app
    int main()
        int age = 21
        int sum = 0
        // 블록문 생략:
        // 블록문은 구문의 집합이며, 중괄호와{} 들여쓰기Indentation로 표현한다.
        // 여기서 중요한 것은 들여쓰기이며, 중괄호는 모호한 케이스를 없애기 위해
		// 표현하는 것이다.
		// 모든 중괄호는 생략될 수 있으며, 들여쓰기만 제대로 되어있으면 문제는 없다.
		// 다만 몇몇 케이스에서는 중괄호 생략이 문제가 될 수 있다는 걸 알아야 한다.
		//
		// 중괄호 생략시 문제케이스 #1:
		// world의 핵심 특징은 모든 구문stmt을 표현식expression으로 대체한 것에 있다.
		// 이는 정의와 사용을 동시에 할 수 있게 하는데, 중괄호가 없을 경우 모호한
		// 상황이 필연적으로 발생한다.
		// e.g.	void print()
		// 			console.out("hello")
		//		() // 이것은 print()인가 아니면 빈 Tuple인가?
		// 		중괄호를 넣으면 직관적으로 변한다.
		// 		void print() {
		//			console.out("hello")
		// 		} // 이 뒤에 ()를 붙이면 클로저의 호출이 된다.
		// 		() // 빈 tuple이다.
		//  
		// 중괄호는 가급적 표현하지 않는 것을 권장한다.

        if age > 20 { // 블록문시 {, }를 사용가능 하지만,
            if age > 20 & age < 20 // 되도록 생략을 권장.
                console.out("can't reach here")
            
            int sum = 0 // 허용된 중복 정의
            for int n in 1~5 // ~는 1부터 5까지를 의미함. [1, 5)
                sum += n
                
            console.out("sum=" + sum) // "sum=10"
        } else if age == 20 // } 뒤에 다음 stmt 가능.
            sum = 0
        if ! (age == 21) | sum // |는 or연산. sum이 0이 아니면 true로 판단
            console.out("sum=" + sum)
        elif ! sum // elif == else if
            console.out("can't reach here")
            return -1 // 함수 종료. 반환

        int bit = 2            
        console.out(bit || 4) // "6"
        // ||, &&, ~~ 비트 연산자
        return 0


import console // 외부 scope 이면, 어느 위치에든 선언 가능.


/* 결과:
sum=10
sum=10
6
*/
```



##### statement 는 expression

```cpp
app
    // 구문statement와 표현식expression:
    // 프로그래밍 언어에서 구문이란 코드의 각 라인을 말하며,
    // 표현식은 특정한 값을 반환할 수 있는 식별자가 조합된 식을 뜻한다.
    //	e.g.in c++)	foo(3); 			// 표현식이므로, 동시에 구문이다.
    //				void func(int age); // 구문이다.
    //				type A;	 			// 구문이다.
    //
    // world는 문법을 간결하게 하기 위해 모든 구문은 표현식으로 정의한다.
    // 이를 위해 2가지 규칙이 있다.
    //	1. 모든 블록문을 갖을 수 있는 키워드는 블록문의 마지막 라인을 밖으로 반환한다.
    //	2. 모든 타입 선언은, 동시에 정의이며, 정의된 식별자는 해당 범위scope내에서 유효하다.
    int foo(int age)
        5 // #1 규칙. return이 없어도 ok.
	void boo(type declared, bool success, int age) // type도 int와 같은 타입의 한 종류.
		// ... type의 인터페이스는 차후 설명

        // bool -> str시 "true" 또는 "false"
        console.out(success + ", age=" + age) // true, age=20

    void main()
        int age = foo(0) // age=5
        bool success = if age // always true.
            console.out("at if blockstmt")
            true
        else
            false
        console.out("success=" + success)

        boo(inner	// #2 규칙. 클래스의 정의. 클래스 자체를 boo함수로 넘긴다.
            		// worldlang은 클래스또한 하나의 타입으로 다룬다. (추후 서술)
            void print()
             	console.out("app.main.inner.print")
        , if success // if의 블록문 2개중 하나의 마지막 라인이 boo함수로 넘겨진다
           	bool(true)
        else
        	bool ok(false) // #2 규칙.
        , int local_age = 20)

		// local_age와 inner는 main 함수 내에서 사용 가능하다.
        console.out(local_age) // 20
        // console.out(ok) // 에러. ok는 이미 else 블록문이 끝남과 동시에 소멸되었다.


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

app
    // prefix _는 protected를 의미. 정의와 동시에 초기화도 ok.
    // 접근시에는 _grade가 아니라 grade
    float _grade = 3.5
    // 3.5처럼 . 포함된 리터럴상수는 float으로 간주.
    int age // 접근자(accessor)는 public. 초기화 표현식이 없을 경우, 각 타입들의 기본값이 assign.
    void main()
        app.double(grade) // static 메소드인 double을 호출.
        console.out("age=" + age + ", grade=" + double(grade)) // app의 범위scope에 있으므로, 본래 app.double() 해야 하나, 'app'을 생략 가능
    
    // prefix $은 static 메소드를 의미.
    // 함수간 선언 순서에 종속되지 않음. app.double() 호출보다 정의가 나중에
    // 나와도 ok.
    int $double(float val) // 인자리스트에 $, _ prefix는 붙일 수 없음.
        int $mul = 0
        mul++
		return val*mul // int mul -> float mul -> (int) val*mul 로 implicit 캐스팅


// 결과: age=0, grade=7
```



##### res & src

```cpp
import console

app
	res boo(res result)
		// 결과타입res:
		// 메소드의 결과를 표현한다. 동작의 성공 여부, 결과의 메시지, 결과의 카테고리
		// (warn, info, err), src 값들을 확인 할 수 있다. res는 ADT이며 동시에
		// occupiable 타입이다.
		//
		// result pretypes:
		// res로부터 상속받은 다양한 결과타입들이 pretypes로써 정의되어 있다. prefix "r"
		// 을 사용하며, 다음은 그 목록이다.
		//    1. rok:    성공적으로 이상없이 수행됨. res의 기본값이다.
		//    2. rfile:    파일 관련 에러
		//    3. rperm: 권한 관련 에러
		//    4. rsuper:기반 클래스에서 발생한 에러로 더 이상 현 메소드에서 진행이 불가
		//                하다.
		//    ...추가예정...
		
		// 어떻게 res는 ADT이며 occupiable이며, 기본값이 ADT가 되는가?:
		// 앞서 설명한 듯 occupiable의 동작은 매우 심플하다.
		//    1.    월드의 모든 변수는 기본적으로 refer에 의해서 감싸져wrapping 있다.
		//    2.    refer는 할당연산 요청이 왔을때 대상(wrapping하는)이 occupiable
		//			타입일 경우, 그 대상에 복제생성자를cloning 수행한다.
		//    3.    반대의 경우에는 단순히 대상을 교체한다.
		//    4.    구체타입이며 occupiable일 경우에는 최적화에 따라 refer가 없도록
		//			코드블럭을 구현한다.
		res ret // 기본값은 rok다.
		
		// 위의 구문은 최종적으로 ret라는 refer가 rok라는 타입의 객체를 가리키게 되는데,
		// 중간과정을 해석하면 다음의 흐름으로 진행된다.
		//    1.	ret의 기본값은 rok() 다.
		//    2.	rok는 선정의타입pretype이며, 괄호 없이 타입만 명시할 경우,
		//			기본생성자를 호출하는것과 같기에, res ret = rok()로 된다.
		//			e.g.	int a // int a()와 같아, 기본생성자가 호출되며, 결과 a = 0.
		//					MyClass b // MyClass()와 같다.
		//					MyADT c = null // ADT일 경우 뒤에 = null을 붙이지 않으면
		//								   // 에러가 된다.
		//    3.	rok()로 생성된 임시객체는 refer인 ret 변수에 할당이 된다.
		//			refer ret는 타입인 res가 occupiable 이므로 주어진 객체의 복제
		//			생성을 시도한다. 결과, res ret = rok().clone()과 같아진다.
		//    4.	위는 최적화를 거치지 않았을때, 기본 규칙에 의해서 동작되는 순수
		//			로직 흐름이며, 실제로는 중복되어 불필요한 객체 생성을 하지 않도록
		//			의미분석기가 최적화 한다.
		
		res ret // 기본값은 rok()다.
		// res = res + result // res는 사칙연산이 허용되지 않는다.
		ret = result
		console.out("ret=" + ret + ", code=" + ret.code) // res=rok, code=0
		return ret

	res foo()
		res ret = boo(rsuper(rwarn)) // Warning으로 새로운 rsuper객체를 생성한다.
		// 출처src:
		// 주어진 심볼(변수, 메소드, 클래스)이 어느 원전(code)에서 기원하였는지를
		// 기록한다. 파서가 구문문석을 하면서 그 src객체의 정보를 채워넣으며
		// 모든 객체는 sharable 타입인 src의 객체를 공유하게 된다.
		src s = ret.src
		console.out(s.method.name + "#" + s.line + " at " + s.file.name) // app.foo()#12 at res.wrd
		return ret

	void main()
		res ret = foo()
		if ret == rsuper() // 기존 규칙대로라면 이게 맞는 비교문이나,
			console.out("ret == rsuper()")
		if ret == rsuper // 편의를 위해, ret는 클래스인 rsuper도 체크할 수 있다.
			console.out("ret == rsuper")
		if ret.isSub(rsuper) // 위의 "== rsuper"는 이것과 같다.
			console.out("ret.isSub(rsuper)")
		if ret.isWarn()
			console.out("ret.isWarn()")
		if ret.isNormal() // ==> (! ret.isWarn() & ! ret.isErr())
			console.out("ret.isNormal()")
		if ret // ! ret.isNormal()과 같다.
			console.out("ret")

/* 결과:
	ret=rok, code=0
	app.foo()#12 at res.wrd
	ret == rsuper()
	ret == rsuper
	ret.isSub(rsuper)
	ret.isWarn()
	ret.isNormal()
	ret
*/
```



##### 확장가능한 블록문extensible Block statement

```cpp
import console

app
	// 확장 가능한 블록문Blockstmt: with <Opt:확장될 식별자> <stmts>
	// 실행가능한 구문의 명시적 집합으로, with 키워드와 들여쓰기indent로 표현한다.
	// 주어진 식별자를 현 범주scope로 확장할 수 있다. 해당 식별자의 모든 멤버를 객체와
	// 접근연산자("."dot) 없이 호출이 가능하게 된다.
	// 다음의 규칙을 따른다.
	//	1.	블록문에서 정의한 식별자(메소드, 변수, ...)는 해당 블록문에서 유효하다.
	//		(블록문을 사용하면 변수의 라이프 사이클을 제어할 수 있다.)
	//	2.	블록문은 독자적인 프로그램 흐름에 대한 제어권을 갖지 못한다.
	//		메소드와 달리, 블록문 내에서 return을 하게 되면 블록문 뿐만 아니라 메소드
	//		자체를 벗어나게 된다. 이는, 블록문이 독자적인 흐름을 갖지 못하기 때문
	//	3.	문법적으로 블록문을 변수에 할당하거나 소유할 수 없다.
	//		(클로져를 대신 사용하라)
	//	4.	키워드(if, for, ...)에 의해 블록문을 사용할 경우를 묵시적 블록문이라 한다. 
	//	5.	with 키워드 뒤에 식별자를 붙이게 되면 해당 블록문 안쪽에서 그 식별자의
	//		소유한 멤버들이 확장된다.
	//	6.	이렇게 확장된 인터페이스들은 this보다는 상위의, 지역변수보다는 하위의
	//		우선순위를 갖는다. 이름 중복 허용 규칙에 의해 동일한 이름이 scope내에 복수
	//		존재하는 경우 우선순위가 가장 높은 개체가 선택된다.
	//	7.	블록문을 통한 인터페이스 확장은 중첩될 수 없다. 즉, 최대 this를 포함해서
	//		2개까지 이다.
	//	8.	식별자는 생략 가능하다. 이 경우, 별다른 확장을 수행하지 않는다.
	//	9.	확장된 식별자는 블록문에서 it 이라는 별칭을 갖는다.
	void foo() // 메소드도 블록문을 기본적으로 가지고 있다.

		with // Rule#8
        	int local = 5
        	updateAge(local) // Rule#2
        	
        	int updateAge(int new_age) // 클로저의 정의
    			int #age = 20
	    		return age // Rule#2: return시 updateAge메소드만 종료된다.

        // updateAge(20) // Rule#3: 접근 할 수 없다. 블록문에서 벗어났기 때문이다.
        with
	    	return // Rule#1: {, } 을 가지고 있는 foo() 메소드에서 벗어난다.
        console.out("can't reach here.")

	Person p // 객체 생성
	void eat() with console // 메소드도 블록문을 가지고 있는 것이다.
		// console은 클래스지만, 이 또한 식별자이므로 유효한 코드다.

		out("app.eat()") // console.out("app.eat()") 과 동일하다.

    int getSome(): return 5
    void doSwitch(int val) with val
        // 다중분기문is: <확장된블록문>
        //					is <식별자와 동일한 타입의 값>
        //						<블록문>
        // switch에 대응하는 문법으로, 다음의 규칙을 따른다.
        //	1.	주어진 식별자에 대해, 값이 일치하는 경우 속한 블록문을 수행한다.
        //		만약 다른 비교연산자를 사용해야 하는 경우, if-else를 사용해야 한다.
        //		(is는 사실 if it == 3 elif it == doSwitch() .. 와 동일하다.)
        //	2.	is의 값은 반드시 확장된 변수와 동일한 타입의 값으로 평가evalutate
        //		될수 있어야 한다.
        //	3.	else는 그 이외의 경우 수행된다.
        is 3 // if it == 3
            console.out("we got 3.")
		is getSome() // else if it == getSome() // 함수 호출도 가능하다.
			console.out("doSwitch")
		else
			with str getString(#str msg) {	// 클로저의 정의와 호출을 괄호로 묶을
                  							// 수 있다.
				return "hello " + msg		// 정의도 표현식이기에 문제없다.
    		} ("world")	// 클로져를 정의와 동시에 호출하고, 그 반환값을 블록문에
			 			// 확장했다.

			/* 클로저 뒤에 중괄호는 생략하면 위의 코드와 완전히 다른 표현이된다:
				with str getString(#str msg)
					return "hello " + msg // 클로져를 자체를 확장한다.
					// 블록문이 끝났다.
				("world") // 문자열 1개를 가진 튜플을 정의했다.
			*/
				is "he": console.out("can't")
				is "lo": console.out("execute")
				is "hello world": console.out("correct.")
				else: console.out("this line.")

	void main() with p // 객체 p에 대해 인터페이스가 확장된다.
		foo()
		print() // p.print()와 동일하다.
		eat() // Person.eat은 this.eat()보다 우선된다.
		void fly()
			console.out("am I a bird?")

		fly() // local에 등록된 fly()는 클래스scope를 가진 Person.fly()보다 우선된다.
		str name = "Chales"
		console.out(p.name)

		doSwitch(4)


Person
	void print()
		console.out("my name is unknown.")
	void eat()
		console.out("I'm eating.")
	void fly()
		console.out("I'm not a bird.")
	str name = "Michel"

/* 결과:
	my name is unknown.
	I'm eating.
	am I a bird?
	Chales
	correct.  */
```

##### 연산자 우선순위operator precedence

위에 있을 수록, 우선된다. 크게 5가지로 다음과 같이 분류하며, 단항 -> 이항 순으로 나온다. 동일한 우선순위라면 왼쪽에서 오른쪽으로 평가된다.

1. 접근
2. 단항
3. 이항 산술
4. 비트연산
5. 비교

| 연산자operator                          | 설명                                            | 예제                    |
| --------------------------------------- | ------------------------------------------------| ----------------------- |
| ()                                      | 괄호                                            | (void func(int val) {}) |
| ( <인자리스트> )                        | 함수호출                                        | func(35)                |
| []                                      | 원소접근                                        | arr[5]                  |
| ++, --, **                              | 후위 단항unary postfix                          | a++                     |
| ++, --, **                              | 전위 단항                                       | **a // a*a              |
| _                                       | 보호 속성 단항protected                         | str _val {}             |
| $, #                                    | 상수 / 정적 속성 단항                           | #str $#_val {}          |
| +                                       | 확장 속성 단항                                  | #str +#$_val {}         |
| -                                       | 음수 단항<br />양수 단항unary plus 연산자는 없다 | a = -a                 |
| !                                       | 부정logical not                                  | !++a                   |
| ~~                                      | 비트연산 부정                                    | ~~a                    |
| *, /, %, ^                              | 이항 곱, 나눗셈, 나머지 연산                    | a % b                   |
| +, -                                    | 이항 덧셈, 뺄셈                                  | a - b                  |
| <<, >>                                  | 비트 SHIFT 연산                                  | a << 3                 |
| &&                                      | 비트 AND 연산                                    | a && 0x01              |
| %%                                      | 비트 XOR 연산                                    | a %% 0x01              |
| \|\|                                    | 비트 OR 연산                                    | 0x02 \|\| 0x01          |
| ~                                       | 범위 연산                                        | 0 ~ b                  |
| <=, <, >, >=, ==, !=                    | 비교 연산                                        | a > b                  |
| &, \|                                   | 논리 연산                                        | if a & b               |
| =, *=, /=, %=, +=, -=, &&=, \|\|=, ^^=, | 할당 연산                                        | a &&= 0x02             |



##### 객체와 라이프 사이클

```cpp
import console

Plant
	int _age = 5
	Plant()
        console.out("constructor. age=" + age)
		age = 20
	Plant(#str msg)
		console.out("Plant(#str)")

    // 인라인 지정자inline-specifier:	<keyword has blockstmt>: stmt
    // 	":" 는 inline 지정자(specifier)로써,
    //	뒤에 stmt 1개를 블록문 없이 사용 가능.
    ~Plant(): console.out(name + " destructor")
    str name = "herb"
    int getName(): return name
    void $test(Plant p, str new_name): p.name = new_name

app
	void main()
		Plant p // 기본생성자로 Plant 객체 정의
		Plant p_null = null // 객체 정의되지 않음.

		if 1
			Plant p1("Where is my santa?") // Plant(#str) 생성자로 객체 정의
			p1.getName() == p.name // "herb" == "herb"
		
			Plant p2 = p1
			p2.name = "chikery"
			p1.getName() == p.name // "chikery" == "chikery"
			
			// p1이 소멸된다.			
			// GC(a.k.a GarbageCollection):
			//	모든 객체(int, str의 primitive 변수 포함해서)는 refcount 기반의 제한적인
			//	GC에 의해 해제된다.
			//	제한적인 이유:
			//		1. 다음의 java 코드는 worldlang으로 구현할 수 없다.
			//			in java)	new Daemon(); // 자바는 ref 없이 생존할 수 있다.
			//		2. GC의 한번쯤은 들어봤을, 유명한 원형-참조circular reference 문제.
			//			(현재 limitation. 해결방안 생각중)

		else: console.out("no") console.out("p.age is " + p.age)
		// 인라인 지정자 뒤에 바로 다음 구문을 붙여쓰고 있다. 유효한 문법이다. 권장 안하나, 허용한다.

		Plant.test(Plant(), str("5.5")) // 이름-없는-객체nameless object 를 생성가능하다.
		console.out("end of program")

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

app
    int _age
    void returning_void()
        // void:
		//	1. void로 정의된 값은 모든 종류의 값을 받아들이고, 동시에 무시한다.
		//	2. 단, 사용을 명확히 하게 위해 명시적으로 void로 변수 정의하면 에러로 판단한다.
		//		e.g. void abc // 컴파일 에러.
		//	3. void로 선언된 값에 대한 묵시적인 할당연산만 예외적으로 허용한다.
		//		e.g. 	int foo(): 3
        // 				void main() {
        //					// return foo() // 명시적 int를 void로 반환하면 에러다.
        //					foo() // 결과적으로 void에 int를 반환하지만, 유효한 문법으로 처리.

        // 묵시적 void 반환:
		_age = 35 // 이 코드는 void ret = _age = 35와 같다.

    void main()
        returning_void()

		// 중첩클래스nested class: 메소드안의 클래스 정의
		// 해당 메소드 안에서만 사용이 가능하다. 이는 블록문 규칙#1에 의한 것이다.
        Person
			int age
            str name
            str say() {
            	console.out("actually we don't those stmts in that block of \"if\"")
				return null

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

		Person p = null
        wow(p)
        wow_short(p)
        wow(p = Person())
        wow_short(p)

    void wow(Person p)
    	if p == null    		
    		return
    	console.out(p.say()[3]) // null[3]은 null이다.

    void wow_short(Person p): console.out(p.say())

// 결과:
//	age=0, name=
//	u
//	actually we don't those stmts in that block of "if"
```



##### sharable & occupiable

| 타입명                                                       | Occupiable / Sharable |
| ------------------------------------------------------------ | --------------------- |
| primitive types:<br />int, str, bool, char, float, byte, res, void | O               |
| pretypes:<br />rok, rfile, rperm, ...                        | O                     |
| 배열(int[]), 맵(int[str])                                    | S                     |
| 튜플()                                                       | O                     |
| type                                                         | S                     |
| 사용자 class의 객체                                          | S                     |

```cpp
import console

//	Sharable & Occupiable:
//		sharable과 occupiable은 할당연산시 원본인가, reference를 할당하는가만 다르다.
//			sharable:	(by reference) 	말그대로 할당된 변수들 끼리 같은 원본을 참조한다.
//			occupiable:	(by value)		각각의 변수들은 독립적인 원본을 따로 소유한다.
//
//		*) immutable & mutable과는 다르다. occupiable이라고 해도, 데이터를 변경할 수
//		있다.

Person // 사용자가 정의한 class는 모두 sharable.
    int _age = 5
    int getAge(): age
    float _grade = 3.5
    float getGrade(): grade
    void setGrade(float new): grade = new // implicit 할당인 void = float 은 무시된다.

app
    void proxied(Person p, str name, float grade, float[3][str] list)
        p.setGrade(age*grade) 		// Sharable 	외부의 Person객체에도 영향을 미친다
        name = "Sissel from Norway"	// Occupiable
        grade *= 2					// Occupiable
        list["vector_x"] = (0.1, 0.1, 0.1)

    void main()
      	Person p
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

// 결과:
//	p.getGrade()=15, name=Imknown, grade=3.000000
//	0.1, 0.1, 0.1
```



##### node & var

```cpp
import console

app
	int foo(? unknown)
		// node:
		//	? 는 node 라는 타입으로 동적바인딩DynamicTyping or DuckTyping 된다.
		unknown += "world!"	// node 타입이 포함된 구문은 binding validation이 되지
							// 않는다. 런타임에 에러가 판별된다.

		console.out(unknown) // 결과가 return 된다.

	void main()
		// var: 타입유추TypeInference로 컴파일타임에 타입을 결정해준다.
		//	python, c++11 표준의 auto와 동일하다.
		var ret1 = foo("hello") // var == int
		foo(3) // str -> int 묵시적형변환이 될 수 없다. (unknown += "world")
			   // 컴파일은 되나, 런타임 에러가 된다.

		bool success = false
		var ret = if success: 35; else: "wow" // 결과에 따라 success나 35 혹은 "wow" 중 하나가 반환된다.
		// int ret = if success: 35; else: "wow" 는 컴파일 에러.
		// 잘못된 묵시적 형번환 str -> int를 요구하기 때문이다.

		// ret의 타입은 ?(node)다.
		// 35와 "wow"를 모두 포함할 수 있는 타입은 node 뿐이다.
		ret1 = ret 	// ret는 node 이므로 validation은 무시된다.
					// success가 false일 경우, int = str 이 되므로 런타임에러가 된다.

/* 결과:
	helloworld
	<런타임 에러로 프로그램 종료>
*/
```



##### Containers

```cpp
import console

app
    void tuple()
		//	튜플: (<표현식expr>, ...)
		//	튜플은 각각의 타입으로 정의된 값들을 묶어놓은 특이한 컨테이너.
		//	사용자는 이 컨테이너 자체를 접근하여, iterate 불가능하며, 오직 worldlang
		//	인터프리터만 컨테이너 자체를 다룰 수 있다. (즉, worldlang 개발자는 튜플타입 변수를
		//	만들 수 없다)
		//	단, worldlang개발자는 "statement 는 expression #2 규칙" 에 의해,
		//	튜플에 들어갈 원소에 이름을 붙여서 이를 직접 다룰 수 있다.
		//	(튜플에 들어간 각 원소는 sharable 속성을 무시된다.)
		//	이를 이용해 다른 객체에 값을 편하게 전달해주는 용도.

		(3, "apple") // 각 원소의 타입이 모두 다름.
		Person // 중첩클래스.
			int a = 0
			str name = ""
			float grade = 2.5

			void print(): console.out(name)

			void assign((float new_grade, str new_msg), int new_a)
				grade = new_grade
		    	msg = new_msg
				a = new_a

		Person p; p.name = "Donald"; p.print()
		// ;은 다음 stmt를 이어서 한 줄에 서술 가능.
		
		str = msg = "Jung-un"
		p.assign((3.0/2, msg), 24) // 인자msg와 파라메터new_msg는 이름이 달라도 된다.

		// 변수 정의 또한 표현식이므로 튜플내에서 사용 가능. 정의된 변수는 해당 scope
		// 내에서 유효. (사용된곳이 블록문 안쪽이면, 해당 블록문이 종료까지 유효.)
		// 튜플과 할당연산의 경우, 객체의 소유한 멤버와 순서대로 할당.
		p.print() // "Jung-un"
		
		msg = "Denis Trillo"  // msg는 현 scope내에 접근.
		p.print() // "Jung-un"
		// p.name과 msg는 별도의 인스턴스.

    (int, str/*변수명 생략가능*/) map(int age, str name)
		// 사실, 인자리스트(int age, str name)도 튜플이며, 함수호출도 튜플이다.

    	//	맵: <타입>[<타입>]
        int[str] dict = [(3, "apple")] // 리스트를 통해 초기화 된다.
        dict.push(3, "apple") // 런타임 에러
        dict["apple"] = 4
        dict["banana"] = 5
        
        for (int x, str name) in dict // dict의 원소들인 튜플을 (x, name)으로 된 튜플로 복사
        	console.out("x, name=" + x + ", " + name)
        	
       	return (dict["apple"], "apple") // 복수개의 값을 튜플로 반환

    void array()
		// 배열: <타입>[<Opt:크기>]
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

    void sequence()
    	// 시퀸스: <정수> ~ <정수>
    	// 범위를 나타내기 위한 컨테이너. 튜플과 동일하게 사용자는 이 컨테이너 자체를
		// 접근하여, iterate 불가능하며, 오직 worldlang 인터프리터만 컨테이너 자체를
		// 다룰 수 있다.
        // ~ 기준으로 한쪽이 없는 경우, 극대(int의 양의 최대값)와 극소(int의 음의 최소값)
		// 를 나타낸다.
        int sum = 0
        for int n in 1~3 // 1~3은 [1, 3)
        	sum += n
        	
       	str msg = "hello world"
       	console.out(sum + msg[5~]) // 5~는 5 이상을 뜻함

    void conversion()
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
		str[] seq1 = ("wow", "hello", 1234)
		// 배열은 튜플을 받아들임.
		// 1234int -> "1234"str
		//int[] seq2 = (1234, "1234") // 컴파일에러. str -> int는 implicit 캐스팅이
									  // 되지 않음.

		// 명시적 타입 캐스팅explicit typecast: (<타입>) 식별자
		// 명시적으로 다른 타입으로 형변환 시도하는 문법이다. 다음의 규칙을 따른다.
		//	1.	명시적 형변환은 묵시적 형변환보다 더 많은 변환을 처리할 수 있다.
		//	2.	임의의 타입이 모든 타입으로 형변환을 지원하는 것은 아니다.
		//		어느 타입으로 형변환이 가능한지는 각 타입의 개발자가 정의한다.
		//	3.	형변환 가능 여부는 컴파일 타입에 확정된다. 지원되지 않는 형변환을 시도할
		//		경우 에러로 간주한다.
		//	4.	형변환은 해당 타입의 sharable, occupiable 속성 관계없이 항상 인스턴스를
		//		발생시킨다.
		//
		// 어떻게 str객체는 int로 명시적 타입캐스팅을 지원하는가:
		// 형변환을 지원하고 싶으면 지원하고 싶은 타입에 생성자를 확장해놓으면 된다.
		// e.g.	+int
		//			int(#str val)
		//				...val을 int로 변환...
		//		str name = ".."
		//		(int) name // 인터프리터는 int(#str) 생성자를 토대로 형변환을 시도한다.
		//
		// 묵시적 형변환implicit typecast: <자동으로 수행됨>
		// 특정 상황에서 인터프리터에 의해 자동으로 수행해 주는 형변환이다. 다음의 규칙을
		// 따른다.
		//	1. 파생클래스를 부모 클래스로 형변환
		//	2. primitive 변수들 간의 형변환(e.g. float -> int)
    	int[] seq2 = (1234, (int) "1234") // ok.
    	?[] tup = (1234, "1234") // ok
    	int[] seq3 = tup // 컴파일 ok, 그러나 런타임 에러
    	
    	str msg = ""
    	for (str e, int n) in seq1 // 튜플과 배열은 사실 맵이며, 맵은 (값 1개)와 (값1개, 키1개) 에 대한 for-in을 지원한다.
    		msg += e + seq2[n] // if n >= seq2.len: n = seq2.len-1
    	console.out("seq1=" + msg) // "wow1234 hello1234 12341234"

		//	단, node로 취급하기 때문에 에러 사전 탐지 불가.
    	for ? e in tup
    		console.out(e) 	// "0"
    						// "banana"
 
	void main()
		tuple()
		if 1
			(str x, str y) = map(1, "Jae-in")
			console.out("x=" + x + ", y=" + y) // "x=4, y=apple"
			
		// console.out("x= " + x + ", y=" + y) // 에러
		array()
		sequence()
		conversion()

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

app
    // 중첩클래스(nested class)
    Plant
    	Plant(): console.out("default ctor")
    	Plant(#str new): _name = new

    	str _name = "Plant"
        str getName(): _name
        // int _age = 1 // Leaf에도 _age가 있기 때문에 Leaf에 중복정의에러 발생한다.
        int getAge(): _age

	// 메소드 재정의Overriding:
	//  * 함수 명세signature가 같은 경우 overriding으로 판단한다. (= Java)
	//  * 함수명과 인자리스트(즉, header) 까지만 일치할 경우, 메소드 은닉hiding 된다.
    Plant Leaf
		// 생성자constructor: <타입명> ()
		// 객체가 생성될때 호출되는 메소드다. 다음의 규칙을 따른다.
		//	1. 생성자가 1개도 서술하지 않은 경우 인터프리터는 기본생성자를 만든다.
		//	2. inline 초기화가 끝난 뒤, 생성자가 호출된다.
		//	3. 부모클래스의 생성자를 명시적으로 호출할 수 있다.
		//	4. 부모클래스의 생성자를 명시하지 않으면 부모의 기본생성자가 호출된다.
		//	5. 부모생성자 호출 구문은 반드시 생성자 메소드 처음에 나와야 한다.

    	Leaf() {} // 별다른 서술이 없어도 인터프리터는 부모클래스Super의 기본생성자를
    			  // 호출한다.
		Leaf(int new) // 생성자에는 재정의 재지정을 넣을 수 없다. 순서는 정해져있다.
			Super("SuperLeaf") // 맨 앞에 와야 한다.
			age = new //

        str getName(): "Leaf" // overriding
        int _age = 3.5
        float getAge(): age // 반환형이 다르므로 은닉이다.

    void main()
        Plant p
        if 1
            p = Leaf(3)
       	console.("name=" + p.getName() + ", age=" + p.getAge())

// 결과: name=Leaf, age=3
```



##### 메소드 재정의 재지정

```cpp
import console

Person
	int print(int a): console.out("print(int a)"); return 0
	float print1(): console.out("print1()"); 2.5
	(int age, float grade) print2(): console.out("print2()"); return (24, 3.5)

Person Student
	int print(int a)
		int ret = me.Super(a) // me.Super(a)는 Person.print(a)와 같다. (추후 서술)
		console.out("Student.print(int a)")
		return ret

    // 재정의 재지정Redirection지정자: (반환값 이름=>) <함수 명세signature> (=>)
    // 메소드 재정의overriding의 실행 순서를 쉽게 표현할 수 있다.
    // 메소드 재정의는 원본 메소드Supermethod가 있던 자리에 다른 메소드로 
    // 덮어쓰는 것으로서, 재정의 한 메소드에서 원본 메소드를 호출 하게 되면 
    // 코드를 "추가" 하는 구현이 된다.
    // 이때 재지정 연산자는 원본 메소드를 시작하기전, 시작 한 후 2 곳에 걸쳐서
   	// 지정할 수 있다.
    
    // 다음의 규칙을 따른다.
    //	1. overriding 메소드에만 사용한다.
    //	2. => 는 "기반 클래스의 오버라이딩된 메소드로 이행"을 의미한다.
    //	   ( "me.Super(인자리스트)" 와 같다.)
	//	3. => 이 함수명에 대해 앞인가 뒤인가로 수행 순서를 결정한다.
	//        ( "=>" 반대편에 Super 가 붙는다고 생각하면 이해가 편하다.)
	//        e.g. => 이 함수명 뒤에 붙는 경우: 내꺼 실행 후, 부모꺼 실행.
	//                        " 앞        "      : 부모꺼 실행후, 내꺼 실행.

	// 이를 활용하면, 다음처럼 줄일 수 있다.
    ret => float print1()	// 재지정이 앞에 있으므로, 부모메소드가 먼저 호출된다.
    	console.out("Student.print1(), ret=" + ret)
    	return ret
    
	// 재지정이 뒤에 있는 경우, 메소드가 끝나면 주어진 인자리스트로
	// 그대로 부모메소드를 호출하고, 그 결과를 반환한다.
	(int age, float grade) print2() =>: console.out("Student.print2()")
    /* 이 코드는 다음과 동일하다.
    	(int age, float grade) print2()
    		console.out("Student.print2()")
    		return print2()
    	
       그리고, 다음과 같이 해도 된다.
    	(int, float) print2() =>
    		if true
    			return (0, 0.0)
    			
    		// 여기에 도달하면, 부모메소드의 반환값이 나간다.
    */


app
	void main()
		Student s()
		console.out("print()=" + s.print(1))
		console.out("print1()=" + s.print1())
		(int a, float g) = s.print2()
		console.out("print2()=" + a + ", " + g)

/* 결과:
	print(int a)
	Student.print(int a)
	print()=0
	print1()
	Student.print1(), ret=2.5
	print1()=2.5
	Student.print2()
	print2()
	print2()=24, 3.5
*/
```



##### 연산자 메소드

```cpp
import console

app
	void main()
		obj Number // 모든 클래스는 명시가 없어도 obj로부터 나온다.
			// 타입 별칭aka: <원본타입> aka <별칭타입>
			// 블록문 규칙에 의해 정의된 scope 내에서만 유효하다.
			int aka MyInt // MyInt 는 int와 동일하다.
			MyInt num

			// 기본 별칭 타입:
			// 모든 클래스는, 별도의 정의가 없어도 다음의 별칭을 갖고 시작한다.
			//	Number aka This
			//	object aka Super
			// 모든 메소드는 다음의 별칭을 갖고 시작한다.
			// 재정의된 메소드의 경우, <부모클래스의 메소드> aka super
			// <현재 실행중인 해당 메소드> aka me
			// <현재 실행중인 메소드를 소유한 객체> aka this
			
			// 연산자 메소드: <반환형> op<연산자기호><미리 정의된 인자리스트> { }
			// 할당연산자 오버로딩
            Number/*반환형은 변경될 수 있다*/ op=(#This rhs) =>
            	console.out("Number will be assigned to.")

            Number op+(#This rhs)
            	Number ret()
            	ret.num += rhs.num
            	return num

            // op+=, op-, op< 등 다수..

			This get(): this
			#This #get(): this
			res set(This)

		Number.num = 5
```


##### 상수와 캐스팅

```cpp
import console

Animal
    // 상수: # <타입>
    // prefix 중 하나로, #로 표현한다. (# 기호가 딱딱함과 고정됨을 연상시키기 때문이다.)
	//	1.	타입 앞에만 붙을 수 있다.
	//		다시말하면, Refer 항상 교체될 수 있으며, 이를 문법적으로 방지해주지 않는다.
	//  2.	prefix를 같이 표기하는 경우, 순서를 지켜야 한다. $#_ 순으로 표기한다.
	//  3.	void에 #을 붙일 수 없다.
    str #getName(): "unknown" // const 메소드.
    #int _age = 1
    int getAge(): _age
   
    #int $#_foo() {} // "static const protected method returning const int."
    // void #$_foo1() {} // 컴파일에러: Rule#2 위반
    void foo1() {}
    // void setAge(int new): age = new // 컴파일에러: age는 const 이다.
    void #walk(): console.out(age + "yo " + getName() + " walked.") // getName()이 const메소드가 아니었다면 에러였다.

Animal Beaver
    #str #getName(): "Beaver"
    void #walk()
        Super.walk() // Super는 기반클래스(Animal)로 캐스팅된 this를 의미한다.
                    // "Animal Super = this" 가 이미 선언된 것과 같다.
        console.out("Beaver's finding a seashell.")

app
    int main()
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

/* 결과:
	1yo Beaver walked
	Beaver's finding a seashell.
	1yo Beaver walked
	Beaver's finding a seashell.
*/
```



##### 타입 확장

```cpp
import console

// 타입 확장:
// worldlang은 이미 정의된 타입의 인터페이스를 확장(추가)할 수 있다.
// 이 모든 과정은 반드시 컴파일 타임에 확정되야 하며, 다음의 규칙을 따른다.
//	1. 총 3가지 방법이 있다. 상속(이전 섹션 참조), 타입확장문법, 인스턴스 확장문법
//	2. 확장문법은 크게 동일하며, 단, 아주 약간의 변화가 있다.
//		<타입> {
//			멤버(메소드, 변수) 정의
//		}
//		(즉, 이제껏 클래스 정의와, 메소드 안에서 변수 정의 모두 타입 확장문법이다.)
//
//	2.	클래스 확장class-extension: +<클래스>
//		미리 정의되어있는 클래스에 새로운 인터페이스를 주입한다.
//		다음의 규칙을 따른다.
//			a. 주입한 인터페이스 안에서 protected 멤버에 접근할 수 없다.
//				(캡슐화encapsulation를 깰 수 없기 때문이다.)
//			b. 은닉되지 않는다.
//			c. overriding 되지 않는다.
//
//	3.	메소드 또한 타입이다. 따라서 메소드 또한 메소드를 확장할 수 있는데,
//		이를 클로져라고 한다. (추후 서술)
+str
	str(#MyClass my) // 생성자
		console.out("str(#MyClass)")

MyClass
	// 4. 인스턴스-확장Instance extension: <멤버변수 정의> { <멤버 정의> }
	// 지정한 1개의 객체의 타입을 확장한 후, 즉시 정의한다.
	// 확장된 타입은 재사용할 수 없다.
	str name // 멤버변수 name 정의
        res set(#str new) { // overriding
        	console.out("name will be changed to " + new)
        	name = new // 에러. 컴파일은 가능하나, 무한 재귀 호출 된다.
        	return ok

	// 위의 str name {} 과 동일하다.
	str name1    
    	// 위의 res set(#str new)=>과 동일하다.
    	set=>: console.out("name will be changed to " + new)

    void print(): name1 = "hello"; console.out ("void print() : " + name1)
    int print(int a): console.out("int print(int)")
    //	name과 name1은 같은 set 메소드를 지니고 있으나, 이 둘은 별개의 메소드다.

	A // 여태까지의 class 정의도 사실은 확장문법이다.
		void $print()
			console.out("MyClass.A.print()") // A는 이제 print()를 갖게되었다.
			// 위의 str name1 케이스와 다를께 없다.


	// type변수:
	// type은 class들을 담을 수 있는 메타클래스 타입이다.
	type $C
		get: return A


MyClass.A a // 전역객체 a
MyClass.B b
// MyClass.C c // 컴파일에러: MyClass.C는 변수다.
type[] types = [MyClass().B, MyClass.C, MyClass.A]

+MyClass
	// int name1 // 컴파일에러 Rule#2: 중복 정의
	// float print(): console.out("float print()") // 컴파일에러 Rule#2: void print().
	// void print()와 float print()를 피호출자callee는 구분 할 수 없다.	
	float print(float a): console.out("name=" + str(this) + (str) this)


MyClass MyClass2
	(age, grade)=> (int, float) print(float a)
		console.out("MyClass.print(float) has been extended.")
		return (age, grade)

	/* 다음과 동일하다
    (int, float) print(float a)
    	(int age, float grade) = me.Super(a)
    	console.out("MyClass.print(float) has been extended.")
    	return (age, grade)
    */

app
	void main()
		MyClass me
		me.print()
		me.print(3.5)

/* 결과:
	will be changed to hello
	void print() : hello
	str(#MyClass)
	str(#MyClass)
	name=hellohello
	MyClass.print(float) has been extended.
*/
```



##### 프로퍼티

```cpp
import console

Person
	void print(): console.out("Person.print()")


app
	Person p1
	// 프로퍼티property: 타입 프로퍼티명 get <블록문> set <블록문>
	// 인스턴스 인터페이스 확장 문법을 사용해서 get, set 메소드를 확장하면,
	// 변수를 정의하는 대신, 변수처럼 동작하는 메소드 2개를 지닌 객체인 프로퍼티를
	// 만든다. 다음의 규칙을 따른다.
	//	1.	프로퍼티는 sharable 타입이다.
	//		refer로 감싸지지 않은 채 raw인 채로 멤버에 추가되기 때문에 직접 get, set을
	//		다룬다. 이 프로퍼티에 op=이 호출되면 set이 수행된다.
	//	2.	<Type> get(), <#Type> #get(), res set(#Type new) 3개의 메소드중 선택
	//		에서 오버라이딩 하면 프로퍼티로 인식한다. (set의 인자는 반드시 const
	//		이다.)
	//	3.	예외적으로 프로퍼티 선언과 인터페이스의 확장을 같이 할 수 없다.
	//		e.g.	app
	//	            	str _name
	//					str name
	//						void print(): console.out("extended")
	//						str get(): _name
	//				// 컴파일 에러: name은 print 인터페이스 확장과
	//				// 프로퍼티선언이 같이 됨
	//
	//			왜 같이 할 수 없는가:
	//			말이 안되기 때문이다. 인터페이스 확장된 타입을 정의한 곳과, 그
	//			인터페이스를 가지고 있어야할 객체를 반환하는 부분이 서로 독립적이다.
    //			객체를 반환하는 곳은 어떤 인터페이스가 확장되었는지 100% 알게 만드는
    //			방법이 없다. (인터프리터에 인공지능이라도 없는 한..)
	//	
	//	4.	프로퍼티에서 상속받은 중첩클래스를 정의하는 것이기에, 안에서
	//		정의된 get, set 메소드에서는 해당 프로퍼티를 소유한 클래스 scope를 갖는다.
	//	5.	<Type> get(), res set(#Type new)은 get, #get, set 으로 단축할 수 있다.
	//		set의 파라메터는 #This 타입에 new라는 변수명을 사용한다.
	//	6.	기본적으로 const get()은 get()의 반환값을 반환하도록 정의된다.
	//		즉, get()만 정의한 경우, const get() 따로 정의할 필요가 없다.
	//		또한 const get()만 정의한 경우는, get은 기본적으로 정의되기 때문에
	//		const get 만 가지게 된다. 따라서 외부에서는 항상 const get만 받게 된다.

	Person p2
		#get
			console.out("p2.get()")
			return p1

		res set(#Person new) // set {  과 동일하다.
			console.out("p2.set()")
			p1 = new;
			return rok() // rok는 타입이므로, return rok는 rok의 객체를 생성하는 것이
		 				 // 아닌, ok라는 타입을 반환한다는 뜻이된다.

	void main()
		//Person p3 = p2 // 컴파일 에러. p2은 항상 const Person으로만 나간다.
		p2 = p1

	B
	    // get: return A // "class" 는 타입을 정의하는 키워드이지, 타입 그자체가 아니다.
	    // 따라서 프로퍼티가 될 수 없다.

/*결과:
    p2.set()
*/
```



##### 클로저

```cpp
import console

app
	str(void) foo()
		// 클로져closure: <메소드 안에서 메소드를 정의한다.>
		// 메소드를 확장한 것을 클로져라고 한다.
		// 클로져는 관련 요소factor들이 캡처capture를 통해 내부로 함축한다. 
		// 인스턴스 메소드의 한 종류이나, 사용시에는 static 메소드처럼
		// 사용하게 되며, 일종의 외부로 늘어진 인터페이스로 만드는 것이 목표이다.
		//
		// 클로져는 다음의 특성을 갖는다.
		//	1. 자신을 포함하는 메소드outer-method와 지역변수local-scope를 공유한다.
		//	2. 중괄호 사용을 권장하지 않는다.
		//		앞서 서술했듯, 블록문에는 중괄호 사용이 원칙이다.
		//		하지만, 클래스와 그 멤버들direct members에게만 중괄호가 필수이며,
		//		그 이외의 경우인 메소드 안쪽에서는 편의를 위해 사용이 권장되지 않는다.
		//		메소드 안쪽에서는 편의를 위해 사용하지 않을 것를 권장한다.
		//	3. 	인터프리터는 해당 클로져의 구문을 파악하여 어떤 식별자를 캡처capture
        //		해야하는지 자동으로 파악한다.
		//	4.	클로져에 의해 캡쳐된 식별자는 클로져의 라이프 사이클과 동기화 된다.
		//		(즉, 지역변수일지라도 소멸되지 않는다)
		int sum = 0
		int add(int a, int b) // 클로져.
			sum = a + b // 클로져는 지역변수를 공유한다.


		// 함수 위임자delegator: <반환형>(<타입리스트>)
		// 메소드 또한 객체1st-class-citizen이며, 이에 대한 refer로 다룰 수 있다.
		//	1. 	refer와 메소드간 타입은 정확하게 일치해야 한다.
		//		묵시적형변환과 관계없다. 단, 반환된 값은 물론 묵시적 형변환이
		//		적용될 수 있다.
		//			e.g.	int foo(int) {}
		//					bool(int) fdelegator = foo // 컴파일 에러.
		//					int(int) fdel1 = foo
		//					bool res = fdel1(35) // ok.
		//	2.	복수의 메소드를 가리킬 수 있으며, +=, -= 연산자를 사용한다.
		//	3.	위임자를 호출시, 가리키는 모든 메소드가 호출된다
		//	4.	메소드를 -= 제거할때, 클로저에 내포된 객체도 동일해야 제거된다.
		//	5.	배열로써, 소유한 메소드를 순회할 수 있다.
		int(int, int) getClosure(): add
		
		int(int, int) fdelegate = int dummy(int a, int b) // 메소드에 대한 refer
			console.out("a=" + a + ", b=" + b)

		fdelegate += getClosure()
		// float(int, int) fptr1 = getClosure() // 컴파일 에러.
		// int(int, float) fptr2 = getClosure() // 컴파일 에러.
		if fdelegate(3, 5) == getClosure()(3,5)
        	MyClass // 중첩클래스.
        		int count = 0;
            	str(void) print(int(int, int) fdel)
                	str to_return() // 클로져를 반환하고 있다.
                		"answer to life the universe and everything is " + fdel(26, 16)

        	return MyClass().print(fdelegate)

        // else가 없으므로 명시적/묵시적인 return은 발생하지 않으며,
        // 반환형 str(void)의 기본값인 null이 유지된다.


    void main()
		str(void) fptr = foo()
		fptr()
        console.out("sum is " + sum)

/*	결과:
	a=3, b=5
	answer to life the universe and everything is 42
	sum is 42
*/
```



##### 예외처리

```cpp
import console
import file

Opener
	file f = null
	str path
		ret => @set
			// 예외처리try-catch: try <코드> catch(인자리스트) <코드>
			// 다음의 규칙을 따른다.
			//	1.	예외가 발생하면, 자동으로 throw 처리된다.
			//	2.	예외exception을 throw <변수> 를 하게 되면,
			//		해당 함수의 호출자에게로 돌아간다propagate.
			//		(1depth stack unwinding.)
			//	3.	처리되지 않은 예외를 받은 호출자(메소드 또는 블록문)는 먼저
			//		자신을 콜스택에서 제거하고, 자신이 소유한 적절한 catch 멤버를
			//		찾아 호출한다.
			//		(catch에서 다시 예외가 발생하면 호출자의 콜스택은 이미
			//		제거되었으므로 무한 재귀는 일어나지 않는다.)
			//	4.	3에서도 찾지 못하면 자동으로 다시 throw 처리된다.
			//	5.	최종적으로 처리되지않은 예외가 main()을 벗어나면
			//		프로세스를 중단한다.
			//	6.	catch에서 throw를 하지 않으면 예외처리를 처리consume했다고
			//		판단한다.
			f.close()
			f.open(new, "rw") // Rule#1, 2: 내부에서 fileexception이 발생한다.

			// Rule#3에 의해서 f.open()에서 발생한 익셉션은, path.@set() 메소드가
			// 소유한 catch() 함수 중 가장 적절한 인자를 가진 catch(fileexcept)로
			// 넘겨진다.
			catch(rfile e)
			     console.out("fail to open " + ret)
			     f.open(new, "rw") // 다시 fileexcept가 발생한다.
			     // Rule#1, 2에 의해 str.@set()을 호출한 foo()의 블록문으로 throw.

			catch(except e) // 눈치챘겠지만, 사실 catch 또한 클로져에 불과하다.
			     console.out("can't reach here.")
			     return ret // catch의 반환형은 외부메소드의 반환형(res ret)여야 한다.
			     // Rule#3: 여기서 return 되면 str.@set()에서 return 되게 된다.
			
			console.out("path is " + new)
			f.open(new, "rw") // Rule#3: 여기 예외도 catch(fileexcept)로 간다.
			return ret

		ret => @get
			consol.out("getting path(" res + ") from some Opener object.")
			return ret


app
    res foo()
        Opener o
		{ // 블록문의 명시적인 정의
			o.path = "/usr/bin/bash" // 최종적으로 fileexcept가 발생한다.

			catch(except e) // 이 블록문에서 나온 예외는 여기서 catch된다.
				console.out("oh dear.")				
				// 블록문이 종료된다.

			console.out("can't reach here.")
		}
    	console.out("can you see this?")
    void main():foo()

/* 결과:
	fail to open /usr/bin/bash
	oh dear.
	can you see this?
*/
```



##### 메타

```cpp
import console

Person
	void say(): console.out(" - I don't know my name.")

Person Chales 
	void say(): console.out(" - My name is Chales Lee.")

Person Park
	void say(): console.out(" - My name is Hoon Park.")


app
	main()
		type[] cls = [Person, Chales, Park] // 사실 class 또한 타입에 불과하다.
		for type e in cls
			console.out("\n" + e.name + " has " + e.subs.len  " children.")
			for var child in e.subs
				console.out("\n - " + child.name)
				console.out(" - " + e.size + " bytes. nd is sub of " + e.name + " ? -> " + ...
				child.isSub(e))

			// 객체 정의: e.instance() | e() | e.new()
			// 모두 node타입의("?") 객체를 반환한다.
			? instance = e.instance()
			Person p = instance // 이것과 위. 2줄은 컴파일 될 수 없다.
			p.say() // 위의 3줄은 e().say()와 같다.


/* 결과:
Person has 2 children.

 - Chales
 - 24 bytes. and is sub of Person ? -> true
 - My name is Chales Lee.

 - Park
 - 24 bytes. and is sub of Person ? -> true
 - My name is Hoon Park.

Chales has 0 children.
Park has 0 children.
*/
```


## 설문

이쪽에서 짧게 진행해주시면 됩니다.



## 끝

하고싶은 말이 더 많이 있지만 worldlang에 대한 주요 내용에 대한 소개는 여기까지만 해야할 것 같네요.

이 프로젝트에 관심있으시면 github(url) 한번 둘러보세요.



시간 내주셔서 다시한번 감사드립니다.

