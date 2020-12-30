# 빌트인 타입

* 인터프리터가 인지하고 있는 타입을 빌트인 타입이라고 한다.
* 빌트인 타입은 다른 타입과 달리 인터프리터 연관된 이점 및 특징을 가진다.

## 종류
* primitive types: int, str, err, node, void, bool, flt
* containers: arr, list, map

## 빌트인 타입은 native로 편하게 접근할 수 있는 경로 제공되는 mgd object이다.

* 대부분 native 클래스로써 제공될 것이다. 인터프리터는 이 클래스의 객체를 생성하기만 하면 되므로 편리한 접근방법을 제시한 것이다.
* 반면, mgd Object라는 것은 일반적인 mgdObject가 가지는 특성을 그대로 가지고 있으며 world시스템 입장에서 봤을때는 이것인 mgdobject인지 native object 인지 구분이 가선 안된다는 것이다.
* 보통은 Object 클래스에서 상속해 native 클래스를 정의한 뒤, 시스템이 초기화되는 시점에 이 native 클래스들을 초기화화는 queue에 집어넣는 형태로 구현된다.
* 일반 mgdobject와 구분이 가면 안되기 때문에 엄연히 moduled path 가 존재해야 한다. 
* 속도 최적화를 위해서 완전한 일반 mgd object 기반으로 만들지 않는 것이다.

## 사용성에 있어서도 mgd object와 native object는 차이가 있어서는 안된다.
* 이를테면 mgd object의 경우 다른 IDE는 source code를 보여주는 창을 띄워줌으로써 해당 타입에 어떠한 메소드들이 있는지를 보게 해준다.
* 이 예를 기준으로 한다면 native object도 소스코드를 보여주지는 못할지언정 마찬가지로 어떠한 메소드가 있는지를 IDE에서 동일하게 리스트로 보여줄 수는 있어야 한다.
