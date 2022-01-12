# pack import

## 다른 언어와 다르게 wrd는 import를 명시적으로 할 필요가 없다.

* interpreter가 시작 하기 전에 지정한 디렉토리를 재귀탐색해서 pack 파일을 찾아 pack객체를 생성해둔다.
  이 시점에서 pack load가 시작된 것은 아니다.
* pack 객체에 접근해서 subs()를 시도한 순간 packloading이 시작된다.

## pack이 가지고 있는 origin object에 쉽게 접근하기 위해서는 aka를 사용한다.

```wrd
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

```swrd
dependencies := [
    {id: 'mymodule', ver: 0.1.2, ....},
]
```

## 전혀 다른 2개 이상의 모듈이름이 중복될 수 있다. 

* 이 경우 manifest에 name 을 별도로 정의하면 된다.
```swrd
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
```wrd
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
