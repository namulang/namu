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

## 2항 연산자와 comma는 Indetation이 무시된다.

* +나 , 같은 경우는 계속해서 이어서 쓰는 경우가 많기 때문에 쉽게 가로로 화면을 벗어난다.
* namulang은 indentation에 민감하기 때문에 이 경우, 블록문이 시작되는 것으로 오인하게 된다.
* 편의를 위해서 col이 화면을 벗어나지만, 다음에 올 토큰이 반드시 블록문이 될 수 없는 상황인 경우
  Indentation체크를 꺼서 블록문으로 오인되지 않게 한다.
* 2항연산자와 comma는, [, (, {, '.' 가 나오면 다음 token이 나올때까지 indentation이 무시된다.
* 다른 연산자나 keyword 등도 반드시 다음에 올 토큰이 블록문이 될 수 없는 경우가 존재하나,
  모든 keyword가 이에 해당하는 것은 아니다. 그러므로 이것마자 지원하게 될 경우 사용자가 keyword별로
  indentation OFF가 지원되는지 여부를 외워야 하므로, 지원하지 않는 것이다.

* indentation OFF가 지원되는 경우, 다음에 유의미한 token(= whitespace가 아닌 token)이 올때까지
  모든 token을 무시한다.
* 유의미한 token이 scanner에 인식된 경우부터는 정상동작으로 돌아간다.

```namu
a = 2 + 3 + constants.VERY_LONG_NAME_I_DONT_KNOW_ITS_NAME_BUT_VERY_LONG + activity.getFrameManager().getScreenPlay(22, (view, context)
    view.update(context)
    view.doSomething(22)
, 23) // 일반적인 경우

// 위와 같은 코드다.
a = 2 + 3 + // + 토큰이 나오면 2항연산자이므로 다음 유의미한 token이 나올때까지 공백이 무시된다.
constants.VERY_LONG_NAME_I_DONT_KNOW_ITS_NAME_BUT_VERY_LONG +
                  activity.getFrameManager().getScreenPlay(22, // indentation 역시 무시된다.
                        (view, context) // 블록문이다.
                view. // . 도 적용된다
                   update(
                22,
        23)
        // view.doSomething(22) // indentation은 현재 view의 시작점에 맞춰져 있다. 
        // view.doSomething(22)은 잘못된 indentation level이다.

                view.doSometing(22) // ok

                /*view.doSomething 
                (22)
                에러:
                    '(' 나오면, 그 다음 token까지를 무시하는 것이다.
                    '(' 나오기 전은 적용되지 않는다. */

                /*view.doSomething(
                    22
                )
                에러: 숫자 뒤에 개행은 무시되지 않는다.*/

                view.doSomething(
                    22) // ok
, 23) // ok
/* comma의 indentation level에 주목하자.
   ,는 getScreenPlay()의 인자인 것이며, 해당 함수호출의 indentation level은 0 이다.
   따라서 새로 나오는 comma 또한 indentation level 0에서 출발해야 한다.

```
