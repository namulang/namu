#pragma once

#include "../DX9DependentModule/DX9DependentModule.hpp"

namespace DX9Graphics
{
	class Pages;

	class NE_DLL PageJPEGPrinter : public DX9DependentModule
	{
	public:
		class Connector : public DX9DependentModule::Connector
		{
		public:
			virtual type_result connect(NEKeyCodeSet& keyset)
			{
				DX9DependentModule::Connector::connect(keyset);
				
				if(keyset.getLength() < 3) return RESULT_TYPE_ERROR;

				_target_directory = static_cast<NETStringKey*>( &keyset[1] );
				_bookname = static_cast<NETStringKey*>( &keyset[2] );

				return RESULT_SUCCESS;
			}

		public:
			NETStringKey& getTargetDirectory() { return *_target_directory; }
			const NETStringKey& getTargetDirectory() const { return *_target_directory; }
			NETStringKey& getBookName() { return *_bookname; }
			const NETStringKey& getBookName() const { return *_bookname; }

		private:
			NETStringKey* _target_directory;
			NETStringKey* _bookname;
		};

	public:
		PageJPEGPrinter()
			: DX9DependentModule()
		{
			
		}
		PageJPEGPrinter(const PageJPEGPrinter& rhs)
			: DX9DependentModule(rhs)
		{
			getConnector().connect(getKeySet());
		}

	public:
		Connector& getConnector() { return _connector; }
		const Connector& getConnector() const { return _connector; }

	public:
		virtual type_result execute();
		virtual type_result initialize()
		{
			DX9DependentModule::initialize();

			getKeySet().resize(getKeySet().getLength() + 2);
			getKeySet().push(NETStringKey(".\\"));
			getKeySet().push(NETStringKey("my_comic"));

			getConnector().connect(getKeySet());

			return RESULT_SUCCESS;
		}
		NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("PageJPEGPrinter.dev.dbg");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("0번키 DX9\n1번키 저장할 디렉토리\n2번키: 만화 제목");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-03-01");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(1);
			}

			return _header;
		}
		NEObject& clone() const { return *(new PageJPEGPrinter(*this)); }

	private:
		void _purifyTargetDirectory()
		{
			NETString& s = getConnector().getTargetDirectory().getValue();
			TCHAR c = s[s.getLengthLastIndex() - 1];
			if(	c == '\\'	||
				c == '/'	)
			{
				s.remove(s.getLengthLastIndex()-1);
				s.resize(s.getLength());
			}
		}
		void _capturePage(LPDIRECT3DDEVICE9 device, LPDIRECT3DSURFACE9 surface, type_int page_n)
		{
			const NETString& base_directory = getConnector().getTargetDirectory().getValue();
			NETString new_filename = base_directory + "\\" + getConnector().getBookName().getValue() + page_n + _T(".jpg");

			__renderSurface(device, surface, page_n);

			D3DXSaveSurfaceToFile(new_filename.toCharPointer(), D3DXIFF_JPG, surface, 0, 0);
		}
		void __renderSurface(LPDIRECT3DDEVICE9 device, LPDIRECT3DSURFACE9 surface, int page);
		LPDIRECT3DSURFACE9 _createSurface(LPDIRECT3DDEVICE9 device)
		{
			LPDIRECT3DSURFACE9	to_return = 0,
								origin = 0;
			device->GetRenderTarget(0, &origin);
			D3DSURFACE_DESC desc;
			origin->GetDesc(&desc);
			device->CreateRenderTarget(desc.Width, desc.Height, desc.Format, D3DMULTISAMPLE_NONE, 0, 1, &to_return, 0);

			return to_return;
		}	
		void _setCameraToTileMode(Pages& pages);

		Pages& _selectPages();
	private:
		Connector _connector;
	};
}