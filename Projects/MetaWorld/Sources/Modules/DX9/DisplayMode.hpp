class DisplayMode : public NEObject, public D3DDISPLAYMODE
{
public:
	DisplayMode()
	{
		DisplayMode::release();
	}

public:
	bool operator==(const DisplayMode& source) const
	{
		if(Width != source.Width) return false;
		if(Height != source.Height) return false;
		if(RefreshRate != source.RefreshRate) return false;
		if(Format != source.Format) return false;
		if(_is_window != source._is_window) return false;

		return true;
	}

	bool operator!=(const DisplayMode& source) const
	{
		return ! operator==(source);
	}

	DisplayMode& operator=(const D3DDISPLAYMODE& source)
	{
		D3DDISPLAYMODE* casted_this = static_cast<D3DDISPLAYMODE*>(this);
		if(casted_this == &source) return *this;

		D3DDISPLAYMODE::operator=(source);

		return *this;
	}

public:
	type_result setD3DDisplayMode(const D3DDISPLAYMODE& source)
	{
		if(this == &source) return RESULT_SUCCESS;

		D3DDISPLAYMODE::operator=(source);

		return RESULT_SUCCESS;
	}
	const D3DDISPLAYMODE getD3DDisplayMode() const
	{
		return D3DDISPLAYMODE(*this);
	}
	bool isWindowed() const
	{
		return _is_window;
	}
	type_result setWindowed(bool new_one)
	{
		_is_window = new_one;

		return RESULT_SUCCESS;
	}
	bool isFormat32BitColor() const
	{
		switch(Format)
		{
		case D3DFMT_R5G6B5:
		case D3DFMT_X1R5G5B5:
		case D3DFMT_A1R5G5B5:
		case D3DFMT_A4R4G4B4:
		case D3DFMT_R3G3B2:
		case D3DFMT_A8R3G3B2:
		case D3DFMT_X4R4G4B4:
		case D3DFMT_A8:
			return false;

		default:
			return true;
		}
	}

public:
	virtual void release()
	{
		Width = 0;
		Format = D3DFORMAT(0);
		Height = 0;
		_is_window = false;
		RefreshRate = 0;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver << Width << Height << RefreshRate << (int) Format << _is_window;
	}
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		loader >> Width >> Height >> RefreshRate;

		int buffer = 0;
		loader >> buffer;
		Format = D3DFORMAT(buffer);

		return loader >> _is_window;
	}
	virtual type_result isValid() const
	{
		if(_is_window) return RESULT_SUCCESS;
		if(Width <= 0) return RESULT_TYPE_ERROR;
		if(Height <= 0) return RESULT_TYPE_ERROR;
		if(RefreshRate <= 0) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}
	virtual NEObject& clone() const
	{
		return *(new DisplayMode(*this));
	}

private:
	bool _is_window;
};