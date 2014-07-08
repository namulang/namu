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
	float4	Pos : POSITION;
	float2	Tex : TEXCOORD0;
};



float	m_TexW;
float	m_TexH;
SvsOut VtxProc0( float3 Pos: POSITION, float2 Tex: TEXCOORD0)
{
	SvsOut Out = (SvsOut)0;

	Out.Pos = float4(Pos, 1);
	Out.Tex = Tex;

	return Out;
}


static const float Weight[13]=
{
   0.0561, 0.1353, 0.278, 0.4868, 0.7261, 0.9231,
1, 0.9231, 0.7261, 0.4868, 0.278, 0.1353, 0.0561};

static const float Total = 6.2108;

float4 PxlBlurX(SvsOut In) : COLOR0
{
	float4	Out=0;

	float2	t = In.Tex;
	float2	uv = 0;

	float	tu= 2./m_TexW;

	for(int i=-6; i<6; ++i)
	{
		uv = t+ float2(tu *i, 0);
		Out += Weight[6+i] * tex2D(smpDif, uv);
	}

	Out /=Total;

	return Out;
}


float4 PxlBlurY(SvsOut In) : COLOR0
{
	float4	Out=0;

	float2	t = In.Tex;
	float2	uv = 0;

	float	tv= 1./m_TexH;

	for(int i=-6; i<6; ++i)
	{
		uv = t+ float2(0, tv *i);
		Out += Weight[6+i] * tex2D(smpDif, uv);
	}

	Out /=Total;

	return Out;
}


technique Tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 PxlBlurX();
	}

	pass P1
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 PxlBlurY();
	}
};