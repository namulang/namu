#include "visitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"
#include "../builtin.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

    me::visitor(): _isLog(false) {
        me::rel();
    }

    me::~visitor() {}

    me& me::setRoot(const node& root) {
        _root.bind(root);
        return *this;
    }

    node& me::getRoot() {
        return *_root;
    }

    me& me::setLog(nbool toShow) {
        _isLog = toShow;
        return *this;
    }

    nbool me::isLog() const {
        return _isLog;
    }

#define X(T) \
    void me::visit(visitInfo i, T& me) { \
        if(nul(me)) return; \
        if(_isLog) {\
            NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str()); \
        } \
        \
        if(!_markVisited(me)) return; \
        \
        onVisit(i, me); \
        onTraverse(i, me); \
        onLeave(i, me); \
    } \
    void me::onVisit(visitInfo i, T& me) { onVisit(i, (T::super&) me); } \
    void me::onLeave(visitInfo i, T& me) { onLeave(i, (T::super&) me); }

#   include "visitee.inl"
#undef X

    void me::rel() {
        setReport(dummyErrReport::singletone);
        _visited.clear();
    }

    me& me::setReport(errReport& rpt) {
        _rpt.bind(rpt);
        return *this;
    }

    errReport& me::getReport() { return *_rpt; }

    void me::visit(visitInfo i, node& me) {
        if(nul(me)) return;
        if(_isLog)
            NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str());

        if(!_markVisited(me)) return;

        onVisit(i, me);
        onTraverse(i, me);
        onLeave(i, me);
    }
    void me::onVisit(visitInfo i, node& me) {}
    void me::onLeave(visitInfo i, node& me) {}

    void me::start() {
        if(!_root) return;

        _visited.clear();
        _root->accept(visitInfo {"", nullptr, 0, 1, 1}, *this);
    }

    nbool me::_markVisited(node& me) {
        if(_visited.find(&me) != _visited.end()) return false;

        return _visited[&me] = true;
    }

    void me::onTraverse(visitInfo i, node& me) {
        if(_isLog)
            NAMU_DI("node[%s]::onTraverse", i.name.c_str());

        nbicontainer& subs = me.subs();
        int n=0;
        ncnt len = me.subs().len();
        auto end = _visited.end();
        for(auto e=subs.begin(); e ;++e, ++n) {
            node& val = e.getVal();
            val.accept(visitInfo {e.getKey(), &me, n, len, i.depth+1}, *this);
        }
    }

    void me::onTraverse(visitInfo i, getExpr& e) {
        if(_isLog)
            NAMU_DI("getExpr[%s]::onTraverse", i.name.c_str());

        // check me:
        const args& args = e.getSubArgs();
        nint n = 0;
        node& me = *e._me;
        ncnt len = (nul(args) ? 0 : args.len()) + (nul(me) ? 0 : 1);
        if(!nul(me))
            me.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);

        // check arguments:
        if(!nul(args))
            for(auto& elem : e.getSubArgs())
                elem.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, frame& f) {
        if(_isLog)
            NAMU_DI("frame[%s]::onTraverse", i.name.c_str());
        // do nothing.
    }

    void me::onTraverse(visitInfo i, runExpr& e) {
        if(_isLog)
            NAMU_DI("runExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = e.getMe();
        node& subject = e.getSubject();
        int len = e.getArgs().len() + (nul(me) ? 0 : 1) + (nul(subject) ? 0 : 1);
        if(!nul(me))
            me.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);
        if(!nul(subject))
            subject.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);

        for(auto& elem : e.getArgs())
            elem.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, func& f) {
        if(_isLog)
            NAMU_DI("func[%s]::onTraverse", i.name.c_str());

        f.getBlock().accept(visitInfo {"", &f, 0, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, blockExpr& b) {
        if(_isLog)
            NAMU_DI("blockExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        narr& stmts = b.getStmts();
        int len = stmts.len();
        for(auto& stmt : stmts)
            stmt.accept(visitInfo {"", &b, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, retExpr& b) {
        if(_isLog)
            NAMU_DI("retExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& ret = b.getRet();
        if(!nul(ret))
            ret.accept(visitInfo {"", &b, n++, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, asExpr& a) {
        if(_isLog)
            NAMU_DI("asExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = (node&) a.getMe();
        node& as = (node&) a.getAs();
        ncnt len = (nul(me) ? 0 : 1) + (nul(as) ? 0 : 1);
        if(!nul(me))
            me.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
        if(!nul(as))
            as.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, assignExpr& a) {
        if(_isLog)
            NAMU_DI("assignExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) a.getLeft();
        node& right = (node&) a.getRight();
        ncnt len = (nul(left) ? 0 : 1) + (nul(right) ? 0 : 1);
        if(!nul(left))
            left.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
        if(!nul(right))
            right.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, defAssignExpr& d) {
        if(_isLog)
            NAMU_DI("defAssignExpr[%s]::onTraverse", i.name.c_str());

        node& right = d.getRight();
        if(!nul(right))
            right.accept(visitInfo {"", &d, 0, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, defPropExpr& d) {
        if(_isLog)
            NAMU_DI("defPropExpr[%s]::onTraverse", i.name.c_str());

        node& org = (node&) d.getOrigin();
        if(!nul(org))
            org.accept(visitInfo {d.getName(), &d, 0, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, FBOExpr& f) {
        if(_isLog)
            NAMU_DI("FBOExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) f.getLeft();
        node& right = (node&) f.getRight();
        ncnt len = (nul(left) ? 0 : 1) + (nul(right) ? 0 : 1);
        if(!nul(left))
            left.accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
        if(!nul(right))
            right.accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, forExpr& f) {
        if(_isLog)
            NAMU_DI("forExpr[%s]::onTraverse", i.name.c_str());

        node& con = *f.getContainer();
        ncnt len = nul(con) ? 1 : 2;
        ncnt n = 0;
        if(!nul(con))
            con.accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
        f.getBlock().accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, retStateExpr& r) {
        if(_isLog)
            NAMU_DI("%s[%s]::onTraverse", r.getType().getName().c_str(), i.name.c_str());
    }

    void me::onTraverse(visitInfo i, ifExpr& f) {
        if(_isLog)
            NAMU_DI("ifExpr[%s]::onTraverse", i.name.c_str());

        blockExpr& elseBlk = f.getElseBlk();
        int len = !nul(elseBlk) ? 3 : 2;

        f.getCondition().accept(visitInfo {"", &f, 0, len, i.depth+1}, *this);

        f.getThenBlk().accept(visitInfo {"", &f, 1, len, i.depth+1}, *this);
        if(!nul(elseBlk))
            elseBlk.accept(visitInfo {"", &f, 2, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, whileExpr& w) {
        if(_isLog)
            NAMU_DI("whileExpr[%s]::onTraverse", i.name.c_str());

        w.getCondition().accept(visitInfo {"", &w, 0, 2, i.depth+1}, *this);
        w.getBlock().accept(visitInfo {"", &w, 1, 2, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, defArrayExpr& d) {
        if(_isLog)
            NAMU_DI("defArrayExpr[%s]::onTraverse", i.name.c_str());

        narr& elems = d.getElems();
        int len = elems.len(),
            n = 0;
        for(node& e : elems)
            e.accept(visitInfo {"", &d, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, genericObj& g) {
        if(_isLog)
            NAMU_DI("genericObj[%s]::onTraverse", i.name.c_str());

        auto& cache = (std::map<std::string, tstr<obj>>&) g.getCache();
        ncnt len = cache.size();
        nint n = 0;
        for(auto& e : cache)
            e.second->accept(visitInfo{e.first, &g, n++, len, i.depth+1}, *this);
    }
}
