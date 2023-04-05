# reference 

## Ref 클래스가 담당한다.

## Strong 바인딩을 표현한다.

## Node의 일종이며 proxy로 동작한다.

## 컴파일러는 mutable 변수를 발견하면 이 Ref를 member로 등록한다.

## 컴파일러는 immutable 변수를 발견하면 그 변수를 직접 member로 등록할 수 있다. (안해도 동작에는 차이가 없다)

## Ref는 Node 타입이면 무엇이든 바인드 할 수 있어야 한다.

## Ref는 getType()이라는 verify용 함수가 있다.
* TVarRef<T>는 getType()을 고정된 TClass<T>로 반환한다.
* GVarRef는 getType()을 변수로 제공한다. 컴파일러가 생성할 수 있도록. 

## verify는 RTTI를 사용하는 것이다.
* 바인딩된 객체가 getType()과 자식 혹은 동일한 타입인지를 체크한다. 

## 메소드에 대한 참조자는 FuncRef 라는 별도의 클래스를 상속받아 사용한다.
* 메소드의 경우에는 상속으로 체크할 수 없고, 인자의 종류와 갯수가 정확히
  일치하는 지를 기준으로 verify 해야 하기 때문이다.'
* 인자의 종류가 정확히 일치해야 한다. 묵시적 변환 같은 것 허용하지 않는다.

## ref의 native 환경에서의 역할

* ref의 존재 의의는 scope에 들어간 mutable 객체의 assign()을 자동으로 지원하기 위해서다.
* mutable 객체가 scope 밖에 있는 경우는 우리의 관심사가 아니다. scope 안에 있는 것들만이
  scope을 넘나들면서 영향을 끼치기 때문에, scope 안에 있는 케이스만 생각한다.
* scope에 들어간 참조자 a가 A를 가리키고 있는 상황에서 B를 가리키도록 변경하고자하는 상황은 매우 다발한다.
* 이때 이를 구현하는 방법은 2가지인데,
    - 1. a를 포함하는 배열에 접근해서 set(인덱스, b) 를 한다.
    - 2. a의 ptr를 B로 변경한다.
* 1번의 경우 항상 container의 참조도 같이 가져가야 하기 때문에 효용성이 떨어진다.
* 2번의 경우 말이 ptr로 써놓은 것이지 배열의 원소 자체가 이미 void*처럼 되어있기 때문에
  별다른 처리가 없다면 1번과 다를게 없다.
* 그러나 namu는 container로 tnarr를 쓰고 있으며 이것은 str 바인더를 값으로 갖는 배열이다.
* 때문에 tnarr[인덱스]에 있는 바인더가 내부에 갖는 ptr를 변경하면 목적을 달성할 수 있다.
* 문제는 바인더는 보다 lowlevel 한 layer에 있는 package이기 때문에 node가 아니다.
  그래서 node를 다루는 범용 메소드들에 바인더를 넣는 게 불가능하기 때문에 이를 처리하려면
  바인더용 로직을 수없이 만들어야 해서 로직이 중복된다.
* 다른 해결방법은 node에서 상속받아서 바인더로 delegation 하는 클래스를 만드는 것이고
  이게 바로 ref다.
* 객체의 set은 평가전략과 직결되는 문제로써, by sharing(by object) 를 구현하기 위해서는
  immutable 객체는 객체간에 직접 할당이 되어야하고 mutable 객체는 참조자만 변경되면 된다.
* 이때 모든 mutable 객체를 ref에 감싸서 배열에 넣고, assign()이라는 공통 함수를 node에 구현한다.
  그리고 ref.assign()은 들어있는 타입이 mutable일때 참조자만 변경한다.
  그리고 immutable.assign()은 자신을 주어진 객체로 진짜로 복제한다.

* ref와 node.assign()으로 1. immutable/mutable에 따른 평가전략 구현과, 2. property의 구현을 위한 API
  2개를 모두 구현할 수 있다.
