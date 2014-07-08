#include "PageJPEGPrinter.hpp"
#include "../Pages/Pages.hpp"
#include "../PerspectiveCamera/PerspectiveCamera.hpp"

namespace DX9Graphics
{
	void PageJPEGPrinter::_setCameraToTileMode(Pages& pages)
	{
		NEModuleCodeSet& ms = pages.getConnector().getPages().getValue();
		for(int n=0; n < ms.getLength() ;n++)
		{
			if(ms[n].getKeySet()[0].isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			{
				NEModuleCodeSet& ms1 = ((NEModuleCodeSetKey&) ms[n].getKeySet()[0]).getValue();
				for(int n2=0; n2 < ms1.getLength() ;n2++)
				{
					static type_code p_code = Kernal::getInstance().getModuleManager().getModule(PerspectiveCamera().getHeader()).getScriptCode();
					if(ms1[n2].getScriptCode() != p_code)
						continue;

					PerspectiveCamera& camera = (PerspectiveCamera&) ms1[n2];
					camera.getConnector().getIsViewportMaxmized().getValue() = false;
				}
			}
		}
	}

	Pages& PageJPEGPrinter::_selectPages()
	{
		static type_code pages_c = Kernal::getInstance().getModuleManager()
			.getModule(Pages().getHeader()).getScriptCode();
		NEModuleSelector s;
		s.setNodeType(NECodeType::ALL);
		s.setModuleType(NECodeType::SCRIPT);
		NECodeSet c(1);
		c.push(pages_c);
		s.setModuleCodeSet(c);

		Pages* to_return = 0;
		while( &s.getModule())
		{
			to_return = (Pages*) &s.peekModule();
			break;
		}

		return *to_return;
	}

	void PageJPEGPrinter::__renderSurface( LPDIRECT3DDEVICE9 device, LPDIRECT3DSURFACE9 surface, int page )
	{
		LPDIRECT3DSURFACE9 origin = 0;
		device->GetRenderTarget(0, &origin);
		device->SetRenderTarget(0, surface);
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 230, 230, 230), 1.0f, 0);
		device->BeginScene();

		Pages& pages = _selectPages();
		if( ! &pages) return;

		type_index origin_index = pages.getConnector().getPageIndex().getValue();
		pages.getConnector().getPageIndex().getValue() = page;

		pages.execute();


		device->EndScene();
		device->Present(0, 0, 0, 0);
		device->SetRenderTarget(0, origin);
		pages.getConnector().getPageIndex().getValue() = origin_index;
	}

	type_result PageJPEGPrinter::execute()
	{
		Pages& pages = _selectPages();
		if( ! &pages)
			return RESULT_TYPE_ERROR;
		DX9& dx9 = getDependent();
		if( ! &dx9)
			return RESULT_TYPE_ERROR;

		_setCameraToTileMode(pages);
		_purifyTargetDirectory();

		LPDIRECT3DSURFACE9 temp = _createSurface(dx9.getDevice());

		NEModuleCodeSet& ms = pages.getConnector().getPages().getValue();
		for(int n=0; n < ms.getLength() ;n++)
			_capturePage(dx9.getDevice(), temp, n);

		if(temp)
			temp->Release();

		return RESULT_SUCCESS;
	}
}