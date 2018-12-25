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
class Float : public Node {};


template <typename S>
class Bindable : public TGet<Instance, S> {
public:
	template <typename V>
	void convert(Bindable<V>& rhs) {
		cout << "rhs.print() is \n\t";
		rhs.get();
		cout << "\n";
	}
};

class Mine : public Bindable<Instance> {};
template <typename T>
class TMine : public TGet<T, Mine> {};
class Refer : public Bindable<Node> {};

template <typename T>
class TRefer : public TGet<T, Refer> {
public:
};

template <typename T>
void foo(TGet<T, Instance>& it)
{
	cout << "ok\n";
}

int main()
{
	TRefer<Int> a;
	a.get().print();
	Refer& b = a;
	b.get().print();

	Mine c;
	TMine<Float> d;
	c.convert(a);
	d.convert(a);
	foo(c);
	foo(d);
	return 0;
}
