// Implementation of the CMcCam class.
//
////////////////////////////////////////////////////////////////////////////////


#include "../_StdAfx.h"


CMcCam::CMcCam()
{

}

CMcCam::~CMcCam()
{

}


INT CMcCam::Create(LPDIRECT3DDEVICE9 pDev)
{
	m_pDev		= pDev;

	m_fYaw		= 0.f;
	m_fPitch	= 0.f;
	m_vcEye		= D3DXVECTOR3(0,10,-180);
	m_vcLook	= D3DXVECTOR3(0,10,0);
	m_vcUp		= D3DXVECTOR3(0,1,0);

	m_fScnW	= 800;
	m_fScnH	= 600;
	m_fFov	= D3DX_PI/4.f;
	m_fNear	= 1.f;
	m_fFar	= 5000.f;

	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, m_fFov, m_fScnW/m_fScnH, m_fNear, m_fFar);
	
	return 0;
}


INT CMcCam::FrameMove()
{
	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, m_fFov, m_fScnW/m_fScnH, m_fNear, m_fFar);

	return 0;
}



void CMcCam::SetParamProjection(FLOAT fScnW, FLOAT fScnH, FLOAT fFov, FLOAT fNear, FLOAT fFar)
{
	m_fScnW	= fScnW;
	m_fScnH	= fScnH;
	m_fFov	= fFov;
	m_fNear	= fNear;
	m_fFar	= fFar;
}

void CMcCam::SetEye(D3DXVECTOR3 v)	{	m_vcEye		= v;	}
void CMcCam::SetLook(D3DXVECTOR3 v)	{	m_vcLook	= v;	}
void CMcCam::SetUp(D3DXVECTOR3 v)	{	m_vcUp		= v;	}

D3DXVECTOR3	CMcCam::GetEye()	{	return m_vcEye;		}
D3DXVECTOR3	CMcCam::GetLook()	{	return m_vcLook;	}
D3DXVECTOR3	CMcCam::GetUp()		{	return m_vcUp;		}



void CMcCam::MoveSide(FLOAT fSpeed)
{
	D3DXVECTOR3 tmp(m_mtViw._11, 0, m_mtViw._31);
	D3DXVec3Normalize(&tmp,&tmp);

	m_vcEye  += tmp * fSpeed;
	m_vcLook += tmp * fSpeed;
}


void CMcCam::MoveForward(FLOAT fSpeed, FLOAT fY)
{
	D3DXVECTOR3 tmp(m_mtViw._13, m_mtViw._23*fY, m_mtViw._33);
	D3DXVec3Normalize(&tmp,&tmp);

	m_vcEye  += tmp * fSpeed;
	m_vcLook += tmp * fSpeed;
}


void CMcCam::Rotation(D3DXVECTOR3 vcDelta)
{
	m_fYaw   = D3DXToRadian(vcDelta.x * 0.1f);
	m_fPitch   = D3DXToRadian(vcDelta.y * 0.1f);
	
	D3DXMATRIX rot;
	D3DXVECTOR3 vcZ = m_vcLook-m_vcEye;
	D3DXVECTOR3 vcX;
	D3DXMatrixRotationY(&rot, m_fYaw);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rot);
	D3DXVec3TransformCoord(&m_vcUp, &m_vcUp, &rot);
	
	m_vcLook = vcZ + m_vcEye;
	D3DXMatrixLookAtLH(&m_mtViw, &m_vcEye, &m_vcLook, &m_vcUp);

	
	vcZ = m_vcLook - m_vcEye;
	vcX =D3DXVECTOR3(m_mtViw._11, m_mtViw._21, m_mtViw._31);
	
	D3DXMatrixRotationAxis(&rot, & vcX, m_fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rot);
	D3DXVec3TransformCoord(&m_vcUp, &m_vcUp, &rot);

	m_vcLook = vcZ + m_vcEye;
}


void CMcCam::SetTransform()
{
	m_pDev->SetTransform(D3DTS_VIEW, &m_mtViw);
	m_pDev->SetTransform(D3DTS_PROJECTION, &m_mtPrj);	
}