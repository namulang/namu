#pragma once

#include "../../Includes/Includes.hpp"

namespace DX9Graphics
{
	template <typename T>
	class NE_DLL BinderTemplate : public NEModule
	{
	public:
		typedef BinderTemplate<T> ThisClass;
		typedef NEModule SuperClass;

	public:
		class NE_DLL Connector : public NEModule::BaseConnector
		{
		public:
			type_result connect(NEKeyCodeSet& keyset)
			{
				if(keyset.getLength() < 1) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
				for(int n=0; n < 1 ;n++)
					if( ! &keyset[n] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

				_dx9_selector = static_cast<NENodeSelector*>( &(keyset[0]) );

				return RESULT_SUCCESS;
			}

		public:
			NENodeSelector& getDependentSelector()
			{
				return *_dx9_selector;
			}
			const NENodeSelector& getDependentSelector() const
			{
				return *_dx9_selector;
			}	

		private:
			NENodeSelector* _dx9_selector;
		};

	public:
		ThisClass()
			: SuperClass()
		{

		}
		ThisClass(const ThisClass& source)
			: SuperClass(source)
		{
			getConnector().connect(getKeySet());
		}

	public:
		const Connector& getConnector() const{return _connector;}
		Connector& getConnector() { return _connector; }

	public:
		virtual type_result initialize()
		{
			getKeySet().create(1);
			getKeySet().push(NENodeSelector());

			getConnector().connect(getKeySet());

			return RESULT_SUCCESS;
		}

	public:
		T& getBinded()
		{
			if( ! _binder.isBinded())
				_bind();
			return static_cast<T&>(_binder.getBinded());
		}
		const T& getBinded() const
		{
			return static_cast<const T&>(_binder.getBinded());
		}		
		NEModuleBinder& getBinder() {return _binder;}
		const NEModuleBinder& getBinder() const {return _binder; }

	protected:
		type_result _bind()
		{
			//	pre:
			//		Å¸°ÙÆÃ:
			static NEModuleSelector selector;
			NENodeSelector& node_selector = getConnector().getDependentSelector();
			selector.NENodeSelector::operator=(node_selector);
			_setModuleScriptCode(selector);
			//		Identifier È¹µæ:
			static NEExportable::Identifier identifier = T().getHeader();

			while( &selector.getModule())
			{
				NEModule& module = selector.peekModule();
				if(identifier == module.getHeader())
				{
					_binder = selector.bindPeeked();
					selector.initializeReferingPoint();
					return RESULT_SUCCESS;
				}
			}



			//	post:
			node_selector = selector;
			return RESULT_TYPE_ERROR;
		}
		void _setModuleScriptCode(NEModuleSelector& selector)
		{
			static NECodeSet codeset;
			if(codeset.getLength() <= 0)
			{
				type_code dx9_scriptcode = Kernal::getInstance().getModuleManager()
					.getModule(T().getHeader()).getScriptCode();
				codeset.create(1);
				codeset.push(dx9_scriptcode);
			}

			selector.setModuleType(NECodeType::SCRIPT);
			selector.setModuleCodeSet(codeset);
		}

	protected:
		NEModuleBinder _binder;
		Connector _connector;
	};
}