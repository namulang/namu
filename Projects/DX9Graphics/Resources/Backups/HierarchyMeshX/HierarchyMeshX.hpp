#pragma once

#include "../RenderableResource/RenderableResource.hpp"
#include <vector>

namespace DX9Graphics
{
	class HierarchyReferer;

	class NE_DLL HierarchyMeshX : public RenderableResource
	{
		typedef HierarchyMeshX ThisClass;
		typedef RenderableResource SuperClass;

	public:
#include "innerclass/BoneFrame/BoneFrame.hpp"
#include "innerclass/BoneMesh/BoneMesh.hpp"
#include "innerclass/OnHierarchyLoad/OnHierarchyLoad.hpp"

		typedef NEListTemplate<BoneFrame> BoneFrameList;

	public:
		ThisClass()
			: SuperClass()
		{
			_release();
		}
		ThisClass(const ThisClass& source)
			: SuperClass(source)
		{
			//	이미 경로값은 assign이 끝나있다.
			//	_materials, _textures를 assign 방지를 위해서 정의하였다.
			_release();
		}

	public:
		virtual ~HierarchyMeshX()
		{
			_release();
		}

	public:
		type_result setHierarchyReferer(HierarchyReferer& source);
		type_ubyte getFaceType() const {return _face_type;}
		type_ubyte getMaxFaceType() const { return _max_face_type; }
		void setFaceType(type_ubyte face_type) { _face_type = face_type;}

	public:
		virtual bool isResourceRetrieved()
		{
			return _framelist.getLength() > 0;
		}
		virtual type_result retrieveResource()
		{
			NETString& path = static_cast<NETStringKey&>(getKeySet()[1]).getValue();
			DX9& dx9 = getDependent();
			if( ! &dx9)
			{
				ALERT_ERROR(" : DX9가 없음");
				return RESULT_TYPE_ERROR;
			}
		


			//	main:			
			NETStringSet splited;
			path.split("\\", splited);
			splited.pop();
			NETString work_directory;
			for(int n=0; n < splited.getLength() ;n++)
				work_directory += splited[n] + "\\";		

			OnHierarchyLoad handler(*this, work_directory);
			LPD3DXFRAME dummy = 0;
			
			HRESULT result = D3DXLoadMeshHierarchyFromX(path.toCharPointer(), D3DXMESH_MANAGED, dx9.getDevice(), &handler, NULL, &dummy, NE_NULL);
			_max_face_type = handler.getFaceCount();
			return true;
		}
		virtual type_result render();
		virtual type_result renderOnPicked();
		virtual type_result renderOnHover();

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			SuperClass::operator=(source);

			return *this;
		}

	public:
		const BoneFrameList& getFrameList() const {return _framelist;}
		BoneFrameList& getFrameList() {return _framelist;}
		BoneFrame& getRootFrame() {return _framelist[0];}
		const BoneFrame& getRootFrame() const {return _framelist[0];}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;

	public:
		virtual type_result execute()
		{
			if( ! isResourceRetrieved())
				return retrieveResource();

			return RESULT_SUCCESS;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}

	protected:
		type_result _renderByReculsive(BoneFrame& mesh, type_byte status, LPDIRECT3DDEVICE9 device, int container);
	
	private:
		void _release()
		{
			D3DXFrameDestroy(&_framelist[0], &OnHierarchyLoad(*this, ""));
			_face_type = 0;
			_framelist.release();
			_max_face_type = 0;
		}

	protected:
		BoneFrameList _framelist;
		HierarchyReferer* _referer;
		type_ubyte _face_type, _max_face_type;
	};
}