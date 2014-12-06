#include "NEPanel.hpp"
#include "../Editor/Editor.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"
#include "../NEDialog/NEDialog.hpp"
#include "../../EntryPoints/Headers.hpp"

namespace NE
{
	NE_DLL NEPanel::NEPanel()
		: NEExecutableUnit()
	{
		_release();
	}
	
	NE_DLL NEPanel::NEPanel(NEModule& source)
		: NEExecutableUnit()
	{
		_release();
		setModule(source);
	}
	
	NE_DLL NEPanel::NEPanel(const NEPanel& source)
		: NEExecutableUnit(source)
	{
		_assign(source);
	}
	NE_DLL NEPanel::~NEPanel()
	{

		
	}
	const NEPanel NE_DLL &NEPanel::operator=(const NEPanel& source)
	{		
		if(this == &source) return *this;
		NEExecutableUnit::operator=(source);

		return _assign(source);
	}
	bool NE_DLL NEPanel::operator==(const NEPanel& source) const
	{
		if(this == &source) return true;
		if(NEExecutableUnit::operator!=(source)) return false;
		if(_componentset != source._componentset) return false;
		if(_module != source._module) return false;

		return true;
	}
	bool NE_DLL NEPanel::operator!=(const NEPanel& source) const
	{
		return !(operator==(source));
	}
	NEType::Type NE_DLL NEPanel::getType() const
	{
		return NEType::NEPANEL;
	}		
	void NE_DLL NEPanel::release()
	{
		NEExecutableUnit::release();

		_release();
	}
	type_result NE_DLL NEPanel::isValid() const
	{
		type_result result = NEExecutableUnit::isValid();
		if(NEResult::hasError(result)) return result;
		result = _componentset.isValid();
		if(NEResult::hasError(result)) return result;
		
		return RESULT_SUCCESS;
	}
	LPCTSTR NE_DLL NEPanel::getErrorMessage(type_errorcode errorcode) const
	{
#ifdef DEVELOPER
		const NEExportable::Identifier& identifier = getHeader();
		KERNAL_WARNING("W100021C52 : 재정의되지 않은 에러메세지 가상함수\n현재 모듈은 어떠한 에러코드도 사용하지 않는데도 불구, 에러코드로 접근하려 했습니다.\n에러코드 : %d\n모듈의 식별자:\n\t이름 : %s\n\t제작자 : %s\n\t개정번호 : %d", errorcode, identifier.getName().toCharPointer(), identifier.getDeveloper().toCharPointer(), identifier.getRevision());
#endif

		return _T("재정의되지 않은 에러메세지 가상함수");
	}
	type_result NE_DLL NEPanel::execute()
	{
		for(int n=0; n < _componentset.getLength() ;n++)
		{
			NEComponent& component = _componentset[n];

			type_result result = component._onUpdate(*this);
			if(NEResult::hasError(result) == true)
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}
	
	NEComponentSet NE_DLL &NEPanel::getComponentSet()
	{
		return _componentset;
	}

	const NEComponentSet NE_DLL &NEPanel::getComponentSet() const
	{
		return _componentset;
	}

	type_result NE_DLL NEPanel::setModule(NEModule& module)
	{		
		if( ! &module)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER;
		}
		if( ! module.isSubClassOf(NEType::NEMODULE))
		{
			_module = NE_NULL;
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_ERROR | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		}
		if(module.getHeader() != getHeader())
		{
			_module = NE_NULL;
			EDITOR_ERROR(" : ")
				return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		}
		
		_module = &module;

		return RESULT_SUCCESS;
	}
	NEModule NE_DLL &NEPanel::getModule()
	{
		return *_module;
	}	
	const NEModule NE_DLL &NEPanel::getModule() const
	{
		return *_module;
	}	

	type_result NE_DLL NEPanel::onUpdate(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onUpdate(*this);
	}

	type_result NE_DLL NEPanel::onUpdate()
	{
		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = _componentset[n]._onUpdate(*this);
			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
					return result;
			}
		}

		return RESULT_SUCCESS;
	}
	type_result NE_DLL NEPanel::onFocus()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onFocus(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onFocus(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}
		
		
		
		//	main:
		//		다른 컴포넌트는 unfocus:
		for(int n=0; n < _componentset.getLength() ;n++)
			if(n != component_index)
				_componentset[n]._onUnfocus(*this);



		//	post:
		return _componentset[component_index]._onFocus(*this);
	}

	type_result NE_DLL NEPanel::onUnfocus()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onUnfocus(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onUnfocus(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onUnfocus(*this);
	}
	
	type_result NE_DLL NEPanel::onLoad()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onLoad(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onLoad(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onLoad(*this);
	}

	type_result NE_DLL NEPanel::onUnload()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onUnload(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onUnload(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onUnload(*this);
	}

	type_result NE_DLL NEPanel::onDialogReturned(NEDialog& dialogue)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onDialogReturned(n, dialogue);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onDialogReturned(type_index component_index, NEDialog& dialogue)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onDialogueReturned(*this, dialogue);
	}
	
	type_result NE_DLL NEPanel::onDisabled()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onDisabled(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
					return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onDisabled(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onDisabled(*this);
	}

	type_result NE_DLL NEPanel::onEnabled()
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}



		for(int n=0; n < _componentset.getLength() ;n++)
		{
			type_result result = onEnabled(n);

			if(NEResult::hasError(result))
			{
				EDITOR_ERROR(" : ")
				return result;
			}
		}

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEPanel::onEnabled(type_index component_index)
	{
		//		사용가능 검사:
		if( ! isEnable())
		{
			EDITOR_INFORMATION(" : ")
				return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION | RESULT_ACCESS_DENIED;
		}
		if(component_index < 0 || component_index > _componentset.getLengthLastIndex())
		{
			EDITOR_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}

		return _componentset[component_index]._onEnabled(*this);
	}
	
	const NEPanel& NEPanel::_assign(const NEPanel& source)
	{
		if(this == &source) return *this;

		_componentset = source._componentset;
		_module = source._module;

		return *this;
	}

	void NEPanel::_release()
	{
		_componentset.release();
		disconnectModule();
	}

	void NEPanel::disconnectModule()
	{
		_module = NE_NULL;
	}
}
