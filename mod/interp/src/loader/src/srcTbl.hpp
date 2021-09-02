#pragma once

#include <unordered_map>
#include "point.hpp"

namespace wrd {

	typedef std::unordered_map<node*, area> srcMap;

	class srcTbl : public typeProvidable {
		WRD(INTERFACE(srcTbl, typeProvidable))

	public:
		const area& operator[](const node* origin) const { return get(origin); }
		const area& operator[](const node& origin) const { return operator[](&origin); }
		area& operator[](const node* origin) { return get(origin); }
		area& operator[](const node& origin) { return operator[](&origin); }

	public:
		const area& get(const node* origin) const { return _map.at((node*) origin); }
		const area& get(const node& origin) const { return get(&origin); }
		area& get(const node* origin) { return _map.at((node*) origin); }
		area& get(const node& origin) { return get(&origin); }

	private:
		srcMap _map;
	};
}
