# pack import

## pack을 import 하려면 manifest에 선언해야 한다.
```swrd
dependencies := [
    {id: 'mymodule', ver: 0.1.2, ....},
]
```

```wrd
with mymodule
```

## 모듈이름이 중복될 수 있다. 이 경우 manifest에 name 을 별도로 정의하면 된다.
```swrd
dependencies := [
    {id: 'mymodule', ver: 0.1.+, at: https://github.com/...},
    {id: 'kniz/mymodule', name: 'mymodule2' at: ./module/path.pak} // rename to mymodule2 to solve name confliction
]
```

```wrd
with mymodule, mymodule2
```

## import를 두는 이유는 속도 최적화 때문이다.
* 이론상 import가 없더라도 동작에는 문제가 없다.
* 단 시스템은 type을 import 할 수 있더라도, 현재 프로그램을 돌리기 위한 최소한의 type만 load 해두는 것이 속도에 매우 이익이 된다.
    * 매우 많은 모듈이 worldlang으로 시스템에 존재한다고 가정하자.
    * 이러한 최적화가 없다면 hello world 프로그램을 돌리기 위해서 필요하지도 않은 directx, socket, opencv 등을 load를 해두거나
    * 2 pass 를 돌릴때 의존 관계를 유추하여 만들어 낼 수 있어야 한다. 많은 시간이 소요될 것이다.

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
