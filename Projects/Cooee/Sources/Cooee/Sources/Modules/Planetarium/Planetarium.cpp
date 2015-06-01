#pragma once

#include "../Planetarium/Planetarium.hpp"
#include "../Filter/Filter.hpp"
#include "../Core/Core.hpp"

void Planetarium::onKeyPressed(int inputed)
{
	Window::onKeyPressed(inputed);
	type_index n = 0;
	switch(inputed)
	{
	case MAP:
		delete_me = true;
		break;

	case UP:
		if( ! focusing->parent) return;
		n = focusing->parent->planets.find(focusing);
		if( n == NE_INDEX_ERROR) return;

		if(n > 0)
			focusing = &focusing->parent->planets[n-1];
		setFocus(*focusing);
		LG::Core::play(LG::Core::SND_TICK);
		break;

	case DOWN:
		if( ! focusing->parent) return;
		n = focusing->parent->planets.find(focusing);
		if( n == NE_INDEX_ERROR) return;

		if(n < focusing->parent->planets.getLengthLastIndex())
			focusing = &focusing->parent->planets[n+1];
		setFocus(*focusing);
		LG::Core::play(LG::Core::SND_TICK);
		break;

	case LEFT:
		if( ! focusing->parent) return;

		focusing = focusing->parent;
		setFocus(*focusing);
		LG::Core::play(LG::Core::SND_TICK);
		break;

	case RIGHT:
		if(	focusing->planets.getLength() > 0	&&
			! focusing->is_closed				)
			focusing = &focusing->planets[0];
		setFocus(*focusing);
		LG::Core::play(LG::Core::SND_TICK);
		break;

	case LG::CANCEL:
		call(Filter());
		break;

	case LG::SPACE:
		focusing->is_closed = ! focusing->is_closed;
		root.updateLines(0);
		break;

	case CONFIRM:
		NEString path = ::Core::createPathBy(*focusing->real);
		LG::Core::play(LG::Core::SND_CONFIRM);
		if (!specified_filter)	//	일반 모드
		{
			if (focusing->real->isSubClassOf(NEType::NEMODULE_CODESET_KEY))
				::Core::openModifierFrom(path);
			else if (focusing->real->isSubClassOf(NEType::NENODE_CODESET_KEY))
				::Core::openModifierFrom(path);
			else if (focusing->real->isSubClassOf(NEType::NEKEY))
				::Core::openModifierFrom((NEKey&)*focusing->real);
			else
				::Core::openModifierFrom(path);
		}
		else
		{	//	선택 모드
			class MyHandler : public ::Core::onObjectFound
			{
			public:
				MyHandler() : last_found(0) {}
				virtual void onKeyFound(NEKey& target) {}
				virtual void onNodeFound(NENode& target) { last_found = &target; }
				virtual void onModuleFound(NEModule& target) {}

				NENode* last_found;
			} handler;			
			NEObject& object = ::Core::getObjectBy(path, handler);
			if( ! &object	|| ! handler.last_found)
			{
				::Core::pushMessage(path + "에 해당하는 객체가 없습니다.");
				return;
			}

			getNodeFilter().setCodes(handler.last_found->getCodes(NECodeType::SCRIPT));
			if (object.isSubClassOf(NEType::NEMODULE) &&
				&getModuleFilter())
			{
				NEModule& casted = static_cast<NEModule&>(object);
				getModuleFilter().setModuleCodes(casted.getCodes(NECodeType::MODULE_SCRIPT));

				NEType::Type manager_type = getModuleFilter().getManagerType();
				bool node_auto_binding = getModuleFilter().NENodeSelector::isUsingAutoBinding();
				bool module_auto_binding = getModuleFilter().isUsingAutoBinding();
				getModuleFilter().isUsingAutoBinding() = false;
				getModuleFilter().NENodeSelector::isUsingAutoBinding() = false;
				if (::Core::isObservingDebug())
					getModuleFilter().setManager(NEType::NENODE_MANAGER);
				else
					getModuleFilter().setManager(NEType::NESCRIPT_EDITOR);

				NEModule* one = 0;
				while (NEModule* e = &getModuleFilter().getModule())
				{
					if(one && e != one)
					{
						if (casted.getNameCode() == 0)
						{
							::Core::pushMessage("동일한 Module이 2개 있습니다. 선택하고 싶은 쪽에 NameCode를 부여하던가, 백스페이스로 필터를 열어 Manual로 조정하세요.");
							getModuleFilter().setModuleCodes(casted.getCodes(NECodeType::MODULE_SCRIPT));
						}
						else
						{
							getModuleFilter().setModuleCodes(casted.getCodes(NECodeType::MODULE_NAME));
							one = 0;
							while (NEModule* e = &getModuleFilter().getModule())
							{
								if(one && e != one)
								{
									::Core::pushMessage("동일한 Module이 2개 있습니다. 선택하고 싶은 쪽에 NameCode를 부여하던가, 백스페이스로 필터를 열어 Manual로 조정하세요.");
									getModuleFilter().setModuleCodes(casted.getCodes(NECodeType::MODULE_SCRIPT));
									break;
								}
								one = e;
							}
						}
						break;
					}
					one = e;
				}

				getModuleFilter().setManager(manager_type);
				getModuleFilter().isUsingAutoBinding() = module_auto_binding;
				getModuleFilter().NENodeSelector::isUsingAutoBinding() = node_auto_binding;
			}
			if(	object.isSubClassOf(NEType::NEKEY)	&&
				&getKeyFilter()						)
			{
				NEKey& casted = static_cast<NEKey&>(object);
				getKeyFilter().setKeyName(casted.getName());
			}				
		}

		break;
	}
}

void Planetarium::onUpdateData()
{
	synchroSelectors();

	NEListTemplate<NEObject*> selected;
	getSelectedByFilter(selected);

	root.updateLines(0);
	root.markColor(selected);
}

void Planetarium::onFocused()
{        
	NEObject* real_object = focusing->real;
	root.planets.release();
	NENodeCodeSet& ncs = ::Core::isObservingDebug() ? 
		Kernal::getInstance().getNodeManager().getRootNodes()
		:
	Editor::getInstance().getScriptEditor().getScriptNodes();
	generate(ncs);

	setFocus(*real_object);

	Window::onFocused();
}

void Planetarium::onDraw()
{
	LG::BackBuffer& buf = LG::Core::back_buffer;
	bool is_color_locked = buf.isColorLocked();
	if(is_color_locked)
		buf.setColorLock(false);

	Window::onDraw();

	root.onDraw();

	if(is_color_locked)
		buf.setColorLock(true);
}

void Planetarium::getSelectedByFilter(NEListTemplate<NEObject*>& selected)
{
	//	현재 어떤 Filter가 활성화 되어있는 지를 판단한다:
	if (switches[2])
	{
		NEType::Type backup = getKeyFilter().getManagerType();
		if (::Core::isObservingDebug())
			getKeyFilter().setManager(NEType::NENODE_MANAGER);
		else
			getKeyFilter().setManager(NEType::NESCRIPT_EDITOR);

		getKeyFilter().initializeReferingPoint();
		while (NEKey* itr = &getKeyFilter().getKey())
			selected.push(itr);

		getKeyFilter().setManager(backup);
		getKeyFilter().getBinder().unbind();
		getKeyFilter().NENodeSelector::getBinder().unbind();
		getKeyFilter().initializeReferingPoint();
	}
	if (switches[1])
	{
		NEType::Type backup = getModuleFilter().getManagerType();
		if (::Core::isObservingDebug())
			getModuleFilter().setManager(NEType::NENODE_MANAGER);
		else
			getModuleFilter().setManager(NEType::NESCRIPT_EDITOR);

		getModuleFilter().initializeReferingPoint();
		while (NEModule* itr = &getModuleFilter().getModule())
			selected.push(itr);

		getModuleFilter().setManager(backup);
		getModuleFilter().getBinder().unbind();
		getModuleFilter().NENodeSelector::getBinder().unbind();
		getModuleFilter().initializeReferingPoint();
	}
	if (switches[0])
	{
		NEType::Type backup = getNodeFilter().getManagerType();
		if (::Core::isObservingDebug())
			getNodeFilter().setManager(NEType::NENODE_MANAGER);
		else
			getNodeFilter().setManager(NEType::NESCRIPT_EDITOR);

		getNodeFilter().initializeReferingPoint();

		bool is_type_me = getNodeFilter().getCodes().getCodeType() == NECodeType::ME;
		if(is_type_me)
		{
			class MyHandler : public ::Core::onObjectFound
			{
			public:
				MyHandler() : last_found(0) {}
				virtual void onKeyFound(NEKey& target) {}
				virtual void onNodeFound(NENode& target) { last_found = &target; }
				virtual void onModuleFound(NEModule& target) {}

				NENode* last_found;
			} handler;
			if(specified_filter)
			{
				NEObject& parsed = ::Core::getObjectBy(::Core::createPathBy(*specified_filter), handler);
				if(handler.last_found)
				{
					getNodeFilter().setCodes(handler.last_found->getCodes(NECodeType::SCRIPT));
				}
			}
		}


		while (NENode* itr = &getNodeFilter().getNode())
			selected.push(itr);

		if (is_type_me)
		{
			NECodeSet cs;
			cs.getCodeType().setCodeType(NECodeType::ME);
			getNodeFilter().setCodes(cs);
		}


		getNodeFilter().setManager(backup);
		getNodeFilter().getBinder().unbind();
		getNodeFilter().initializeReferingPoint();
	}
}