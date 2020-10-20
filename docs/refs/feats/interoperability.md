# extends other languages

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

## 모듈 attach는 module manager에서 담당한다.

## 언어 별로 다양한 형태의 진입점을 갖는다.

* modulemanager는 각 언어별로 attacher를 가지고 있다.
* attacher는 built in 이다.
* attacher는 진입점에 접근할 수 있다.

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

## 자동으로 attach 된다.

* entrypoint가 필요없다.
* 각 Wrapper클래스는 static 변수가 init이 되면서 Class객체가 attach 되도록 구현되어야 한다.
* C++ API의 경우 따라서 attach가 따로 없게 한다.
