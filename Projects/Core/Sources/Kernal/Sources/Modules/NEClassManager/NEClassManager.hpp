#pragma once

//	include:
#include "../NEModule/NEModule.hpp"
#include "../NETString/NETString.hpp"
#include "../NEClassBaseSet/NEClassBaseSet.hpp"

namespace NE
{
	///	@file	NEClassManager.hpp
	///	@class	make it possible to provide a reflectional function to World framework.
	///	@see	NETClass
	///	@author kniz
	class NE_DLL NEClassManager : public NEModule
	{
		NE_DECLARE_CLASS(NEClassManager, NEModule)

			virtual const NEHeader& getHeader() const
		{
			static const NEExportable::ModuleHeader _inner;

			if(NEResult::hasError(_inner.isValid()))
			{
				_inner.getName() = "NEClassManager";
				_inner.getDeveloper() = "kniz";
				_inner.setRevision(1);
				_inner.getComment() = "make it possible to provide a reflectional function to World framework.";
				_inner.getReleaseDate() = "2016-03-21";
			}

			return _inner;
		}

		//	생성자:
	public:
		NEClassManager()
			: Super()
		{

		}
		NEClassManager(const This& source)
			: Super(source)
		{
			_assign(source);
		}

		//	소멸자:
	public:
		virtual ~NEClassManager()
		{
			_release();
		}

	public:
		const This& operator=(const This& source)
		{
			if(this == &source) return *this;

			Super::operator=(source);

			return _assign(source);
		}
		bool operator==(const This& source) const
		{
			if( ! Super::operator==(source)) return false;

			return true;
		}
		bool operator!=(const This& source) const
		{
			return ! operator==(source);
		}

		//	인터페이스:
		//		상속:
		//			NEModule:
	public:
		virtual type_result initialize()
		{
			return _enrollBuiltInClasses();
		}

		//		고유 인터페이스:
	public:
		type_result enroll(const NEClassBase& new_class)
		{
			//	pre:
			//		Acquire static instance:
			static NETClass<NEAdam> root;
			//		exception handlings:
			if( ! &new_class) return KERNEL_WARNING("...");
			if(new_class.isRegistered()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;


			//	main:
			//		enroll parent:
			const NEClassBase& super = new_class.getSuperClass();
			if( ! &super)
				//	if new_class is a NEAdam class, its returend 'super' is a instance of Null.
				return RESULT_SUCCESS;
			//		hee- ha! lets do this reculsively.
			enroll(super);

			//		enrolls:
			//			supers: we can call this because Superclasses are all enrol
			//			led.
			new_class._onEnrolledSuperClasses(super);	//	in this handler, each super classes receive sub classes.


			//	post:
			super._onEnrollChildClass(new_class);
			return _manage(new_class);
		}

		//	내부함수:
	private:
		type_result _manage(const NEClassBase& new_class)
		{
			//	pre:
			//		resize:
			if(_classes.getLength() >= _classes.getSize())
				_classes.resize(_classes.getSize() * 2);


			//	main:
			type_index n = _classes.push(new_class);
			if (n == NE_INDEX_ERROR)
				return KERNEL_ERROR("...")


				//	post:
				//		give _class id as pushed index:
				//			there is no instance changing after inserted.
				//			(except for whole initializing)
				//			so, when new_class take new class id, it's ne
				//			ver get changed.
				new_class._setId(n);
			return RESULT_SUCCESS;
		}

		type_result _enrollBuiltInClasses()
		{
			//....
			//....
		}

	private:
		NEClassBaseSet _classes;
	};
}
