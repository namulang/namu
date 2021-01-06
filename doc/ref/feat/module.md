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

## module은 obj다.

## module은 자신의 shared scope을 중첩객체에게 포함시키는 유일한 객체다

* world는 중첩객체를 위해 특별한 동작을 하지 않는다. 중첩객체와 그것을 소유한 객체간에는 아무런 접점도 없다.
* 그러나 module만은 예외로써 module의 shared scope을 module밑에 놓인 객체와 그것의 모든 중첩객체는 반드시 module의 shared scope을 공유해야 한다.
* 모든 origin 객체는 반드시 1개의 module을 지녀야만 한다.

## module 키워드 뒤에 나온 것이 module 객체의 이름이 된다.

## .wrd 파일은 module의 직접적인 sub가 된다.
* .wrd 파일에는 반드시 1개의 module 키워드를 넣어서 이 파일이 어떠한 모듈의 일부분인지를 표시한다.
* .wrd 파일 밑에 나오는 origin 객체, 전역변수, 함수는 모두 module에 바로 직속한 것이 된다.
* 따라서 .wrd 파일 안에 바로 함수를 적는 것이 허용된다.
