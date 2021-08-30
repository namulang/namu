#pragma once

#include <unordered_map>
#include "srcArea.hpp"

namespace wrd {

	typedef std::unordered_map<node*, srcArea> srcMap;

	class srcTbl : public typeProvidable {
		WRD_INTERFACE(srcTbl, typeProvidable)

	public:
		const srcArea& operator[](const node* origin) const { return get(origin); }
		const srcArea& operator[](const node& origin) const { return operator[](&origin); }
		srcArea& operator[](const node* origin) { return get(origin); }
		srcArea& operator[](const node& origin) { return operator[](&origin); }

	public:
		const srcArea& get(const node* origin) const { return _map.at((node*) origin); }
		const srcArea& get(const node& origin) const { return get(&origin); }
		srcArea& get(const node* origin) { return _map.at((node*) origin); }
		srcArea& get(const node& origin) { return get(&origin); }

	private:
		srcMap _map;
	};
}
