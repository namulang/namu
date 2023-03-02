# Type deduction 

* 타입을 다른 타입으로 변환이 가능한지를 판단하여, 유추하는 것을 말한다.
* 2개를 대상으로 하는 유추와 3개를 대상으로 하는 유추가 있다.

## Type변환은 Type 객체에서 담당한다.
* static 으로 제공한다.
* node 도 redirection 해서 API를 제공한다.

## 단순 유추
* 타겟 <-- 소스 로 변환이 가능한지를 검토하면 된다.
* 묵시적 변환이 허용되는지만 검토하면 된다.
    * 묵시적 변환은 primitive 간의 변환, 함수를 delegator의 변환과 upcasting만 해당한다.

## 2항 유추
* ? <-- 소스 & 소스 로써, 2개의 소스가 주어졌을때 이 둘을 모두 만족시킬 수 있는 타겟을 찾는다.

### 2항 유추의 알고리즘
* 2항 유추는 다음의 케이스로 먼저 분류한다.
* 2개 모두 predifined 된 타입일 경우 (예, primitive 혹은 delegator 등):
    * 미리 정의된 table에 의해서 타입이 유도된다.
* 2개 중 1개만 predefined된 타입일 경우:
    * 유도는 실패한다. 실패한 경우 node (== void*) 로 유도된다.
* 2개 모두 predefined 된 타입이 아닐 경우:
    * 공통의 부모 클래스로 유도되는데 그 방법은 다음과 같다.
```go
deduce(t1 type, t2 type) type
    // tier는 조상클래스의 size()
    minTier := min(t1.tier, t2.tier)
    while minTier
        if t1.ancestor[minTier] == t2.ancestor[minTier]: return A.ancestor
        minTier--
    return node
```

### N항 유추
* 다음과 같은 케이스를 말한다.
```go
arr := [3.5, 55, true, "wow"]
// arr은 무슨 타입의 배열인가?
```

* 단순하게 2항 유추를 N-1번 반복하면 된다.
* 코드로 적으면 이렇다.
```go
arrType := deduce(deduce(deduce(flt, int), bool), str)
```

## node.get(name, args)는 타입유추를 담당한다.
* gets() 다르게 get() 은 유일한 1개를 추출하려는 API다. 당연히 타입 유추를 Type 클래스를 통해서 실시한다.
