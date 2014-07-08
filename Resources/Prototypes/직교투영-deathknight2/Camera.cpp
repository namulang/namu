#include "Camera.h"

CCamera::CCamera(void)
{
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_Rot);
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
}

CCamera::~CCamera(void)
{
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 카메라 투영 셋팅 
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CCamera::SetUpProjection(LPDIRECT3DDEVICE9 Device, float fovY, float Aspect, float fnear, float ffar)
{
	//D3DXMatrixPerspectiveFovLH(&m_Projection, fovY, Aspect, fnear, ffar);
	 D3DXMatrixOrthoLH(&m_Projection, 800.0f, 600.0f, 1.0f, 1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &m_Projection);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 위치 값을 받는다
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CCamera::SetPosition(D3DXVECTOR3* Pos)
{
	m_vPosition = *Pos;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 Look의 값을 받는다
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
// 앞걸음질
void CCamera::Walk(float Units)
{
	D3DXVECTOR3 vWalk;

	vWalk.x = m_Rot._31;
	vWalk.y = m_Rot._32;
	vWalk.z = m_Rot._33;

	D3DXVec3Normalize(&vWalk, &vWalk);

	m_vPosition += vWalk * Units;

}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 옆걸음질
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.

void CCamera::Strafe(float Units)
{
	D3DXVECTOR3 vStrafe;

	vStrafe.x = m_Rot._11;
	vStrafe.y = m_Rot._12;
	vStrafe.z = m_Rot._13;

	D3DXVec3Normalize(&vStrafe, &vStrafe);

	m_vPosition += vStrafe * Units;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 위로 올라가는것
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
 void CCamera::Fly(float Units)
{
	D3DXVECTOR3 vFly;

	vFly.x = m_Rot._21;
	vFly.y = m_Rot._22;
	vFly.z = m_Rot._23;

	D3DXVec3Normalize(&vFly, &vFly);

	m_vPosition += vFly * Units;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 실시간 업데이트 
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
void CCamera::Update(LPDIRECT3DDEVICE9 Device)
{
	m_Rot._41 = m_vPosition.x;
	m_Rot._42 = m_vPosition.y;
	m_Rot._43 = m_vPosition.z	;
	D3DXMatrixInverse(&m_View, 0, &m_Rot);
	Device->SetTransform(D3DTS_VIEW, &m_View);
}


void CCamera::UpdateYallPitchRoll(float fYaw, float fPitch, float fRoll)
{
	m_fYaw += fYaw;
	m_fPitch += fPitch;
	m_fRoll += fRoll;
	D3DXMatrixRotationYawPitchRoll(&m_Rot, m_fYaw, m_fPitch, m_fRoll);
}