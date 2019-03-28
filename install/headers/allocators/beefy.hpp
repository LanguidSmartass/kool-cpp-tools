/** @file beefy.hpp
 * 
 * @author Novoselov Ivan
 * @email  jedi.orden@gmail.com
 * @date   14.03.2019
 *
 * MIT License
 *
 * Copyright (c) 2019 Ivan Novoselov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @brief Static allocator, all memory pools are allocated at compile time.
 *        Classes are divided into pure virtual 'storage_base' --
 *        pool holder interface
 *        and an allocator itself, which works on the array of storage_base
 *        pointers.
 *
 * @details
 *
 *        Storage_base is implied to hold three heaps that track the following:
 *        - either the pointer is allocated or not (heap_flags)
 *
 *        - movement of the pointers indices along the heap itself
 *          (heap_indices), used for constant-time access to the pointer
 *
 *        - movement of the pointers original indices (heap_indices_reversed),
 *          used for O(1) access time during deallocation when the requested
 *          pointer is being searched for
 *
 *        - non-heap sorted_pointers -- array of pointers to the internal pool
 *
 *        All of this makes this storage really chunky and fat.
 *        Each block of data in the pool will require:
 *        - one bool (heap_flags>
 *        - two std::size_t (heap_indices)
 *        - one std::uintptr_t (sorted_pointers)
 *        If (hopefully) sizeof(std::size_t) == sizeof(std::uintptr_t) the
 *        overhead table will be something like this:
 *
 *        System    Overhead in bytes
 *        address   per one block of data
 *        16 bit    1 + 2 + 2 == 5
 *        32 bit    1 + 4 + 4 == 9
 *        64 bit    1 + 8 + 8 == 17
 *
 *        This is the price you pay for O(logN) allocation and deallocation.
 *
 *        The second price you pay is pure abstract interface indirection so
 *        that the allocator could traverse multiple storages with different
 *        block sizes (the type of the elements is still the same)
 *
 *        My proposal would be to use it when your data blocks are at least as
 *        twice as big as the overhead, but this is purely a personal opinion.
 *
 *        Summing up:
 *        It's beefy because of the 5..17 bytes of overhead per single data
 *        block.
 *        It's fast because this overhead allows the allocator to traverse
 *        the control heaps with logN time
 *
 * Usage example:
 *
 * /// declare multiple storages types
 * using storage_0 = storage<   2, 1024>;
 * using storage_1 = storage<  11,  500>;
 * using storage_2 = storage<  50,   22>;
 * using storage_3 = storage<4023,    3>;
 *
 * /// instantiate the storages
 * static auto s0 = storage_0();
 * static auto s1 = storage_1();
 * static auto s2 = storage_2();
 * static auto s3 = storage_3();
 *
 * /// make std::array of pointers to these storages (virtual base ones)
 * static auto storage = make_ptrs_to_storages_array(s0, s1, s2, s3);
 *
 * /// Bind the storage to the allocator
 * using alloc = allocator<decltype(storage), storage>;
 *
 * /// From here everything is simple -- use your memory to your heart's content
 * auto myalloc = alloc();
 * auto p0 = myalloc.allocate(0);
 * auto p1 = myalloc.allocate(1);
 * auto p2 = myalloc.allocate(2222);
 * auto p3 = myalloc.allocate(2222);
 * myalloc.deallocate(p2, 2222);
 * myalloc.deallocate(p3, 2222);
 * p2 = myalloc.allocate(2222);
 *
 */

#ifndef KCPPT_ALLOCATORS_BEEFY_HPP
#define KCPPT_ALLOCATORS_BEEFY_HPP

#include "../range.hpp"
#include "../c_array.hpp"

#include <array>
#include <cinttypes>
#include <type_traits>

namespace kcppt {

namespace allocators {

namespace beefy {

namespace _implementation {

template <typename T, std::size_t Sz>
[[nodiscard]]
constexpr static auto build_pointers_array (
    T* base = nullptr, std::size_t block_size = 0
) noexcept {
    std::array<T*, Sz> ret {base};
    for (auto i : range::range(1u, ret.size())) {
        ret[i] = block_size + ret[i - 1u];
    }
    return ret;
}

template <std::size_t Sz>
[[nodiscard]]
constexpr static auto build_indices_array () noexcept {
    std::array<std::size_t, Sz> ret {};
    for (auto i : range::indices(ret)) {
        ret[i] = i;
    }
    return ret;
}

}

class storage_base {
public:
    /**
     * @return size of a single block of bytes
     */
    [[nodiscard]]
    virtual auto block_size () const noexcept -> std::size_t = 0;
    /**
     * @return total number of blocks of bytes (each block has 'block_size')
     */
    [[nodiscard]]
    virtual auto blocks_count () const noexcept -> std::size_t = 0;
    /**
     * @return pointer to an array of size 'blocks_count' that contains
     *         boolean 'heap_flags', true if allocated or false if deallocated
     */
    [[nodiscard]]
    virtual auto heap_flags () noexcept -> bool* = 0;
    /**
     * @return heap of original indices, tracks where the original indices were
     */
    [[nodiscard]]
    virtual auto heap_indices () noexcept -> std::size_t* = 0;
    /**
     * @return same for a reversed table of indices
     *         (provides constant index search instead of linear)
     */
    [[nodiscard]]
    virtual auto heap_indices_reversed () noexcept -> std::size_t* = 0;
    /**
     * @return pointer to an array of pointers to each byte block in the
     *         internal pool
     */
    [[nodiscard]]
    virtual auto sorted_pointers () const noexcept -> void* const* = 0;
    
    virtual ~storage_base () noexcept = default;
};

template <std::size_t TBlockSize, std::size_t TBlocksCount>
class storage final : public storage_base {
    static_assert(TBlockSize != 0);
    static_assert(TBlocksCount != 0);

private:
    c_array::c_array<std::uint8_t, TBlockSize * TBlocksCount> _pool_of_bytes;
//    std::uint8_t _pool_of_T[TBlockSize * TBlocksCount];
    
    /******
     * @brief _heap_flags, _heap_pointers and _heap_indices are a part of a
     *        single heap-like data structure. Heap elements are sink, float and
     *        sorted based on values in _heap_flags.
     *        Values of _heap_pointers and _heap_indices are just dragged along
     *        according to the swapped indices.
     *        _heap_indices contains the original indices and is used to monitor
     *        where the original flags and pointers are located.
     */
    
    /**
     * @brief heap of flags, allocated -- 1, deallocated -- 0
     */
    std::array<bool, TBlocksCount> _heap_flags;
    /**
     * @brief heap of indices, used to watch the original element position
     *        against the heap indices
     */
    std::array<std::size_t, TBlocksCount> _heap_indices;
    /**
     * @brief heap of reversed indices, used to track the original element
     *        position against the _sorted_pointers indices
     */
    std::array<std::size_t, TBlocksCount> _heap_indices_reversed;
    /**
     * @brief sorted array of const pointers to each block in _pool_of_bytes
     */
    const std::array<void*, TBlocksCount> _sorted_pointers;

public:
    storage () noexcept :
        _pool_of_bytes(),
        _heap_flags(),
        _heap_indices(
            _implementation::build_indices_array<TBlocksCount>()
        ),
        _heap_indices_reversed(
            _implementation::build_indices_array<TBlocksCount>()
        ),
        _sorted_pointers(
            _implementation::build_pointers_array<void, TBlocksCount>
                (_pool_of_bytes, TBlockSize)
        ) {}
    
    ~storage () noexcept final = default;

public:
    [[nodiscard]]
    auto block_size () const noexcept -> std::size_t final {
        return TBlockSize;
    }
    
    [[nodiscard]]
    auto blocks_count () const noexcept -> std::size_t final {
        return TBlocksCount;
    }
    
    [[nodiscard]]
    auto heap_flags () noexcept -> bool* final {
        return _heap_flags.data();
    }
    
    [[nodiscard]]
    auto heap_indices () noexcept -> std::size_t* final {
        return _heap_indices.data();
    }
    
    [[nodiscard]]
    auto heap_indices_reversed () noexcept -> std::size_t* final {
        return _heap_indices_reversed.data();
    }
    
    [[nodiscard]]
    auto sorted_pointers () const noexcept -> void* const* final {
        return _sorted_pointers.data();
    }
};

template <
    template <typename, std::size_t...> class FixedSequenceContainer,
    std::size_t...Sizes
>
struct ptrs_to_storages_container {
    using type = FixedSequenceContainer<storage_base*, Sizes...>;
};

template <
    template <typename, std::size_t...> class FixedSequenceContainer,
    std::size_t...Sizes
>
using ptr_to_storages_container_t =
typename ptrs_to_storages_container<FixedSequenceContainer, Sizes...>::type;

template <std::size_t...Sizes>
using ptrs_to_storages_array_t =
typename ptrs_to_storages_container<std::array, Sizes...>::type;

template <
    template <typename, std::size_t...> class FixedSequenceContainer,
    typename...Ss
>
constexpr auto make_ptrs_to_storages_container (Ss&&...ss) noexcept {
    ptr_to_storages_container_t<
        FixedSequenceContainer, sizeof...(ss)
    > ret {&ss...};
    return ret;
}

template <typename...Ss>
constexpr auto make_ptrs_to_storages_array (Ss&& ...ss) noexcept {
    return ptrs_to_storages_array_t<sizeof...(ss)> {&ss...};
}

/**
 * @brief
 * @tparam SequenceContainer -- any SequenceContainer class.
 * @tparam Container -- reference to SequenceContainer,
 *         the pointers inside must satisfy two requirements:
 *         -- they are ascending-sorted by storage's block_size
 *         -- every block_size must be unique (blocks_count can be the same)
 *         i.e. sort them by Container[i]->block_size()
 */
template <typename SequenceContainer, SequenceContainer& Container>
class allocator {
    static_assert(
        std::is_same_v<
            typename SequenceContainer::value_type,
            storage_base*
        >
    );
    /**
     * @brief Amortizing variables
     */
    std::size_t _block_size;
    std::size_t _blocks_count;
    bool* _heap_flags;
    std::size_t* _heap_indices;
    std::size_t* _heap_indices_reversed;
    void* const* _sorted_pointers;

public:
    constexpr allocator () noexcept :
    _block_size(),
    _blocks_count(),
    _heap_flags(),
    _heap_indices(),
    _heap_indices_reversed(),
    _sorted_pointers()
    {}

public:
    [[nodiscard]]
    auto allocate (std::size_t nT) noexcept -> void* {
        auto i = _search_fitting_container(nT); ///< O(logn)
        if (_container_index_out_of_bounds(i)) { ///< O(1)
            return nullptr;
        }
        _amortize(i); ///< O(1)
        
        if (_heap_top_is_allocated()) { ///< O(1)
            return nullptr;
        }
        
        auto p = _heap_top_pointer(); ///< O(1)
        _heap_top_mark_as_allocated(); ///< O(1)
        _heap_top_sink(); ///< O(logn)
        return p;
    }
    
    auto deallocate (void* p, std::size_t nT) noexcept -> void {
        auto i = _search_fitting_container(nT); ///< O(logn)
        if (_container_index_out_of_bounds(i)) { ///< O(1)
            return;
        }
        _amortize(i); ///< O(1)
        
        auto ip = _search_pointer_original_index(p); ///< O(logn)
        if (_index_out_of_bounds(ip)) { ///< O(1)
            return;
        }
        
        auto iheap = _heap_position_of_original_element(ip); ///< O(1)
        _heap_mark_as_deallocated(iheap); ///< O(1)
        _heap_el_float(iheap); ///< O(logn)
    }

private:
    /**
     * @brief
     * @param i
     * @return
     */
    auto _amortize (std::size_t i) noexcept {
        auto& s = *Container[i];
        _block_size = s.block_size();
        _blocks_count = s.blocks_count();
        _heap_flags = s.heap_flags();
        _heap_indices = s.heap_indices();
        _heap_indices_reversed = s.heap_indices_reversed();
        _sorted_pointers = s.sorted_pointers();
    }
    
    /**
     * @brief Search for appropriate storage, logN given that the pointers
     *        are sorted by Container[i]->block_size() and every block_size()
     *        is unique in that container.
     */
    [[nodiscard]]
    auto _search_fitting_container (std::size_t nT) noexcept -> std::size_t {
        auto container_end = Container.size();
        auto il = 0u;          /// start left border at the start
        auto ir = container_end; /// start right border past the end
        /**
         * @brief Simple binary search for an exact match
         */
        while (il != ir) {
            auto im = (il + ir) / 2u;
            auto m = Container[im]->block_size(); /// maybe cache it somehow?
            
            if (nT > m) {
                il = im + 1u;  /// move left border
            } else if (nT < m) {
                ir = im;       /// move right border
            } else {
                return im;     /// exact size match
            }
        }
        
        /**
         * @brief If we got here, check if the 'next' greater element will fit
         */
        if ((ir < container_end) &&
            (nT < Container[ir]->block_size()) &&
            (nT != 0u)) {
            return ir;
        }
        
        return container_end; /// return 'past the end'
    }
    
    [[nodiscard]]
    auto _container_index_out_of_bounds (std::size_t i) const noexcept ->
    bool {
        return i >= Container.size();
    }
    
    /**
     * @brief heap operations
     */
    auto _heap_top_mark_as_allocated () noexcept -> void {
        _heap_flags[0u] = true;
    }
    
    auto _heap_mark_as_deallocated (std::size_t i) noexcept -> void {
        _heap_flags[i] = false;
    }
    
    [[nodiscard]]
    auto _heap_top_is_allocated () noexcept -> bool {
        return _heap_flags[0u];
    }
    
    [[nodiscard]]
    auto _heap_top_is_deallocated () noexcept -> bool {
        return !_heap_flags[0u];
    }
    
    [[nodiscard]]
    auto _heap_top_pointer () noexcept -> void* {
        return _sorted_pointers[_heap_indices[0u]];
    }
    
    auto _heap_top_sink () noexcept -> void {
        _heap_el_sink(0u);
    }
    
    auto _heap_swap (std::size_t i0, std::size_t i1) noexcept -> void {
        auto ri0 = _heap_indices[i0];
        auto ri1 = _heap_indices[i1];
        std::swap(_heap_flags[i0], _heap_flags[i1]);
        std::swap(_heap_indices[i0], _heap_indices[i1]);
        std::swap(_heap_indices_reversed[ri0], _heap_indices_reversed[ri1]);
    }
    
    /**
     * @brief Sort subheap of a parent and two children
     * @param i
     * @return index to which the original i was swapped
     *         if the same value is returned (== i) it means that no swap took
     *         place and the bottom of the heap was reached
     */
    [[nodiscard]]
    auto _heap_build_triple (std::size_t i) noexcept -> std::size_t {
        
        auto ret = i;
        
        auto il = 2 * i + 1u;
        if (il >= _blocks_count) {
            return ret;
        }
        
        if (_heap_flags[i] > _heap_flags[il]) {
            _heap_swap(i, il);
            ret = il;
        }
        
        auto ir = 2 * i + 2u;
        if (ir >= _blocks_count) {
            return ret;
        }
        
        if (_heap_flags[i] > _heap_flags[ir]) {
            _heap_swap(i, ir);
            ret = (ret == il) ? il : ir;
        }
        
        return ret;
    }
    
    auto _heap_el_sink (std::size_t i) noexcept -> void {
        std::size_t idx_as_parent = i;
        std::size_t idx_as_child {};
        
        while (true) {
            idx_as_child = _heap_build_triple(idx_as_parent);
            if (idx_as_child != idx_as_parent) {
                idx_as_parent = idx_as_child;
            } else {
                break;
            }
        }
    }
    
    auto _heap_el_float (std::size_t i) noexcept -> void {
        do {
            auto i_even = ((i & 0b1u) == 0u);
            auto ip = i / 2u - i_even; /// parent index
            
            if (_heap_flags[ip] > _heap_flags[i]) {
                _heap_swap(ip, i);
                i = ip;
            } else {
                break;
            }
        } while (i != 0);
    }
    
    /**
     * @brief Used for constant access in deallocation
     * @param origidx
     * @return
     */
    [[nodiscard]]
    auto _heap_position_of_original_element (
        std::size_t origidx
    ) noexcept -> std::size_t {
        return _heap_indices_reversed[origidx];
    }
    
    /**
     * @brief Non-heap operations
     */
    
    /**
     * @brief  Used for logN access in deallocation
     * @param p
     * @return
     */
    [[nodiscard]]
    auto _search_pointer_original_index (const void* p)
    noexcept -> std::size_t {
        auto il = 0llu;        /// start left border at the start
        auto ir = _blocks_count; /// start right border past the end
        /**
         * @brief Simple binary search for an exact match
         */
        while (il != ir) {
            auto im = (il + ir) / 2u;
            auto m = _sorted_pointers[im];
            
            if (p > m) {
                il = im + 1u;  /// move left border
            } else if (p < m) {
                ir = im;       /// move right border
            } else {
                return im;     /// exact pointer value match
            }
        }
        
        return _blocks_count; /// return 'past the end'
    }
    
    [[nodiscard]]
    auto _index_out_of_bounds (std::size_t i) noexcept -> bool {
        return i >= _blocks_count;
    }
    
};

}
    
}
    
}

#endif /// KCPPT_ALLOCATORS_BEEFY_HPP
