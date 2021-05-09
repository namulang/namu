# 중첩 객체

* world는 중첩객체에 대해서 별다른 기능을 지원하지 않는다. 그냥 객체와 다를 게 없다.
```go
def A
    foo() void
    def B // 여기서 B와 A는 아무런 관련이 없다. foo()를 호출하려면 A객체가 필요하다.
```

## 중첩 객체를 지원하지 않는 이유는 무엇인가
* java처럼 중첩객체가 소유자 객체를 capture하는 식으로 지원하는데, 문제를 복잡하게 만든다. 예제를 보자.
```go
def A
    def B
        def C
def D A.B // 에러
def A2 A
    def D A.B // ok
```
* 예제에서 def D A.B와 같은 케이스는 컴파일 에러가 되어야 한다.
* 자바는 이러한 케이스를 다 계산한다. 그러나 굳이 지원하지 않아도 ptr를 직접 만들면 해결이 가능하고, 아니면 메소드내 객체방식으로 해결도 가능하다.
* namespace는 pack이라는 키워드가 있기 때문에 중첩객체의 필요성이 없다 (실제로 자바에서 namespace가 있는가?) 중첩객체를 써야하는 이유는 없는 것이다.
* C#, swift, python 모두 지원하지 않는다. java만 지원한다.

## 단, pack 만은 예외다.
* pack scope은 pack 밑의 origin 객체의 shared chain을 구성할때 밑에 깔리고 시작한다.

# 메소드 내 중첩 객체
* 메소드 내의 객체는 별도의 문법으로 취급한다. 별도의 origin, 별도의 복제방법
* 메소드 내에서 정의한 origin의 복제 객체는 생성시점의 모든 scope을 다 접근 가능한 상태가 된다. (= closure)
* 메소드 내에서 정의했으므로 private로 선언된다.
* 이 객체의 타입을 그대로 public API로 만들거나 외부에서 접근이 불가능하다.
* 외부에 이 객체를 public type으로 upcasting 해서 return 하는 것은 가능하다.
* 호출자의 scope을 생성자 안에서 알 수 있어야 한다.

## 메소드 내 중첩 객체의 origin 정의 알고리즘
* 일반적인 origin객체는 verify(binding) 시점에서 상속을 완성하면서 pack scope위에 각 객체의 shared scope 이 chain을 쌓기 시작하는데, 메소드 내 객체도 동일하게 진행한다.
* 완성된 origin 객체는 func의 shared 에 private로써 추가한다.
* protected 심볼을 public API의 반환형 및 인자로써 넣으면 verify시 에러로 간주해야 한다.
* 메소드 내의 origin 객체는 별도의 c++ 클래스로 표현한다. 일반적인 Origin 객체와는 달라야 한다.

## 메소드 내 중첩객체의 복제
* "메소드 내의 객체의 복제객체"는 일반 복제 객체와 동일한 클래스로 구성할 수 있다.
* 객체를 생성할때 일반 origin객체는 shared chain ref를 shallow cpy하고 NS 배열을 deepcpy하면 끝이다. 그러나 메소드 내 origin 객체라는 별도의 native c++ 클래스의 clone()을 수행할 때는 origin의 S chain을 순회하면서 pack scope을 제외하고 나머지 부분들의 chain copy를 deepcpy 한다.
* 이때 복제한 제일 첫번째 원소는 생성 시점의 현재 호출자 scope의 맨 뒤를 가리키도록 한다. NS는 deepcpy 한다. 다
* 호출자의 scope(= frame)을 알아내기 위해서 stackframe[1] 을 호출하면 된다. stackframe[0]은 생성자 자신의 scope이 할당되어있을 것이다.
* native 환경에서 clone()을 호출할 수 있어야 한다. native 환경에서 stackframe[1] 할때도 호출자의 frame이 반환되어야 한다.
