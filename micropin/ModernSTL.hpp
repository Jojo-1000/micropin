/* ModernSTL.h
*
* Copyright (C) 2018 Jan Rogall
*
* This software may be modified and distributed under the terms
* of the MIT license.  See the LICENSE file for details.
*/


#ifndef MODERNSTL_H_
#define MODERNSTL_H_

namespace MicroPin
{
    //STL stuff which we dont have (std::index_sequence, std::tuple, std::array)
    template<size_t... Indices>
    struct indices
    {
        using next = indices<Indices..., sizeof...(Indices)>;
    };

    template<size_t Size>
    struct build_indices
    {
        using type = typename build_indices<Size - 1>::type::next;
    };

    template<>
    struct build_indices<0>
    {
        using type = indices<>;
    };

    //own_tuple does not have most of std::tuple functions
    template<typename... Ts>
    struct own_tuple
    {
        constexpr own_tuple() = default;
    };

    template<typename First, typename... Rest>
    struct own_tuple<First, Rest...> : own_tuple<Rest...>
    {
        constexpr own_tuple(First first, Rest... rest)
        : own_tuple<Rest...>(rest...), head(first)
        {}
        First head;
    };

    template<size_t I, typename Tuple>
    struct own_tuple_element
    {};

    template<typename First, typename... Rest>
    struct own_tuple_element<0, own_tuple<First, Rest...>>
    {
        //First type
        using type = First;
        //Implementation detail
        using tuple_type = own_tuple<First, Rest...>;
    };
    template<size_t I, typename First, typename... Rest>
    struct own_tuple_element<I, own_tuple<First, Rest...>> : own_tuple_element<I - 1, own_tuple<Rest...>>
    {};

    template<size_t I, typename Tuple>
    using own_tuple_element_t = typename own_tuple_element<I, Tuple>::type;

    template<typename Tuple>
    struct own_tuple_size
    {};
    template<typename... Ts>
    struct own_tuple_size<own_tuple<Ts...>>
    {
        static constexpr size_t value = sizeof...(Ts);
    };

    //get overloads
    template<size_t I, typename... Types>
    constexpr const own_tuple_element_t<I, own_tuple<Types...>>& get(const own_tuple<Types...>& tuple)
    {
        using tuple_type = typename own_tuple_element<I, own_tuple<Types...>>::tuple_type;
        //tuple inherits recursively, head of the base class accesses the correct member
        return static_cast<const tuple_type&>(tuple).head;
    }
    template<size_t I, typename... Types>
    constexpr own_tuple_element_t<I, own_tuple<Types...>>& get(own_tuple<Types...>& tuple)
    {
        using tuple_type = typename own_tuple_element<I, own_tuple<Types...>>::tuple_type;
        return static_cast<tuple_type&>(tuple).head;
    }

    template<typename... Ts>
    constexpr auto make_own_tuple(Ts&&... ts)
    {
        return own_tuple<decay_t<Ts>...>(forward<Ts>(ts)...);
    }

    //Not as flexible as std::tuple_cat, but easier
    template<typename... TupleTypes0, typename... TupleTypes1, size_t... Indices0, size_t... Indices1>
    constexpr auto own_tuple_cat(own_tuple<TupleTypes0...> t0, own_tuple<TupleTypes1...> t1, indices<Indices0...>, indices<Indices1...>)
    {
        return make_own_tuple(get<Indices0>(t0)..., get<Indices1>(t1)...);
    }
    template<typename... TupleTypes0, typename... TupleTypes1>
    constexpr auto own_tuple_cat(own_tuple<TupleTypes0...> t0, own_tuple<TupleTypes1...> t1)
    {
        return own_tuple_cat(t0, t1, typename build_indices<own_tuple_size<own_tuple<TupleTypes0...>>::value>::type{},
        typename build_indices<own_tuple_size<own_tuple<TupleTypes1...>>::value>::type{});
    }

    template<typename T, size_t N>
    struct own_array
    {
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        //Raw pointers as iterators
        using iterator = pointer;
        using const_iterator = const_pointer;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        constexpr reference operator[](size_type pos)
        {
            return arr[pos];
        }
        constexpr const_reference operator[](size_type pos) const
        {
            return arr[pos];
        }
        constexpr reference front()
        {
            return arr[0];
        }
        constexpr const_reference front() const
        {
            return arr[0];
        }
        constexpr reference back()
        {
            return arr[N - 1];
        }
        constexpr const_reference back() const
        {
            return arr[N - 1];
        }
        constexpr T* data() noexcept
        {
            return arr;
        }
        constexpr const T* data() const noexcept
        {
            return arr;
        }
        iterator begin() noexcept
        {
            return arr;
        }
        const_iterator begin() const noexcept
        {
            return arr;
        }
        iterator end() noexcept
        {
            return arr + N;
        }
        const_iterator end() const noexcept
        {
            return arr + N;
        }
        constexpr bool empty() const noexcept
        {
            return false;
        }
        constexpr size_type size() const noexcept
        {
            return N;
        }
        constexpr size_type max_size() const noexcept
        {
            return N;
        }
        void fill(const T& value)
        {
            for (T& t : arr)
            {
                t = arr;
            }
        }
        //void swap(own_array& other)
        //{
        //    for (auto it = begin(), otherIt = other.begin(); it != end(); ++it, ++otherIt)
        //    {
        //        std::iter_swap(it, otherIt);
        //    }
        //}

        T arr[N];
    };
    template<typename T>
    struct own_array<T, 0>
    {
        constexpr own_array() = default;
        //Workaround for empty init lists
        constexpr own_array(true_type){}
        using value_type = T;
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        //Raw pointers as iterators
        using iterator = pointer;
        using const_iterator = const_pointer;
        //using reverse_iterator = std::reverse_iterator<iterator>;
        //using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        //constexpr reference operator[](size_type pos);
        //constexpr const_reference operator[](size_type pos);
        //constexpr reference front();
        //constexpr const_reference front();
        //constexpr reference back();
        //constexpr const_reference back();
        //constexpr T* data() noexcept;
        //constexpr const T* data() const noexcept;
        iterator begin() noexcept
        {
            return nullptr;
        }
        const_iterator begin() const noexcept
        {
            return nullptr;
        }
        iterator end() noexcept
        {
            return nullptr;
        }
        const_iterator end() const noexcept
        {
            return nullptr;
        }
        constexpr bool empty() const noexcept
        {
            return true;
        }
        constexpr size_type size() const noexcept
        {
            return 0;
        }
        constexpr size_type max_size() const noexcept
        {
            return 0;
        }
        void fill(const T& value) noexcept
        {}
        void swap(own_array& other) noexcept
        {}
    };

    //Should check if swappable
    template<typename T, size_t N>
    void swap(own_array<T, N>& l, own_array<T, N>& r)
    {
        l.swap(r);
    }


    //own_tuple to array
    template<typename T, typename Tuple, size_t... Indices>
    constexpr own_array<T, own_tuple_size<decay_t<Tuple>>::value> toArray(Tuple&& tuple, indices<Indices...>)
    {
        return { { get<Indices>(forward<Tuple>(tuple))... } };
    }
    template<typename T, typename Tuple>
    constexpr auto toArray(Tuple&& tuple)
    {
        return toArray<T>(forward<Tuple>(tuple), typename build_indices<own_tuple_size<decay_t<Tuple>>::value>::type{});
    }
}


#endif
