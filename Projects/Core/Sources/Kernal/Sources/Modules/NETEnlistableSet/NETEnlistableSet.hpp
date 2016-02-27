#pragma once

#include "../../Commons/Interfaces/NEOnEnlisted/NEOnEnlisted.hpp" 
#include "../../Commons/Units/NEGlobalManagerOffer/NEGlobalManagerOffer.hpp"
#include "../NENamedUnit/NENamedUnit.hpp"

namespace NE
{
	class NEEnlistableManager;
	class NENode;

	template <typename T>
	class NE_DLL NETEnlistableSet : public T, public NEOnEnlisted
	{
	public:
		typedef NETEnlistableSet<T> ThisClass;
		typedef T SuperClass;

	public:
		NETEnlistableSet()
			: T(), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
		{
			//	getGlobalManagerOnCopyConstructor에 관하여:
			//		NEIndexedModuleSet.cpp에 관련 주석을 참고하라
		}
		NETEnlistableSet(NEEnlistableManager& manager)
			: T(), _manager(&manager), _is_enlisted(false)
		{

		}
		NETEnlistableSet(type_index size)
			: T(size), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
		{

		}

	public:		
		NETEnlistableSet(const ThisClass& source)
			: T(source), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
		{
			//	getGlobalManagerOnCopyConstructor에 관하여:
			//		NEIndexedModuleSet.cpp에 관련 주석을 참고하라
		}

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			/*
				_manager를 복사하지 않도록 하기 위해서 operator=를 정의한다.
			*/
			T::operator=(source);

			return *this;
		}

	public:
		NEEnlistableManager& getManager()
		{
			return *_manager;
		}
		const NEEnlistableManager& getManager() const
		{
			return *_manager;
		}
		bool isManaged() const
		{
			return _manager != NE_NULL;
		}
		bool isEnlisted() const
		{
			return _is_enlisted;
		}

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver <<_is_enlisted;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _is_enlisted;
		}

	protected:
		type_result _setManager(NEEnlistableManager& manager)
		{
			_manager = &manager;

			return RESULT_SUCCESS;
		}
		type_result _setEnlisted(bool enlisted)
		{
			_is_enlisted = enlisted;

			return RESULT_SUCCESS;
		}

	protected:
		NEEnlistableManager* _manager;
		bool _is_enlisted;
	};	

	template <>
	class NE_DLL NETEnlistableSet<NENamedUnit> : public NENamedUnit, public NEOnEnlisted
	{
	public:
		typedef NETEnlistableSet<NENamedUnit> ThisClass;
		typedef NENamedUnit SuperClass;

	public:
		NETEnlistableSet(const NECodeType& script_type, const NECodeType& name_type);
		
	public:
		NETEnlistableSet(const ThisClass& source);

	public:
		const ThisClass& operator=(const ThisClass& source);

	public:
		NEEnlistableManager& getManager();
		const NEEnlistableManager& getManager() const;
		bool isManaged() const;
		bool isEnlisted() const;

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		type_result _setManager(NEEnlistableManager& manager);
		type_result _setEnlisted(bool enlisted);

	protected:
		NEEnlistableManager* _manager;
		bool _is_enlisted;
	};
}