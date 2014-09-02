#include "ModuleTerminal.hpp"
#include "../Core/Core.hpp"

void ModuleTerminal::ArgumentNameList::onKeyPressed(char inputed)
{
	class CodeInputer : public LG::InputWindow
	{
	public:
		FUNC_TO_CALLER(ModuleTerminal)
		virtual NEObject& clone() const { return *(new CodeInputer(*this)); }

		CodeInputer(NENode& new_owner) 
			: LG::InputWindow("새로 추가할 키의 이름을 좌우방향키로 선택하세요. \n물론 직접 이름을 입력 할 수도 있어요.", BLACK, WHITE),
			owner(new_owner)
		{
			
		}

		virtual void onUpdateData()
		{
			if( ! &owner) return;
			const NEKeyCodeSet& ks = owner.getKeySet();

			for(int n=0; n < ks.getLength() ;n++)
				if(input.history.find(ks[n].getName()) == NE_INDEX_ERROR)
					input.history.push(ks[n].getName());

			input.history_idx = 0;
			input.text = input.history[input.history_idx];
		}

		virtual void onInputed()
		{
			NEModule& m = toCaller().castObject();
			NEArgumentBase& arg = m.getArguments()[toCaller().argument_namelist.choosed];
		
			arg.setKeyName(input.text);
			
			delete_me = true;
		}

		NENode& owner;
	};

	ListGliph::onKeyPressed(inputed);

	if(inputed == CONFIRM)
		toOwner()->call(CodeInputer(_getOwnerNodeOf(toOwner()->castObject())));
}

NENode& ModuleTerminal::ArgumentNameList::_getOwnerNodeOf(NEModule& target)
{
	class MyHandler : public Core::onObjectFound
	{
	public:
		MyHandler() : last_pointer(0) {}
		virtual void onNodeFound(NENode& node)
		{
			last_pointer = &node;
		}
		NENode* last_pointer;
	};

	MyHandler myhandler;
	Core::getObjectBy(toOwner()->path, myhandler);
	
	return *myhandler.last_pointer;
}
