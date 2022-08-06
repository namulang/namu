#pragma once

#include "../../ast/node.hpp"

namespace namu {

    class blockExpr;
    class defBlock;

    /// delayRule can be mutated into something else while interpreting.
    /// for example, there are 2 block stmt in namu lang.
    ///     1. normal block stmt.
    ///     2. def block stmt.
    /// the 2nd one is constructed with stmts to define something.
    /// if there is a object in namu source code, that object also has variables and funcs
    /// inside of its block stmt.
    /// the block stmt only can contain what define something. so it's titled to def block stmt.
    ///
    /// however, some ast nodes should behave different reactions depending on which block stmt
    /// contains the stmt. here is an example.
    /// e.g. in the case of 'defVarExpr':
    ///         just add it to a block stmt if the block stmt is normal.
    ///         but add it like to define new variable if the block stmt is to 'def' one.
    /// by algorithm of generated parser, we don't know which block stmt will come along while
    /// parsing a 'def stmt'. this is the problem why I need this 'delayRule' class.
    /// because this class can delay reaction of specific rule, while containing the meaning initially assigned to it.
    template <typename C1, typename C2, typename R1 = node*, typename R2 = node*>
    class delayRule : public node {
        NAMU(CLASS(delayRule, node))
        typedef std::function<R1(C1)> action1;
        typedef std::function<R2(C2)> action2;

    public:
        delayRule(action1 act1, action2 act2): _act1(act1), _act2(act2) {}

    public:
        str run(const ucontainable& args) override { return str(); }
        nbool canRun(const ucontainable& args) const override { return false; }
        nbicontainer& subs() override;

        R1 case1(C1 arg) { return _act1(arg); }
        R2 case2(C2 arg) { return _act2(arg); }

    private:
        action1 _act1;
        action2 _act2;
    };
    template <typename C2, typename R1, typename R2>
    class delayRule<void, C2, R1, R2> : public node {
        NAMU(CLASS(delayRule, node))
        typedef std::function<R1()> action1;
        typedef std::function<R2(C2)> action2;

    public:
        delayRule(action1 act1, action2 act2): _act1(act1), _act2(act2) {}

    public:
        str run(const ucontainable& args) override { return str(); }
        nbool canRun(const ucontainable& args) const override { return false; }
        nbicontainer& subs() override;

        R1 case1() { return _act1(); }
        R2 case2(C2 arg) { return _act2(arg); }

    private:
        action1 _act1;
        action2 _act2;
    };
    template <typename C1, typename R1, typename R2>
    class delayRule<C1, void, R1, R2> : public node {
        NAMU(CLASS(delayRule, node))
        typedef std::function<R1(C1)> action1;
        typedef std::function<R2()> action2;

    public:
        delayRule(action1 act1, action2 act2): _act1(act1), _act2(act2) {}

    public:
        str run(const ucontainable& args) override { return str(); }
        nbool canRun(const ucontainable& args) const override { return false; }
        nbicontainer& subs() override;

        R1 case1(C1 arg) { return _act1(arg); }
        R2 case2() { return _act2(); }

    private:
        action1 _act1;
        action2 _act2;
    };
    template <typename R1, typename R2>
    class delayRule<void, void, R1, R2> : public node {
        NAMU(CLASS(delayRule, node))
        typedef std::function<R1()> action1;
        typedef std::function<R2()> action2;

    public:
        delayRule(action1 act1, action2 act2): _act1(act1), _act2(act2) {}

    public:
        str run(const ucontainable& args) override { return str(); }
        nbool canRun(const ucontainable& args) const override { return false; }
        nbicontainer& subs() override;

        R1 case1() { return _act1(); }
        R2 case2() { return _act2(); }

    private:
        action1 _act1;
        action2 _act2;
    };

    typedef delayRule<void, defBlock&> blockRule;
}
