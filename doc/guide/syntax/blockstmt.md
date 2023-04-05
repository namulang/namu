# block stmt 

## 블록문은 생략한다.

## 개행이 되면 블록문이 종료된 것으로 판단한다.

```cpp
		void print()
		    console.out("hello")
        ()
```

위의 () 는 메소드 print의 호출이 아니라, 빈 튜플의 정의다.

## 블록문을 사용하는 흐름 제어 키워드에서 변수를 정의할 수 있다.

```cpp
if a := 55
    print(a)
a++ // err
```

* if 의 조건expr도 또 하나의 local scope으로 정의한다.
* 따라서 if가 종료되면 변수도 사라진다.

```cpp
for a := get()
    print(a)
a++ // err
```

get()의 결과가 true 일 동안 계속 반복한다.

## 메소드의 호출은 블록문이 아니다.

```cpp
print(a := 55)
a++
```
