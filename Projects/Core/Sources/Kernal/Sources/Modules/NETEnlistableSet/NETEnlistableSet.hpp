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
		NE_DECLARE_INTERFACE(NETEnlistableSet, T)

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
		NETEnlistableSet(const This& source)
			: T(source), _manager(&NEGlobalManagerOffer::getGlobalManager()), _is_enlisted(false)
		{
			//	getGlobalManagerOnCopyConstructor에 관하여:
			//		NEIndexedModuleSet.cpp에 관련 주석을 참고하라
		}

	public:
		const This& operator=(const This& source)
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
		type_bool isManaged() const
		{
			return _manager != NE_NULL;
		}
		type_bool isEnlisted() const
		{
			return _is_enlisted;
		}

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			Super::serialize(saver);

			return saver <<_is_enlisted;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			Super::serialize(loader);

			return loader >> _is_enlisted;
		}

	protected:
		type_result _setManager(NEEnlistableManager& manager)
		{
			_manager = &manager;

			return RESULT_SUCCESS;
		}
		type_result _setEnlisted(type_bool enlisted)
		{
			_is_enlisted = enlisted;

			return RESULT_SUCCESS;
		}

	protected:
		NEEnlistableManager* _manager;
		type_bool _is_enlisted;
	};	

	template <>
	class NE_DLL NETEnlistableSet<NENamedUnit> : public NENamedUnit, public NEOnEnlisted
	{
		NE_DECLARE_INTERFACE(NETEnlistableSet<NENamedUnit>, NENamedUnit)

	public:
		NETEnlistableSet(const NECodeType& script_type, const NECodeType& name_type);
		
	public:
		NETEnlistableSet(const This& source);

	public:
		const This& operator=(const This& source);

	public:
		NEEnlistableManager& getManager();
		const NEEnlistableManager& getManager() const;
		type_bool isManaged() const;
		type_bool isEnlisted() const;

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		type_result _setManager(NEEnlistableManager& manager);
		type_result _setEnlisted(type_bool enlisted);

	protected:
		NEEnlistableManager* _manager;
		type_bool _is_enlisted;
	};
}