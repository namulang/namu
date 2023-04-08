# C-REPL

## Context based Read Evaluate Print Loop

* 인터프리터가 계속 동작 중이면서 input으로 들어오는 code를 evaluate 해서 결과를 반환한다.
* 전체 코드를 모두 기억하고 있다.
* 일부 수정된 코드가 들어왔을때 해당 부분만 diff를 적용해서 다시 evaluate 한다.
* 수행 결과는 에러가 있다면 표시한다. 없다면 따로 표현하지 않는다.
    * 물론 수행하는 코드가 결과를 print하도록 구현했을 수는 있다.
* 단 결과를 받는 쪽은 언제든 수행중 혹은 수행한 AST 구조를 실시간으로 받을 수 있어야 한다.

## 4 phase를 거친다, generation -> bind&verify -> initialize -> merge

* generation은 파서가 일단 AST 객체를 생성한다.
* bind&verify에서는 AST를 깊이 탐색하면서 검증한다. AST객체를 meet 한 경우 필요하면 bind를 수행한다. (상속 등)
* initialize는 origin 객체의 초기식을 수행하고 origin객체를 완성한다.
* merge는 처리한 pack과 그 origin 객체를 최종적으로 시스템에 반영한다.

## C-REPL 모드, REP 모드 2종류가 있다.

* REP 모드는 JAVA와 비슷하게 돌아간다. (정적바인딩)
* C-REPL모드는 동적바인딩을 사용한다.
* 이 모드는 코드를 읽어서 실행하기 전에 외부 process에서 option으로 선택할 수 있어야 한다.

## AST객체는 동작 중에 계속 유지된다.

## origin 객체는 어느 AST객체 & 어느 소스 코드 텍스트 라인에서 생성되었는지를 추적가능하다.

## 소스코드 input은 stream으로 줄 수도 있고, 파일을 지정할 수도 있다.

## 파일이 갱신되면 auto로 AST를 갱신하지는 않는다.

* 매번 갱신하면 퍼포먼스가 우려된다.
* 요청하는 쪽에서 제어할 수 있어야 한다.

## 최적화를 거친 AST는 C-REPL 이 아니라 REP가 된다.

* AST는 원본을 잃어버리는 대신 비가역적으로 최적화가 된다. (최적화 효율 상승)
* 소스코드를 100% 정확하게 추정하지 못하게 된다.
* AST 대신 instruction 형태로 imparative하게 만들수도 있을 것이다.
* 최적화 코드를 실행 중에는 코드 수정(reevaluate loop)이 불가능해진다.
* 한번에 READ하고 한번에 EVALUATE하고 끝낸다. (배치처리)

## 최적화는 interpreter.exe와 통합도 가능해야 한다.

## 검증은 Visitor 패턴으로 처리한다.

* 검증 코드가 각 클래스 안에 있으면 안된다.

## verification 까지 모두 종료가 되면 시스템의 AST를 새로운 AST로 교체한다.

## 이미 과거의 AST의 메소드를 실행중인 경우, 보간해준다.

* 과거의 소스코드 라인이 현재의 소스코드의 몇번째 라인으로 이전했는지를 알아낸다.
* 해당 라인 처음부터 다시 실행한다.
* 과거 해당 라인 실행 중에 생성된 변수들은 제거한다.

## 일단 스레드는 생각하지 않는다.

## 종속 관계를 무시할 수 있는 인터프리팅 알고리즘
* 모던 언어들은 다음과 같은 의존관계도  쉽게 컴파일 해준다.
```go
pack my

def B A // 아직 A가 나오지 않았어도 컴파일 ok다.
    foo(a A, c C) void // 역시 아직 A가 나오지 않았다.

def A // 같은 파일 내에 어딘가 나오면 괜찮다.
// C 또한 같은 my pack안에 다른 파일 어딘가에만 있다면 괜찮다.
```

* 다음과 같이 동작하면 된다.
    * Type에는 부모 클래스가 무엇인지 generation 단계에서 정의된다.
    * packr 는 Type을 input으로 넘겨주면 바로 origin 객체를 넘길 준비가 되어야 한다.
    * Type이 mgd 인 경우에도 부모 클래스 정보가 참조자를 가리키는 sub nodes로써 구현이 되어야 한다.
    * packr는 pack을 import할 때, native pack이라면 dynlink 만 수행하면 되지만 mgd pack이라면 interpret 단계를 모두 거쳐야 한다.
    * 하나의 pack을 interpret 하는 도중에 다른 pack을 interpret 할 수 있어야 한다.
    * packr 또한 obj의 일종이다. scope 안에 해당 packr가 load한 pack들이 sub로 chain구조로 자리잡는다.
    * packr는 하나의 pack을 load할때 임시packr를 만든다.
        * 만들때 시스템 packr의 scope을 chain의 base에 bind하고나서 자신의 scope를 push 한다.
        * interpret 과정에서 찾아낸 pack, obj는 임시packr에 push 한다. 
        * load가 성공하면 시스템 packr에 pack을 merge 하고 임시packr는 제거한다.
    * 하나의 pack은 다음과 같이 load 된다.
        * generation 단계:
            * MgdType을 생성하여 상속 관계 정보를 만든다.
            * 빈 origin 객체를 생성하여 mgdType을 끼워넣는다.
            * interpret 하면서 심볼(func, 중첩객체 등)을 발견하면 origin 객체에 add 한다.
            * 이 단계에서 모든 심볼(expr, func, obj, ...)은 다 AST로 나와야 한다.
            * 바인딩 정보를 요하는 부분은 임시로 AdapterExpr을 넣어둔다.
                * scope에 "~~가 있을거라고 한다" 수준의 expr이다.
            * pack은 임시packr에 들어가 있는 상태다.

        * bind&verify:
            * pack을 순회한다.
            * pack내의 sub를 순회한다.
            * origin obj를 만나면 obj.isInit()== true 라면 pass 한다.
                * false라면 obj.getType().getSuper()로 부모 타입을 뽑는다.
                * 부모 타입을 packr에 질의하여 origin 객체를 가져온다.
                * 부모 origin 객체를 가져와서 상속 과정을 완료한다.
                    * 부모의 S를 복제한 후, this.S를 add 한다.. 등등
                * AdapterExpr을 발견하면 scope에 정말로 ~~가 있는지 검사한다.
                    * 있다면 AccessorExpr로 인스턴스를 교체한다.

        * initialization:
            * 생성한 origin 객체를 순회하면서 초기식을 수행해서 상속을 완료한다.

        * merge:
            * 여기까지 문제가 없었다면 임시packr의 pack을 시스템packr에 추가한다.
            * 임시packr는 제거한다.

## generation 단계에서 AccessExpr을 생성할때 뒤에 괄호까지 봐야 한다.
* 다음 예제를 보자.
```go
def a()
    b := 5
    b() void
    b(val int) void
```
* 여기서 a.b는 AccessExpr(AccessExpr(scope, "a", null), "b", null) 로 번역된다.
* 여기서 a.b()는 AccessExpr(AccessExpr(scope, "a", null), "b", {}) 로 번역된다.
* 여기서 a.b(5)는 AccessExpr(AccessExpr(scope, "a", null), "b", {int(5)}) 로 번역된다.

## 추적검증

* 코드의 변경시 이 코드를 사용하는 코드가 어디인지 빠르게 검증해야 한다.
    * 검증시간이 길어지면 사용성이 급감한다.

* 코드의 종류에 따라 변경시 충격 크기가 다르다.
    * 메소드의 한 줄을 바꾼 경우는 추적 없다.
    * 메소드 안의 변수명 혹은 타입을 바꾼 경우는 해당 메소드 전체
    * 메소드의 signature를 변경한 경우는 메소드를 사용하는 모든 라인.
    * 객체를 변경한 경우는, ...
    * 메소드 signature와 메소드를 사용하는 라인을 동시에 변경한 경우, ...

## 검증은 scope에 AST가 들어있는지, 논리적으로 말이 안되는지를 테스트한다.

* visitor는 definExpr 같은 걸 만나면 수행은 하지 않고 scope에 식별자와 타입만 추가해둔다.
* 그 외에 never reach 코드 처럼 추가적으로 논리적인 에러를 검출한다.
* 2PASS를 타지 않도록 한다. 이미 2 PASS를 돌고 있으므로 여기서도 2PASS를 타면 총 3 PASS가 된다.

## 객체의 프로퍼티는 검증 도중에는 생성되지 않는다.

* 타입과 식별자만 scope에 등록이 되면 된다.
* 순환 참조를 걸고 있는 경우, 사전에 생성을 해버리면 무한루프에 빠진다.

## IDE와 통합시 interpreter는 별도의 프로세스가 되어야 한다.

* IPC

## 매우 빠른 검증시간에 도달해야 한다.

* 느릴 경우 개발 경험이 현저하게 나빠진다.
* 타이핑이 절대로 버벅이지 않도록 해야 한다.
* IDE에서는 스레드를 사용해야 할 것이다.

## IPC 방법

* socket?
* shared memory?
* 먼저 초당 대역폭이 얼마나 되는지 봐야 한다.

## AST 변경시 남은 객체들은 그냥 놔둔다.

* 새로 생긴 AST는 이전에 생긴 AST객체를 교체해서 들어간다.
* 이전의 AST로부터 복제된 객체는 heap에 놔둔다.
* 동일한 코드를 다시 실행했을 때 새로운 AST로부터 복제된 객체가 나온다.
* 이전 AST로부터 복제된 객체가 모두 소멸하면 이전 AST도 소멸한다.
* 사용자는 HEAP을 깨끗이 비우거나 객체를 쉽게 제거하거나 할 수 있어야 한다.

## 모든 IDE의 개발언어에 호환이 가능한 IPC 방법을 제공해야 한다.

## 클래스는 동적 로딩이 되어야 한다.

* import 한 mod는 동적으로 추가/제거가 되어야 한다.
* origin 객체 또한 시스템에 의해서 동적으로 추가/제거가 되어야 한다.
* origin 객체가 제거 될때 시스템의 모든 복제 객체 또한 제거가 되어야 한다.
* native의 meta class 정보 또한 런타임에 추가/제거가 되어야 한다.
    * 객체가 존재한 상태에서도 dll 바인딩을 끊을 수 있다.
    * 객체도 유지되지만, 메소드를 호출하는 순간 fault가 발생한다.
    * 객체가 유지된 상태에서 메소드를 호출하기 전에 dll을 다시 바인딩하면 상관없다.
