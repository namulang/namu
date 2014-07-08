// OpenGLDoc.cpp : COpenGLDoc 클래스의 구현
//

#include "stdafx.h"
#include "[!output PROJECT_NAME].h"

#include "[!output PROJECT_NAME]Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// [!output PROJECT_NAME]Doc

IMPLEMENT_DYNCREATE(C[!output PROJECT_NAME]Doc, CDocument)

BEGIN_MESSAGE_MAP(C[!output PROJECT_NAME]Doc, CDocument)
END_MESSAGE_MAP()


// C[!output PROJECT_NAME]Doc 생성/소멸

C[!output PROJECT_NAME]Doc::C[!output PROJECT_NAME]Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

C[!output PROJECT_NAME]Doc::~C[!output PROJECT_NAME]Doc()
{
}

BOOL C[!output PROJECT_NAME]Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 다시 초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// C[!output PROJECT_NAME]Doc serialization

void C[!output PROJECT_NAME]Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// C[!output PROJECT_NAME]Doc 진단

#ifdef _DEBUG
void C[!output PROJECT_NAME]Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C[!output PROJECT_NAME]Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// C[!output PROJECT_NAME]Doc 명령
