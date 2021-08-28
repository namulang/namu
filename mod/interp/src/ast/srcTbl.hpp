#pragma once

#include <unordered_map>
#include "src.hpp"

namespace wrd {

	typedef std::unordered_map<node*, src> srcMap;

	class srcTbl : public typeProvidable {
		WRD_INTERFACE(srcTbl, typeProvidable)

	public:
		const src& operator[](const node* origin) const { return get(origin); }
		const src& operator[](const node& origin) const { return operator[](&origin); }
		src& operator[](const node* origin) { return get(origin); }
		src& operator[](const node& origin) { return operator[](&origin); }

	public:
		const src& get(const node* origin) const { return _map.at((node*) origin); }
		const src& get(const node& origin) const { return get(&origin); }
		src& get(const node* origin) { return _map.at((node*) origin); }
		src& get(const node& origin) { return get(&origin); }

	private:
		srcMap _map;
	};
}
