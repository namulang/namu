#include "uiterable.hpp"

// nested class of tucontainable.hpp
class iteration : public instance, public iterable, public clonable {
    WRD(ADT(iteration, instance))
    friend class iter;

public:
    wbool isFrom(const tucontainable& rhs) const override {
        return &this->getContainer() == &rhs;
    }
};
