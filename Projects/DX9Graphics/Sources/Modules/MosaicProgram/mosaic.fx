/*
	모자이크 셰이더
*/

// 3D Scene Texture
sampler smp0:register(s0);

struct SvsOut
{
	float4	Pos : POSITION;
	float2	Tex : TEXCOORD0;
};

SvsOut VtxProc0(	float3 Pos: POSITION
				,	float2 Tex: TEXCOORD0)
{
	SvsOut Out = (SvsOut)0;

	Out.Pos = float4(Pos, 1);
	Out.Tex = Tex;

	return Out;
}

int	mosaic_precision = 30;
float4 Pxlsharp(SvsOut In) : COLOR0
{
	float4	Color = 0;
	float grids = (float) mosaic_precision;
		
	float2 tex_coord = floor(grids * In.Tex + 0.5f) / grids;
	Color = tex2D(smp0, tex_coord);	

	return Color;
}

technique Tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 Pxlsharp();
	}	
};