# null safety

## exception handling의 한 종류이다.

## non null타입과 nullable 타입을 혼용한다.

* ?를 붙이면 nullable, 기본적으로는 non null 이다.

## 편의를 위해 safe navigation을 제공한다.

* 문법: "?."
* 멤버의 반환에 대해서만 사용이 가능하다.

```go
boo(3)?.sayHello()

// 2:
try b := boo(3)
    on nullErr: return
```

## ref가 boolean으로 캐스팅이 될때 null 여부 체크 결과를 반환한다.

```go
a := view?.activity
b := view?.fragment

if a & b
   ... 
```

## nullablle 타입에 대해 이 코드라인에서 null 체크가 이루어졌다는걸 컴파일러는 기억해야 한다.

```go
a := view?.fragment // a fragment?

go(nonnull fragment)
    nonnull.doSomething()

go(a) // err. a is nullable.
if a
    go(a) // ok. a was nullable. but null checked.
```
