#include "NEArgumentSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NEArgumentSet::NEArgumentSet(type_count size)
		: SuperClass(size)
	{

	}

	NEArgumentSet::NEArgumentSet(const ThisClass& rhs)
		: SuperClass(rhs)
	{

	}

	NEArgumentSet::NEArgumentSet()
		: SuperClass()
	{

	}

	NEBinaryFileSaver& NEArgumentSet::serialize(NEBinaryFileSaver& saver) const
	{
		//	@임시:
		//	NEArgument의 Serialize 정책:
		//		이런 다형성을 이용한 배열은 원형패턴을 이용해서 원본으로부터 인스턴스를 복사하는
		//		과정이 serialize에 포함되어야 한다. 그러나, Argument는 인스턴스가 들어있다고 가정하고
		//		serialize를 수행한다.
		//		인스턴스를 채워오기 위해서 원형패턴의 Manager 역할을 수행하는 주체가 만들기에는 역할이
		//		작기 때문이다.
		//		어짜피 임시 코드 이므로 NEModule이 _onFetchArguement의 함수에서 인스턴스를 가져오는 역할
		//		을 수행할 것이며, 이말은 NEArgumentSet::serialize는 반드시 외부에서 호출되는 것이 아니라
		//		NEModule내에서만 호출이 되어야 한다는 의미가 된다.
		saver << getLength();

		for(int n=0; n < getLength() ;n++)
			saver << getElement(n);

		return saver;
	}

	NEBinaryFileLoader& NEArgumentSet::serialize(NEBinaryFileLoader& loader)
	{
		/*
			NEArgument의 인스턴스는 다형성을 사용하므로 원칙적으로 load가 불가능하다.
			그래서 오직 NEModule에서만 호출되어야 한다.
			외부에서 호출할 수 없도록 private로 접근제한자가 걸려있다.
		*/
		//	main:
		//		생성한 인스턴스를 바탕으로 load 시퀸스 개시:
		type_count length = 0;
		loader >> length;
		if(length != getLength())
			KERNAL_ERROR("길이가 맞지 않는다. 어디선가 데이터가 꼬였다");

		for(int n=0; n < getLength() ;n++)
			loader >> getElement(n);

		return loader;
	}

	NEArgumentSet& NEArgumentSet::operator=(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		SuperClass::operator=(rhs);

		return *this;
	}

	bool NEArgumentSet::isBinded() const
	{
		for(int n=0; n < getLength() ;n++)
			if( ! getElement(n).isBinded()) return false;

		return true;
	}

	type_result NEArgumentSet::bind()
	{
		type_result to_return = RESULT_SUCCESS;

		for(int n=0; n < getLength() ;n++)
		{
			NEArgumentBase& arg = getElement(n);
			if( ! arg.isBinded())
				to_return |= arg.bind();
		}

		return to_return;
	}

}