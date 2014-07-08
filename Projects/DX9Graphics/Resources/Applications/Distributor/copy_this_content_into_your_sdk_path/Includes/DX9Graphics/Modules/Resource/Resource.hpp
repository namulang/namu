#pragma once

#include "../DX9Binder/DX9Binder.hpp"

namespace DX9Graphics
{
	class NE_DLL Resource : public DX9Binder
	{
	public:
		typedef DX9Binder SuperClass;
		typedef Resource ThisClass;

	public:
		Resource()
			: SuperClass()
		{
			_release();
		}
		Resource(const ThisClass& source)
			: SuperClass(source)
		{
			_assign(source);
		}

	public:
		virtual type_result initializeResource()
		{
			_is_resource_initailized = true;

			return RESULT_SUCCESS;
		}
		virtual type_result releaseResource()
		{
			_is_resource_initailized = false;

			return RESULT_TYPE_ERROR;
		}

	public:
		bool isResourceInitialized()
		{
			return _is_resource_initailized;
		}

	public:
		virtual void release()
		{
			SuperClass::release();

			_release();
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			return saver << _is_resource_initailized;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			return loader >> _is_resource_initailized;
		}

	protected:
		type_result _setResourceRetrieved()
		{
			_is_resource_initailized = true;
			return RESULT_SUCCESS;
		}

	private:
		type_result _release()
		{
			_is_resource_initailized = false;

			return RESULT_SUCCESS;
		}
		ThisClass& _assign(const ThisClass& source)
		{
			_is_resource_initailized = source._is_resource_initailized;

			return *this;
		}

	protected:
		bool _is_resource_initailized;
	};
}