#pragma once

#include "core/type/as/tas.hpp"
#include "core/builtin/container/native/tnarr.hpp"

namespace nm {

    class _nout ases: public tnarr<aser>, public asable {
        NM(CLASS(ases, tnarr<aser>))

    public:
        ases();
        template <typename... Es>
        explicit ases(const Es&... elems): super(elems...) {}

    public:
        using asable::is;
        nbool is(const type& from, const type& to) const override;

        using asable::as;
        str as(const node& from, const type& to) const override;
    };
}
