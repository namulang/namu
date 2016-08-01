///	@author	kniz
#pragma once

#include "../NETClass/NETClass.hpp"
#include "../NEHeader/NEHeader"
#include "../NEClassBaseList/NEClassBaseList.hpp"

namespace NE
{
	class NE_DLL NEPackage : public] NEHeader
	{
		NE_DECLARE_CLASS(NEPackage, NEHeader)

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
		const NEClassBaseList& getClasses() const;
		type_bool isLoaded() const;

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEObject& clone() const;

	protected:
		//	for PackageManager.
		NEClassBaseList& _getClasses();

	private:
		This& _assign(const This& rhs);
		void _release();

	private:
		NETString _path;
		HINSTANCE _instance;
		EntryPoint _entrypoint;
		NEIntSet _compatible_revisions;
		NEClassBaseList _components;
	};
}