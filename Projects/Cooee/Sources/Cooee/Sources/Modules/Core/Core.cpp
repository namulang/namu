#include "Core.hpp"
#include "../ModuleSetTerminal/ModuleSetTerminal.hpp"
#include "../NodeSetTerminal/NodeSetTerminal.hpp"
#include "../KeySetTerminal/KeySetTerminal.hpp"
#include "../ModuleTerminal/ModuleTerminal.hpp"
#include "../NodeTerminal/NodeTerminal.hpp"
#include "../Modifier/Modifier.hpp"
#include "../../Commons/Templates/ContainerModifier/ContainerModifier.hpp"
#include "../Planetarium/Planetarium.hpp"

Commander Core::commander = Commander();
NEString Core::path("/");
NEString Core::path_to_be_copied;
bool Core::is_cutting_off = false;

void Core::openModifierFrom(const NEString& path, NEKey* real_key)
{
	NEObject& obj = getObjectBy(path);
	if( ! &obj) return;

	if(	obj.isSubClassOf(NEType::NEMODULE_CODESET_KEY)	||
		obj.isSubClassOf(NEType::NEMODULE_CODESET)		)
		::LG::Core::open(ModuleSetTerminal(path, real_key)); 
	else if(obj.isSubClassOf(NEType::NENODE_CODESET_KEY)	||
		obj.isSubClassOf(NEType::NENODE_CODESET)		)
		::LG::Core::open(NodeSetTerminal(path, real_key));
	else if(obj.isSubClassOf(NEType::NEKEY_CODESET))
		::LG::Core::open(KeySetTerminal(path));
	else if(obj.isSubClassOf(NEType::NENODE))
		::LG::Core::open(NodeTerminal(path));
	else if(obj.isSubClassOf(NEType::NEMODULE))
		::LG::Core::open(ModuleTerminal(path));
	else
		::Core::pushMessage("경로 " + path + "에 있는 객체에 대한 적당한 수정자가 없습니다.");
}

void Core::openModifierFrom(NEKey& key)
{
	switch(key.getType())
	{
	case NEType::NEBOOLEAN_KEY:
		::LG::Core::open(Modifier<NEBooleanKey>((NEBooleanKey&)key));
		break;

	case NEType::NECHAR_KEY:
		::LG::Core::open(Modifier<NECharKey>((NECharKey&)key));
		break;
	case NEType::NEWCHAR_KEY:
		::LG::Core::open(Modifier<NEWCharKey>((NEWCharKey&)key));
		break;
	case NEType::NEBYTE_KEY:
		::LG::Core::open(Modifier<NEByteKey>((NEByteKey&)key));
		break;
	case NEType::NEUBYTE_KEY:
		::LG::Core::open(Modifier<NEUByteKey>((NEUByteKey&)key));
		break;
	case NEType::NESHORT_KEY:
		::LG::Core::open(Modifier<NEShortKey>((NEShortKey&)key));
		break;
	case NEType::NEUSHORT_KEY:
		::LG::Core::open(Modifier<NEUShortKey>((NEUShortKey&)key));
		break;
	case NEType::NEINT_KEY:
		::LG::Core::open(Modifier<NEIntKey>((NEIntKey&)key));
		break;
	case NEType::NEUINT_KEY:
		::LG::Core::open(Modifier<NEUIntKey>((NEUIntKey&)key));
		break;
	case NEType::NEINT64_KEY:
		::LG::Core::open(Modifier<NEInt64Key>((NEInt64Key&)key));
		break;
	case NEType::NEFLOAT_KEY:
		::LG::Core::open(Modifier<NEFloatKey>((NEFloatKey&)key));
		break;
	case NEType::NEDOUBLE_KEY:
		::LG::Core::open(Modifier<NEDoubleKey>((NEDoubleKey&)key));
		break;
	case NEType::NESTRING_KEY:
		::LG::Core::open(Modifier<NEStringKey>((NEStringKey&)key));
		break;
	case NEType::NEWSTRING_KEY:
		::LG::Core::open(Modifier<NEWStringKey>((NEWStringKey&)key));
		break;

	case NEType::NEBOOLEAN_SET_KEY:
		::LG::Core::open(ContainerModifier<NEBooleanSetKey, NEBooleanKey>((NEBooleanSetKey&)key));
		break;
	case NEType::NEBYTE_SET_KEY:
		::LG::Core::open(ContainerModifier<NEByteSetKey, NEByteKey>((NEByteSetKey&)key));
		break;
	case NEType::NEUBYTE_SET_KEY:
		::LG::Core::open(ContainerModifier<NEUByteSetKey, NEUByteKey>((NEUByteSetKey&)key));
		break;
	case NEType::NESHORT_SET_KEY:
		::LG::Core::open(ContainerModifier<NEShortSetKey, NEShortKey>((NEShortSetKey&)key));
		break;
	case NEType::NEUSHORT_SET_KEY:
		::LG::Core::open(ContainerModifier<NEUShortSetKey, NEUShortKey>((NEUShortSetKey&)key));
		break;
	case NEType::NEINT_SET_KEY:
		::LG::Core::open(ContainerModifier<NEIntSetKey, NEIntKey>((NEIntSetKey&)key));
		break;
	case NEType::NEUINT_SET_KEY:
		::LG::Core::open(ContainerModifier<NEUIntSetKey, NEUIntKey>((NEUIntSetKey&)key));
		break;
	case NEType::NEINT64_SET_KEY:
		::LG::Core::open(ContainerModifier<NEInt64SetKey, NEInt64Key>((NEInt64SetKey&)key));
		break;
	case NEType::NEFLOAT_SET_KEY:
		::LG::Core::open(ContainerModifier<NEFloatSetKey, NEFloatKey>((NEFloatSetKey&)key));
		break;
	case NEType::NEDOUBLE_SET_KEY:
		::LG::Core::open(ContainerModifier<NEDoubleSetKey, NEDoubleKey>((NEDoubleSetKey&)key));
		break;
	case NEType::NESTRING_SET_KEY:
		::LG::Core::open(ContainerModifier<NEStringSetKey, NEStringKey>((NEStringSetKey&)key));
		break;
	case NEType::NEWSTRING_SET_KEY:
		::LG::Core::open(ContainerModifier<NEWStringSetKey, NEWStringKey>((NEWStringSetKey&)key));
		break;
	case NEType::NENODE_SELECTOR:
		LG::Core::open(Planetarium((NENodeSelector*)&key, 5, 3, 70, 18));
		break;
	case NEType::NEMODULE_SELECTOR:
		LG::Core::open(Planetarium((NEModuleSelector*)&key, 5, 3, 70, 18));
		break;
	case NEType::NEKEY_SELECTOR:
		LG::Core::open(Planetarium((NEKeySelector*)&key, 5, 3, 70, 18));
		break;


	default:
		::Core::pushMessage("경로 " + path + "에 있는 객체에 대한 적당한 수정자가 없습니다.");
	}
}

NEObject& Core::getObjectBy(const NEString& path, onObjectFound& handler)
{
	NERootNodeCodeSet& nodeset = Editor::getInstance().getScriptEditor().getScriptNodes();	
	NEObject* nullpointer = 0;
	if( ! &Kernal::getInstance()					||
		! &Kernal::getInstance().getNodeManager()	||
		! &path										||
		path == ""									)
		return nodeset;


	//	main:
	NEStringSet splited;
	path.split("/", splited);
	
	return _searchNodeSet(nodeset, splited, handler);
}

namespace
{
	bool __s_ks(const NEKeyCodeSet& ks, const NEObject& t, NEString& text);
	bool __s_ms(const NEModuleCodeSet& ms, const NEObject& t, NEString& text);
	bool __s_ns(const NENodeCodeSet& ns, const NEObject& t, NEString& text)
	{
		for(int n=0; n < ns.getLength() ;n++)
		{
			if(&ns[n] == &t)
			{
				text = "/" + NEString(n);
				return true;
			}

			if(&ns[n].getKeySet() == &t)
			{
				text = "/" + NEString(n) + "/k" + text;
				return true;
			}
			if(&ns[n].getModuleSet() == &t)
			{
				text = "/" + NEString(n) + "/m" + text;
				return true;
			}
			if(__s_ks(ns[n].getKeySet(), t, text))
			{
				text = "/" + NEString(n) + "/k" + text;
				return true;
			}
			if(__s_ms(ns[n].getModuleSet(), t, text))
			{
				text = "/" + NEString(n) + "/m" + text;
				return true;
			}
		}

		return false;
	}

	bool __s_ks(const NEKeyCodeSet& ks, const NEObject& t, NEString& text)
	{
		for(int n=0; n < ks.getLength() ;n++)
		{
			if(&ks[n] == &t)
			{
				text = "/" + NEString(n);
				return true;
			}

			if(ks[n].isSubClassOf(NEType::NEMODULE_CODESET_KEY))
			{
				NEModuleCodeSetKey& c = (NEModuleCodeSetKey&) ks[n];
				if(__s_ms(c.getValue(), t, text))
				{
					text = "/" + NEString(n) + text;
					return true;
				}
			}
			else if(ks[n].isSubClassOf(NEType::NENODE_CODESET_KEY))
			{
				NENodeCodeSetKey& c = (NENodeCodeSetKey&) ks[n];
				if(__s_ns(c.getValue(), t, text))
				{
					text = "/" + NEString(n) + text;
					return true;
				}
			}
		}

		return false;
	}

	bool __s_ms(const NEModuleCodeSet& ms, const NEObject& t, NEString& text)
	{
		for(int n=0; n < ms.getLength() ;n++)
		{
			if(&ms[n] == &t)
			{
				text = "/" + NEString(n);
				return true;
			}
		}

		return false;
	}
}
NE::NEString Core::createPathBy(const NEObject& target)
{
	NEString to_return;

	NENodeCodeSet& ns = Editor::getInstance().getScriptEditor().getScriptNodes();
	if(&ns == &target)
		return "/";

	__s_ns(ns, target, to_return);

	return to_return;
}