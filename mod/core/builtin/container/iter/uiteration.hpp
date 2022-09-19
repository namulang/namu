#include "uiterable.hpp"

// nested class of tucontainable.hpp
class iteration : public instance, public iterable {
    NAMU(ADT(iteration, instance))
    friend class iter;

public:
    nbool isFrom(const tucontainable& rhs) const override {
        return &this->getContainer() == &rhs;
    }
};
