# pack import

## 다른 언어와 다르게 namu는 import를 명시적으로 할 필요가 없다.

* interpreter가 시작 하기 전에 지정한 디렉토리를 재귀탐색해서 pack 파일을 찾아 pack객체를 생성해둔다.
  이 시점에서 pack load가 시작된 것은 아니다.
* pack 객체에 접근해서 subs()를 시도한 순간 packloading이 시작된다.
* verification시 코드의 모든 subs()를 검증하므로 링킹에러가 있을 경우라도,
  import 키워드 없이 런타임 전에 알 수 있게 된다.

## 단, verification이 끝난 이후 dependency check loop을 돌아야 한다.
* 예를 들어, mypack 이라는 pack은 file이라는 pack에 의존하며, 반대도 그러하다고 하자.
    * mypack을 verification을 하게 되었고 file pack.subs()를 요청한다.
    * file pack은 mypack.subs()을 요청하였고 mypack은 검증중이기 때문에 subs()를 일단
      그대로 반환하여야 한다.
    * file은 mypack의 목록을 정상적으로 받아서 검증을 완료한다.
    * mypack은 이후 검증을 계속하다가 자신의 에러코드에 의해서 검증실패 된다.
* 위의 경우, mypack은 '실패'라는 걸 알 수 있지만, 실패한 mypack을 참조하는
  file pack 또한 '실패'라는 걸 알순 없다.
* 이를 해결 하기 위해서 다음과 같은 로직을 추가한다.
    * subs()를 호출당하면 AST Parsing을 한다.
      이후 verification을 돌게 되는데, 도중에 이 객체로 subs()를 다시 호출당하면
      정상적으로 객체가 반환되도록 한다.
      (무슨 말이냐면, verification이란 타 pack의 검증되지 않은 AST 구조체에 대해서만 보장 가능한
       단계라는 뜻이다. 이 단계는 모든 AST가 올바르다고 전제하에 돌리는 것으로,
       다른 pack이 만들어진 AST 구조체가 사실은 실패하더라도 이것을 알아챌 수 없다.)
    * verification 도중 다른 pack을 참조하는 expr이 발견되면 해당 pack의
      'dependents' 리스트에 이 pack의 참조를 추가한다.
        * 이 참조하는 expr은 매우 다양한 종류가 있다. (상속, 접근, aka, ...)
        * 모든 expr을 다 찾아야 하므로 세심한 주의가 필요하다.
    * 모든 pack과정이 끝나면 dependency check 단계를 수행한다.
      packs의 루프를 돌면서, 해당 pack이 verification이 통과했으면 pass,
      실패했다면 해당 pack에 의존하는 dependents를 루프돌면서 그 pack들을
      최종 verification false로 만든다. 그리고 그 pack들마다 다시 dependents
      루프를 돌린다.

## pack이 가지고 있는 origin object에 쉽게 접근하기 위해서는 aka를 사용한다.

```namu
pack example1

aka -> sys.console.monitor
// same as 'aka sys.console.monitor -> monitor'

main() void
    monitor.print("...")
    // same as 'sys.console.monitor.print("...")'
```

## pack loading시 같은 pack 경로로 여러개의 버전이 있을 수 있다.

* 이 경우 가장 최신 버전을 기본적으로 loading한다.
* pack의 manifest에 dependencies를 선언한 경우, 해당 버전을 로드한다.

```seedling
dependencies := [
    {id: 'mymodule', ver: 0.1.2, ....},
]
```

## 전혀 다른 2개 이상의 모듈이름이 중복될 수 있다. 

* 이 경우 manifest에 name 을 별도로 정의하면 된다.
```seedling
dependencies := [
    {id: 'mymodule', ver: 0.1.+, at: https://github.com/...},
    {id: 'kniz/mymodule', name: 'mymodule2' at: ./module/path.pak} // rename to mymodule2 to solve name confliction
]
```

## pack 안에 있는 srcfile은 모두 pack scope를 가짐
* pack 안에서 바로 정의한 객체들은 모두 pack 객체 밑에 sub()로 놓여지게 된다는 것
* srcFile 안에 바로 메소드를 정의할 수도 있다. 이건 pack의 메소드가 된다.
* pack 또한 변수를 가질 수 있고.

## 다른 모듈에 서로 같은 클래스가 있는 경우는 aka를 사용하거나 모듈을 다 적는다.
* 다음과 같은 상황에 있다고 하자.
```namu
/* pack/
    Founders/
        def OrderedSet
    BTree/
        def BTree
            def OrderedSet*/

// 1: err
with Founders, BTree
OrderedSet.do() // err: ambigious.

// 2: err
BTree.OrderedSet.do() // err: BTree 모듈 에는 OrderedSet이 없다.

// 3: ok
BTree.BTree.OrderedSet.do()
Founders.OrderedSet.wow()

// 4: ok
with BTree
// with를 호출 당시의 BTree는 pack 이다.
// with는 pack인 BTree.subs()를 현재 frame의 object frame에 추가한다.

BTree.OrderedSet.do()
// interpreter는 BTree는 현재 frame에서 찾는다:
//  local scope에는 없다.
//  object scope에는 방금 with가 넣어준 BTree가 나온다.
//  verify 중이라면 동일한 object scope에 또 BTree가 있는지 검색한다.
//      pack과 pack이 import한 것은 global scope으로 간주한다.
//  없으므로 에러가 아니다.
```
