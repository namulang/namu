// -------------------------------------------------------------
// 거리포그
// 
// Copyright (c) 2002,2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// 전역변수
// -------------------------------------------------------------
float4x4 mWVP;		// 로컬에서 투영공간으로의 좌표변환
float4	 vLightDir;	// 광원방향
float4   vCol;		// 메시색
float4   vFog;		// (Far/(Far-Near), -1/(Far-Near))
float4   vEye;		// 시점

// -------------------------------------------------------------
// 정점셰이더에서 픽셀셰이더로 넘기는 데이터
// -------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float4 Col		: COLOR0;
	float2 Tex		: TEXCOORD0;
	float  Fog		: FOG;
};

// -------------------------------------------------------------
// 정점셰이더
// -------------------------------------------------------------
VS_OUTPUT VS (
	float4 Pos		: POSITION,			// 모델정점
	float4 Normal	: NORMAL,			// 모델법선
	float2 Tex		: TEXCOORD0
){
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 출력데이터
	
	Out.Pos = mul( Pos, mWVP );          // 좌표변환
	
	Out.Col = vCol * max( dot(vLightDir, Normal), 0);	// 조명계산
	
	Out.Tex = Tex;						// 텍스처좌표
	
	// 거리포그
	float4 pos = Pos - vEye;
	Out.Fog = vFog.x + length(pos) * vFog.y;
	
	return Out;
}
// -------------------------------------------------------------
// 테크닉
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        // 셰이더
        VertexShader = compile vs_1_1 VS();
        
		FogEnable = true;			// 포그사용
        FogVertexMode = Linear;		// 선형 포그
        FogColor = 0xd8e3fe;		// 포그 색
    }
}
