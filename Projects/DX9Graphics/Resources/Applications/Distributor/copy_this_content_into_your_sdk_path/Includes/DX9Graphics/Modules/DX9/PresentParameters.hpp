class PresentParameters : public NEObject, public D3DPRESENT_PARAMETERS
{
public:
	PresentParameters()
	{
		PresentParameters::release();
	}
public:
	bool operator==(const PresentParameters& source) const
	{
		if(BackBufferWidth != source.BackBufferWidth) return false;
		if(BackBufferHeight != source.BackBufferHeight) return false;
		if(BackBufferFormat != source.BackBufferFormat) return false;
		if(BackBufferCount != source.BackBufferCount) return false;
		if(MultiSampleType != source.MultiSampleType) return false;
		if(MultiSampleQuality != source.MultiSampleQuality) return false;
		if(SwapEffect != source.SwapEffect) return false;
		if(hDeviceWindow != source.hDeviceWindow) return false;
		if(Windowed != source.Windowed) return false;
		if(EnableAutoDepthStencil != source.EnableAutoDepthStencil) return false;
		if(AutoDepthStencilFormat != source.AutoDepthStencilFormat) return false;
		if(Flags != source.Flags) return false;
		if(FullScreen_RefreshRateInHz != source.FullScreen_RefreshRateInHz) return false;
		if(PresentationInterval != source.PresentationInterval) return false;		

		return true;
	}

	bool operator!=(const PresentParameters& source) const
	{
		return ! operator==(source);
	}

	PresentParameters& operator=(const D3DPRESENT_PARAMETERS& source)
	{
		D3DPRESENT_PARAMETERS* casted_this = static_cast<D3DPRESENT_PARAMETERS*>(this);
		if(casted_this == &source) return *this;

		D3DPRESENT_PARAMETERS::operator=(source);

		return *this;
	}

public:
	D3DPRESENT_PARAMETERS& getD3DPresentParameters()
	{
		return *this;
	}
	const D3DPRESENT_PARAMETERS& getD3DPresentParameters() const
	{
		return *this;
	}
	type_result setPreferredDisplayMode(const DisplayMode& new_one)
	{
		if(NEResult::hasError(new_one.isValid())) return RESULT_TYPE_ERROR;

		Windowed = new_one.isWindowed();
		BackBufferFormat = new_one.Format;
		BackBufferWidth = new_one.Width;
		BackBufferHeight = new_one.Height;
		FullScreen_RefreshRateInHz = new_one.RefreshRate;

		return RESULT_SUCCESS;
	}
	DisplayMode getPreferredDisplayMode() const
	{
		DisplayMode buffer;
		buffer.Height = BackBufferHeight;
		buffer.Width = BackBufferWidth;
		buffer.Format = BackBufferFormat;
		buffer.RefreshRate = FullScreen_RefreshRateInHz;
		buffer.setWindowed(Windowed != 0);

		return buffer;
	}

public:
	virtual void release()
	{
		BackBufferCount = 0;
		BackBufferFormat = D3DFORMAT(0);
		BackBufferHeight = 0;
		BackBufferWidth = 0;
		MultiSampleQuality = 0;
		MultiSampleType = D3DMULTISAMPLE_TYPE(0);
		SwapEffect = D3DSWAPEFFECT(0);
		hDeviceWindow = 0x00;
		Windowed = false;
		EnableAutoDepthStencil = false;
		AutoDepthStencilFormat = D3DFORMAT(0);
		Flags = 0;
		FullScreen_RefreshRateInHz = 0;
		PresentationInterval = 0;
	}
	// hDeviceWindow는 저장 할 수 없다.
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver << BackBufferWidth << BackBufferHeight << (int) BackBufferFormat << BackBufferCount << (int) MultiSampleType << MultiSampleQuality << (int) SwapEffect << Windowed << EnableAutoDepthStencil << (int) AutoDepthStencilFormat << Flags << FullScreen_RefreshRateInHz << PresentationInterval;
	}
	// hDeviceWindow는 저장 할 수 없다.
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		int buffer = 0;
		loader >> BackBufferWidth >> BackBufferHeight >> buffer;
		BackBufferFormat = D3DFORMAT(buffer);
		buffer = 0;
		
		loader >> BackBufferCount >> buffer;
		
		MultiSampleType = D3DMULTISAMPLE_TYPE(buffer);
		buffer = 0;
		
		loader >> MultiSampleQuality >> buffer;
		SwapEffect = D3DSWAPEFFECT(buffer);	
		buffer = 0;

		loader >> Windowed >> EnableAutoDepthStencil >> buffer;
		AutoDepthStencilFormat = D3DFORMAT(buffer);
		
		return loader >> Flags >> FullScreen_RefreshRateInHz >> PresentationInterval;
	}
	virtual type_result isValid() const
	{
		if(BackBufferWidth <= 0) return RESULT_TYPE_ERROR;
		if(BackBufferHeight <= 0) return RESULT_TYPE_ERROR;			
		/*
			나머지 멤버변수에 대해서 Valid 체크는 0이 될 수도 있으므로 확인이 불가능하다
		*/

		return RESULT_SUCCESS;
	}
	virtual NEObject& clone() const
	{
		return *(new PresentParameters(*this));
	}
};