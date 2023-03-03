# if

* branch 한다.

## if 역시 expr 으로 취급한다.

## if 에서 else를 적지 않을 경우 기본값이 나갈 수 있다.

```go
retVal := if size > 0: obj // size <= 0 이면 retVal은 null,
// retVal 타입은 obj?가 된다.
```
