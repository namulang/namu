#pragma once

#include "../../Interfaces/NEArgumentInterfaceBase/NEArgumentInterfaceBase.hpp"
#include "../NEArgumentTemplate/NEArgumentTemplate.hpp"
#include "../../../Modules/NEArgumentSet/NEArgumentSet.hpp"

namespace NE
{
	template <typename T>
	class NEArgumentInterfaceTemplate : public NEArgumentInterfaceBase
	{
	public:
		typedef NEArgumentInterfaceTemplate ThisClass;
		typedef NEArgumentInterfaceBase SuperClass;
		typedef NEArgumentTemplate<T> ConcreteClass;
		typedef ThisClass ITArgument;	// @important 이거 작동하지 않는다!

	public:
		friend class NEArguments;

	public:
		NEArgumentInterfaceTemplate() 
			: _concrete_class(0x00) {}
		NEArgumentInterfaceTemplate(const ThisClass& rhs)
			: _concrete_class(rhs._concrete_class), _default(rhs._default) {}
		NEArgumentInterfaceTemplate(const T& new_default)
			: _concrete_class(0x00), _default(new_default) {}

	public:
		ThisClass& operator=(const ThisClass& src)
		{
			if(this == &src) return *this;

			_default = src._default;
			//	구체클래스 깊은복사 실행:
			//		정책:
			//			생성시 인터페이스에 구체클래스 인스턴스를 바인딩한다.
			//			이후, 인터페이스를 통해서만 구체클래스의 인스턴스를 관리한다.
			//			이 정책을 따르면 항상 인스턴스가 오염되지 않도록 보장 가능.
			if(	_concrete_class && src._concrete_class												&&
				_concrete_class->getTypeToBeBinded() == src._concrete_class->getTypeToBeBinded()	)
				*_concrete_class = *src._concrete_class;				

			return *this;
		}

	public:
		ConcreteClass& getConcreteInstance() { return *_concrete_class; }
		const ConcreteClass& getConcreteInstance() const { return *_concrete_class; }
		T& getKey() 
		{ 
			if(_concrete_class)
				return _concrete_class->getBindedKey();

			T* nullpointer = 0;
			return *nullpointer;
		}
		const T& getKey() const
		{
			if(_concrete_class)
				return _concrete_class->getBindedKey();

			T* nullpointer = 0;
			return *nullpointer;
		}
		typename T::Trait& getValue()
		{
			T::Trait* nullpoint = 0x00;
			if( ! _concrete_class) return *nullpoint;

			T::Trait& to_return = _concrete_class->getValue();
			if( ! &to_return)
			{
				static T::Trait _to_be_returned;
				_to_be_returned = _default.getValue();
				return _to_be_returned;
			}

			return to_return;
		}
		const T& getDefault() const
		{
			return _default;
		}
		T& getDefault()
		{
			return _default;
		}

	private:
		virtual type_result _onInsertedInArguments(type_index index, NEArgumentSet& rhs)
		{
			if(rhs.getLength() == rhs.getSize())
				rhs.resize(rhs.getLength() + 1);

			ConcreteClass& pushed = (ConcreteClass&) rhs[rhs.push(ConcreteClass())];
			if( ! &pushed)
				return RESULT_TYPE_WARNING;

			_concrete_class = &pushed;

			return RESULT_SUCCESS;
		}


	private:
		ConcreteClass* _concrete_class;
		T _default;
	};
}