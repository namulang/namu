//  #1 ByVal and ByRef policy
class Class1
    int age = 5
    void print()
        Console.out("age = " + age)

class Class2
    void foo(Class1 cls)
        cls.print()
        Class1 cls2 = cls1 // copy
        cls2.age = 6
        if cls2.age == cls.age
            Console.out("Never happen this.")
        cls2 -> cls1 // share
        if cls2.age == cls.age
            Console.out("ok")

        Class1 cls3 -> cls1 // share.

    int main(string[] args)
        int a1 = 5, a2 = 8
        a2 = a1 // copy
        a1 = 0 // but a2 is still 5.        
        a2 -> a1 // share. a2 is now 0