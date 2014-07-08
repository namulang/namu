#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	class NE_DLL Pages : public DX9DependentModule
	{
		typedef Pages ThisClass;
		typedef DX9DependentModule SuperClass;

	public:
		class Connector : public DX9DependentModule::Connector
		{
		public:
			virtual type_result connect(NEKeyCodeSet& keyset)
			{
				if(keyset.getLength() < 3)
					return RESULT_TYPE_ERROR;

				_page_index = static_cast<NEUIntKey*>(&keyset[1]);
				_pages = static_cast<NEModuleCodeSetKey*>(&keyset[2]);

				return RESULT_SUCCESS;
			}

		public:
			NEModuleCodeSetKey& getPages() { return *_pages; }
			const NEModuleCodeSetKey& getPages() const { return *_pages; }
			NEUIntKey& getPageIndex() { return *_page_index; }
			const NEUIntKey& getPageIndex() const { return *_page_index; }

		private:
			NEUIntKey* _page_index;
			NEModuleCodeSetKey* _pages;
		};

	public:
		ThisClass()
			: SuperClass(), _font(0)
		{
			_release();
		}
		ThisClass(const ThisClass& rhs)
			: SuperClass(rhs), _font(0)
		{
			_release();
			getConnector().connect(getKeySet());
		}

	public:
		Connector& getConnector() { return _connector; }
		const Connector& getConnector() const { return _connector; }

	public:
		virtual type_result initialize() 
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			if(keyset.getLength() == keyset.getSize())
				keyset.resize(keyset.getLength()+2);
			keyset.push(NEUIntKey(0));
			keyset.push(NEModuleCodeSetKey());

			getConnector().connect(keyset);

			return RESULT_SUCCESS;
		}

	public:
		virtual type_result execute() 
		{
			NEModuleCodeSet& ms = getConnector().getPages().getValue();
			type_uint index = getConnector().getPageIndex().getValue();
			if((int) index > ms.getLengthLastIndex())
			{
				ALERT_ERROR(" : 주어진 인덱스가 최대 인덱스를 넘어섬");
				return RESULT_TYPE_ERROR;
			}



			//	main:
			DX9& dx9 = (DX9&) getDependent();
			if( ! &dx9)
			{
				ALERT_ERROR(" : DX가 없습니다");
				return RESULT_TYPE_ERROR;
			}
			if( ! _font)
				_initiailizeFont();
			LPDIRECT3DDEVICE9 device = dx9.getDevice();
			D3DVIEWPORT9 origin, temp;
			device->GetViewport(&origin);
			temp.X = 0;
			temp.Y = 0;
			temp.Height = dx9.getPresentParameters().BackBufferHeight;
			temp.Width = dx9.getPresentParameters().BackBufferWidth;
			temp.MinZ = 0.0f;
			temp.MaxZ = 100.0f;
			device->SetViewport(&temp);
			device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 230, 230, 230), 1.0f, 0);
			device->SetViewport(&origin);
			
			ms[index].execute();

			device->SetViewport(&temp);
			_renderPageNumber(dx9);
			device->SetViewport(&origin);
			return RESULT_SUCCESS;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const 
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("Pages.dev.dbg");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("0번키 DX9\n1번키 Page 인덱스키 \n2번키: 카메라가 담길 모듈셋");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-03-01");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(1);
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const { return *(new ThisClass(*this)); }

	protected:
		void _initiailizeFont()
		{
			_release();

			DX9& dx9 = getDependent();
			if( ! &dx9)
			{
				ALERT_ERROR(" : dx9 없음");
				return;
			}
			D3DXCreateFont(dx9.getDevice(), 15, 0, FW_THIN, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
				ANTIALIASED_QUALITY , DEFAULT_PITCH || FF_DONTCARE, _T("굴림체"), &_font);
		}
		void _renderPageNumber(DX9& dx9)
		{
			//	백버퍼에 바로 그린다.
			if( ! _font) return;
			LPDIRECT3DDEVICE9 device = dx9.getDevice();

			type_uint	page_index			= getConnector().getPageIndex().getValue(),
						left_page_number	= (2 * page_index + 1),
						right_page_number	= 2 * (page_index+1),
						screen_width		= dx9.getPresentParameters().BackBufferWidth * 2,
						screen_half_width	= screen_width / 2,
						left_page_x			= screen_half_width / 2,
						right_page_x		= screen_half_width + left_page_x,
						screen_height		= dx9.getPresentParameters().BackBufferHeight * 2,
						adjustment			= 20,
						font_height			= 15,
						page_y				= (screen_height - adjustment) - font_height * 2;
			
			NETString	left_page = "- " + NETString((int)left_page_number)+ " -",
						right_page = "- " + NETString((int)right_page_number) + " -";

			D3DXMATRIX origin_world, origin_view;
			device->GetTransform(D3DTS_WORLD, &origin_world);
			device->GetTransform(D3DTS_VIEW, &origin_view);
			device->BeginScene();
			RECT	left_rect	= {left_page_x, page_y, 0, 0},
					right_rect	= {right_page_x, page_y, 0, 0};
			_font->DrawTextW(0, left_page.toCharPointer(), -1, &left_rect, DT_NOCLIP | DT_VCENTER | DT_CENTER, 0xff000000);
			_font->DrawTextW(0, right_page.toCharPointer(), -1, &right_rect, DT_NOCLIP | DT_VCENTER | DT_CENTER, 0xff000000);
			device->EndScene();
			device->SetTransform(D3DTS_WORLD, &origin_world);
			device->SetTransform(D3DTS_VIEW, &origin_view);
		}
		void _release()
		{
			if(_font)
				_font->Release();
		}

	private:
		Connector _connector;
		LPD3DXFONT _font;
	};
}