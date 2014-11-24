//	NEITArgument<NEKey>:	
//	왜 필요한가:	
//		키의 타입을 고려하지 않고 동작해야 하는 모듈이 있을 수 있기 때문이다.	
//		예를들어, 키 간의 assign을 동작하는 모듈의 경우 키의 타입을 특화시키면	
//		(NEIntKey 처럼) 각 키의 타입마다 모듈이 필요하게 된다.	
//		(NEIntKeyAssignModule, NEFloatKeyAssignModule ...)	
//		이 경우 물론, 외부의 키의 타입에 상관없이 implicit conversion 기능이	
//		동작된다.	

#pragma once

#include "../../Units/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"
#include "../NEArgumentTemplate/NEArgumentTemplate.hpp"
#include "../../../Modules/NEArgumentSet/NEArgumentSet.hpp"
#include "../../../Modules/NEKey/NEKey.hpp"

namespace NE
{
	template <typename T>
	class NEITArgument : public NEArgumentInterfaceBase
	{
	public:
		typedef NEITArgument ThisClass;
		typedef NEArgumentInterfaceBase SuperClass;
		typedef NEArgumentTemplate<T> ConcreteClass;

	public:
		friend class NEArguments;

	public:
		NEITArgument(const ThisClass& rhs);
		NEITArgument(typename const T::Trait& new_default = T::Trait());

	public:
		ThisClass& operator=(const ThisClass& src);

	public:
		virtual NEType::Type getKeyType() const;

	public:
		ConcreteClass& getConcreteInstance();
		const ConcreteClass& getConcreteInstance() const;
		T& getKey();
		const T& getKey() const;
		typename T::Trait& getValue();
		typename const T::Trait& getValue() const;
		typename const T::Trait& getDefault() const;
		typename T::Trait& getDefault();

	private:
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs);
		virtual type_result _onBindInstance(NEArgumentBase& concreted);

	private:
		ConcreteClass* _concrete_class;
		typename T::Trait _constant_default;
		typename T::Trait _default;
	};

	//	템플릿 클래스의 별칭 사용에 관하여:
	//		template<typename T>
	// 		typedef NEITArgument ITArgument;
	//		아쉽게도 아직은 지원되지 않는다. 해당 기능은 alias template이라고 하여,
	//		C++ x11부터 지원이 된다. (거기서부터는 using을 사용한다)
}

#include "NEITArgument.inl"