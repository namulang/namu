# Type deduction 

3. **객체 정의 구현 알고리즘**

   1. 컴파일을 시작한다.

   2. scope에서 origin 객체를 찾아, 없으면 ManagedObject를 생성해 scope에 넣는다.

   3. Origin 객체로부터 상속 구조를 만들어낸다. 그리고 메소드 / 멤버변수를 복제&추가한다.(Mouse1 -> Part)

        1. Unique한 멤버변수들은 origin에 바로 담고, sharing 할 것들은 origin이 binder로 가리키는 shared에 담는다.

        ```cpp
        uniques = parent.uniques.clone()
        if C-REPL
            shared = new Chain()
            shared->chain(*parent.shared)
        else // optimization
            shared = new Array()
            *shared = parent.shared->clone()
        ```

        2. 초기화 수식은 실행하지 않는다. 각 멤버변수들은 default 상태로 구성된다. 멤버변수는 절대로 삭제되거나, 여기서 추가되지 않는다. 이를 OriginShell이라 하자.

   4. origin shell을 바탕으로 컴파일 validation을 진행한다.

   5. 프로그램 시작 도중, static변수 초기화처럼 origin객체들을 모두 생성한다.

   6. 각 origin 객체 마다

      1. scope에서 찾아, 초기화가 되었는지 state 질의해, 안되어있으면 init 한다.

         1. **origin_shell.assign(expr) 한다.**

            1. **반환한 객체가 null이면 에러.**

               **origin_shell 기준으로 assign이므로 expr의 객체가 origin 객체 scope을 초과한 멤버변수/메소드가 있다면 자연스럽게 무시된다.**

         2. 멤버변수의 초기화식을 수행한다.

         3. origin객체의 완성. 확정짓는다.

      2. 있으면 scope에서 바로 반환한다. 초기화 중이건 상관하지 않는다.

   7. 사용자가 생성자를 호출하면, origin객체를 가상 복제한다.

   8. 가상 복제한 객체에 생성자를 수행한다.

   9. 생성자 체인 내부에서는 이미 생성된 멤버변수들에 대해 조작만 가한다.

``` cpp
def Part
    Part(str newname=""/*default*/): name = new_name

    _name = "unknown"
    void say(): null
    #year = foo(lambda, complex_msg) // year is const

def Body = Part
    void say(): c.out("Body")

def Button = Part("button") // prototyped from Part has text "button" of its name.
def Mouse = Part("mouse")
    Mouse(): super("overwrite this")
    Mouse(int a) // do nothing

def app
    void main()
        c.out(Mouse().name) // "overwrite this"
        c.out(Mouse(1).name) // "mouse"

    parts = [Part null]
    tuple = Part:str null
    maps = [Part:str null]
```
