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
int Core::test_running_count = 0;
LG::WindowList Core::debug_windows;
LG::WindowList Core::script_windows;

void Core::openModifierFrom(const NEString& path, NEKey* real_key)
{
	NEObject& obj = getObjectBy(path);
	if( ! &obj) return;

	if(	obj.isSubClassOf(NEType::NEMODULE_CODESET_KEY)	||
		obj.isSubClassOf(NEType::NEMODULE_CODESET)		)
		::LG::Core::open(ModuleSetTerminal(path, real_key)); 
	else if(obj.isSubClassOf(NEType::NENODE_CODESET_KEY)||
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
template <typename K>
bool __open(NEKey& key, bool not_use_name)
{
	if (K().getType() != key.getType())
		return false;

	K& casted = (K&)key;
	if (not_use_name)
		::LG::Core::open(Modifier<K>(casted.getValue()));
	else
		::LG::Core::open(Modifier<K>(casted));

	return true;
}
template <typename K, typename KU>
bool __open_c(NEKey& key, bool not_use_name)
{
	if (K().getType() != key.getType())
		return false;

	K& casted = (K&)key;
	if (not_use_name)
		::LG::Core::open(ContainerModifier<K, KU>(casted.getValue()));
	else
		::LG::Core::open(ContainerModifier<K, KU>(casted));

	return true;
}

void Core::openModifierFrom(NEKey& key, bool not_use_name)
{
	if (__open<NEBooleanKey>(key, not_use_name))	return;
	if (__open<NECharKey>(key, not_use_name))	return;
	if (__open<NEWCharKey>(key, not_use_name))	return;
	if (__open<NEByteKey>(key, not_use_name))	return;
	if (__open<NEUByteKey>(key, not_use_name))	return;
	if (__open<NEShortKey>(key, not_use_name))	return;
	if (__open<NEUShortKey>(key, not_use_name))	return;
	if (__open<NEIntKey>(key, not_use_name))	return;
	if (__open<NEUIntKey>(key, not_use_name))	return;
	if (__open<NEInt64Key>(key, not_use_name))	return;
	if (__open<NEFloatKey>(key, not_use_name))	return;
	if (__open<NEDoubleKey>(key, not_use_name))	return;
	if (__open<NEStringKey>(key, not_use_name))	return;
	if (__open<NEWStringKey>(key, not_use_name))	return;
	if (__open_c<NEBooleanSetKey, NEBooleanKey>(key, not_use_name))	return;
	if (__open_c<NEByteSetKey, NEByteKey>(key, not_use_name))		return;
	if (__open_c<NEUByteSetKey, NEUByteKey>(key, not_use_name))		return;
	if (__open_c<NEShortSetKey, NEShortKey>(key, not_use_name))		return;
	if (__open_c<NEUShortSetKey, NEUShortKey>(key, not_use_name))	return;
	if (__open_c<NEIntSetKey, NEIntKey>(key, not_use_name))			return;
	if (__open_c<NEUIntSetKey, NEUIntKey>(key, not_use_name))		return;
	if (__open_c<NEInt64SetKey, NEInt64Key>(key, not_use_name))		return;
	if (__open_c<NEFloatSetKey, NEFloatKey>(key, not_use_name))		return;
	if (__open_c<NEDoubleSetKey, NEDoubleKey>(key, not_use_name))	return;
	if (__open_c<NEStringSetKey, NEStringKey>(key, not_use_name))	return;
	if (__open_c<NEWStringSetKey, NEWStringKey>(key, not_use_name))	return;

	if(key.getType() == NEType::NENODE_SELECTOR)
		LG::Core::open(Planetarium((NENodeSelector*)&key, 5, 3, 70, 18));		
	if(key.getType() == NEType::NEMODULE_SELECTOR)
		LG::Core::open(Planetarium((NEModuleSelector*)&key, 5, 3, 70, 18));
	if(key.getType() == NEType::NEKEY_SELECTOR)
		LG::Core::open(Planetarium((NEKeySelector*)&key, 5, 3, 70, 18));	
}

NEObject& Core::getObjectBy(const NEString& path, onObjectFound& handler)
{
	NERootNodeCodeSet& nodeset = ::Core::isObservingDebug() ? 
			Kernal::getInstance().getNodeManager().getRootNodes()
		:
			Editor::getInstance().getScriptEditor().getScriptNodes();	
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

void Core::initializeWindows(LG::WindowList& windows)
{
	for(LG::WindowList::Iterator* i=windows.getIterator(0)
		; i
		; i=i->getNext())
		i->getValue().delete_me = true;

	windows.pushFront(NodeSetTerminal());
}