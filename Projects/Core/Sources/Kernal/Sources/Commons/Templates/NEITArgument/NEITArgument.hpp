#pragma once

#include "../../Units/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"
#include "../NEArgumentTemplate/NEArgumentTemplate.hpp"
#include "../../../Modules/NEArgumentSet/NEArgumentSet.hpp"

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
		NEITArgument();
		NEITArgument(const ThisClass& rhs);
		NEITArgument(const T& new_default);

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
		const T& getDefault() const;
		T& getDefault();

	private:
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs);
		virtual type_result _onBindInstance(NEArgumentBase& concreted);

	private:
		ConcreteClass* _concrete_class;
		T _default;
	};

	//	템플릿 클래스의 별칭 사용에 관하여:
	//		template<typename T>
	// 		typedef NEITArgument ITArgument;
	//		아쉽게도 아직은 지원되지 않는다. 해당 기능은 alias template이라고 하여,
	//		C++ x11부터 지원이 된다. (거기서부터는 using을 사용한다)
}

#include "NEITArgument.inl"