# Interoperability 

## 다른 언어로 모듈을 작성할 수 있도록 API를 제공하는 것이 목적이다.

## 타겟언어를 worldlang에 맞출것인지, worldlang을 맞출것인지 2가지 방향이 있다.

* worldlang을 맞춘다는 것은 타겟 언어 빌트인 타입대신,  worldlang frx의 타입을 사용한다.
    * Py_ C API, JNI가 여기에 해당한다.
    * 각 언어의 특색이 전혀 반영되지 않는다. (기본 타입, 메소드 콜, 상속, OOP 등)
* worldlang에 맞춘다는 것은 worldlang 문법과 유사한 형태로 API를 구성하는 것이다.
    * Boost python, pybind가 여기에 해당한다.

## worldlang에 맞추는 방향으로 API를 구성한다.

* 물리적으로 불가능한 경우가 있다.
    * 타겟 언어자체가 OOP를 지원하지 못할 경우 등
    * 불가능한 경우는 worldlang을 맞춘다.
    * C API

## 모듈 단위로 각 언어는 바이너리를 배포한다.

## 모듈 attach는 pack manager에서 담당한다.

## 언어 별로 다양한 형태의 진입점을 갖는다.

* packmanager는 각 언어별로 attacher를 가지고 있다.
* attacher는 built in 이다.
* attacher는 진입점에 접근할 수 있다.

## namu 파일 안에서 다른 언어의 메소드를 직접 호출 할 수 없다.

* 그러나 다른 언어로 빌드 > AST의 형태로 모듈매니저가 import > import 한 것을 namu 소스코드 내에서 메소드 콜
  이러한 흐름은 물론 가능하다.

## java와 같이 native 메소드를 namu 안에서 정의할 수 없다.

* 이는 간결한 문법을 유지 하기 위한 것이다.
* native 메소드를 놓고 여기서 namu클래스를 상속해서 일부 메소드만 native를 사용하는 효과를 내는 것은
  추천하지 않는다.
  * 대신 작은 helper native 클래스를 만들고, 이를 redirection 하는 식으로 namu 클래스를 만드는 것이 더 좋다.
  * 물론 helper native클래스는 package class여야 한다.

## 하나의 패키지는 여러가지 언어로 작성될 수 있다.

* 예를들어
    * .namu 와 .c 로 작성된 패키지가 있다면 .c를 위한 C API entrypoint에서 .c로 빌드된 ast를 가져온다.
    * .namu 파일은 모듈매니져가 .namu 파일을 위한 entrypoint에서 가져온다.

## 일단 모듈이 attach가 되면 결국은 AST 구조로 나온다.

* world interpreter입장에서는 언어에 관계없이 결국 똑같은 것이다.

## 따라서 Bridge API는 attach 가능한 AST 구조를 build 하는 데 있다.

## 언제든 모듈의 detach/reattach가 가능해야 한다.



# C++ Bridge API

## 가장 기본이 되는 API이다.

* worldlang이 C++로 구성되어있기 때문에.
* 기본 native library가 C++로 만들어질 예정이다.
* 완성도에 신경을 써야 한다.

## Worldfrx에서 사용하는 API를 대부분 그대로 사용한다

* worldlang 내부에서 사용하는 접근, 메소드콜, 제어 API를 그대로 사용할 수 있다.

## worldlang에 C++ 언어가 맞춘다.

* 앞에 있는 내용이지만 중요하므로 2번 서술하였다.
* 예제
```c++
class Demo
{
public:
    void sayHello(const char* message) {
        ....
    }

    int get();
    void set(int n);
};

WRD_BRIDGE_CPP(....) {
    return def(...)
        .func(....)
        .property(...)
        .property(..., &get(), &set())
};
```

## Wrapper는 wobj의 상속관계에 있어야 한다.

## Wrapper는 wrapping하는 객체와 상속관계에 있어서는 안된다.

## Wrapper에서 wrapping하는 객체를 꺼낼 수 있는 건, 시스템 뿐이어야 한다.

## worldlang에 pointer가 나와서는 안된다.

* boost python 처럼 python 코드에 pointer 관련 함수 / 캐스팅 / 연산이 나오면 잘못된 것이다.
* 귀찮더라도 사용자가 wrapper를 짜는게 맞다.
* 타겟언어야, 니가 worldlang에 맞춰라.

## entrypoint가 필요하다.

* origin객체를 내보내도록 한다.

# 마샬링

## 마샬링은 지원한다.

* 마샬링이란 input으로 worldlang type --> C++ type 혹은  worldlang type <-- c++ type 의 변환을 말한다.

## 마샬링 목록은 런타임에 확장되지 않는다.

## T가 worldlang의 immutable일 경우 non const T* <--> T는 지원하지 않는다.

* const T* <--> T는 지원한다.
* 단, const void*는 예외로 지원하지 않는다.

## T가 worldlang의 mutable일 경우 T* <--> T를 지원한다.

## Methodwrapper는 복수개의 반환이 가능해야 한다.

* primitive T* 같은 경우 마샬링이 안된다. 사용자가 list로 반환해야만 한다.

## primitive에 대해 마샬링을 지원한다.

* wint <--> int, unsigned short int
* wint64 <--> long long, unsigned int, int64, wint64_t
* wint16 <--> short int, unsigned char
* wint8 <--> char
* wflt <--> float
* wflt64 <--> double
* wstr <--> const char*, std::string
* wT <--> 위 primitive 들의 const T*

## T** 도 지원하지 않는다.

## primitive 중 mutable 타입에 대해서 지원하지 않는다.

* primitive에 대한 모든 pointer
* string <--> char* 도 지원하지 않는다.
    * worldlang에서 str은 immutable이기 때문이다.

## mutable인 T가 node에서 상속받은 경우 마샬링을 지원한다.

* 각 "T*" 타입은 "T"로 마샬링을 지원한다.
* "T" <--> T by Wrapper<T> // Wrapper<T*>에서 객체를 clone하는게 추가된다.
* "T" <--> T* by Wrapper<T*> // Wrapper<T*>는 기본이 된다.
* "T" <--> T& by Wrapper<T&> // Wrapper<T*>에서 역참조가 추가된다.

## T에 대해서 Wrapper<T>로 반환하는 경우 사용자는 복사생성자를 T에 define해야 한다.

* clone을 사용하기 때문에.

## T가 node와 상속관계가 아닐 경우 지원하지 않는다.

* T*, T&도 마찬가지다.
* 직접 다른 타입으로 변환하는 wrap 메소드를 작성해야 한다.

## worldlang 문법상으로  T* <--> T로 변환할 수 없다.

* 캐스팅 안된다.
* 마샬링, as, cast 등은 가능하다. 다만 이것들은 native(c++)에서 일어나는 일이다.

## def(), func()에 람다도 넣을 수 있게 해달라.

* wrapper를 직접 사용자가 작성해야할 경우가 있을 것이다.
* 만약 native 타입 T가 라이브러리 클래스라면 wrapper 클래스가 2개가 된다.

## 사용자가 작성한 Wrapper 안에 매크로를 넣도록 할 수 있을까?
```cpp
// Boost코드를 참고함.
class My : public obj {

  WRD_DEF(My) {
      def()
          .func(&My::sayMsg)
  }

  void sayMsg(str msg) {
    cout << msg.toStr() << "\n";
  }

};
```

* 사용자가 wrapper 클래스를 작성할 가능성이 높다.
* wrapper 클래스가 계층도에 2개 나오지 않도록 하고 싶다.


## Wrapper는 Ref<T>로 반환해야 한다.

* 값으로 넘겨야 하는 경우 인스턴스 free를 해줘야 하기 때문이다.
* 자세히 설명하면
    * Wrapper 즉, mashaling객체는 native메소드를 wrap 한 메소드객체 내에서 사용될 것이다.
    * mashaling객체는 메소드 인자갯수만큼 미리 생성될 것이며
    * 각 인자 타입과 byval이냐 bypointer이냐에 따라서 객체를 생성해야 하는지 혹은 단순히 redirection만 하면 되는지도 정해져서 객체로 만들어져 있을 것이다.
    * Wrap한 메소드는 범용적으로 설계될 것이므로 각 mashaling객체가 값으로 반환해야 하는지는 알 수 없다.
    * mashaling은 일단 한번 변환이 끝나면 이후에 다시 process할 기회가 없다.
    * 따라서 반환값 자체가, 자신이 byval일 경우 알아서 소멸되어야 한다.
    * 즉, Ref다. mashaling객체는 자신이 byval로 넘겨야 할때는 clone을 해서 넘겨주면 된다.

## worldlang 타입을 C++ 메소드에 인자로 넣어도 호환이 가능하다.

* T <--> T
* wint <--> Wrapper<wint>
* 최적화를 한다면, 아예 마샬링을 건너뛰게 하면 좋을 것이다.

## 반환형을 wlist, warr 등으로 사용자가 직접 작성할 수도 있어야 한다.

## Closure 객체도 인자로 사용할 수 있다.

* 함수포인터를 대체할 것이다.
* Closure의 인자 체크로 메소드콜의 verification 과정에 포함되어야 한다.

## Wrapper의 연산자 오버로딩은 지원하지 않는다.

* native 타입 T의 연산자 오버로딩은 해도 된다.
    * 어짜피 C++에서만 사용 가능한 것이다.

## Wrapper를 worldlang에서 상속이 가능해야 한다.

## 메소드 wrapper를 override 할 수 있어야 한다.

## 메소드 콜시 node.run() 메소드를 사용하도록 유도해야 한다.

* 직접 C++에서 콜을 하도록 유도하면 override가 동작하지 않게 된다.

