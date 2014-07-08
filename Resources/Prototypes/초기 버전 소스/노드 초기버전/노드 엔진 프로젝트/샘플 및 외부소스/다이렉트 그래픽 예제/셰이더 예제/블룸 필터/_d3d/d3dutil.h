// Helper functions and typing shortcuts for Direct3D programming.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _D3DUTIL_H_
#define _D3DUTIL_H_


#include <D3D9.h>
#include <D3DX9Math.h>



// Initializes a D3DMATERIAL9 structure, setting the diffuse and ambient
// colors. It does not set emissive or specular colors.

VOID D3DUtil_InitMaterial( D3DMATERIAL9& mtrl, FLOAT r=0.0f, FLOAT g=0.0f,
                                               FLOAT b=0.0f, FLOAT a=1.0f );




// Initializes a D3DLIGHT structure, setting the light position. The
// diffuse color is set to white, specular and ambient left as black.

VOID D3DUtil_InitLight( D3DLIGHT9& light, D3DLIGHTTYPE ltType,
                        FLOAT x=0.0f, FLOAT y=0.0f, FLOAT z=0.0f );



// Helper function to create a texture. It checks the root path first,
// then tries the DXSDK media path (as specified in the system registry).

HRESULT D3DUtil_CreateTexture( LPDIRECT3DDEVICE9 pd3dDevice, TCHAR* strTexture,
                               LPDIRECT3DTEXTURE9* ppTexture,
                               D3DFORMAT d3dFormat = D3DFMT_UNKNOWN );




// Returns a view matrix for rendering to a face of a cubemap.

D3DXMATRIX D3DUtil_GetCubeMapViewMatrix( DWORD dwFace );




// Returns a quaternion for the rotation implied by the window's cursor
// position.

D3DXQUATERNION D3DUtil_GetRotationFromCursor( HWND hWnd,
                                              FLOAT fTrackBallRadius=1.0f );



// Builds and sets a cursor for the D3D device based on hCursor.

HRESULT D3DUtil_SetDeviceCursor( LPDIRECT3DDEVICE9 pd3dDevice, HCURSOR hCursor,
                                 BOOL bAddWatermark );




// Returns the string for the given D3DFORMAT.
// bWithPrefix determines whether the string should include the "D3DFMT_"

TCHAR* D3DUtil_D3DFormatToString( D3DFORMAT format, bool bWithPrefix = true );


#endif // D3DUTIL_H





