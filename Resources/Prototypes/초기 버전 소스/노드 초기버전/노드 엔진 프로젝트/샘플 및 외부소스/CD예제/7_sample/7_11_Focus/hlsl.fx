// ------------------------------------------------------------
// Æ÷Ä¿½º ÇÊÅÍ
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// ------------------------------------------------------------

// ------------------------------------------------------------
// ÅØ½ºÃ³
// ------------------------------------------------------------
texture SrcTex;
sampler SrcSamp = sampler_state
{
    Texture = <SrcTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// ------------------------------------------------------------
texture BlurTex;
sampler BlurSamp = sampler_state
{
    Texture = <BlurTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// ------------------------------------------------------------
texture BlendTex;
sampler BlendSamp = sampler_state
{
    Texture = <BlendTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// ------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ¿¡¼­ ÇÈ¼¿¼ÎÀÌ´õ·Î ³Ñ±â´Â µ¥ÀÌÅÍ
// ------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float2 Tex0			: TEXCOORD0;
	float2 Tex1			: TEXCOORD1;
	float2 Tex2			: TEXCOORD2;
	float2 Tex3			: TEXCOORD3;
};

// ------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ
// ------------------------------------------------------------
VS_OUTPUT VS_pass0 (
      float4 Pos    : POSITION           // ¸ðµ¨Á¤Á¡
     ,float4 Tex0   : TEXCOORD0	         // ÅØ½ºÃ³ÁÂÇ¥
     ,float4 Tex1   : TEXCOORD1	         // ÅØ½ºÃ³ÁÂÇ¥
     ,float4 Tex2   : TEXCOORD2	         // ÅØ½ºÃ³ÁÂÇ¥
     ,float4 Tex3   : TEXCOORD3	         // ÅØ½ºÃ³ÁÂÇ¥
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // Ãâ·Âµ¥ÀÌÅÍ
    
    // À§Ä¡ÁÂÇ¥
    Out.Pos = Pos;
    
    Out.Tex0 = Tex0;
    Out.Tex1 = Tex1;
    Out.Tex2 = Tex2;
    Out.Tex3 = Tex3;
    
    return Out;
}

// ------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// ------------------------------------------------------------
float4 PS_pass0 (VS_OUTPUT In) : COLOR
{
	float4 Out = 0;
	
	float3 col0 = tex2D( SrcSamp,   In.Tex0 );
	float3 col1 = tex2D( SrcSamp,   In.Tex1 );
	float3 col2 = tex2D( SrcSamp,   In.Tex2 );
	float3 col3 = tex2D( SrcSamp,   In.Tex3 );
	
	Out.xyz = 0.25f*(col0+col1+col2+col3);
	
	return Out;
}


// ------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ
// ------------------------------------------------------------
VS_OUTPUT VS_pass1 (
      float4 Pos    : POSITION           // ¸ðµ¨Á¤Á¡
     ,float4 Tex0   : TEXCOORD0	         // ÅØ½ºÃ³ÁÂÇ¥
     ,float4 Tex1   : TEXCOORD1	         // ÅØ½ºÃ³ÁÂÇ¥
     ,float4 Tex2   : TEXCOORD2	         // ÅØ½ºÃ³ÁÂÇ¥
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // Ãâ·Âµ¥ÀÌÅÍ
    
    // À§Ä¡ÁÂÇ¥
    Out.Pos = Pos;
    
    Out.Tex0 = Tex0;
    Out.Tex1 = Tex1;
    Out.Tex2 = Tex2;
    
    return Out;
}

// ------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// ------------------------------------------------------------
float4 PS_pass1 (VS_OUTPUT In) : COLOR
{
	float4 Out = 0;
	
	float3 col  = tex2D( SrcSamp,   In.Tex0 );
	float3 blur = tex2D( BlurSamp,  In.Tex1 );
	float3 w    = tex2D( BlendSamp, In.Tex2 );
	
	Out.xyz = w*col + (1-w)*blur;
	
	return Out;
}

// ------------------------------------------------------------
// Å×Å©´Ð
// ------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS_pass0();
        PixelShader  = compile ps_1_1 PS_pass0();
        
        AddressU[0] = Clamp;
        AddressV[0] = Clamp;
        AddressU[1] = Clamp;
        AddressV[1] = Clamp;
        AddressU[2] = Clamp;
        AddressV[2] = Clamp;
        AddressU[3] = Clamp;
        AddressV[3] = Clamp;
        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MinFilter[1] = Linear;
        MagFilter[1] = Linear;
        MinFilter[2] = Linear;
        MagFilter[2] = Linear;
        MinFilter[3] = Linear;
        MagFilter[3] = Linear;
    }
    pass P1
    {
        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS_pass1();
        PixelShader  = compile ps_1_1 PS_pass1();

        AddressU[0] = Clamp;
        AddressV[0] = Clamp;
        AddressU[1] = Clamp;
        AddressV[1] = Clamp;
        AddressU[2] = Clamp;
        AddressV[2] = Clamp;
	}
}
