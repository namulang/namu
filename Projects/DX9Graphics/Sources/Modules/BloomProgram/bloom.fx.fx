//
// Shader Example.
// Copyleft (c) 2007 Heesung Oh(Galic Studio). All rights Not reserved.
////////////////////////////////////////////////////////////////////////////

// 3D Scene Texture

sampler smp0:register(s0);
sampler smp1:register(s1);
sampler smp2:register(s2);
sampler smp3:register(s3);

struct SvsOut
{
	float4	Pos : POSITION;
	float2	Tex : TEXCOORD0;
};

float	m_TexW = 640;
float	m_TexH = 480;
SvsOut VtxProc0(	float3 Pos: POSITION
				,	float2 Tex: TEXCOORD0)
{
	SvsOut Out = (SvsOut)0;

	Out.Pos = float4(Pos, 1);
	Out.Tex = Tex;

	return Out;
}

int	_gamma = 4;
float4 Pxlsharp(SvsOut In) : COLOR0
{
	float4	Out= 0;

	float4 t0 = tex2D(smp0, In.Tex);
	Out = pow(t0, _gamma);
	Out *= 30;

	return Out;
}

static float fBgn = 7;
static float fIns=0.1f;
static float fInc=2.0f;
static float fDelta= 0.025f;
float4 PxlBlurX(SvsOut In) : COLOR0
{
	float4	Out=0;
	float4	t = 0;

	float2	uv = 0;

	for(int i=-fBgn; i<=fBgn; ++i)
	{
		uv = In.Tex + float2(i*fInc/m_TexW, 0);
		Out += tex2D(smp0, uv) * exp( -i*i * fDelta);
	}

	Out *=fIns;
	//Out.w = 1;
	return Out;
}

float4 PxlBlurY(SvsOut In) : COLOR0
{
	float4	Out=0;
	float4	t = 0;

	float2	uv = 0;

	for(int i=-fBgn; i<=fBgn; ++i)
	{
		uv = In.Tex + float2(0, i*fInc/m_TexH);
		Out += tex2D(smp0, uv) * exp( -i*i * fDelta);
	}

	Out *=fIns;
	//Out.w = 1;
	return Out;
}

// Final Process. Multi texturing
float	_bloom = 0.35f;
float4 PxlMulti(SvsOut In) : COLOR0
{
	float4	Out=0;

	float4 t0 = tex2D(smp0, In.Tex);
	float4 t1 = tex2D(smp1, In.Tex);

	Out = t0 + t1 * _bloom;	
	//Out.w = 1;

	return Out;
}


technique Tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 Pxlsharp();
	}
	pass P1
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 PxlBlurX();
	}
	pass P2
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 PxlBlurY();
	}
	pass P3
	{
		VertexShader = compile vs_2_0 VtxProc0();
		PixelShader  = compile ps_2_0 PxlMulti();
	}
};