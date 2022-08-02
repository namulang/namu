// nested class of ucontainable.hpp
class iterable {
    WRD_DECL_ME(iterable)

public:
    virtual ~iterable() {}

    virtual wbool isEnd() const = 0;
    /// proceed iteration obj to point next element by given step.
    /// @param  step    how much it proceeds.
    ///                 positive value only.
    /// @return how many step it proceeded. if it tries to proceed further when it reached to End()
    ///         it won't be counted as returning value.
    ///         it'll return '0' if it already reached to the end.
    virtual wcnt next(wcnt step) = 0;
    virtual T& get() = 0;
    const T& get() const WRD_UNCONST_FUNC(get())
    virtual wbool isFrom(const tucontainable& it) const = 0;
    virtual tnucontainer<T>& getContainer() = 0;
    const tnucontainer<T>& getContainer() const WRD_UNCONST_FUNC(getContainer())
};
