#include "../TestManager.hpp"
#include <ctime>

namespace wrd
{
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
}

time_t run1(int& crc, int n)
{
	PA* parr[100000] = {0, };
	time_t start = clock();
	crc = 0;
	for(int i=0; i < n ;i++) {
		parr[i] = new PB();
		crc += *(int*) parr[i];
	}
	for(int i=0; i < n ;i++)
		delete parr[i];
	return start;
}

time_t run2(int& crc, int n)
{
	crc = 0;
	A* arr[100000] = {0, };
	time_t start = clock();
	for(int i=0; i < n ;i++) {
		arr[i] = new B();
		crc += *(int*) arr[i];
	}
	for(int i=0; i < n ;i++)
		delete arr[i];
	return start;
}



WRD_TEST_START(MemRobustTest)

	int crc = 0;

#define SPRINT(n) \
	WRD_WARN("%d times new/delete : %f ms elapsed. crc=%d", n, ((float) clock() - run1(crc, (n))) / CLOCKS_PER_SEC*1000.0f, crc); \
	WRD_WARN("%d times mempool    : %f ms elapsed. crc=%d", n, ((float) clock() - run2(crc, (n))) / CLOCKS_PER_SEC*1000.0f, crc);

	SPRINT(10)
	SPRINT(100);
	SPRINT(1000);
	SPRINT(10000);
	SPRINT(50000);
	return "";
WRD_TEST_END(MemRobustTest)
