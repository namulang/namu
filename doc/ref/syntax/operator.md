# operator 

## 연산자 기본
```cpp
def app
    int main()
        age = 21
        sum = 0

        if age > 20 { // 블록문시 {, }를 사용가능 하지만,
            if age > 20 & age < 20 // 생략을 권장.
                console.out("can't reach here")

            sum = 0 // 허용된 중복 정의
            for n in 1~5 // ~는 1부터 5까지를 의미함. [1, 5)
                sum += n

            console.out("sum=" + sum) // "sum=10"
        } else if age == 20 // 블록문 뒤에 다음 stmt 가능.
            sum = 0
        if ! (age == 21) | sum // |는 or연산. sum이 0이 아니면 true로 판단
            console.out("sum=" + sum)
        elif ! sum // elif == else if
            console.out("can't reach here")
            return -1 // 함수 종료. 반환

        bit = 2
        console.out(bit || 4) // "6"
        // ||, &&, ~~ 비트 연산자
        return 0


import console // 외부 scope 이면, 어느 위치에든 선언 가능.


/* 결과:
sum=10
sum=10
6
*/
```

## 연산자 우선순위

위에 있을 수록, 우선된다. 크게 5가지로 다음과 같이 분류하며, 단항 -> 이항 순으로 나온다. 동일한 우선순위라면 왼쪽에서 오른쪽으로 평가된다.

1. 접근
2. 단항
3. 이항 산술
4. 비트연산
5. 비교

| 연산자operator                          | 설명                                            | 예제                    |
| --------------------------------------- | ------------------------------------------------| ----------------------- |
| ()                                      | 괄호                                            | (void func(int val) {}) |
| 메소드명( <인자리스트> )                | 함수호출                                        | func(35)                |
| .                                       | 접근자                                          | a.b                     |
| <타입>                                  | 캐스팅                                          | int val                 |
| []                                      | 원소접근                                        | arr[5]                  |
| ++, --, **                              | 후위 단항unary postfix                          | a++                     |
| ++, --, **                              | 전위 단항                                       | **a // a*a              |
| _                                       | 보호 속성 단항protected                         | str _val {}             |
| $, #                                    | 상수 / 정적 속성 단항                           | #str $#_val {}          |
| +                                       | 확장 속성 단항                                  | #str +#$_val {}         |
| -                                       | 음수 단항<br />양수 단항unary plus 연산자는 없다 | a = -a                 |
| !                                       | 부정logical not                                  | !++a                   |
| ~~                                      | 비트연산 부정                                    | ~~a                    |
| *, /, %, ^                              | 이항 곱, 나눗셈, 나머지 연산                    | a % b                   |
| +, -                                    | 이항 덧셈, 뺄셈                                  | a - b                  |
| <<, >>                                  | 비트 SHIFT 연산                                  | a << 3                 |
| &&                                      | 비트 AND 연산                                    | a && 0x01              |
| %%                                      | 비트 XOR 연산                                    | a %% 0x01              |
| \|\|                                    | 비트 OR 연산                                    | 0x02 \|\| 0x01          |
| ~                                       | 범위 연산                                        | 0 ~ b                  |
| <=, <, >, >=, ==, !=, --                | 비교 연산                                        | a > b                  |
| &, \|                                   | 논리 연산                                        | if a & b               |
| =, *=, /=, %=, +=, -=, &&=, \|\|=, ^^=, | 할당 연산                                        | a &&= 0x02             |


## 비교연산자와 참조자 비교 연산자

```wrd
a1 := My()
a2 := My()

a1 == a2 // true
a1 === a2 // false
a2 = a1 // now a2 reference to what a1 is pointing.
a1 === a2 // true
```

## 할당연산자는 참조자만 변경한다.

