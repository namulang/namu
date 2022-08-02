#pragma once

namespace namu
{
    template <typename T>
    class TypeTrait {
    public:
        typedef T Org;
        typedef T& Ref;
        typedef T* Ptr;
        static constexpr wbool is_ptr = false;
        static constexpr wbool is_ref = false;
    };

    template <typename T>
    class TypeTrait<T&> {
    public:
        typedef T Org;
        typedef T& Ref;
        typedef T* Ptr;

        static constexpr wbool is_ptr = false;
        static constexpr wbool is_ref = true;
    };

    template <typename T>
    class TypeTrait<T*> {
    public:
        typedef T Org;
        typedef T& Ref;
        typedef T* Ptr;

        static constexpr wbool is_ptr = true;
        static constexpr wbool is_ref = false;
    };
}
