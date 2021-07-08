#pragma once

#include <pybind11/numpy.h>
#include <span>

// see https://github.com/pybind/pybind11/issues/1042#issuecomment-647147819
/**
 * \brief Returns py:array<T> from vector<T>. Efficient as zero-copy.
 * - Uses std::move to obtain ownership of said vector and transfer everything to the heap.
 * - Only accepts parameter using std::move(...), or else the vector metadata on the stack will go out of scope (heap data will always be fine).
 * \tparam T Type.
 * \param passthrough Numpy array.
 * \return py::array_t<T> with a clean and safe reference to contents of Numpy array.
 */
template<typename T>
inline pybind11::array_t<T> toPyArray(std::vector<T>&& passthrough)
{
    // Pass result back to Python.
    // Ref: https://stackoverflow.com/questions/54876346/pybind11-and-stdvector-how-to-free-data-using-capsules
    auto* transferToHeapGetRawPtr = new std::vector<T>(std::move(passthrough));
    // At this point, transferToHeapGetRawPtr is a raw pointer to an object on the heap. No unique_ptr or shared_ptr, it will have to be freed with delete to avoid a memory leak.

    // Alternate implementation: use a shared_ptr or unique_ptr, but this appears to be more difficult to reason about as a raw pointer (void *) is involved - how does C++ know which destructor to call?

    const pybind11::capsule freeWhenDone(transferToHeapGetRawPtr, [](void* toFree) {
        delete static_cast<std::vector<T>*>(toFree);
        //fmt::print("Free memory."); // Within Python, clear memory to check free: sys.modules[__name__].__dict__.clear()
    });

    auto passthroughNumpy = pybind11::array_t<T>(
            /*shape=*/{transferToHeapGetRawPtr->size()}, /*strides=*/{sizeof(T)},
            /*ptr=*/transferToHeapGetRawPtr->data(), freeWhenDone);
    return passthroughNumpy;
}

namespace PyConversions {
    template<typename>
    struct is_array_t : std::false_type {
    };

    template<typename T, int ExtraFlags>
    struct is_array_t<pybind11::array_t<T, ExtraFlags>> : std::true_type {
    };

    template<typename T>
    inline constexpr bool is_array_t_v = is_array_t<T>::value;

    // see https://github.com/pybind/pybind11/issues/1042#issuecomment-663154709
    /**
     * \brief Returns span<T> from py:array_T<T>. and span<const T> from const py:array_T<T>&
     * Efficient as zero-copy.
     * \tparam T Type.
     * \param source Numpy array.
     * \return Span<T> that with a clean and safe reference to contents of Numpy array.
     */
    template<typename Source>
    [[nodiscard]] auto getSpan(Source&& source)
    {
        using vector_type = std::remove_reference_t<Source>;
        static_assert(is_array_t_v<std::remove_const_t<vector_type>>);
        using value_type = std::remove_cvref_t<typename vector_type::value_type>;
        using T = std::conditional_t<std::is_const_v<vector_type>, const value_type, value_type>;

        pybind11::buffer_info passthroughBuf = source.request();
        if (passthroughBuf.ndim != 1)
        {
            throw std::runtime_error("Error. Number of dimensions must be one");
        }
        size_t length = passthroughBuf.shape[0];
        T* passthroughPtr = static_cast<T*>(passthroughBuf.ptr);
        return std::span<T>(passthroughPtr, length);
    }

    template<typename Source>
    [[nodiscard]] auto forwardToSpan(Source&& source)
    {
        using T = std::remove_cvref_t<Source>;
        if constexpr (is_array_t_v<T>)
            return getSpan(std::forward<Source>(source));
        else
            return std::forward<Source>(source);
    }
}// namespace PyConversions
