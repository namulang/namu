#pragma once

#include "frame.hpp"
#include "loader.hpp"

namespace wrd {

    /// the 'starter' is the facade of this wrd module.
    ///
    /// external modules or programs interact only through this 'starter'.
    /// it also prepares the system of wrd, connects the subcomponents,
    /// and makes them operable.
    class starter {
        WRD(CLASS(starter))
    };
}
