#include "./TStrong.hpp"
#include "./TWeak.inl"

namespace wrd { namespace memlite {

#define TEMPL	template <typename T>
#define THIS	TStrong<T>
#define SUPER   TWeak<T>

    TEMPL THIS::TStrong() {}
    TEMPL THIS::TStrong(T& it) : SUPER() { this->bind(it); }
    TEMPL THIS::TStrong(T* it) : SUPER() { this->bind(*it); }
    TEMPL THIS::TStrong(const This& rhs) : SUPER() { this->_assign(rhs); }
	TEMPL THIS::~TStrong() { unbind(); }

	TEMPL THIS& THIS::operator=(const This& rhs) {
		SUPER::operator=(rhs);
	    return *this;
	}

	TEMPL wbool THIS::unbind() {
		if(!this->isBind()) return true;

		BindTag& tag = this->_getBindTag(this->getItsId());
        WRD_NUL(tag, SUPER::unbind());

		tag._onStrong(-1);
	    return SUPER::unbind();
	}

	TEMPL wbool THIS::_bind(const Instance& it) {
		wbool res = SUPER::_bind(it);
        if(!res) {
            WRD_E("super::_bind() was failed.");
            return res;
        }

		if(!it.isHeap()) {
			WRD_W("it is local variable. couldn't bind it strongly.");
            return true;
        }

		//  처음에 Instance가 Instancer에 생성되었을때는 strong==0 이며,
		//  StrongBinder가 붙지 않는다면 그대로 계속 메모리상주하게 된다.
		//  Strong이 Count.strong=0인 instance를 bind하는 순간, 이 instance는
		//  bind에 의해서 해제될 수 있게 된다.
		return this->_getBindTag(this->getItsId())._onStrong(1);
	}

#undef THIS
#define THIS    TStrong<const T>

	TEMPL THIS::TStrong() {}
	TEMPL THIS::TStrong(T& it) : SUPER() { this->bind(it); }
	TEMPL THIS::TStrong(T* it) : SUPER() { this->bind(*it); }
	TEMPL THIS::TStrong(const T& it) : SUPER() { this->bind(it); }
	TEMPL THIS::TStrong(const T* it) : SUPER() { this->bind(*it); }
	TEMPL THIS::TStrong(const This& rhs) : SUPER() { this->_assign(rhs); }
	TEMPL THIS::TStrong(const TStrong<T>& rhs) : SUPER() { this->_assign(rhs); }
	TEMPL THIS::~TStrong() { unbind(); }

	TEMPL THIS& THIS::operator=(const This& rhs) {
		SUPER::operator=(rhs);
	    return *this;
	}

	TEMPL THIS& THIS::operator=(const TStrong<T>& rhs) {
		SUPER::operator=(rhs);
	    return *this;
	}

	TEMPL wbool THIS::unbind() {
		if(!this->isBind()) return true;

		BindTag& tag = this->_getBindTag(this->getItsId());
        WRD_NUL(tag, SUPER::unbind());

		tag._onStrong(-1);
	    return SUPER::unbind();
	}

	TEMPL wbool THIS::_bind(const Instance& it) {
        wbool res = _bind(it);
        if(!res) {
            WRD_E("super::_bind() was failed.");
            return res;
        }

	    if(!it.isHeap()) {
	        WRD_W("it is local variable. couldn't bind it strongly.");
            return true;
        }

	    return this->_getBindTag(this->getItsId())._onStrong(1);
	}

#undef TEMPL
#undef THIS
#undef SUPER

}}
