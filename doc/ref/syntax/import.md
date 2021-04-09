# import

## import 뒤에 사용할 type과 module path를 적어야 한다.

## import를 두는 이유는 속도 최적화 때문이다.
* 이론상 import가 없더라도 동작에는 문제가 없다.
* 단 시스템은 type을 import 할 수 있더라도, 현재 프로그램을 돌리기 위한 최소한의 type만 load 해두는 것이 속도에 매우 이익이 된다.
    * 매우 많은 모듈이 worldlang으로 시스템에 존재한다고 가정하자.
    * 이러한 최적화가 없다면 hello world 프로그램을 돌리기 위해서 필요하지도 않은 directx, socket, opencv 등을 load를 해두거나
    * 2 pass 를 돌릴때 의존 관계를 유추하여 만들어 낼 수 있어야 한다. 많은 시간이 소요될 것이다.

## import 는 .wrd 파일 바로 안쪽에서만 서술할 수 있다.
* 따라서 import는 expr이 아니다.
* generation 단계에서 import가 보이면 해당 모듈을 초기화한다. module은 이 과정에서 .so 파일을 load 하고 내부의 origin obj를 interpreting 혹은 dyn link 한다.

## import는 정적에서만(ast가 만들어지는 순간) 판단된다.

## import는 뒤따라오는 module을 src frame에 넣어두는 것이다.
* 각 소스코드 파일에서 import를 선언한 것들이 srcframe 에 들어가게 된다.
* 이 srcframe을 base로 삼아서 이 소스코드 파일에서 정의된 것들은 모두 자신의 chain 뒤에 srcframe을 link 하고 본다.
