//
// Shader Example.
// Copyleft (c) 2007 Heesung Oh(Galic Studio). All rights Not reserved.
////////////////////////////////////////////////////////////////////////////


sampler smp0:register(s0);
sampler smp1:register(s1);
sampler smp2:register(s2);
sampler smp3:register(s3);

struct SvsOut
{
	float4 Pos:POSITION;
	float4 Dif:COLOR0;
	float2 Tex:TEXCOORD0;
};

SvsOut VtxProc( float3 Pos:POSITION
			,	float4 Dif:COLOR0
			,	float2 Tex:TEXCOORD0)
{
	SvsOut Out;

	Out.Pos = float4(Pos,1);
	Out.Dif = Dif;
	Out.Tex = Tex;

	return Out;
}

float	m_fRepeatX = 10;					// Repeat for X
float	m_fRepeatY = 10;					// Repeat for Y
float4 PxlProc0(SvsOut In) : COLOR0
{
	float4 Out=0;
	float4 t0= 0;
	float2 t= 0;

	t = In.Tex;
	t.x *= m_fRepeatX;
	t.y *= m_fRepeatY;

	t0= tex2D(smp1, t)-0.5;			// Sampling from Noise Texture ==> [-0.5, 0.5];
	t0 *=0.1f;							// [-0.05, 0.05];

	t = In.Tex + float2(t0.x, t0.y);	// Modified Texture Coordinate
	t0= tex2D(smp0, t);			// Sampling from Diffuse Texture

	Out	= t0;

	return Out;
}



technique Tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VtxProc();
		PixelShader  = compile ps_2_0 PxlProc0();
	}
};
