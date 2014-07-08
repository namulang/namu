struct BoneMesh : public D3DXMESHCONTAINER
{
	ID3DXMesh* OriginMesh;
	std::vector< D3DMATERIAL9 > materials;
	std::vector< IDirect3DTexture9 *> textures;

	D3DXATTRIBUTERANGE* attributeTable;
	DWORD NumAtttributeGroup;
	D3DXMATRIX* pBoneOffsetMatrices;
};