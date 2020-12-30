# module

## worldlang interpreter에서 attach 할 수 있는 AST 패키지를 module이라고 한다.

## C module, C++ module, worldlang module 여러가지가 있다.

## 확장자는 wmod

## 모듈 식별자

* 고유의 모듈을 식별하기 위해서 다음의 구성을 사용한다.
* package는 여러개가 붙을 수 있다.

    <id>.<package>.<objname>
    kniz.example1.consoleTest
    kniz.example1.demo1.situ1.test2.consoleTest2

## id는 고유한 것이다.

* worldlang site에서 등록해야 한다.
* 등록 방법은 비밀번호와 id만 묻는 것으로 간단하다.
* 등록된 id로만 worldlang store에 모듈을 등록할 수 있다.
* 등록된 id로만 이 모듈이 verified 된 것인지 보장할 수 있다.

