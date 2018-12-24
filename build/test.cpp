#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T, typename S>
class TGet : public S{
public:
	T& get() { static T inner; 
		cout << "get<" << typeid(T).name() << ">\n";
	return inner; }
};

class Instance {
public:
	virtual void print() { cout << "Instance\n";}
};
class Node : public Instance {
public:
	virtual void print() { cout << "Node\n";}
};
class Int : public Node {
public:
	virtual void print() { cout << "Int\n";}
};

template <typename S>
class Bindable : public TGet<Instance, S> {};

class Refer : public Bindable<Node> {};

template <typename T>
class TRefer : public TGet<T, Refer> {
public:
};

int main()
{
	TRefer<Int> a;
	a.get().print();
	Refer& b = a;
	b.get().print();
	return 0;
}
