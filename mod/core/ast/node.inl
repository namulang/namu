#pragma once

#include "node.hpp"
#include "baseObj.hpp"

namespace namu {

#define ME node

    template <typename T>
    class _nout priorities : public std::vector<tnarr<T>> {
        typedef std::vector<tnarr<T>> super;
    public:
        tnarr<T>& operator[](nidx n) {
            while(n >= this->size())
                push_back(tnarr<T>());
            return this->super::operator[](n);
        }
        const tnarr<T>& operator[](nidx n) const NAMU_UNCONST_FUNC(priorities<T>, operator[](n))

    public:
        tnarr<ME::prior<T>> join() const {
            tnarr<ME::prior<T>> ret;
            for(int n=0; n < this->size(); n++) {
                for(const T& elem : (*this)[n])
                    ret.add(ME::prior<T>(elem, ME::priority(n)));
            }
            return ret;
        }
        using super::push_back;
        void push_back(const ME::prior<T>& elem) {
            (*this)[elem.lv].add(*elem.elem);
        }
    };

    template <typename T>
    T& ME::sub() const {
        return subs().get<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name) const {
        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name;
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const args& a) {
        if(nul(a))
            return sub<T>(name);

        return subs().get<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        });
    }

    template <typename T>
    T& ME::sub(const std::string& name, const args& a) const NAMU_UNCONST_FUNC(sub<T>(name, a))

    template <typename T>
    tnarr<ME::prior<T>, strTactic> ME::_costPriority(const tnarr<T>& subs, const args& a) const {
        priorities<T> ps;
        // subs is arranged already to its scope:
        //  so if priority of sub was same level, I need to keep the priority of original container.
        for(const T& sub : subs) {
            const baseObj& o = sub.template cast<baseObj>();
            if(!nul(o)) {
                auto subs = sub.template subAll<T>(baseObj::CTOR_NAME, a);
                for(const prior<T>& p : subs)
                    ps.push_back(p);
                continue;
            }

            priority p = sub.prioritize(a);
            ps.push_back(prior<T>(sub, p));
        }

        return ps.join();
    }

    template <typename T>
    tnarr<T, strTactic> ME::subAll() const {
        return subs().template getAll<T>([](const std::string& key, const T& val) {
            return true;
        });
    }

    template <typename T>
    tnarr<T, strTactic> ME::subAll(const std::string& name) const {
        return subs().getAll<T>([&](const std::string& key, const T& val) {
            return key == name;
        });
    }

    template <typename T>
    tnarr<ME::prior<T>, strTactic> ME::subAll(const std::string& name, const args& a) {
        if(nul(a)) return NAMU_W("a == null"), tnarr<prior<T>>();

        return _costPriority<T>(subs().getAll<T>([&](const std::string& key, const T& val) {
            NAMU_DI("this=%s[%x]: key=%s name=%s", getType().getName().c_str(), this, key.c_str(), name.c_str());
            return key == name && val.canRun(a);
        }), a);
    }

    template <typename T>
    tnarr<ME::prior<T>, strTactic> ME::subAll(const std::string& name, const args& a) const NAMU_UNCONST_FUNC(subAll<T>(name, a))

#undef ME
}
