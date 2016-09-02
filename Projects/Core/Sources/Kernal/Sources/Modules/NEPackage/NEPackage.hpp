///	@author	kniz
#pragma once

#pragma message("NEPackage.hpp - 1")
#include "../NETClass/NETClass.hpp"
#pragma message("NEPackage.hpp - 2")
#include "../NEHeader/NEHeader.hpp"
#pragma message("NEPackage.hpp - 3")
#include "../NEClassBaseList/NEClassBaseList.hpp"
#pragma message("NEPackage.hpp - 4")

namespace NE
{
	typedef type_result (*EntryPoint)(NEHeader&, NEClassBaseList&);

	class NE_DLL NEPackage : public NEHeader
	{
		NE_DECLARE_CLASS_ONLY(NEPackage, NEHeader)

	public:
		friend class NEPackageManager;

	public:
		NEPackage();
		NEPackage(const This& rhs);

	public:
		virtual ~NEPackage();

	public:
		const This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

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
		virtual type_id getId() const;

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		//	for PackageManager.
		NEClassBaseList& _getClasses();
		type_result _setId(type_id new_id);

	private:
		This& _assign(const This& rhs);
		void _release();

	private:
		NETString _path;
		HINSTANCE _instance;
		EntryPoint _entrypoint;
		NEIntSet _compatible_revisions;
		NEClassBaseList _components;
		type_id _id;
	};
}