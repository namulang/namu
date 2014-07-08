// -------------------------------------------------------------
// º¼·ýÆ÷±×
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// Àü¿ªº¯¼ö
// -------------------------------------------------------------
float4x4 mWVP;		// ·ÎÄÃ¿¡¼­ Åõ¿µ°ø°£À¸·ÎÀÇ ÁÂÇ¥º¯È¯
float4x4 mWVPT;		// ·ÎÄÃ¿¡¼­ ÅØ½ºÃ³°ø°£À¸·ÎÀÇ ÁÂÇ¥º¯È¯
float4	 vLightDir;	// ±¤¿ø¹æÇâ
float4   vCol;		// ¸Þ½Ã»ö

// -------------------------------------------------------------
// ÅØ½ºÃ³
// -------------------------------------------------------------
texture DecaleMap;
sampler DecaleMapSamp = sampler_state
{
    Texture = <DecaleMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};


// -------------------------------------------------------------
// -------------------------------------------------------------
// ÆÐ½º1:»ö¹öÆÛ¿Í ±íÀÌ¹öÆÛ »ý¼º
// -------------------------------------------------------------
// -------------------------------------------------------------

// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ¿¡¼­ ÇÈ¼¿¼ÎÀÌ´õ·Î ³Ñ±â´Â µ¥ÀÌÅÍ
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float4 Col		: COLOR0;
	float2 Tex		: TEXCOORD0;
	float2 Depth	: TEXCOORD1;
};

// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ
// -------------------------------------------------------------
VS_OUTPUT VS (
	  float4 Pos	: POSITION          // Á¤Á¡À§Ä¡
	, float4 Normal	: NORMAL			// ¹ý¼±º¤ÅÍ
	, float4 Tex	: TEXCOORD0			// ÅØ½ºÃ³ÁÂÇ¥
){
	VS_OUTPUT Out = (VS_OUTPUT)0;       // Ãâ·Âµ¥ÀÌÅÍ
	
	float4 pos = mul( Pos, mWVP );		// ÁÂÇ¥º¯È¯
	
	Out.Pos = pos;						// À§Ä¡ÁÂÇ¥
	
	Out.Col = vCol * max( dot(vLightDir, Normal), 0);	// Á¶¸í°è»ê
	
	Out.Tex = Tex;						// ÅØ½ºÃ³ÁÂÇ¥
	
	Out.Depth = 0.1f*pos.w;				// ±íÀÌ
	
	return Out;
}
// -------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õÀÇ Ãâ·Âµ¥ÀÌÅÍ
// -------------------------------------------------------------
struct PS_OUTPUT {
	float4 Color : COLOR0;
	float4 Depth : COLOR1;
};
// -------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// -------------------------------------------------------------
PS_OUTPUT PS ( VS_OUTPUT In ) {
	
	PS_OUTPUT Out = ( PS_OUTPUT ) 0;
	
	// ±âº»»ö
	Out.Color = In.Col * tex2D( DecaleMapSamp, In.Tex );
	
	//±íÀÌ
	Out.Depth.x = In.Depth;

    return Out;
}

// -------------------------------------------------------------
// Å×Å©´Ð
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();

		Sampler[0] = (DecaleMapSamp);
    }
}


// -------------------------------------------------------------
// -------------------------------------------------------------
// ÆÐ½º2:Æ÷±×¸Ê »ý¼º
// -------------------------------------------------------------
// -------------------------------------------------------------

// -------------------------------------------------------------
// ÅØ½ºÃ³
// -------------------------------------------------------------
texture DepthMap;
sampler DepthMapSamp = sampler_state
{
    Texture = <DepthMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
texture FrameBuffer;
sampler FrameBufferSamp = sampler_state
{
    Texture = <FrameBuffer>;
    MinFilter = POINT;
    MagFilter = POINT;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ¿¡¼­ ÇÈ¼¿¼ÎÀÌ´õ·Î ³Ñ±â´Â µ¥ÀÌÅÍ
// -------------------------------------------------------------
struct VS_OUTPUT_VOLUME
{
	float4 Pos		: POSITION;
	float4 Depth	: COLOR0;
	float4 Tex		: TEXCOORD0;
};
// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ
// -------------------------------------------------------------
VS_OUTPUT_VOLUME VS_VOLUME (
	  float4 Pos	: POSITION          // Á¤Á¡ÁÂÇ¥
	, float4 Tex	: TEXCOORD0			// ÅØ½ºÃ³ÁÂÇ¥
){
	VS_OUTPUT_VOLUME Out = (VS_OUTPUT_VOLUME)0;        // Ãâ·Âµ¥ÀÌÅÍ
	
	float4 pos = mul( Pos, mWVP );	// ÁÂÇ¥º¯È¯
	
	Out.Pos = pos;					// À§Ä¡ÁÂÇ¥
	
	Out.Tex = mul(Pos, mWVPT);		// ÅØ½ºÃ³ÁÂÇ¥
	
	Out.Depth = 0.1f*pos.w;			// ±íÀÌ
	
	return Out;
}
// -------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// -------------------------------------------------------------
float4 PS_VOLUME1( VS_OUTPUT_VOLUME In) : COLOR
{
	float depth_map    = tex2Dproj(    DepthMapSamp, In.Tex ).x;
	float frame_buffer = tex2Dproj( FrameBufferSamp, In.Tex ).x;
	
	return frame_buffer
	 + 10.0f*((depth_map < In.Depth.x) ? depth_map : In.Depth.x);
}

// -------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// -------------------------------------------------------------
float4 PS_VOLUME2 ( VS_OUTPUT_VOLUME In) : COLOR
{
	float depth_map    = tex2Dproj(    DepthMapSamp, In.Tex ).x;
	float frame_buffer = tex2Dproj( FrameBufferSamp, In.Tex ).x;
	
	return frame_buffer
	 - 10.0f*((depth_map < In.Depth.x) ? depth_map : In.Depth.x);
}

// -------------------------------------------------------------
// Å×Å©´Ð
// -------------------------------------------------------------
technique TVolume
{
    pass P0
    {
		Sampler[0] = (DepthMapSamp);
		Sampler[1] = (FrameBufferSamp);
		
		// ·»´õ¸µ ½ºÅ×ÀÌÆ®
        CullMode = CW;// — –Ê‚ðƒŒƒ“ƒ_ƒŠƒ“ƒO
		Zenable = False;
        
        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS_VOLUME ();
        PixelShader  = compile ps_2_0 PS_VOLUME1();

    }
    pass P1
    {
		Sampler[0] = (DepthMapSamp);
		Sampler[1] = (FrameBufferSamp);
		
		// ·»´õ¸µ ½ºÅ×ÀÌÆ®
        CullMode = CCW;// ¾Õ¸é·»´õ¸µ
		Zenable = False;
        
        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS_VOLUME ();
        PixelShader  = compile ps_2_0 PS_VOLUME2();
    }
}

// -------------------------------------------------------------
// -------------------------------------------------------------
// ÆÐ½º4:Æ÷±×ÇÕ¼º
// -------------------------------------------------------------
// -------------------------------------------------------------

// -------------------------------------------------------------
// ÅØ½ºÃ³
// -------------------------------------------------------------
texture FogMap;
sampler FogMapSamp = sampler_state
{
    Texture = <FogMap>;
    MinFilter = POINT;
    MagFilter = POINT;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
texture ColorMap;
sampler ColorMapSamp = sampler_state
{
    Texture = <ColorMap>;
    MinFilter = POINT;
    MagFilter = POINT;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ¿¡¼­ ÇÈ¼¿¼ÎÀÌ´õ·Î ³Ñ±â´Â µ¥ÀÌÅÍ
// -------------------------------------------------------------
struct VS_OUTPUT_FINAL
{
	float4 Pos		: POSITION;
	float2 Tex		: TEXCOORD0;
};
// -------------------------------------------------------------
// Á¤Á¡¼ÎÀÌ´õ
// -------------------------------------------------------------
VS_OUTPUT_FINAL VS_FINAL (
	  float4 Pos	: POSITION          // Á¤Á¡À§Ä¡
	, float2 Tex	: TEXCOORD0			// ÅØ½ºÃ³ÁÂÇ¥
){
	VS_OUTPUT_FINAL Out;        // Ãâ·Âµ¥ÀÌÅÍ
	
	// À§Ä¡ÁÂÇ¥
	Out.Pos = Pos;
	
	// ÅØ½ºÃ³ÃÒÇ¥
	Out.Tex = Tex;
	
	return Out;
}
// -------------------------------------------------------------
// ÇÈ¼¿¼ÎÀÌ´õ
// -------------------------------------------------------------
float4 PS_FINAL ( VS_OUTPUT_FINAL In) : COLOR
{
	float  fog_map = tex2D( FogMapSamp,   In.Tex ).x;
	float4 col_map = tex2D( ColorMapSamp, In.Tex );
	float4 fog_color = {0.84f, 0.88f, 1.0f, 1.0f};
	
	return lerp(col_map, fog_color, fog_map);
}

// -------------------------------------------------------------
// Å×Å©´Ð
// -------------------------------------------------------------
technique TFinal
{
    pass P0
    {
		Sampler[0] = (FogMapSamp);
		Sampler[1] = (ColorMapSamp);
		
		// ·»´õ¸µ ½ºÅ×ÀÌÆ®
        AlphaBlendEnable = False;

        // ¼ÎÀÌ´õ
        VertexShader = compile vs_1_1 VS_FINAL();
        PixelShader  = compile ps_2_0 PS_FINAL();
    }
}
