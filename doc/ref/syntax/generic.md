# generic

## C# 수준의 제네릭을 지원한다.

* 자바와 같이 꼼수로 처리하는 수준보다 뛰어나야 한다.
* 대체될 수 있는 타입의 빈공간을 파라메터로써 마련한 뒤에 컴파일이 종료되어야 한다.
* 제네릭 객체 자체는 사용자가 접근하지 못한다. 항상 타입파라메터를 채운 객체만 접근할 수 있다.

## 문법

```go
def (identifier)<(identifier)>
    ...
```

## unique 객체를 처음으로 접근한 순간 unique 객체가 생성된다.

## binding(=verification)은 unique 객체가 생성된 순간 처음으로 실시된다.

* 다시말해서 런타임에 verification이 발생할 수 있어야 한다.
* 사용자는 항상 디버깅 모드에 있기 때문이다.

## generic 객체는 일반 obj하고는 동작이 다르다.

* 객체로써 나오긴 하였으나 T가 들어가는 곳에 parameterizedType 배열의 인덱스의 접근하는 코드로 대신 채워진다.
* 완성된 unique 객체는 parameterizedType 배열에 T 원소를 채워넣는 것을 말한다.
* T가 채워넣어지기 전 generic에 접근한 경우 parameterizedType이 비어있으므로 동작에 실패한다.

## T는 동일한 클래스 계층이 아니어도 돌아갈 수 있어야 한다.

```go
def A
    foo(msg str) void
def B
    foo(msg str) int

def generic<T>
    elem := T()
    
    foo() void
        elem.foo("wow")

def app
    main() void
        generic<A>.foo()
        generic<B>.foo()

        generic.foo() // err
```

* 만약 elem.foo("wow")의 반환값을 처리하는 코드가 있었다면 generic<A>는 컴파일되지 않았을 것이다.

## generic은 인자T를 받아들여서 obj를 생성하는 간편 함수를 제공해야 한다.

## 기본 container 들 모두 namu 언어로 짜야한다.

* native binding API를 통해서 C++ container 등을 proxy 한다.

## 타입파라메터가 없는 generic 객체를 만들때는 verification은 하지 않는다.

## scope는 외부에서 제네릭객체에 접근한다는 사실을 판별해야 한다.

* 제네릭 객체에 접근하려고 하고 있으며, 그 generic 객체가 아직 없다면 새로 unique객체를 만들어야 하기 때문에.
* 혹은 generic 객체에 접근할때의 이벤트를 외부에서 cb을 받을 수있게 하거나.
