# pack

## worldlang interpreter에서 attach 할 수 있는 AST 패키지를 pack이라고 한다.

## C pack, C++ pack, worldlang pack 여러가지가 있다.

## 확장자는 wmod

## 팩 식별자

* 고유의 팩을 식별하기 위해서 다음의 구성을 사용한다.
* pack는 여러개가 붙을 수 있다.

    <id>.<pack>.<objname>
    kniz.example1.consoleTest
    kniz.example1.demo1.situ1.test2.consoleTest2

## id는 고유한 것이다.

* worldlang site에서 등록해야 한다.
* 등록 방법은 비밀번호와 id만 묻는 것으로 간단하다.
* 등록된 id로만 worldlang store에 팩을 등록할 수 있다.
* 등록된 id로만 이 팩이 verified 된 것인지 보장할 수 있다.

## pack은 obj다.

## pack은 자신의 shared scope을 중첩객체에게 포함시키는 유일한 객체다

* world는 중첩객체를 위해 특별한 동작을 하지 않는다. 중첩객체와 그것을 소유한 객체간에는 아무런 접점도 없다.
* 그러나 pack만은 예외로써 pack의 shared scope을 pack밑에 놓인 객체와 그것의 모든 중첩객체는 반드시 pack의 shared scope을 공유해야 한다.
* 모든 origin 객체는 반드시 1개의 pack을 지녀야만 한다.

## pack 키워드 뒤에 나온 것이 pack 객체의 이름이 된다.

## .namu 파일은 pack의 직접적인 sub가 된다.
* .namu 파일에는 반드시 1개의 pack 키워드를 넣어서 이 파일이 어떠한 팩의 일부분인지를 표시한다.
* .namu 파일 밑에 나오는 origin 객체, 전역변수, 함수는 모두 pack에 바로 직속한 것이 된다.
* 따라서 .namu 파일 안에 바로 함수를 적는 것이 허용된다.

## pack 키워드 또한 srcframe에 origin, 커스텀 func 들을 넣어두는 역할을 수행하는 것이다.
* pack은 객체다.
* pack의 S에는 팩 공통 API가 들어간다.
    * getPath()
    * getName()
* NS에는 pack 만의 커스텀 필드/func가 들어간다.
    * origin 객체, func
* 이 NS를 srcframe에 넣어두는 것이 pack 키워드의 역할이다.

## src frame이란 SrcFile 객체가 들고 있는 chain을 말한다.
* 객체다.
* S에는 SrcFile 공통의 API가,
* NS에는 이 srcFrame에서 정의된 pack 키워드와 import 문들을 위한 scope들이 들어가 있다.
* origin 객체가 생성될때 자신이 어느 srcFile 객체로부터 나왔는지를 trace 할 수 있어야 C-REPL을 달 성할 수 있다.

## pack은 여러개의 진입점을 가질 수 있다.
* world lang은 java의 native와 같은 키워드를 갖고 있지 않다.
  이 말은 하나의 pack에 native객체와 mgd 객체가 혼재해 있을 수 있다는 말이된다.
* 하나 pack의 객체로 부터 origins를 빼오는 주체를 extraction이라고 한다.
* 여러가지 extraction 들이 predefine 되어있으며 각각 다른 언어체계로부터 origin 객체를 빼온다.
* 한번 추출된 origin 객체는 언어의 관계없이 동일한 API 구성을 가지므로 호환성에 문제 없다.

## packLoader는 init() 시에 pack을 1차로 load 한다.
* pack은 manifest 파일, 각 entrypoint 별 load할 origin 객체들로 구성되며 1개의 파일로 배포된다.
* pack은 'wpak' 확장자를 갖는다.
* packLoader는 지정한 path에 있는 pack을 재귀적으로 탐색한다.
* 탐색한 pack의 manifest 파일만 읽는다.
    * manifest 에는 pack의 기본적인 정보와 pack path와 읽어야할 entrypoint가 기록되어있다.
    * packLoader는 이시점에서 pack객체를 만들고 path와 매핑만 해둔다.
* pack객체는 subs()를 처음 호출당하면 lazy하게 entrypoint들로부터 origin 객체를 extraction 시도한다.
* entrypoint 갯수만큼 여러개의 extraction 들이 수행될 수 있다.

## packLoader는 다양한 extraction을 가지고 있다.
* c++ extraction, mgd extraction, c# extraction 등

## packLoader는 subs()로 자신의 origin 객체들, 즉 pack을 반환할 수 있다.

## packLoader는 chain 구조로 되어있다.
* obj이므로 당연하다.
* 1개의 packLoader는 다른 packLoader 객체를 link 할 수 있어야 한다.

## mgd extraction은 interpreter 객체를 통해서 origin 객체 배열을 뽑아낸다.
* extraction은 interpreter에게 해석할 파일들을 전달하면서 link할 defaultPackLoader도 같이 넘긴다.
* interpreter는 packLoader객체를 하나 만들고 넘겨받은 packLoader객체를 link한다.
    * 이 packLoader는 subs()에서 defaultPackLoader의 것들까지 포함해서 반환할 것이다.
* interpreter가 추출한 origin 객체들은 모두 생성한 packLoader의 container에 넣는다.
    * link()의 packLoader에 넣는게 아니다.
* 1차로 추출된 이후, verification 한다.
    * packerLoader의 container 부분만 검증한다.
    * scope을 찾을때는 packLoader.sub()를 검색하므로 defaultPackLoader.subs()도 검색하게 된다.
* 이상이 없다면 packLoader의 container 부분을 defaultPackLoader에 add한다.

## app도 pack이 될 수 있다. pack을 모듈로 사용하던 app으로 사용하던 차이가 없다.
* 내부적으로는 2개 모두 pack으로 취급한다.
* main()이 있으면 먼저 main() 실행한다.
* 2개 모두 동일하게 packLoader로부터 읽혀진다.
* 2개 모두 동일하게 manifest를 먼저 읽는다.
* 즉, project == app 또한 packLoader가 읽어들인다.

## main()이 담긴 pack을 배포할수 있다.
* android를 떠올려보면 java main()이 android sdk 안에 있다는걸 알 수있다.
  이와 같은 pack이 될 것이다.

## 클래스는 항상 어떤 pack 안에 있다.
* 동일한 pack 내에 다른 클래스를 사용할때는 with(== import)를 하지 않아도 되는 이유는,
  2개가 같은 pack scope안에 있기 때문에 불과하다.
* 다른 pack안에 있는 클래스를 접근할때에는 pack을 먼저 접근하는 것이 원칙이다.
* 그러나 매번 이렇게 하면 힘드므로 with 문을 주로 사용한다.

```namu
// myapp pack scope:
mymodule.person.foo() // 1

    with mymodule
    person.foo() // 2
```

* interpreter는 시작시 mymodule을 pack의 scope에도 넣어둔다.
* filescope은 packscope을 link 시킨다.
* filescope에 import가 나올 경우 이 pack의 subs()를 모두 filescope에 추가해둔다.
* 이미 다른 문서에서 언급했다시피 동일한 frame 객체 내에 2개 이상의 이름이 verify단계에서 검출하면
  에러다.
* 실제 runtime에서는 가장 먼저 이름과 일치하는 객체로 바로 실행한다. 2개 이상의 이름이 있는지 verify
  를 하지 않는다.

