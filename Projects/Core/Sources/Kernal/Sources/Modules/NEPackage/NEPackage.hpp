///	@author	kniz
#pragma once

#include "../NETClass/NETClass.hpp"
#include "../NEIdentifier/NEIdentifier.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"

namespace NE
{
	typedef NEClassBaseList (NE_FUNCTION_CALL *EntryPoint)(void);

	class NE_DLL NEPackage : public NEPackageHeader
	{
		//	Define typedefs for RTTI in manual:
		//		because this class was designated to block calling 'clone()'
		//		for some reason. so, we can't just use DECLARE_CLASS macro.
		typedef NEPackage This;
		typedef NEIdentifier Super;
		typedef NETConcreteClass<This> MetaClass;

	public:
		friend class NEPackageManager;

	private:
		NEPackage();
		NEPackage(const This& rhs);
		
	public:
		virtual ~NEPackage();

	public:
		const This& operator=(const This& source);
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;

	public:
		NETString& getPath();
		const NETString& getPath() const;
		HINSTANCE& getInstance();
		const HINSTANCE& getInstance() const;
		EntryPoint& getEntryPoint();
		const EntryPoint& getEntryPoint() const;
		const NEClassBaseList& getComponents() const;
		NEClassBaseList& getComponents();
		bool isLoaded() const;

	public:
		virtual const NEClassBase& getClass() const;
		virtual void release();
		virtual type_result isValid() const;
	private:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;

	private:
		This& _assign(const This& rhs);
		void _release();		

	private:
		NETString _path;
		HINSTANCE _instance;
		EntryPoint _entrypoint;
		NEIntSet _compatible_revisions;
		NEClassBaseList _components;

	public:
		static const NEClassBase& getClassStatically();
	};
}