class Capabilities : public NEObject, public D3DCAPS9
{
public:
	Capabilities()
	{
		Capabilities::release();
	}
public:
	bool operator==(const Capabilities& source) const
	{
		if(DeviceType != source.DeviceType) return false;
		if(AdapterOrdinal != source.AdapterOrdinal) return false;
		if(Caps != source.Caps) return false;
		if(Caps2 != source.Caps2) return false;
		if(Caps3 != source.Caps3) return false;
		if(PresentationIntervals != source.PresentationIntervals) return false;
		if(CursorCaps != source.CursorCaps) return false;
		if(DevCaps != source.DevCaps) return false;
		if(PrimitiveMiscCaps != source.PrimitiveMiscCaps) return false;
		if(RasterCaps != source.RasterCaps) return false;
		if(ZCmpCaps != source.ZCmpCaps) return false;
		if(SrcBlendCaps != source.SrcBlendCaps) return false;
		if(DestBlendCaps != source.DestBlendCaps) return false;
		if(AlphaCmpCaps != source.AlphaCmpCaps) return false;
		if(ShadeCaps != source.ShadeCaps) return false;
		if(TextureCaps != source.TextureCaps) return false;
		if(TextureFilterCaps != source.TextureFilterCaps) return false;
		if(CubeTextureFilterCaps != source.CubeTextureFilterCaps) return false;
		if(VolumeTextureFilterCaps != source.VolumeTextureFilterCaps) return false;
		if(LineCaps != source.LineCaps) return false;
		if(TextureAddressCaps != source.TextureAddressCaps) return false;
		if(LineCaps != source.LineCaps) return false;
		if(MaxTextureWidth != source.MaxTextureWidth) return false;
		if(MaxTextureAspectRatio != source.MaxTextureAspectRatio) return false;
		if(MaxAnisotropy != source.MaxAnisotropy) return false;
		if(MaxVertexW != source.MaxVertexW) return false;
		if(GuardBandLeft != source.GuardBandLeft) return false;
		if(GuardBandRight != source.GuardBandRight) return false;
		if(GuardBandTop != source.GuardBandTop) return false;
		if(GuardBandBottom != source.GuardBandBottom) return false;
		if(ExtentsAdjust != source.ExtentsAdjust) return false;
		if(StencilCaps != source.StencilCaps) return false;
		if(FVFCaps != source.FVFCaps) return false;
		if(TextureOpCaps != source.TextureOpCaps) return false;
		if(MaxTextureBlendStages != source.MaxTextureBlendStages) return false;
		if(MaxSimultaneousTextures != source.MaxSimultaneousTextures) return false;
		if(VertexProcessingCaps != source.VertexProcessingCaps) return false;
		if(MaxActiveLights != source.MaxActiveLights) return false;
		if(MaxUserClipPlanes != source.MaxUserClipPlanes) return false;
		if(MaxVertexBlendMatrices != source.MaxVertexBlendMatrices) return false;
		if(MaxVertexBlendMatrixIndex != source.MaxVertexBlendMatrixIndex) return false;
		if(MaxPointSize != source.MaxPointSize) return false;
		if(MaxPrimitiveCount != source.MaxPrimitiveCount) return false;
		if(MaxVertexIndex != source.MaxVertexIndex) return false;
		if(MaxStreams != source.MaxStreams) return false;
		if(MaxStreamStride != source.MaxStreamStride) return false;
		if(VertexShaderVersion != source.VertexShaderVersion) return false;
		if(MaxVertexShaderConst != source.MaxVertexShaderConst) return false;
		if(PixelShaderVersion != source.PixelShaderVersion) return false;
		if(PixelShader1xMaxValue != source.PixelShader1xMaxValue) return false;
		if(DevCaps2 != source.DevCaps2) return false;
		if(MaxNpatchTessellationLevel != source.MaxNpatchTessellationLevel) return false;
		if(Reserved5 != source.Reserved5) return false;
		if(MasterAdapterOrdinal != source.MasterAdapterOrdinal) return false;
		if(AdapterOrdinalInGroup != source.AdapterOrdinalInGroup) return false;
		if(NumberOfAdaptersInGroup != source.NumberOfAdaptersInGroup) return false;
		if(DeclTypes != source.DeclTypes) return false;
		if(NumSimultaneousRTs != source.NumSimultaneousRTs) return false;
		if(StretchRectFilterCaps != source.StretchRectFilterCaps) return false;
		if(VS20Caps.Caps != source.VS20Caps.Caps) return false;
		if(VS20Caps.DynamicFlowControlDepth != source.VS20Caps.DynamicFlowControlDepth) return false;
		if(VS20Caps.NumTemps != source.VS20Caps.NumTemps) return false;
		if(VS20Caps.StaticFlowControlDepth != source.VS20Caps.StaticFlowControlDepth) return false;
		if(PS20Caps.Caps != source.PS20Caps.Caps) return false;
		if(PS20Caps.DynamicFlowControlDepth != source.PS20Caps.DynamicFlowControlDepth) return false;
		if(PS20Caps.NumTemps != source.PS20Caps.NumTemps) return false;
		if(PS20Caps.StaticFlowControlDepth != source.PS20Caps.StaticFlowControlDepth) return false;
		if(PS20Caps.NumInstructionSlots != source.PS20Caps.NumInstructionSlots) return false;
		if(VertexTextureFilterCaps != source.VertexTextureFilterCaps) return false;
		if(MaxVShaderInstructionsExecuted != source.MaxVShaderInstructionsExecuted) return false;
		if(MaxPShaderInstructionsExecuted != source.MaxPShaderInstructionsExecuted) return false;
		if(MaxVertexShader30InstructionSlots != source.MaxVertexShader30InstructionSlots) return false;
		if(MaxPixelShader30InstructionSlots != source.MaxPixelShader30InstructionSlots) return false;

		return true;
	}

	bool operator!=(const Capabilities& source) const
	{
		return ! operator==(source);
	}

	Capabilities& operator=(const D3DCAPS9& source)
	{
		D3DCAPS9* casted_this = static_cast<D3DCAPS9*>(this);
		if(casted_this == &source) return *this;

		D3DCAPS9::operator=(source);

		return *this;
	}

public:
	type_result setD3DCaps9(const D3DCAPS9& source)
	{
		if(this == &source) return RESULT_SUCCESS;

		D3DCAPS9::operator=(source);

		return RESULT_SUCCESS;
	}
	const D3DCAPS9 setD3DCaps9() const
	{
		return D3DCAPS9(*this);
	}
	bool isHardWareVertexProcessingAvailable()
	{
		return (DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 1;
	}

public:
	virtual void release()
	{		
		DeviceType = D3DDEVTYPE(0);
		AdapterOrdinal = 0;
		Caps = 0;
		Caps2 = 0;
		Caps3 = 0;
		PresentationIntervals = 0;
		CursorCaps = 0;
		DevCaps = 0;
		PrimitiveMiscCaps = 0;
		RasterCaps = 0;
		ZCmpCaps = 0;
		SrcBlendCaps = 0;
		DestBlendCaps = 0;
		AlphaCmpCaps = 0;
		ShadeCaps = 0;
		TextureCaps = 0;
		TextureFilterCaps = 0; 
		CubeTextureFilterCaps = 0;
		VolumeTextureFilterCaps = 0;
		TextureAddressCaps = 0;
		VolumeTextureAddressCaps = 0;
		LineCaps = 0;
		MaxTextureWidth = 0;
		MaxTextureHeight = 0;
		MaxVolumeExtent = 0;
		MaxTextureRepeat = 0;
		MaxTextureAspectRatio = 0; 
		MaxAnisotropy = 0;
		MaxVertexW = 0;
		GuardBandLeft = 0;
		GuardBandTop = 0;
		GuardBandRight = 0;
		GuardBandBottom = 0;
		ExtentsAdjust = 0;
		StencilCaps = 0;
		FVFCaps = 0;
		TextureOpCaps = 0;
		MaxTextureBlendStages = 0;
		MaxSimultaneousTextures = 0;
		VertexProcessingCaps = 0;
		MaxActiveLights = 0;
		MaxUserClipPlanes = 0;
		MaxVertexBlendMatrices = 0;
		MaxVertexBlendMatrixIndex = 0;
		MaxPointSize = 0;
		MaxPrimitiveCount = 0;
		MaxVertexIndex = 0;
		MaxStreams = 0;
		MaxStreamStride = 0;
		VertexShaderVersion = 0;
		MaxVertexShaderConst = 0;
		PixelShaderVersion = 0;
		PixelShader1xMaxValue = 0;
		DevCaps2 = 0;
		MaxNpatchTessellationLevel = 0;
		Reserved5 = 0;
		MasterAdapterOrdinal = 0;
		AdapterOrdinalInGroup = 0;
		NumberOfAdaptersInGroup = 0;
		DeclTypes = 0;
		NumSimultaneousRTs = 0;
		StretchRectFilterCaps = 0;
		VS20Caps.Caps = 0;
		VS20Caps.DynamicFlowControlDepth = 0;
		VS20Caps.NumTemps = 0;
		VS20Caps.StaticFlowControlDepth = 0;
		PS20Caps.Caps = 0;
		PS20Caps.DynamicFlowControlDepth = 0;
		PS20Caps.NumTemps = 0;
		PS20Caps.StaticFlowControlDepth = 0;
		VertexTextureFilterCaps = 0;
		MaxVShaderInstructionsExecuted = 0;
		MaxPShaderInstructionsExecuted = 0;
		MaxVertexShader30InstructionSlots = 0;
		MaxPixelShader30InstructionSlots = 0;
	}
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const 
	{
		return saver	<< (int)DeviceType << AdapterOrdinal << Caps << Caps2 << Caps3 << PresentationIntervals << CursorCaps << DevCaps << PrimitiveMiscCaps << RasterCaps << ZCmpCaps << SrcBlendCaps << DestBlendCaps << AlphaCmpCaps << ShadeCaps << TextureCaps << TextureFilterCaps << CubeTextureFilterCaps << VolumeTextureFilterCaps << TextureAddressCaps << VolumeTextureAddressCaps << LineCaps << MaxTextureWidth << MaxTextureHeight << MaxVolumeExtent << MaxTextureRepeat << MaxTextureAspectRatio << MaxAnisotropy << MaxVertexW << GuardBandLeft << GuardBandTop << GuardBandRight << GuardBandBottom << ExtentsAdjust << StencilCaps << FVFCaps << TextureOpCaps << MaxTextureBlendStages << MaxSimultaneousTextures << VertexProcessingCaps << MaxActiveLights << MaxUserClipPlanes << MaxVertexBlendMatrices << MaxVertexBlendMatrixIndex << MaxPointSize << MaxPrimitiveCount << MaxVertexIndex << MaxStreams << MaxStreamStride << VertexShaderVersion << MaxVertexShaderConst << PixelShaderVersion << PixelShader1xMaxValue << DevCaps2 << MaxNpatchTessellationLevel << Reserved5 << MasterAdapterOrdinal << AdapterOrdinalInGroup << NumberOfAdaptersInGroup << DeclTypes << NumSimultaneousRTs << StretchRectFilterCaps 
			<< VS20Caps.Caps << VS20Caps.DynamicFlowControlDepth << VS20Caps.NumTemps << VS20Caps.StaticFlowControlDepth 
			<< PS20Caps.Caps << PS20Caps.DynamicFlowControlDepth << PS20Caps.NumTemps << PS20Caps.StaticFlowControlDepth 
			<< VertexTextureFilterCaps << MaxVShaderInstructionsExecuted << MaxPShaderInstructionsExecuted << MaxVertexShader30InstructionSlots << MaxPixelShader30InstructionSlots;		
	}

	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		int buffer = 0;
		loader >> buffer;
		DeviceType = D3DDEVTYPE(buffer);

		return loader	>> AdapterOrdinal >> Caps >> Caps2 >> Caps3 >> PresentationIntervals >> CursorCaps >> DevCaps >> PrimitiveMiscCaps >> RasterCaps >> ZCmpCaps >> SrcBlendCaps >> DestBlendCaps >> AlphaCmpCaps >> ShadeCaps >> TextureCaps >> TextureFilterCaps >> CubeTextureFilterCaps >> VolumeTextureFilterCaps >> TextureAddressCaps >> VolumeTextureAddressCaps >> LineCaps >> MaxTextureWidth >> MaxTextureHeight >> MaxVolumeExtent >> MaxTextureRepeat >> MaxTextureAspectRatio >> MaxAnisotropy >> MaxVertexW >> GuardBandLeft >> GuardBandTop >> GuardBandRight >> GuardBandBottom >> ExtentsAdjust >> StencilCaps >> FVFCaps >> TextureOpCaps >> MaxTextureBlendStages >> MaxSimultaneousTextures >> VertexProcessingCaps >> MaxActiveLights >> MaxUserClipPlanes >> MaxVertexBlendMatrices >> MaxVertexBlendMatrixIndex >> MaxPointSize >> MaxPrimitiveCount >> MaxVertexIndex >> MaxStreams >> MaxStreamStride >> VertexShaderVersion >> MaxVertexShaderConst >> PixelShaderVersion >> PixelShader1xMaxValue >> DevCaps2 >> MaxNpatchTessellationLevel >> Reserved5 >> MasterAdapterOrdinal >> AdapterOrdinalInGroup >> NumberOfAdaptersInGroup >> DeclTypes >> NumSimultaneousRTs >> StretchRectFilterCaps 
			>> VS20Caps.Caps >> VS20Caps.DynamicFlowControlDepth >> VS20Caps.NumTemps >> VS20Caps.StaticFlowControlDepth 
			>> PS20Caps.Caps >> PS20Caps.DynamicFlowControlDepth >> PS20Caps.NumInstructionSlots >> PS20Caps.NumTemps >> PS20Caps.StaticFlowControlDepth 
			>> VertexTextureFilterCaps >> MaxVShaderInstructionsExecuted >> MaxPShaderInstructionsExecuted >> MaxVertexShader30InstructionSlots >> MaxPixelShader30InstructionSlots;
	}

	virtual type_result isValid() const
	{
		return RESULT_SUCCESS;
	}
	virtual NEObject& clone() const
	{
		return *(new Capabilities(*this));
	}
};