#pragma once

#include "../Particle/Particle.hpp"
#include "../ShaderProgram/ShaderProgram.hpp"

namespace DX9Graphics
{
	class NE_DLL Camera : public Particle
	{
	public:
		typedef Particle SuperClass;
		typedef Camera ThisClass;
		typedef NEArrayTemplate<ShaderProgram*, true> ShaderProgramSet;

	public:
		NETArgument<NENodeSelector>		arg_targets;		
		NETArgument<NEUIntKey>			arg_viewport_x;
		NETArgument<NEUIntKey>			arg_viewport_y;
		NETArgument<NEUIntKey>			arg_viewport_width;
		NETArgument<NEUIntKey>			arg_viewport_height;
		NETArgument<NEUIntKey>			arg_viewport_minimum_z;
		NETArgument<NEUIntKey>			arg_viewport_maximum_z;
		NETArgument<NEModuleCodeSet>	arg_shaders;

	public:
		struct EulerAngles
		{
			EulerAngles() : x_axis_angle(0.0f), y_axis_angle(0.0f), z_axis_angle(0.0f) {}
			EulerAngles(type_float new_x, type_float new_y, type_float new_z)
				: x_axis_angle(new_x), y_axis_angle(new_y), z_axis_angle(new_z) {}
			EulerAngles(const D3DXVECTOR3& look)
				: x_axis_angle(0.0f), y_axis_angle(0.0f), z_axis_angle(0.0f)
			{
				fromVector(look);
			}

			type_float x_axis_angle;
			type_float y_axis_angle;
			type_float z_axis_angle;

			EulerAngles& operator*=(type_float value)
			{
				x_axis_angle *= value;
				y_axis_angle *= value;
				z_axis_angle *= value;

				return *this;
			}
			D3DXVECTOR3 toVector() const
			{
				D3DXVECTOR3 to_return;
				type_float adjustment = D3DX_PI / 180.0f;
				type_float cosx = cosf(x_axis_angle * adjustment);
				to_return.x = cosx * sinf(y_axis_angle * adjustment);
				to_return.y = -sinf(x_axis_angle * adjustment);
				to_return.z = cosx * cosf(y_axis_angle * adjustment);

				return to_return;
			}
			void fromVector(const D3DXVECTOR3& look);

		private:
			bool _isPredictionOfEulerConversionRight(type_float predicted_x_radian, type_float predicted_y_radian, type_float right_answer) const;
			bool _isEqual(type_float lhs, type_float rhs) const
			{
				const type_float EPSILON = 0.0001f;
				if(	lhs > rhs - EPSILON &&
					lhs < rhs + EPSILON	)
					return true;
				return false;
			}

		};

	public:
		Camera()
			: SuperClass()
		{
			_release();
		}
		Camera(const Camera& source)
			: SuperClass(source)
		{
			_assign(source);
		}

	public:
		const ThisClass& operator=(const ThisClass& source)
		{
			if(this == &source) return *this;

			SuperClass::operator=(source);

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			if(	SuperClass::operator!=(source)		||
				_look		!= source._look			||
				_up			!= source._up			||
				_projection	!= source._projection	||
				_view		!= source._view			||
				_right		!= source._right		)
				return false;

			return true;			
		}
		bool operator!=(const ThisClass& source) const
		{
			return ! operator==(source);
		}

	public:
		D3DXMATRIX& getViewMatrix() { return _view; }
		const D3DXMATRIX& getViewMatrix() const { return _view; }
		D3DXMATRIX& getProjectionMatrix() { return _projection; }
		const D3DXMATRIX& getProjectionMatrix() const { return _projection; }

	protected:
		virtual type_result _onFetchModule()
		{
			SuperClass::_onFetchModule();

			arg_viewport_x.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_viewport_y.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_viewport_width.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_viewport_height.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_viewport_minimum_z.setPurposeLimitation(NEArgumentBase::READ_BY);
			arg_viewport_maximum_z.setPurposeLimitation(NEArgumentBase::READ_BY);

			return RESULT_SUCCESS;
		}
		virtual type_result _onFetchArguments(NEArgumentList& tray)
		{
			tray.push(arg_targets);

			SuperClass::_onFetchArguments(tray);

			tray.push(arg_viewport_x);			
			tray.push(arg_viewport_y);			
			tray.push(arg_viewport_width);		
			tray.push(arg_viewport_height);		
			tray.push(arg_viewport_minimum_z);	
			tray.push(arg_viewport_maximum_z);	
			tray.push(arg_shaders);	

			return RESULT_SUCCESS;
		}

	public:
		const NEExportable::ModuleHeader& getHeader() const
		{

		}
		virtual type_result render()
		{
			if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			

			//	main:
			DX9& dx9 = _getBinded();
			LPDIRECT3DDEVICE9 device = &dx9 ? dx9.getDevice() : 0;
			if( ! device)
			{
				ALERT_ERROR("DX9가 바인드 되지 않았습니다.");
				return RESULT_TYPE_ERROR;
			}			
			D3DVIEWPORT9 vp = createViewPort();
			device->SetViewport(&vp);
			/*
				ModuleSet에 담긴 Module이 ShaderProgram의 하위클래스라는 걸
				알 도리가 없음. getType이 지정되지 않기 때문에.
				TypeManager가 추가되기 전까지는 현재는 그냥 Shader로 강제 캐스팅.
			*/
			NEModuleCodeSet& moduleset = getShaderPrograms();
			for(int n=0; n < moduleset.getSize() ;n++)
			{
				ShaderProgram& program = static_cast<ShaderProgram&>(moduleset[n]);
				program._render(*this);
			}

			return RESULT_SUCCESS;
		}
		virtual type_result execute()
		{
			if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
			
			//	main:
			_updateRightVector();
			_updateLookVector();
			_updateUpVector();
			_updateViewMatrix();
			_updateProjectionMatrix();

			_dockTransforms();

			return render();
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			SuperClass::serialize(saver);

			saver.execute((char*) &_view, sizeof(D3DXMATRIX));
			saver.execute((char*) &_projection, sizeof(D3DXMATRIX));
			saver.execute((char*) &_right, sizeof(D3DXVECTOR3));
			saver.execute((char*) &_look, sizeof(D3DXVECTOR3));
			saver.execute((char*) &_up, sizeof(D3DXVECTOR3));

			return saver;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			loader.execute((char*) &_view, sizeof(D3DXMATRIX));
			loader.execute((char*) &_projection, sizeof(D3DXMATRIX));
			loader.execute((char*) &_right, sizeof(D3DXVECTOR3));
			loader.execute((char*) &_look, sizeof(D3DXVECTOR3));
			loader.execute((char*) &_up, sizeof(D3DXVECTOR3));

			return loader;
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}

	public:
		type_result yaw(type_float angle)
		{
			D3DXMATRIX rotated;		

			D3DXMatrixRotationAxis(&rotated, &_up, angle);
			// rotate _right and _look around _up
			D3DXVec3TransformCoord(&_right,&_right, &rotated);
			D3DXVec3TransformCoord(&_look,&_look, &rotated);



			//	post:
			setUpVector(_up);
			setLookVector(_look);
			return RESULT_SUCCESS;
		}
		type_result pitch(type_float angle)
		{
			D3DXMATRIX rotated;			
			D3DXMatrixRotationAxis(&rotated, &_right, angle);

			// rotate _up and _look around _right vector
			D3DXVec3TransformCoord(&_up,&_up, &rotated);
			D3DXVec3TransformCoord(&_look,&_look, &rotated);
			


			//	post:
			setUpVector(_up);
			setLookVector(_look);
			return RESULT_SUCCESS;
		}
		type_result roll(type_float angle)
		{
			D3DXMATRIX rotated;
			D3DXMatrixRotationAxis(&rotated, &_look, angle);

			// rotate _up and _right around _look vector
			D3DXVec3TransformCoord(&_right,&_right, &rotated);
			D3DXVec3TransformCoord(&_up,&_up, &rotated);



			//	post:
			setLookVector(_look);
			setUpVector(_up);
			return RESULT_SUCCESS;
		}
		type_result forward(type_float distance)
		{
			const D3DXVECTOR3& look = getLookVector();
			getTranslationX() += look.x * distance;
			getTranslationY() += look.y * distance;
			getTranslationZ() += look.z * distance;

			return RESULT_SUCCESS;
		}
		type_result stepAside(type_float distance)
		{
			const D3DXVECTOR3& right = getRightVector();
			getTranslationX() += right.x * distance;
			getTranslationY() += right.y * distance;
			getTranslationZ() += right.z * distance;

			return RESULT_SUCCESS;
		}
		type_result goUp(type_float distance)
		{
			getTranslationX() += getUpX() * distance;
			getTranslationY() += getUpY() * distance;
			getTranslationZ() += getUpZ() * distance;

			return RESULT_SUCCESS;
		}
		D3DVIEWPORT9 createViewPort() const
		{
			if(isViewportMaximized()) return createMaximizedViewPort();

			D3DVIEWPORT9 viewport = {
				getViewportX(), getViewportY(), getViewportWidth(), getViewportHeight(),
				getViewportMinimumZ(), getViewportMaximumZ()
			};			

			return viewport;
		}
		D3DVIEWPORT9 createMaximizedViewPort() const
		{
			D3DVIEWPORT9 to_return;
			const DX9& dx9 = _getBinded();
			if( ! &dx9)
			{
				ALERT_ERROR(" : 바인딩 실패");
				to_return.X = 0;
				to_return.Y = 0;
				to_return.Width = 0;
				to_return.Height = 0;
				to_return.MinZ = 0.0f;
				to_return.MaxZ = 1.0f;
			}
			else
			{
				const DX9::PresentParameters& parameters = dx9.getPresentParameters();
				to_return.X = 0;
				to_return.Y = 0;
				to_return.Width = parameters.BackBufferWidth;
				to_return.Height = parameters.BackBufferHeight;
				to_return.MinZ = 0.0f;
				to_return.MaxZ = 1.0f;
			}

			return to_return;		
		}

	private:	
		type_result _dockTransforms()
		{
			DX9& dx9 = _getBinded();
			if( ! &dx9)
			{
				ALERT_ERROR("DX9가 바인드 되지 않았습니다.");
				return RESULT_TYPE_ERROR;
			}
			LPDIRECT3DDEVICE9 device = dx9.getDevice();

			device->SetTransform(D3DTS_VIEW, &_view);
			device->SetTransform(D3DTS_PROJECTION, &_projection);
			return RESULT_SUCCESS;
		}
		virtual type_result _updateProjectionMatrix() = 0;
		type_result _updateViewMatrix()
		{
			//	타겟팅:				
			D3DXVECTOR3	pos		= createTranslationVector(),
						look_at = pos + _look;



			//	main:
			//		사전 보정:
			//			type_float연산이기 때문에 아무래도 계속 회전, 이동을 수행하다
			//			보면 값이 어긋나져버린다.(look, up, right는 각각 90도 간격
			//			이루어야만 하기 때문이다) 따라서 이를 보정한다.
			//			look:
			D3DXVec3Normalize(&_look, &_look);
			//			right:
			D3DXVec3Cross(&_right, &_up, &_look);
			D3DXVec3Normalize(&_right, &_right);
			//			up:
			D3DXVec3Cross(&_up, &_look, &_right);
			D3DXVec3Normalize(&_up, &_up);
			
			
			D3DXMatrixLookAtLH(&_view, &pos, &look_at, &_up);
			return RESULT_SUCCESS;
		}
		type_result _updateUpVector()
		{
			_up.x = getUpX();
			_up.y = getUpY();
			_up.z = getUpZ();

			return RESULT_SUCCESS;
		}		
		type_result _updateLookVector()
		{
			_look = EulerAngles(getRotationX(), getRotationY(), getRotationZ()).toVector();

			return RESULT_SUCCESS;
		}
		type_result _updateRightVector()
		{
			D3DXVec3Cross(&_right, &_look, &_up);
			return RESULT_SUCCESS;
		}
		void _release()
		{
			D3DXMATRIX i;
			D3DXMatrixIdentity(&i);

			_view = _projection = i;
			_right = _up = _look = D3DXVECTOR3();
		}
		ThisClass& _assign(const ThisClass& source)
		{
			if(this == &source) return *this;

			_view = source._view;
			_projection = source._projection;
			_right = source._right;
			_look = source._look;
			_up = source._up;

			return *this;
		}
		type_result _applyViewMatrix();	
		void _setModuleCodeSet(NEModuleSelector& selector);
		type_result _setViewPort();
		DX9& _getBinded();
		const DX9& _getBinded() const;
	
	private:
		D3DXMATRIX _view;
		D3DXMATRIX _projection;
		D3DXVECTOR3 _right;
		D3DXVECTOR3 _look;
		D3DXVECTOR3 _up;

	public:
		static const NECodeSet& getModuleScriptCodes();
	};
}