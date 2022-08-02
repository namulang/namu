#pragma once

#include "../../ast/node.hpp"

namespace namu {

    /// muna(Mutable Unit Node of Ast) can be mutated into something else while interpreting.
    /// there are 2 block stmt in namu lang.
    ///     1. normal block stmt.
    ///     2. def block stmt.
    /// the 2nd one is constructed with stmts to define something.
    /// e.g. if there is a object in namu source code, that object also has variables and funcs
    ///      inside of its block stmt. the block stmt only can contain what define something.
    ///      so it's titled to def block stmt.
    ///
    /// however, some ast nodes should behave different reactions depending on which block stmt
    /// contains the stmt. here is an example.
    /// e.g. in the case of 'defVarExpr':
    ///         just add it to a block stmt if the block stmt is normal.
    ///         but add it like to define new variable if the block stmt is to 'def' one.
    /// by algorithm of generated parser, we don't know which block stmt will come along while
    /// parsing a 'def stmt'. this is the problem why I need 'muna' class.
    /// because muna class can delay reaction, while containing the meaning initially assigned to it.

    class blockExpr;
    class defBlock;

    class muna : public node {
        WRD(CLASS(muna, node))
        typedef std::function<node*(void)> lambOnBlock;
        typedef std::function<void(defBlock&)> lambOnDefBlock;

    public:
        muna(lambOnBlock newOnBlock, lambOnDefBlock newOnDefBlock): _onBlock(newOnBlock),
                _onDefBlock(newOnDefBlock) {}

        str run(const ucontainable& args) override { return str(); }
        nbool canRun(const ucontainable& args) const override { return false; }
        nbicontainer& subs() override;

        node* onBlock() {
            return _onBlock();
        }

        defBlock& onDefBlock(defBlock& blk) {
            _onDefBlock(blk);
            return blk;
        }

    private:
        lambOnBlock _onBlock;
        lambOnDefBlock _onDefBlock;
    };

}
