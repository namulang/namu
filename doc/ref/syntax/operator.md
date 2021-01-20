# operator 

## 연산자 우선순위

* 위에 있을 수록, 우선된다.

| 연산자operator                  | 설명                       | Associativity | 예제           |
| ------------------------------- | ---------------------------| --------------| -------------- |
| ()                              | 괄호                       | None          | (func(val))    |
| (), [], ., ++, --, **           | Postfix(함수호출, 접근 등) | right         | func(35)       |
| ++, --, **, !, -, ~~            | Prefix                     | left          | **a // a*a     |
| as                              | 캐스팅                     | None          | int val        |
| *, /, %                         | 이항 곱, 나눗셈, 나머지    | right         | a % b          |
| +, -                            | 이항 덧셈, 뺄셈            | right         | a - b          |
| <<, >>                          | 비트 SHIFT 연산            | right         | a << 3         |
| &&                              | 비트 AND 연산              | right         | a && 0x01      |
| ^^                              | 비트 XOR 연산              | right         | a %% 0x01      |
| \|\|                            | 비트 OR 연산               | right         | 0x02 \|\| 0x01 |
| ..                              | 범위 연산                  | None          | 0 ~ b          |
| <=, <, >, >=, ==, !=, ===, !==  | 비교 연산                  | right         | a > b          |
| &                               | 논리 AND 연산              | right         | a & b          |
| \|                              | 논리 OR 연산               | right         | a | b          |
| =, *=, /=, %=, +=, -=           | 할당 연산                  | left          | a &&= 0x02     |


## 비교연산자와 참조자 비교 연산자

```go
a1 := My()
a2 := My()

a1 == a2 // true
a1 === a2 // false
a2 = a1 // now a2 reference to what a1 is pointing.
a1 === a2 // true
```

## 할당연산자는 참조자만 변경한다.
