#pragma once

#include "Id.hpp"

namespace wrd { namespace memlite {

	class BindTag;
	class Instancer;

	class Instance : public TypeProvidable {
        WRD_DECL_THIS(Instance)
        WRD_INIT_META(Instance)
		friend class BindTag;
		friend class Watcher; // for Vault.
		friend class Chunks; // for Vault.
		friend class Instancer; // for _id.

	public:
		class Vault {

		public:
			wbool set(void* rcver, widx chk_n);
			widx get(void* rcver);
			wbool rel();

		private:
			void* _rcver;
			widx _chk_n;
		};

		Instance();
		Instance(Id id);
		virtual ~Instance();

		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;
		void* operator new(size_t sz);
		void operator delete(void* pt, size_t sz);

		virtual Id getId() const;
		virtual wbool isHeap() const;
		const BindTag& getBindTag() const;

	protected:
		wbool _setId(Id new1);
		static BindTag& _getBindTag(Id id);
        static Instancer& _getMgr();

	private:
		Id _id;
		static Vault _vault;
	};
}}
