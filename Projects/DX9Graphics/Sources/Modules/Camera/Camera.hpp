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
		NEModuleSelector& getDX9Selector()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEModuleSelector&>(casted->getDX9Selector());
		}
		const NEModuleSelector& getDX9Selector() const
		{
			const NEKey& key = getKeySet()[15];
			if( ! &key || ! key.isSubClassOf(NEType::NEMODULE_SELECTOR))
			{
				ALERT_ERROR("15번째 키는 NEMODULE_SELECTOR여야 합니다.");
				NEModuleSelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEModuleSelector&>(key);
		}
		NENodeSelector& getTargetSelector()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NENodeSelector&>(consted_this->getTargetSelector());
		}
		const NENodeSelector& getTargetSelector() const
		{
			const NEKey& somekey = getKeySet()[16];
			if( ! somekey.isSubClassOf(NEType::NENODE_SELECTOR))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 16번키가 NENODE_SELECTOR여야 합니다.");
				const NENodeSelector* nullpoint = 0;
				return *nullpoint;
			}

			const NENodeSelector& target = static_cast<const NENodeSelector&>(somekey);
			return target;
		}
		type_float& getUpX()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getUpX());
		}
		const type_float& getUpX() const
		{
			const NEKey& somekey = getKeySet()[17];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 17번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getUpY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getUpY());
		}
		const type_float& getUpY() const
		{
			const NEKey& somekey = getKeySet()[18];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 18번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getUpZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getUpZ());
		}
		const type_float& getUpZ() const
		{
			const NEKey& somekey = getKeySet()[19];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 19번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& isViewportMaximized()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->isViewportMaximized());
		}
		const type_float& isViewportMaximized() const
		{
			const NEKey& somekey = getKeySet()[20];
			if( ! somekey.isSubClassOf(NEType::NEBOOLEAN_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 20번키가 NEBOOLEAN_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_uint& getViewportX()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_uint&>(consted_this->getViewportX());
		}
		const type_uint& getViewportX() const
		{
			const NEKey& somekey = getKeySet()[21];
			if( ! somekey.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 21번키가 NEUINT_KEY여야 합니다.");
				const type_uint* nullpoint = 0;
				return *nullpoint;
			}

			const NEUIntKey& target = static_cast<const NEUIntKey&>(somekey);
			return target.getValue();
		}
		type_uint& getViewportY()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_uint&>(consted_this->getViewportY());
		}
		const type_uint& getViewportY() const
		{
			const NEKey& somekey = getKeySet()[22];
			if( ! somekey.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 22번키가 NEUINT_KEY여야 합니다.");
				const type_uint* nullpoint = 0;
				return *nullpoint;
			}

			const NEUIntKey& target = static_cast<const NEUIntKey&>(somekey);
			return target.getValue();
		}
		type_uint& getViewportWidth()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_uint&>(consted_this->getViewportWidth());
		}
		const type_uint& getViewportWidth() const
		{
			const NEKey& somekey = getKeySet()[23];
			if( ! somekey.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 23번키가 NEUINT_KEY여야 합니다.");
				const type_uint* nullpoint = 0;
				return *nullpoint;
			}

			const NEUIntKey& target = static_cast<const NEUIntKey&>(somekey);
			return target.getValue();
		}
		type_uint& getViewportHeight()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_uint&>(consted_this->getViewportHeight());
		}
		const type_uint& getViewportHeight() const
		{
			const NEKey& somekey = getKeySet()[24];
			if( ! somekey.isSubClassOf(NEType::NEUINT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 24번키가 NEUINT_KEY여야 합니다.");
				const type_uint* nullpoint = 0;
				return *nullpoint;
			}

			const NEUIntKey& target = static_cast<const NEUIntKey&>(somekey);
			return target.getValue();
		}
		type_float& getViewportMinimumZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getViewportMinimumZ());
		}
		const type_float& getViewportMinimumZ() const
		{
			const NEKey& somekey = getKeySet()[25];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 25번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}
		type_float& getViewportMaximumZ()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<type_float&>(consted_this->getViewportMaximumZ());
		}
		const type_float& getViewportMaximumZ() const
		{
			const NEKey& somekey = getKeySet()[26];
			if( ! somekey.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 26번키가 NEFLOAT_KEY여야 합니다.");
				const type_float* nullpoint = 0;
				return *nullpoint;
			}

			const NEFloatKey& target = static_cast<const NEFloatKey&>(somekey);
			return target.getValue();
		}		
		NEModuleCodeSet& getShaderPrograms()
		{
			const ThisClass* consted_this = (const ThisClass*) this;

			return const_cast<NEModuleCodeSet&>(consted_this->getShaderPrograms());
		}
		const NEModuleCodeSet& getShaderPrograms() const
		{
			const NEKey& somekey = getKeySet()[27];
			if( ! somekey.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			{
				ALERT_ERROR("키의 배열이 이상합니다. 27번키가 NEMODULECODE_SET_KEY여야 합니다.");
				const NEModuleCodeSet* nullpoint = 0;
				return *nullpoint;
			}

			const NEModuleCodeSetKey& target = static_cast<const NEModuleCodeSetKey&>(somekey);
			return target.getValue();
		}
		const D3DXVECTOR3& getLookVector() const { return _look; }
		D3DXVECTOR3& getUpVector() { return _up; }
		const D3DXVECTOR3& getUpVector() const { return _up; }
		D3DXVECTOR3& getRightVector() { return _right; }
		const D3DXVECTOR3& getRightVector() const { return _right; }
		D3DXMATRIX& getViewMatrix() { return _view; }
		const D3DXMATRIX& getViewMatrix() const { return _view; }
		D3DXMATRIX& getProjectionMatrix() { return _projection; }
		const D3DXMATRIX& getProjectionMatrix() const { return _projection; }
		type_result setLookVector(D3DXVECTOR3& new_vector)
		{
			EulerAngles converted;
			converted.fromVector(new_vector);
			getRotationX() = converted.x_axis_angle;
			getRotationY() = converted.y_axis_angle;
			//getRotationZ() = converted.z_axis_angle;

			return RESULT_SUCCESS;
		}
		type_result setTranslationVector(D3DXVECTOR3& new_vector)
		{
			getTranslationX() = new_vector.x;
			getTranslationY() = new_vector.y;
			getTranslationZ() = new_vector.z;

			return RESULT_SUCCESS;
		}
		type_result setUpVector(D3DXVECTOR3& new_vector)
		{
			getUpX() = new_vector.x;
			getUpY() = new_vector.y;
			getUpZ() = new_vector.z;

			return RESULT_SUCCESS;
		}

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 13);
			keyset.push(NEModuleSelector());	//	15:	DX9
			keyset.push(NENodeSelector());		//	16:	촬영 대상
			//	업 벡터:
			keyset.push(NEFloatKey(0.0f));		//	17:	UpX
			keyset.push(NEFloatKey(1.0f));		//	18:	UpY
			keyset.push(NEFloatKey(0.0f));		//	19:	UpZ
			//	viewport:
			keyset.push(NEBooleanKey(true));	//	20:	isViewportMaximized
			keyset.push(NEUIntKey(0));			//	21:	ViewportX
			keyset.push(NEUIntKey(0));			//	22:	ViewportY
			keyset.push(NEUIntKey(0));			//	23:	ViewportWidth
			keyset.push(NEUIntKey(0));			//	24:	ViewportHeight
			keyset.push(NEFloatKey(0.0f));		//	25:	ViewportMinimumZ
			keyset.push(NEFloatKey(0.0f));		//	26:	ViewportMaximumZ
			//	ShaderProgram:
			keyset.push(NEModuleCodeSetKey());	//	27:	ShaderProgram

			return RESULT_SUCCESS;
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
		static const NECodeSet& getCameraCodeSet();
	};
}