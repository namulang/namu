#pragma once

#include "../../Includes/Includes.hpp"
#include "../NEClassBase/NEClassBase.hpp"
//	checkers:
#include "../NETADTChecker/NETADTChecker.hpp"
#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#include "../NEUnknown/NEUnknown.hpp"

namespace NE
{
	template <typename T>
	class NETClassBase : public NETClassBaseCommon<T>
	{
	public:
		typedef NETClassBase<T> This;
		typedef NEClassBase Super;
		//    type determind:
		typedef typename NETMetaClassDeterminder<T>::MetaClass MetaClass;
		typedef typename NETTraitDeterminder<T>::Trait Trait;
		typedef typename NETSuperClassDeterminder<T>::Super SuperTrait;

	public:
		friend class NEClassManager;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		///	@brief	returns the identifer for NETClass.
		///			As you can inspect codes, this returns the static variable.
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();
	};
}