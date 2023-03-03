# type

## worldlang은 타입이 존재한다.

## type은 worldfrx에 type, ttype<T> 와 같은 컴포넌트로 구현된다.

## type은 monostate다.

## type은 C++의 RTTI를 제공한다.

* 부모 클래스 판단
* "is" 메소드가 여기서 구현

## type은 메소드콜의 인자의 verification에도 사용된다.

## type은 nativeType과 mgdType 2종류로 상속된다.

## mgdType은 origin객체를 반환할 수 있다.

## type을 정의하면 그것의 unique object가 그 type이름에 대신들어간다.

* 메소드도 마찬가지다.

## type에 대고 생성자를 호출하면 unique obj의 복제가 아니라 type의 복제가 된다.

## class란 native type 을 의미하며 meta 모듈에 의해 관리된다.

## meta pack

* 별도의 기반 모듈로써 native의 reflection을 담당한다.
* world에서 제공하는 메타 API의 backend 에 해당한다.

### unregister를 지원해야 한다.

* C-REPL 지원을 위해서 native 모듈도 붙었다가 떼어졌다가 된다.
* 따라서 native class 정보 또한 시스템에서 제거될 수 있어야 한다.

### 타입의 연관정보는 모두 meta 모듈에 의존한다.

### 매크로를 통해서 meta class를 생성할 수 있어야 한다.

* 이경우 프로그램이 시작하기 전에 자동으로 register를 한다.
* unregister는 자동으로 할수 없다.

### 사용자가 정의한 metaclass 객체를 생성/등록 할 수도 있어야 한다.

* 상속 기반이 아니라 객체 기반이어야 한다는 것이다.
* 물론 unregister도 가능해야 한다.

## 빌트인 타입

* 인터프리터가 인지하고 있는 타입을 빌트인 타입이라고 한다.
* 빌트인 타입은 다른 타입과 달리 인터프리터 연관된 이점 및 특징을 가진다.

### 종류
* primitive types: int, str, err, node, void, bool, flt
* containers: arr, list, map

### 빌트인 타입은 native로 편하게 접근할 수 있는 경로 제공되는 mgd object이다.

* 대부분 native 클래스로써 제공될 것이다. 인터프리터는 이 클래스의 객체를 생성하기만 하면 되므로 편리한 접근방법을 제시한 것이다.
* 반면, mgd Object라는 것은 일반적인 mgdObject가 가지는 특성을 그대로 가지고 있으며 world시스템 입장에서 봤을때는 이것인 mgdobject인지 native object 인지 구분이 가선 안된다는 것이다.
* 보통은 Object 클래스에서 상속해 native 클래스를 정의한 뒤, 시스템이 초기화되는 시점에 이 native 클래스들을 초기화화는 queue에 집어넣는 형태로 구현된다.
* 일반 mgdobject와 구분이 가면 안되기 때문에 엄연히 packd path 가 존재해야 한다. 
* 속도 최적화를 위해서 완전한 일반 mgd object 기반으로 만들지 않는 것이다.

### 사용성에 있어서도 mgd object와 native object는 차이가 있어서는 안된다.
* 이를테면 mgd object의 경우 다른 IDE는 source code를 보여주는 창을 띄워줌으로써 해당 타입에 어떠한 메소드들이 있는지를 보게 해준다.
* 이 예를 기준으로 한다면 native object도 소스코드를 보여주지는 못할지언정 마찬가지로 어떠한 메소드가 있는지를 IDE에서 동일하게 리스트로 보여줄 수는 있어야 한다.

## Type.getType() 은 자기 자신이 나와야 한다.
