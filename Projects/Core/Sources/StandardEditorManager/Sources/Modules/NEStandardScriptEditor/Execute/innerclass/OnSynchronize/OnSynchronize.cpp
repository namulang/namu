#include "../../NEStandardScriptEditor.hpp"

namespace NE
{
	NEStandardScriptEditor::OnSynchronize::OnSynchronize(NEStandardScriptEditor& owner, const NECode& to_be_manipulated, bool is_insertion_mode)
		: _owner(owner), _code(to_be_manipulated), _is_insertion_mode(is_insertion_mode),
		_stop_finding(false)
	{

	}
	void NEStandardScriptEditor::OnSynchronize::_setCodesDirectly(NENode& target, const NECodeSet& new_codes) const
	{
		_owner._setCodesDirectly(target, new_codes);
	}
	const NECode& NEStandardScriptEditor::OnSynchronize::getCode() const
	{
		return _code;
	}
	bool NEStandardScriptEditor::OnSynchronize::isInserting() const
	{
		return _is_insertion_mode;
	}
	NEStandardScriptEditor& NEStandardScriptEditor::OnSynchronize::getOwner()
	{
		return _owner;
	}
	const NEStandardScriptEditor& NEStandardScriptEditor::OnSynchronize::getOwner() const
	{
		return _owner;
	}

	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NENodeCodeSet& ncs)
	{
		type_result result = RESULT_SUCCESS;
		for(int n=0; n < ncs.getLength() ;n++)
		{
			if(_stop_finding) return result;
			NENode& target = ncs[n];
			result = synchronize(target);

			NEKeyCodeSet& kcs = target.getKeySet();
			for(int n=0; n < kcs.getLength() ;n++)
			{
				if(_stop_finding) return result;

				result |= synchronize(kcs[n]);
			}

			result |= synchronize(target.getModuleSet());
		}

		return result;
	}

	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NEModuleCodeSet& mcs)
	{
		type_result result = RESULT_SUCCESS;

		for(int n=0; n < mcs.getLength() ;n++)
		{
			if(_stop_finding) return result;

			NEArgumentSet& args = mcs[n].getArguments();

			for(int arg_n=0; arg_n < args.getLength() ;arg_n++)
				result |= synchronize(args[arg_n].getDefaultKey());
		}

		return result;
	}

	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NEKey& key)
	{
		type_result result = RESULT_SUCCESS;

		if(key.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
		{
			NEModuleCodeSet& mcs = (static_cast<NEModuleCodeSetKey&>(key)).getValue();

			result |= synchronize(mcs);
		}
		else if(key.isSubClassOf(NEType::NENODE_CODESET_KEY))
		{
			NENodeCodeSet& ncs = (static_cast<NENodeCodeSetKey&>(key)).getValue();

			result |= synchronize(ncs);
		}
		else if(key.isSubClassOf(NEType::NENODE_SELECTOR))
		{
			NENodeSelector& selector = static_cast<NENodeSelector&>(key);
			if(selector.getCodesType() == getCode())
			{
				//	복사:
				NECodeSet codeset = selector.getCodes();
				//	코드셋 변경:
				synchronize(codeset);
				//	변경한 코드셋 적용:
				result |= selector.setCodes(codeset);
			}
		} 
		else if(key.isSubClassOf(NEType::NECODE_KEY))
		{
			NECode& code = (static_cast<NECodeKey&>(key)).getValue();

			if(synchronize(code))
				code.release();
		}
		else if(key.isSubClassOf(NEType::NECODE_SET_KEY))
		{
			NECodeSet& cs = (static_cast<NECodeSetKey&>(key)).getValue();

			result |= synchronize(cs);
		}

		return result;
	}

	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NECodeSet& cs)
	{
		const NECodeType& type = getCode();
		const NECode& my_code = getCode();

		for(int n=0; n < cs.getLength() ;)
		{
			if(_stop_finding) return RESULT_SUCCESS;

			if(synchronize(cs[n]))	//	true 반환하면, 이 코드를 지우라는 뜻이다
				cs.remove(n);
			else
				n++;
		}

		if(cs.getLength() < cs.getSize())
			cs.resize(cs.getLength());

		return RESULT_SUCCESS;
	}

	//	true 반환시 Code를 삭제하라는 뜻이다.
	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NECode& code)
	{
		const NECodeType& type = getCode();
		const NECode& my_code = getCode();
		if(type != code)	return false;

		if(isInserting())
		{
			if(code >= my_code)
				code++;
		}
		else
		{
			if(code.getCode() == my_code.getCode())
				return true;
			else if(code > my_code)
				code--;
		}

		return false;
	}

	type_result NEStandardScriptEditor::OnSynchronize::synchronize(NENode& target)
	{
		NECodeSet codeset = target.getCodes(getCode());

		type_result result = synchronize(codeset);

		_setCodesDirectly(target, codeset);

		return result;
	}
}
