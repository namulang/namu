struct BoneFrame : D3DXFRAME
{
	bool operator==(const BoneFrame& source) const
	{
		return true;
	}
	D3DXMATRIXA16 CombinedTransformMatrix;		//실제 월드 변환 정보를 담고 있는다.
	bool picked;

	NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}
	NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}	
};