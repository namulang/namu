#include "../TestCase.hpp"
#include <ctime>

WRD_TEST_START(MemRobustTest)
	class A : public Object {
	public:
		virtual const Class& getClass() const {
			static TClass<A> in;
			return in;
		}

		int age;
	};
	class B : public A {
	public:
		virtual const Class& getClass() const {
			static TClass<B> in;
			return in;
		}

		float grade;
	};
class PInstance : public Thing {
	Id _id;
	virtual Res& release() { return wasgood; }
};
class PNode : public PInstance {};
class PObject : public PNode {};
class PA : public PObject {
public:
	virtual const Class& getClass() const {
		static TClass<PA> in;
		return in;
	}

	int age;
};
class PB : public PA {
public:
	virtual const Class& getClass() const {
		static TClass<PB> in;
		return in;
	}

	float grade;
};
	class Sprint {
	public:
		static void run(int n)
		{
			PA* parr[100000] = {0, };
			time_t start = clock();
			int crc = 0;
			for(int i=0; i < n ;i++) {
				parr[i] = new PB();
				crc += (int) parr[i];
			}
			for(int i=0; i < n ;i++)
				delete parr[i];
			WRD_WARN("%d times new/delete : %d ms elapsed. crc=%d", n, ((float) clock() - start) / CLOCKS_PER_SEC*1000, crc);

			crc = 0;
			A* arr[100000] = {0, };
			start = clock();
			for(int i=0; i < n ;i++) {
				arr[i] = new B();
				crc += (int) arr[i];
			}
			for(int i=0; i < n ;i++)
				delete arr[i];
			WRD_WARN("%d times mempool    : %d ms elapsed. crc=%d", n, ((float) clock() - start) / CLOCKS_PER_SEC*1000, crc);
		}
	};

	Sprint::run(10);
	Sprint::run(100);
	Sprint::run(1000);
	Sprint::run(10000);
	Sprint::run(50000);
	return "";
WRD_TEST_END(MemRobustTest)
