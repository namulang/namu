#pragma once

#include <iostream>
#include <vector>
#define DEVELOPER
#include "../../../Kernal/Sources/Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"
#include "../../../Kernal/Sources/Commons/Templates/NEIndexedArrayTemplate/NEIndexedArrayTemplate.hpp"
#include "../../../Kernal/Sources/Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../../Kernal/Sources/Commons/Templates/NEManagedSetTemplate/NEManagedSetTemplate.hpp"
#pragma comment(lib, "../../../../Binaries/Core/Kernal.dev.dbg.lib")
using namespace NE;
using namespace std;

class MyObject : public NEObject
{
public:
	MyObject()
		: value(0)
	{

	}
	MyObject(int size)
		: value(size)
	{

	}
	MyObject(const MyObject& source)
		: value(source.value)
	{

	}
	bool operator==(const MyObject& source) const
	{
		return value == source.value;
	}
	virtual ~MyObject()
	{

	}
	virtual void release()
	{
		value = 0;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}	
	virtual NEObject& clone() const
	{
		return *(new MyObject(*this));
	}
	virtual NEType::Type getType() const
	{
		return NEType::NEOBJECT;
	}
	virtual type_result isValid() const
	{
		return RESULT_SUCCESS;
	}

	int value;
};

class MyArray : public NEArrayTemplate<MyObject>
{
public:
	MyArray(type_index size)
		: NEArrayTemplate<MyObject>(size)
	{

	}

public:
	void print()
	{
		cout << name << " : ";

		for(int n=0; n < getSize() ;n++)
		{
			( &getElement(n)) ? cout << getElement(n).value << "(" << &getElement(n) << ") " : cout << "null ";
		}

		cout << endl;
	}

	LPCSTR name;
};

class MyInt : public NEObject
{
public:
	MyInt()
		:value(0)
	{

	}
	MyInt(int new_value)
		:value(new_value)
	{

	}

	operator int() 
	{
		return value;
	}

	bool operator==(const MyInt& source) const
	{
		return value == source.value;
	}

	virtual void release() 
	{
		value = 0;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		return loader >> value;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver << value; 
	}
	virtual NEObject& clone() const
	{
		return static_cast<NEObject&>(*(new MyInt(*this)));
	}
	virtual type_result isValid() const
	{
		return RESULT_SUCCESS;
	}


	int value;
};

MyArray objs(15);

class MyArray21 : public NEArrayTemplate<int>
{
	typedef NEArrayTemplate<int> Super;

public:
	void print()
	{
		cout << "MyArray2 : ";
		for(int n=0; n < getLength() ;n++)
			cout << getElement(n) << ":" << &getElement(n) << ", ";

		cout << endl;
	}
};



class MyArray2 : public NEArrayTemplate<MyInt*, true, MyObject>
{
	typedef NEArrayTemplate<MyInt*, true, MyObject> Super;

public:
	using Super::serialize;

public:
	MyArray2()
		: Super()
	{

	}
	MyArray2(const MyArray2& source)
		: Super(source)	//	여기서는 아무런 복사를 하지 않는다.
	{
		create(source.getSize());
		for(int n=0; n < source.getLength() ;n++)
			push(source[n]);
	}

public:
	virtual type_index insert(type_index index, const MyObject& source)
	{
		int n = objs.push(source);
		if(n <= NE_INDEX_ERROR)
			return NE_INDEX_ERROR;

		MyInt m(n);

		return _insert(getLength(), &m);
	}
	virtual type_result remove(type_index index)
	{
		int real_index = (int) *(_getElement(index));
		if(real_index <= NE_INDEX_ERROR)
			return RESULT_TYPE_ERROR;
		
		if(objs.remove(real_index) & RESULT_TYPE_ERROR)
			return RESULT_TYPE_ERROR;

		return _remove(index);
	}
	virtual MyObject& getElement(type_index index)
	{
		int rindex = _getElement(index)->value;

		return objs[rindex];
	}
	virtual const MyObject& getElement(type_index index) const
	{
		return objs[ _getElement(index)->value ];
	}
	virtual type_result setElement(type_index index, const MyObject& source)
	{
		MyObject& target = objs[_getElement(index)->value];
		if( ! &target)
			return RESULT_TYPE_ERROR;

		target = source;

		return RESULT_SUCCESS;
	}
	virtual type_index find(const MyObject& source) const
	{
		int index = objs.find(source);

		MyInt m(index);
				
		return _find(&m);
	}
	virtual void release()
	{
		while(getLength())
			pop();

		Super::release();
	}

	virtual NEObject& clone() const
	{
		return *(new MyArray2(*this));
	}

	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}

	void print()
	{
		cout << "MyArray2 : ";
		for(int n=0; n < getLength() ;n++)
		{
			MyObject& target = getElement(n);
			if( &target)
				cout << _getElement(n)->value << ":" << (_getElement(n)) << "-->(" << target.value << " : " << (void*)&target << "), ";
			else
				cout << "null, ";
		}

		cout << endl;
	}
};



typedef NEIndexedArrayTemplate<int> Test;

class MyIndexArray : public Test
{
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyIndexArray\n";
		cout << "\telements : ";
		for(int n=0; n < getSize() ;n++)
		{
			cout << _data[n] << "(";
			(_occupiedset[n]) ? cout << "o" : cout << "x";
			cout << "), ";
		}
		cout << "\n";
	}
};

class MyIndexArray1 : public NEIndexedArrayTemplate<int*, false>
{
	typedef NEIndexedArrayTemplate<int*, false> SuperClass;
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyIndexArray\n";
		cout << "\telements : ";
		for(int n=0; n < getSize() ;n++)
		{
			cout << _data[n] << "(";
			(_occupiedset[n]) ? cout << "o" : cout << "x";
			cout << "), ";
		}
		cout << "\n";
	}

public:
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		for(int n=0; n < getSize() ;n++)
			if( &getElement(n))
			{
				const int* const data = &getElement(n);
				int buffer = (int) data;
				saver << buffer;
			}

		return saver;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		for(int n=0; n < getSize() ;n++)
			if( _occupiedset[n])
			{
				int buffer = 0;
				loader >> buffer;

				setElement(n, (int*)buffer);
			}

		return loader;
	}
	virtual NEObject& clone() const
	{
		return *(new MyIndexArray1(*this));
	}
};

class MyIndexArray2 : public NEIndexedArrayTemplate<MyInt*, true>
{
	typedef NEIndexedArrayTemplate<MyInt*, true> SuperClass;
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyIndexArray\n";
		cout << "\telements : ";
		for(int n=0; n < getSize() ;n++)
		{
			MyInt& unit = getElement(n);
			if(&unit)
				cout << getElement(n) << "-->" << _data[n] << "(";
			else
				cout << "0x00000000(";

			(_occupiedset[n]) ? cout << "o" : cout << "x";
			cout << "), ";			
		}
		cout << "\n";
	}

public:
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		for(int n=0; n < getSize() ;n++)
			if( &getElement(n))
				saver << getElement(n);

			return saver;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		for(int n=0; n < getSize() ;n++)
			if( _occupiedset[n])
			{
				int buffer = 0;
				loader >> buffer;

				setElement(n, MyInt(buffer));
			}

			return loader;
	}
	virtual NEObject& clone() const
	{
		return *(new MyIndexArray2(*this));
	}
};


class MyList : public NEListTemplate<MyInt>
{
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyList<T>\n";
		cout << "\telements : ";
		for(NEListTemplate<MyInt>::Iterator* itr=getIterator(0); itr ;itr=itr->getNext())
		{
			MyInt& unit = itr->getValue();
			if(&unit)
				cout << unit.value << "(" << &unit << "), ";
			else
				cout << "0x00000000(), ";
		}
		cout << "\n";
	}
};

class MyList2 : public NEListTemplate<int*>
{
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyList<T>\n";
		cout << "\telements : ";
		for(NEListTemplate<int*>::Iterator* itr=getIterator(0); itr ;itr=itr->getNext())
		{
			int unit = (int) (&(itr->getValue()));
			cout << unit << "(" << &unit << "), ";
		}
		cout << "\n";
	}

public:
	virtual NEObject& clone() const
	{
		return *(new MyList2(*this));
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		NEListTemplate<int*>::serialize(saver);

		const NEListTemplate<int*>::Iterator* itr = getIterator(0);
		while(itr)
		{
			int data = (int) &(itr->getValue());

			saver << data;

			itr = itr->getNext();
		}

		return saver;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		NEListTemplate<int*>::serialize(loader);
		type_index length = getLength();
		_length = 0;

		for(int n=0; n < length ;n++)
		{
			int data = 0;
			loader >> data;

			push((int*)data);
		}

		return loader;
	}
};

class MyList3 : public NEListTemplate<MyInt*, true>
{
public:
	void print(int phase_count)
	{
		cout << "PHASE - " << phase_count << " MyList<MyInt*, true>\n";
		cout << "\telements : ";
		for(NEListTemplate<MyInt*, true>::Iterator* itr=getIterator(0); itr ;itr=itr->getNext())
		{
			MyInt& unit = itr->getValue();
			cout << unit.value << "(" << &unit << "), ";
		}
		cout << "\n";
	}

public:
	virtual NEObject& clone() const
	{
		return *(new MyList3(*this));
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		NEListTemplate<MyInt*, true>::serialize(saver);

		const NEListTemplate<MyInt*, true>::Iterator* itr = getIterator(0);
		while(itr)
		{
			int data = itr->getValue().value;

			saver << data;

			itr = itr->getNext();
		}

		return saver;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		NEListTemplate<MyInt*, true>::serialize(loader);
		type_index length = getLength();
		_length = 0;

		for(int n=0; n < length ;n++)
		{
			int data = 0;
			loader >> data;

			push(MyInt(data));
		}

		return loader;
	}
};


void main()
{
	NE_MEMORYLEAK;

	if(0)
	{
		MyArray21 c;

		c.create(2);
		c.push(1);
		c.push(2);
		c.push(3);
		c.print();

		c.resize(4);
		c.pushFront(4);
		c.setElement(1, 5);
		c.print();


		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << c;
		saver.close();

		c.release();
		c.print();

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		c.serialize(loader);
		//loader >> c;
		loader.close();
		c.print();
	}

	if(0)
	{
		objs.create(15);
		int n=0;
		while( n++ < 10)
			objs.push(MyObject());

		for(int n=0; n < 3 ;n++)
			objs[n].value = n;

		cout << "test : value is " << objs[2].value << "\n\n";

		/*
			MyObject* p1 = new MyObject(1),
				* p2 = new MyObject(2),
				* p3 = new MyObject(3);
		*/

		MyObject p1(1), p2(2), p3(3);

		/*
		cout	<< "p1 : " << p1 << endl
				<< "p2 : " << p2 << endl
				<< "p3 : " << p3 << endl;
		*/

		MyArray a(2), b(a);
		a.push(p1);
		a.push(p2);
		a.name = "a";
		b.name = "b";

		a.print();
		b.print();

		

		b.release();
		b.create(6);
		a.print();
		b.print();

		b.pushFront(a);

		a.print();
		b.print();

		cout << "\n\n\n";

		objs.name = "OBJS";
		MyArray2 c;
		c.create(2);
		c.push(MyObject(7));
		c.push(MyObject(8));
		objs.print();
		c.print();
		c.release();
		objs.print();
		c.print();
		c.resize(4);
		c.push(MyObject(7));
		objs.print();
		c.print();
		c.push(MyObject(9));

		c.find(2);


		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << c;
		saver.close();

		c.release();
		c.print();

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		c.serialize(loader);
		//loader >> c;
		loader.close();
		c.print();

	}

	if(0)
	{
		MyIndexArray test;
		test.print(0);
		test.push(0);
		test.push(5);
		test.print(1);

		test.create(2);
		test.insert(0, 0);
		test.push(1);
		test.print(2);
		test.insert(0, 1);
		test.print(3);

		test.resize(4);
		test.print(4);
		test.pushFront(2);
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push(3);
		test.insert(3, 4);
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}

	if(0)
	{
		MyIndexArray1 test;
		test.print(0);
		test.push( (int*) 0);
		test.push((int*) 5);
		test.print(1);

		test.create(2);
		test.insert(0, (int*) 0);
		test.push((int*) 1);
		test.print(2);
		test.insert(0, (int*) 1);
		test.print(3);

		test.resize(4);
		test.print(4);
		test.pushFront((int*) 2);
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push((int*) 3);
		test.insert(3, (int*) 4);
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}

	if(0)
	{
		MyIndexArray2 test;
		test.print(0);
		test.push( MyInt(0));
		test.push( MyInt(5));
		test.print(1);

		test.create(2);
		test.insert(0, MyInt(0));
		test.push( MyInt(1) );
		test.print(2);
		test.insert(0, MyInt(1));
		test.print(3);

		test.resize(4);
		test.print(4);
		test.pushFront( MyInt(2));
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push( MyInt(3));
		test.insert(3, MyInt(4));
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}


	if(0)
	{
		MyList test;

		test.print(0);
		test.push( MyInt(0));
		test.push( MyInt(5));
		test.print(1);

		test.insert(0, MyInt(0));
		test.push( MyInt(1) );
		test.print(2);
		test.insert(0, MyInt(1));

		MyList test2 = test;
		test.print(3);

		test.release();
		test.print(4);
		test.pushFront( MyInt(2));
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push( MyInt(3));
		test.insert(3, MyInt(4));
		test.pushFront(test2);
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}

	if(0)
	{
		MyList2 test;

		test.print(0);
		test.push( (int*)0);
		test.push( (int*)(5));
		test.print(1);

		test.insert(0, (int*)(0));
		test.push( (int*)(1) );
		test.print(2);
		test.insert(0, (int*)(1));

		MyList2 test2 = test;
		test.print(3);

		test.release();
		test.print(4);
		test.pushFront( (int*)(2));
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push( (int*)(3));
		test.insert(3, (int*)(4));
		test.pushFront(test2);
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}

	if(0)
	{
		NEListTemplate<NEListTemplate<int>> a;

		a.push(NEListTemplate<int>());
		a.getElement(0).push(1);

		cout << a[0][0];
	}

	if(0)
	{
		MyList3 test;

		test.print(0);
		test.push( MyInt(0));
		test.push( MyInt(5));
		test.print(1);

		test.insert(0, MyInt(0));
		test.push( MyInt(1) );
		test.print(2);
		test.insert(0, MyInt(1));

		MyList3 test2 = test;
		test.print(3);

		test.release();
		test.print(4);
		test.pushFront( MyInt(2));
		test.print(5);
		test.pop();
		test.print(6);
		test.popFront();
		test.print(7);
		if( ! &test.getElement(0)) cout << "\n\nelement 0 is null!\n";

		test.push( MyInt(3));
		test.insert(3, MyInt(4));
		test.pushFront(test2);
		test.print(8);

		NEBinaryFileSaver saver(L"test.txt");
		saver.open();
		saver << test;
		saver.close();

		test.release();
		test.print(9);

		NEBinaryFileLoader loader(L"test.txt");
		loader.open();
		loader >> test;
		loader.close();
		test.print(10);
	}

	if(1)
	{
		//ManagedMyInt a;
	}

	//MyObject* news =new MyObject();
}