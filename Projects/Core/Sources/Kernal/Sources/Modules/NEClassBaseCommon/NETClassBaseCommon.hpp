#pragma once

#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	///	@class	NETClassBaseCommon
	///	@brief	Implemented common method and data among specialized from NETClassBase
	///			class.
	template <typename T>
	class NETClassBaseCommon : public NEClassBase
	{
	public:
		typedef NETClassBaseCommon<T> This;
		typedef NEClassBase Super;

	public:
		virtual const NEClassBase& getClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual const NEClassIdentifier& getIdentifier() const;
	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);
		virtual type_result _setIdentifier(const NEClassIdentifier& new_identifier);

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassIdentifier& getIdentifierStatically();
		static const NEClassBase& getClassStatically();
		static const NETString& getNameStatically();
	};
}

#include "NETClassBaseCommon.inl"