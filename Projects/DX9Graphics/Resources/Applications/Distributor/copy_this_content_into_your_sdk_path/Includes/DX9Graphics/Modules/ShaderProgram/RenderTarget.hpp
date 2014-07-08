class RenderTarget : public NEObject
{
public:
	typedef RenderTarget ThisClass;
	typedef NEObject SuperClass ;

public:
	RenderTarget()
		: SuperClass(), _surface(0), _texture(0)
	{
		 
	}
	RenderTarget(const ThisClass& source)
		: SuperClass(source), _surface(0), _texture(0)
	{
		
	}
	~RenderTarget()
	{
		ThisClass::release();
	}

public:
	bool operator==(const ThisClass& source) const
	{
		if(this != &source) return false;

		return true;
	}
	bool operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}

public:
	IDirect3DTexture9& getTexture() { return *_texture; }
	const IDirect3DTexture9& getTexture() const { return *_texture; }
	IDirect3DSurface9& getSurface() { return *_surface; }
	const IDirect3DSurface9& getSurface() const { return *_surface; }
	bool isInitialized() const
	{
		return _texture != 0;
	}

public:
	type_result initialize(DX9& dx9)
	{
		const NEFloatSet& rates = _getWidthHeightRates();

		_initializeTexture(dx9, rates[0], rates[1]);
		return _initializeSurface();
	}

public:
	virtual void release()
	{
		if(_texture)
			_texture->Release();
		_texture = 0;
		if(_surface)
			_surface->Release();
		_surface = 0;
	}
	NEObject& clone() const { return *(new ThisClass(*this)); }
	virtual type_result isValid() const
	{
		if( ! _texture || ! _surface) return RESULT_TYPE_ERROR;
		
		return RESULT_SUCCESS;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const { return saver; }
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader) { return loader; }

private:
	type_result _initializeTexture(DX9& dx9, type_float width_rate, type_float height_rate);
	type_result _initializeSurface();
		
private:
	LPDIRECT3DTEXTURE9 _texture;
	LPDIRECT3DSURFACE9 _surface;

private:
	static const NEFloatSet& _getWidthHeightRates();
	static type_result _writeDefaultWidthHeightRatesToINI();
	static type_float _readRateFromINI(const NETString& title)
	{
		NETString buffer;
		NEINIManager& ini = Kernal::getInstance().getINIManager();


		//	main:
		ini.read("RenderTarget", title, buffer);
		return static_cast<type_float>(buffer.toDouble());
	}
};