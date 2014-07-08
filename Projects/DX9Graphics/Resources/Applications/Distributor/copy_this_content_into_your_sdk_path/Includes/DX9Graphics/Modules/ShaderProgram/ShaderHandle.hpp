class ShaderHandle : public NEObject
{
public:
	typedef ShaderHandle ThisClass;
	typedef NEObject SuperClass;

public:
	ShaderHandle()
		: SuperClass()
	{
		ThisClass::release();
	}
	ShaderHandle(LPCTSTR new_name, bool is_technique = false)
		: SuperClass(), _is_technique_handle(is_technique), _name(new_name)
	{

	}

public:
	bool operator==(const ThisClass& source) const
	{
		if(_is_technique_handle != source._is_technique_handle) return false;
		if(_handle != source._handle) return false;
		if(_name != source._name) return false;

		return true;
	}
	bool operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}

public:
	D3DXHANDLE& getHandle() { return _handle; }
	const D3DXHANDLE& getHandle() const { return _handle; }
	NEString& getName() { return _name; }
	const NEString& getName() const { return _name; }	//	wchar_t는 D3DX에서 지원하지 않는다.
	bool& isTechniqueHandle() { return _is_technique_handle; }
	const bool& isTechniqueHandle() const { return _is_technique_handle; }

public:
	virtual void release()
	{
		_handle = 0;
		_name.release();
		_is_technique_handle = false;
	}
	virtual type_result isValid() const
	{
		if( ! _handle) return RESULT_TYPE_ERROR;
		if(NEResult::hasError(_name.isValid())) return RESULT_TYPE_ERROR;
		if( _name.getSize() <= 1) return RESULT_TYPE_ERROR;	//	null문자를 포함해서 1이다

		return RESULT_SUCCESS;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _name << _is_technique_handle;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _name >> _is_technique_handle;
	}
	virtual NEObject& clone() const
	{
		return *(new ThisClass(*this));
	}

private:
	D3DXHANDLE _handle;
	NEString _name;
	bool _is_technique_handle;
};