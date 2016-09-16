#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"
#include "../NETDerivedClassChecker/NETDerivedClassChecker.hpp"

namespace NE
{
	template <typename T, type_bool IS_VALID_TYPE = NETDerivedClassChecker<T, NEUnit>>
	class NETWeakBinder : public NEBinderBase
	{
		NE_DECLARE_CLASS(NETWeakBinder<T>, NEBinderBase)

	public:
		virtual type_result bind(const T& target);

	public:
		T& operator->();
		const T& operator->() const;
		T& operator*();
		const T& operator*() const;
		//	method hiding:
		//		When you want to get binded one as NEUnit&, use NEBinderBase's one.
		//		Do as like, 
		//			NEUnit& binded = NEBinderBase::get();
		T& get();
		const T& get() const;
	};

	template <typename T>
	class NETWeakBinder<T, false> : public NEBinderBase	
	{
		///	if you encountered such a message like "there is no such function at NETWeak/Binder...",
		///	The type parameter which you want to bind is not one of NEUnit.
	};

}