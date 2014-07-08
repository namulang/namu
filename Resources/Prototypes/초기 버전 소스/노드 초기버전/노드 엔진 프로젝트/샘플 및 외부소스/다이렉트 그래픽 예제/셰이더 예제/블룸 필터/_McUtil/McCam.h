// Interface for the CMcCam class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MCCAMERA_H_
#define _MCCAMERA_H_

class CMcCam
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;

	D3DXMATRIX			m_mtViw;												// View Matrix
	D3DXMATRIX			m_mtPrj;												// Projection Matrix

	D3DXVECTOR3			m_vcEye;												// Camera position
	D3DXVECTOR3			m_vcLook;												// Look vector
	D3DXVECTOR3			m_vcUp;													// up vector

	FLOAT				m_fScnW;
	FLOAT				m_fScnH;
	FLOAT				m_fFov;
	FLOAT				m_fNear;
	FLOAT				m_fFar;

	FLOAT				m_fYaw;
	FLOAT				m_fPitch;
	
public:
	CMcCam();
	~CMcCam();

	INT		Create(LPDIRECT3DDEVICE9 pDev);
	INT		FrameMove();

	D3DXMATRIX	GetViewMatrix()	{	return m_mtViw;	}

public:
	void		SetParamProjection(FLOAT fScnW, FLOAT fScnH, FLOAT fFov, FLOAT fNear, FLOAT fFar);

	void		SetEye(D3DXVECTOR3 vcEye);
	void		SetLook(D3DXVECTOR3 vcLook);
	void		SetUp(D3DXVECTOR3 vcUp);

	D3DXVECTOR3	GetEye();
	D3DXVECTOR3	GetLook();
	D3DXVECTOR3	GetUp();

	void	MoveSide(FLOAT	fSpeed);
	void	MoveForward	(FLOAT	fSpeed, FLOAT fY=0);
	void	Rotation(D3DXVECTOR3 vcDelta);

	void	SetTransform();
};

#endif
