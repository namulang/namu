#include <iostream>
#include <vector>
#include <typeinfo>
#include <cxxabi.h>
#include <limits>
#include <initializer_list>
using namespace std;

typedef unsigned int uint;

template <typename T>
class A {
public:
	void print() {
		cout << "A::print() = " << abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0) << "\n";
	}
};

class Obj {
public:
	int age;
	Obj() {}
	Obj(const Obj& rhs) { cout << "rhs\n"; }
	virtual void print() const = 0;
};

class AObj : public Obj {
public:
	float grade;
	void print() const {
		cout << "AObj::print()\n";
	}
};

class BObj : public Obj {
public:
	virtual void print() const {
		cout << "BObj::print()\n";
	}
};

class B {
public:
	B() { cout << "B::B()\n"; }
	template <typename... Ts>
	B(Ts... args) {
		std::initializer_list<Obj*> lst = {&args...};
		for(auto e=lst.begin(); e != lst.end() ;e++)
			(*e)->print();
	}
};

vector<int> foo() {
	vector<int> ret;
	ret.push_back(3);
	ret.push_back(2);
	ret.push_back(1);
	return ret;
}

int main()
{
	A<int> a;
	A<unsigned int> b;
	A<uint> c;

	a.print(); b.print(); c.print();


	int d = std::numeric_limits<int>::max();
	cout << "\n\n" << d;


	B bb = {AObj(), BObj()};
	B bb2 = {AObj()};

	cout << "gogog\n";
	vector<int> f1 = foo();
	for(auto e : foo())
		cout << e << ", ";

	return 0;
}
