/* TypeTraits.h
 *
 * Copyright (C) 2018 Jan Rogall
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef MICROPIN_TYPETRAITS_INCLUDED
#define MICROPIN_TYPETRAITS_INCLUDED

#include <stddef.h>

namespace MicroPin
{
    template<typename T, T v>
    struct integral_constant
    {
        using value_type = T;
        using type = integral_constant;
        static constexpr T value = v;
        constexpr operator value_type() const noexcept
        {
            return value;
        }
        constexpr value_type operator()() const noexcept
        {
            return value;
        }
    };
    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    template<typename T> struct remove_reference { using type = T; };
    template<typename T> struct remove_reference<T&> { using type = T; };
    template<typename T> struct remove_reference<T&&> { using type = T; };
    template<typename T> using remove_reference_t = typename remove_reference<T>::type;

    template<typename T> struct is_array : false_type {};
    template<typename T> struct is_array<T[]> : true_type {};
    template<typename T, size_t N> struct is_array<T[N]> : true_type {};

    template<typename T> struct remove_extent { using type = T; };
    template<typename T> struct remove_extent<T[]> { using type = T; };
    template<typename T, size_t N> struct remove_extent<T[N]> { using type = T; };
    template<typename T> using remove_extent_t = typename remove_extent<T>::type;

    //is_function:
    // primary template
    template<class>
    struct is_function : false_type { };

    // specialization for regular functions
    template<class Ret, class... Args>
    struct is_function<Ret(Args...)> : true_type {};

    // specialization for variadic functions such as std::printf
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...)> : true_type {};

    // specialization for function types that have cv-qualifiers
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) volatile> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const volatile> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) volatile> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const volatile> : true_type {};

    // specialization for function types that have ref-qualifiers
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) volatile &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const volatile &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) volatile &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const volatile &> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) && > : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const &&> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) volatile &&> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args...) const volatile &&> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) && > : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const &&> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) volatile &&> : true_type {};
    template<class Ret, class... Args>
    struct is_function<Ret(Args..., ...) const volatile &&> : true_type {};


    template<typename T> struct remove_volatile { using type = T; };
    template<typename T> struct remove_volatile<volatile T> { using type = T; };
    template<typename T> using remove_volatile_t = typename remove_volatile<T>::type;

    template<typename T> struct remove_const { using type = T; };
    template<typename T> struct remove_const<const T> { using type = T; };
    template<typename T> using remove_const_t = typename remove_const<T>::type;

    template<typename T> struct remove_cv
    {
        using type = remove_volatile_t<remove_const_t<T>>;
    };
    template<typename T> using remove_cv_t = typename remove_cv<T>::type;

    //add_pointer
    namespace detail {
        template< class T, bool is_function_type = false >
        struct add_pointer {
            using type = typename remove_reference<T>::type*;
        };

        template< class T >
        struct add_pointer<T, true> {
            using type = T;
        };

        template< class T, class... Args >
        struct add_pointer<T(Args...), true> {
            using type = T(*)(Args...);
        };

        template< class T, class... Args >
        struct add_pointer<T(Args..., ...), true> {
            using type = T(*)(Args..., ...);
        };

    } // namespace detail

    template< class T >
    struct add_pointer : detail::add_pointer<T, is_function<T>::value> {};
    template<typename T> using add_pointer_t = typename add_pointer<T>::type;

    template<bool B, typename T, typename F>
    struct conditional { using type = T; };
    template<typename T, typename F>
    struct conditional<false, T, F> { using type = F; };
    template<bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;

    template<typename T>
    struct decay
    {
        private:
        using U = remove_reference_t<T>;
        public:
        using type = conditional_t<is_array<U>::value, remove_extent_t<U>*,
        conditional_t<is_function<U>::value, add_pointer_t<U>, remove_cv_t<U>>>;
    };

    template<typename T>
    using decay_t = typename decay<T>::type;

    template<typename T>
    constexpr T&& forward(remove_reference_t<T>& t) noexcept
    {
        return static_cast<T&&>(t);
    }
    template<typename T>
    constexpr T&& forward(remove_reference_t<T>&& t) noexcept
    {
        return static_cast<T&&>(t);
    }


    namespace detail
    {
        template<typename T>
        struct is_integral_helper : false_type {};
        template<> struct is_integral_helper<bool> : true_type {};
        template<> struct is_integral_helper<char> : true_type {};
        template<> struct is_integral_helper<signed char> : true_type {};
        template<> struct is_integral_helper<unsigned char> : true_type {};
        template<> struct is_integral_helper<short> : true_type {};
        template<> struct is_integral_helper<unsigned short> : true_type {};
        template<> struct is_integral_helper<char16_t> : true_type {};
        template<> struct is_integral_helper<char32_t> : true_type {};
        template<> struct is_integral_helper<wchar_t> : true_type {};
        template<> struct is_integral_helper<int> : true_type {};
        template<> struct is_integral_helper<unsigned int> : true_type {};
        template<> struct is_integral_helper<long> : true_type {};
        template<> struct is_integral_helper<unsigned long> : true_type {};
        template<> struct is_integral_helper<long long> : true_type {};
        template<> struct is_integral_helper<unsigned long long> : true_type {};
    }

    template<typename T>
    struct is_integral : detail::is_integral_helper<remove_cv_t<T>> {};

    template<typename T>
    struct underlying_type
    {
        using type = __underlying_type(T);
    };
    template<typename T>
    using underlying_type_t = typename underlying_type<T>::type;

    template<typename T>
    struct is_enum : public integral_constant<bool, __is_enum(T)> {};


    template<bool B, typename T = void>
    struct enable_if {};
    template<typename T>
    struct enable_if<true, T>
    {
        using type = T;
    };

    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template<typename T, typename U>
    struct is_same : false_type {};

    template<typename T>
    struct is_same<T, T> : true_type {};
}

#endif
