#pragma once

#include "../Referer/Referer.hpp"

namespace DX9Graphics
{
	class NE_DLL HierarchySubReferer : public Referer
	{
		typedef HierarchySubReferer ThisClass;
		typedef Referer SuperClass;
		typedef void(ThisClass::*onSearched)(ThisClass&);

	public:
		ThisClass()
			:SuperClass(), _ball(NE_NULL), _ball_size(5.0f)
		{
			
		}
		ThisClass(const ThisClass& source)
			:SuperClass(source), _ball(NE_NULL), _ball_size(5.0f)
		{

		}

	public:
		virtual ~HierarchySubReferer()
		{
			if(_ball)
				_ball->Release();
		}

	public:
		type_float getBallSize() const {return _ball_size;}
		type_result setBallSize(type_float new_ball_size) {_ball_size = new_ball_size; return RESULT_SUCCESS;}
		NETString& getName() {return _name;}
		const NETString& getName() const {return _name;}
		float getScaledSphereRadius() 
		{
			D3DXVECTOR3 vector(getWorldMatrix()._11, getWorldMatrix()._12, getWorldMatrix()._13);
			
			return D3DXVec3Length(&vector) * _ball_size;
		}
		D3DXVECTOR3 getSphereCenter()
		{
			return D3DXVECTOR3(getTransitionMatrix()._41, getTransitionMatrix()._42, getTransitionMatrix()._43);
		}
		LPD3DXMESH getBall() { return _ball;}

	public:
		virtual type_result render()
		{
			if( ! isEnable())
				return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			static D3DMATERIAL9 _material	=	{
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f, 1.0f},
				5.0f,
			},
			_greenie	=	{
				{0.0f, 1.0f, 0.0f, 1.0f},
				{0.0f, 1.0f, 0.0f, 1.0f},
				{0.0f, 1.0f, 0.0f, 1.0f},
				{0.0f, 1.0f, 0.0f, 1.0f},
				5.0f,
			},
			_red	=	{
				{1.0f, 0.0f, 0.0f, 1.0f},
				{1.0f, 0.0f, 0.0f, 1.0f},
				{1.0f, 0.0f, 0.0f, 1.0f},
				{1.0f, 0.0f, 0.0f, 1.0f},
				5.0f,
			};

			if( &Referer::getGlobalHoveredReferer() == this)
				return _render(_greenie);
			else if( &Referer::getGlobalReferer() == this)
				return _render(_red);
			else
				if(GetAsyncKeyState(VK_SPACE) & 0x8001)
					return _render(_material);

			return RESULT_SUCCESS;
		}

	public:
		virtual type_result execute()
		{	
			//	main:
			//		CombinedMatrix 계산:
 			getWorldMatrix() = createCombinedMatrix() * getParentWorldMatrix();
			//		자식에게 전파:
			_searchModuleSet(getConnector().getModuleCodeSetKey().getValue(), &ThisClass::_updateParentWorldMatrix);
			getConnector().getModuleCodeSetKey().getValue().execute();

			return RESULT_SUCCESS;
		}

	public:
		NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("HierarchySubReferer.dev.dbg");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("0번. DX9 바인더\n1번. TransitionX\n2번.TransitionY\n3번. TransitionZ\n1번. ScaleX\n2번.ScaleY\n3번. ScaleZ\n1번. RotationX\n2번.RotationY\n3번. RotationZ");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(1);
			}

			return _header;
		}

	public:
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}

	protected:
		type_result _render(D3DMATERIAL9& material);
		void _initializeMesh()
		{
			if(_ball) return;
			DX9& dx9 = getDependent();
			if( ! &dx9) return;

			D3DXCreateSphere(dx9.getDevice(), getBallSize(), 10, 10, &_ball, NULL);
		}

	protected:
		type_float _ball_size;
		NETString _name;
		LPD3DXMESH _ball;
	};
}
