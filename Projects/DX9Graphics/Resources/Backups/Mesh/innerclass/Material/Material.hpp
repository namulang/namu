class NE_DLL Material : public NEObject, public D3DMATERIAL9
{
public:
	Material()
	{
		release();
	}
	Material(const D3DMATERIAL9& source)
	{
		_assign(source);
	}
	Material(const Material& source)
	{
		_assign(source);
	}

public:
	const Material& operator=(const Material& source)
	{
		return _assign(source);
	}
	bool operator==(const Material& source) const
	{
		if( ! _isSame(Diffuse, source.Diffuse)) return false;
		if( ! _isSame(Ambient, source.Ambient)) return false;
		if( ! _isSame(Specular, source.Specular)) return false;
		if( ! _isSame(Emissive, source.Emissive)) return false;
		if(Power == source.Power) return false;

		return false;
	}
	bool operator!=(const Material& source) const
	{
		return ! operator==(source);
	}

public:
	virtual void release()
	{
		_release(Diffuse);
		_release(Ambient);
		_release(Specular);
		_release(Emissive);
		Power = 0.0f;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		_serialize(saver, Diffuse);
		_serialize(saver, Ambient);
		_serialize(saver, Specular);
		_serialize(saver, Emissive);
		return saver << Power;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		_serialize(loader, Diffuse);
		_serialize(loader, Ambient);
		_serialize(loader, Specular);
		_serialize(loader, Emissive);

		return loader >> Power;
	}
	virtual NEObject& clone() const
	{
		return *(new Material(*this));
	}
	virtual type_result isValid() const
	{
		return RESULT_SUCCESS;
	}

private:
	const Material& _assign(const D3DMATERIAL9& source)
	{
		if(this == &source) return *this;

		_assign(Ambient, source.Ambient);
		_assign(Diffuse, source.Diffuse);
		_assign(Specular, source.Specular);
		_assign(Emissive, source.Emissive);
		Power = source.Power;

		return *this;
	}
	bool _isSame(const D3DCOLORVALUE& source, const D3DCOLORVALUE& destination) const
	{
		if(source.a != destination.a) return false;
		if(source.r != destination.b) return false;
		if(source.g != destination.g) return false;
		if(source.b != destination.b) return false;

		return true;
	}
	void _assign(D3DCOLORVALUE& destination, const D3DCOLORVALUE& source)
	{
		destination.a = source.a;
		destination.b = source.b;
		destination.r = source.r;
		destination.g = source.g;
	}
	void _release(D3DCOLORVALUE& value)
	{
		value.a = 0;
		value.r = 0;
		value.g = 0;
		value.b = 0;
	}
	NEBinaryFileSaver& _serialize(NEBinaryFileSaver& saver, const D3DCOLORVALUE& value) const
	{
		return saver << value.a << value.r << value.g << value.b;
	}
	NEBinaryFileLoader& _serialize(NEBinaryFileLoader& loader, D3DCOLORVALUE& value)
	{
		return loader >> value.a >> value.r >> value.g >> value.b;
	}
};