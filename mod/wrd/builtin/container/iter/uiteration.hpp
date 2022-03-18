#include "uiterable.hpp"

// nested class of tucontainable.hpp
class iteration : public instance, public iterable, public clonable {
    WRD(INTERFACE(iteration, instance))
    friend class iter;

public:
    wbool isFrom(const tucontainable& rhs) const override;
};
