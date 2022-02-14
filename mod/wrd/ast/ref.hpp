#pragma once

#include "../common.hpp"

namespace wrd {

	class ref : public str {
		WRD(ME(ref, str),
			INIT_META(me))

	public:
		ref(const std::string& name = "");
		ref(const node& it, const std::string& name = "");
		ref(const node* it, const std::string& name = "");
		ref(const me& rhs);
		explicit ref(const binder& rhs);

    public:
        me& operator=(const super& rhs) {
            if(this == &rhs) return *this;
            return _assign(rhs);
        }

    public:
        const std::string& getName() const { return _name; }
        void setName(const std::string& new1) { _name = new1; }

    private:
        me& _assign(const super& rhs);

    private:
        std::string _name;
	};
}
