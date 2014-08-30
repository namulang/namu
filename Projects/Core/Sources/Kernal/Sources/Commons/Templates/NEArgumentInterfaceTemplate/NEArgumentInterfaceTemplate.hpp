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

	public:
		friend class NEArguments;

	public:
		NEArgumentInterfaceTemplate() 
			: _concrete_class(0x00) {}
		NEArgumentInterfaceTemplate(const ThisClass& rhs)
			: NEArgumentInterfaceBase(rhs), _concrete_class(0x00), _default(rhs._default) {}
		NEArgumentInterfaceTemplate(const T& new_default)
			: _concrete_class(0x00), _default(new_default) {}

	public:
		ThisClass& operator=(const ThisClass& src)
		{
			if(this == &src) return *this;

			_default = src._default;
			//	정책:
			//		"	절대로 내부 바인딩의 결과는 공유 및 할당하지 않는다.
			//			내부 바인딩을 "할 수 있는" 정보만 넘겨줘서, 그 놈이 바인딩 다시 하도록 하라	"
			//		그래서 바인딩 결과물인 _concreate_class는 넘겨주지 않는다. 
			//		대신 default_value 같은 것만 할당 시켜준다.
			//		밑에 처럼 하지 않는다는 거야.
			//	
			// 			if(	_concrete_class && src._concrete_class												&&
			// 				_concrete_class->getTypeToBeBinded() == src._concrete_class->getTypeToBeBinded()	)
			// 				*_concrete_class = *src._concrete_class;				

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
//	템플릿 클래스의 별칭 사용에 관하여:
//		template<typename T>
// 		typedef NEArgumentInterfaceTemplate ITArgument;
//		아쉽게도 아직은 지원되지 않는다. 해당 기능은 alias template이라고 하여,
//		C++ x11부터 지원이 된다. (거기서부터는 using을 사용한다)
}