#pragma once

#define WRD_INITIATOR(name, body) \
    static inline Initiator* WRD_CONCAT(__initi__ ## name ##_, __COUNTER__) = new Initiator([]() body);

namespace namu {
    /// Initiator can runs statements before main().
    /// @Usage  just @refer WRD_INITIATOR(myIniti) { <your codes> };
    ///         static<optional> Initiator <name>([]() { <your codes> });
    struct _wout Initiator {
        template <typename T>
        Initiator(T func) { func(); }
    };
}

