#pragma once

#include "node.hpp"
#include "baseObj.hpp"
#include "tpriorities.inl"

namespace namu {

#define ME node
#define TEMPLATE template <typename T>

    template <typename T>
    class _nout tprioritiesBucket : public std::vector<tnarr<T>> {
        typedef std::vector<tnarr<T>> super;
    public:
        tnarr<T>& operator[](nidx n) {
            while(n >= this->size())
                push_back(tnarr<T>());
            return this->super::operator[](n);
        }
        const tnarr<T>& operator[](nidx n) const NAMU_UNCONST_FUNC(tprioritiesBucket<T>, operator[](n))

    public:
        tpriorities<T> join() const {
            tpriorities<T> ret;
            for(int n=0; n < this->size(); n++) {
                for(const T& elem : (*this)[n])
                    ret.add(new tprior<T>(elem, priority(n)));
            }
            return ret;
        }
        using super::push_back;
        void push_back(const tprior<T>& elem) {
            (*this)[elem.lv].add(*elem.elem);
        }
    };

    TEMPLATE
    T& ME::sub() {
        return subs().get<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    TEMPLATE
    T& ME::sub(const std::string& name) {
        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name;
        });
    }

    TEMPLATE
    T& ME::sub(const std::string& name, const args& a) {
        if(nul(a))
            return sub<T>(name);

        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        });
    }

    TEMPLATE
    tpriorities<T> ME::_costPriority(const tnarr<T>& subs, const args& a) const {
        tprioritiesBucket<T> ps;
        // subs is arranged already to its scope:
        //  so if priority of sub was same level, I need to keep the priority of original container.
        for(const T& sub : subs) {
            const baseObj& o = sub.template cast<baseObj>();
            if(!nul(o)) {
                auto subs = sub.template subAll<T>(baseObj::CTOR_NAME, a);
                for(const tprior<T>& p : subs)
                    ps.push_back(p);
                continue;
            }

            priority p = sub.prioritize(a);
            if(p != NO_MATCH)
                ps.push_back(tprior<T>(sub, p));
        }

        return ps.join();
    }

    TEMPLATE
    tnarr<T, strTactic> ME::subAll() const {
        return subs().template getAll<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    TEMPLATE
    tnarr<T, strTactic> ME::subAll(const std::string& name) const {
        return subs().getAll<T>([&](const std::string& key, const T& val) {
            return key == name;
        });
    }

    TEMPLATE
    tpriorities<T> ME::subAll(const std::string& name, const args& a) const {
        if(nul(a)) return NAMU_W("a == null"), tpriorities<T>();

        return _costPriority<T>(subs().getAll<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        }), a);
    }

#undef TEMPLATE
#undef ME
}
