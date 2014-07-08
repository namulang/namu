#pragma once

#include "../Referer/Referer.hpp"
#include "../HierarchyMeshX/HierarchyMeshX.hpp"
#include "../HierarchySubReferer/HierarchySubReferer.hpp"

namespace DX9Graphics
{	
	class NE_DLL HierarchyReferer : public Referer
	{
		typedef HierarchyReferer ThisClass;
		typedef Referer SuperClass;
		typedef void(ThisClass::*onSearched)(ThisClass&);
		typedef NEArrayTemplate<HierarchySubReferer*> MatrixPointers;
		typedef NEArrayTemplate<MatrixPointers> MatrixPointersSet;

	public:
#include "innerclass/Connector/Connector.hpp"

	public:
		class Matrix : public D3DXMATRIX
		{
		public:
			Matrix()
			{
				release();
			}
		public:
			const Matrix& operator=(const D3DXMATRIX& source)
			{
				CopyMemory(&m, &source.m, sizeof(m));

				return *this;
			}
		public:
			NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
			{
				loader.execute((char*)m, sizeof(m));

				return loader;
			}
			NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
			{
				saver.execute((char*)m, sizeof(m));

				return saver;
			}
			void release()
			{
				ZeroMemory(&m, sizeof(m));
			}			
		};

		typedef NEArrayTemplate<Matrix> Matrixes;
		typedef NEArrayTemplate<Matrixes> MatrixesSet;

	public:
		ThisClass()
			: SuperClass()
		{
			getConnector().connect(getKeySet());
		}

		ThisClass(const ThisClass& source)
			: SuperClass(source)
		{
			getConnector().connect(getKeySet());
		}

	public:
		Connector& getConnector() { return _connector;}
		const Connector& getConnector() const {return _connector;}

	public:
		MatrixPointersSet& getMatrixPointersSet() { return _matrixes_set; }
		const MatrixPointersSet& getMatrixPointersSet() const {return _matrixes_set;}
		MatrixesSet& getFinalWorldsSet() {return _final_worlds_set; }
		const MatrixesSet& getFinalWorldsSet() const {return _final_worlds_set; }
		bool isMatrixPointersSetInitialized() const 
		{
			return _matrixes_set.getLength() > 0;
		}
	
	public:
		virtual type_result render();

	public:
		virtual type_result initialize()
		{
			SuperClass::initialize();

			NEKeyCodeSet& keyset = getKeySet();
			keyset.resize(keyset.getLength() + 2);
			keyset.push(NEUByteKey());
			keyset.push(NEFloatKey(5.0f));

			getConnector().connect(keyset);

			return RESULT_SUCCESS;
		}

	public:
		virtual type_result execute();
		
	public:
		NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("HierarchyReferer.dev.dbg");
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
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			SuperClass::serialize(loader);

			_release();

			return loader;			
		}
		virtual void release()
		{
			SuperClass::release();

			_release();
		}

	protected:
		HierarchyMeshX& _getBindedHierarchyMeshX();
		type_result _initializeSubReferers()
		{
			HierarchyMeshX& mesh = _getBindedHierarchyMeshX();
			if( ! &mesh)
			{
				ALERT_ERROR(" : 바인딩 실패");
				return RESULT_TYPE_ERROR;
			}
			HierarchyMeshX::BoneFrame& root_frame = mesh.getRootFrame();

			_release();

			_createSubReferers(root_frame, *this);	//	frame = sub referer

			_bindSubReferers(root_frame);
			_initializeFinalWorldsSet();

			return RESULT_SUCCESS;
		}
		void _initializeFinalWorldsSet()
		{
			_final_worlds_set.create(_matrixes_set.getLength());
			_final_worlds_set.push(Matrixes());

			for(int n=0; n < _final_worlds_set.getLength() ;n++)
			{
				_final_worlds_set[n].create(_matrixes_set[n].getLength());
				for(int push_n=0; push_n < _matrixes_set[n].getLength() ;push_n++)
					_final_worlds_set[n].push(Matrix());
			}
		}
		HierarchySubReferer& _createSubReferer(HierarchyMeshX::BoneFrame& frame, Referer& owner);
		void _createSubReferers(HierarchyMeshX::BoneFrame& frame, Referer& owner);
		HierarchySubReferer& _getRefererBy(NEModuleCodeSet& ms, const NETString& name);
		void _bindSubReferers(HierarchyMeshX::BoneFrame& frame)
		{
			if(	frame.pMeshContainer			&&
				frame.pMeshContainer->pSkinInfo	)
			{
				HierarchyMeshX::BoneMesh& boneMesh = static_cast<HierarchyMeshX::BoneMesh&>(*frame.pMeshContainer);

				int bone_count = boneMesh.pSkinInfo->GetNumBones();
				MatrixPointersSet& set = getMatrixPointersSet();
				if(set.getLength() == set.getSize())
					set.resize(set.getLength() + 1);
				set.push(MatrixPointers());
				MatrixPointers& lastone = set[set.getLengthLastIndex()];
				lastone.create(bone_count);
				NEModuleCodeSet& my_ms = getConnector().getModuleCodeSetKey().getValue();

				for(int n=0; n < bone_count; n++)
				{
					HierarchySubReferer& found = _getRefererBy(my_ms, boneMesh.pSkinInfo->GetBoneName(n) );
					if(&found)
						lastone.push(&found);
					else
						lastone.push(NE_NULL);
				}
			}

			if(frame.pFrameSibling)
				_bindSubReferers((HierarchyMeshX::BoneFrame&)*frame.pFrameSibling);
			if(frame.pFrameFirstChild)
				_bindSubReferers((HierarchyMeshX::BoneFrame&)*frame.pFrameFirstChild);
		}		

		
		void _computeFinalWorldMatrix(int container_n, HierarchyMeshX::BoneMesh& container);
		void _fillFinalWorldMatrix(HierarchyMeshX::BoneFrame& frame, int container_n)
		{
			if(frame.pMeshContainer)
			{
				_computeFinalWorldMatrix(container_n, (HierarchyMeshX::BoneMesh&) *frame.pMeshContainer);
				container_n++;
			}

			if(frame.pFrameSibling)
				_fillFinalWorldMatrix((HierarchyMeshX::BoneFrame&) *frame.pFrameSibling, container_n);
			if(frame.pFrameFirstChild)
				_fillFinalWorldMatrix((HierarchyMeshX::BoneFrame&) *frame.pFrameFirstChild, container_n);
		}

	private:
		void _release()
		{
			_matrixes_set.release();
			_final_worlds_set.release();
		}

	protected:		
		MatrixPointersSet _matrixes_set;
		MatrixesSet _final_worlds_set;

	private:
		Connector _connector;
	};
}