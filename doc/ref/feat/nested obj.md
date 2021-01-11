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
* namespace는 module이라는 키워드가 있기 때문에 중첩객체의 필요성이 없다 (실제로 자바에서 namespace가 있는가?) 중첩객체를 써야하는 이유는 없는 것이다.
* C#, swift, python 모두 지원하지 않는다. java만 지원한다.

## 단, module 만은 예외다.
* module scope은 module 밑의 origin 객체의 shared chain을 구성할때 밑에 깔리고 시작한다.

