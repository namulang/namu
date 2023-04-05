# chain

* C-REPL를 달성하기 위해서 정적언어이지만 동적으로 타입이 쉽게 변경될 수 있는 유연한 구조를 가져야 한다.
* 이를 위해서 각 객체의 scope을 쉽게 bind 하기 위해 chain 이라는 자료구조를 정의한다.
* 이 자료구조는 이미 시스템에 존재하는 chain 위에 새로운 scope 객체를 쉽게 얹을 수 있어야 한다.
* 이때 각 객체의 scope의 변경이 발생하면 chain 또한 동기화가 즉각되어야 한다.
* 시나리오 검증을 통해서 chain의 뒤에만 추가가 일어나는 FILO 구조면 충분하다.

## chain은 linked list의 Node다.

* Linked list는 본래 Node 라고 하는 중첩객체를 연결하고 HEAD를 가리킴으로써 구현하곤 한다.
* chain은 이 Node를 그대로 자료구조로써 사용하는 것이다.

## 각 chain은 container를 binding 한다.
* next, container 2개의 subs가 핵심 객체다.

## chain은 pushBack이 매우 빠르다.

* linked list의 add를 구현하듯, 새로 만든 chain 객체의 next가 이미 있는 chain을 가리키도록만 하면 bind가 완료된다.

## chain은 동기화 비용이 없다.

* 먼저 생긴 객체의 container의 변경이 생겨도 chain과 그 chain을 가리키는 chain은 어떠한 수행도 없이 동기화가 유지된다.

## FILO 구조다
* 그러나 만약 새로만든 객체를 이미 만든 chain객체 앞에 넣고자 하는 경우 chain 객체를 deepcpy해야 한다.
* chain객체를 deepcpy하는 것이지, chain 객체의 container를 deepcpy하는 것이 아니다.
* 이때 복제된 chain객체는, 런타임에 구성이 바뀌어도 (container가 아니라 chain 객체가 다른 객체를 가리키는 등의 "chain객체"의 구성이 바뀌는 것) 원본의 데이터에는 영향을 주지 못한다. 다행히 worldlang 인터프리터에는 이와 같은 동기화 비용을 요구하는 시나리오는 없다.

## chain은 단방향 linked list 다.

* 새로 생긴 객체가 먼저 생긴 객체에 접근 가능하다.
* 먼저 생긴 객체일 수록 자신을 참조하는 많은 객체를 거느리는 구조가 된다.
* 이는 프로그래밍 언어를 구현할때 인터프리터가 관리해야 하는 수많은 객체(pack, main, object, func 등)의 scope이 형성/조합되는 구조와 잘 부합한다.

## chain의 임의접근은 항상 O(n) 복잡도다.

* 탐색이 쉽지 않다.

## 사용자는 chain의 node가 아니라 array 와 같은 구조로 되어있다고 생각하게 만들어야 한다.

## chain은 2depth까지 지원한다.

* chain은 본래 array를 품고 있는 것이지만, 또다른 chain을 품고 있을 수도 있다.
* 1depth가 array만 품고 있는 chain을 연결한 것을 의미하다고 했을때 chain은 2depth까지 지원한다.
    * nchain<T> 은 array를 포함할 수 있는 일반적인 chain이다.
    * ndeepChain<T> 은 일반 nchain<T>을 포함할 수 있는 chain이다.

## 3 depth부터는 iteration이 동작하지 않는다.

## ndeepChain<T>는 2가지 변수를 갖는다.
* nChain<T>는 Chain* next, ncontainer라는 변수 2개만 있으면 된다.
* ndeep는 Chain* next, nChain* bean 이라는 변수 2개가 필요하다.
* bean에는 포함할 다른 2depth nchain이, next에는 1depth 다음 chain이 들어있다.

## ChainIteration::next() 알고리즘
* nchain<T>은 _nextChain(ChainIteration&) = 0; 이라는 pure virtual 을 가진다. 이 함수는 
  인자로 주어진 ChainIteration을 하나 움직인다.
    * _nextChain()은 nChain과 ndeepChain이냐에 따라서 동작이 다르다.

* ChainIteration은 nchain* face, nchain* bean 2개의 변수를 갖는다.
* ChainIteration::get() 은 *bean 을 한다.
* ChainIteration::next() 에서는 face->_nextChain(*this) 를 수행한다.

* nChain::_nextChain(ChainIteration& e) 에서는,
```cpp
e.face = e.face->next;
e.bean = e.face;
```

* ndeepChain::_nextChain(ChainIteration& e) 에서는,
```cpp
if(e.bean == e.face)
    e.bean = this->bean;
else
    e.bean = e.bean->next;
if (!e.bean) {
    // nmonoChain과 동일하다:
    e.face = e.face->next;
    e.bean = e.face;
}
```

## 잘 구성하면 ndeepChain은 nChain에서 상속받게 할 수 있을 것이다.

## ndeepChain을 iteration으로 탐색시에는 1depth chain과 비교했을때 퍼포먼스 차이가 거의 없다는 것이 특징이다.

## ndeepChain으로 임의 접근을 하는 경우에는 물론 2번 접근이 필요하므로 배로 느리다.

## chain은 element 별 iterator와 container 별 iterator 2개를 제공할 수 있어야 한다.
