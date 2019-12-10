//
// Created by ivan.novoselov on 11/5/2019.
//

#ifndef KCPPT_C_FILE_HPP
#define KCPPT_C_FILE_HPP

#include <array>
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <vector>

#include "c_array.hpp"

namespace kcppt::c_file {

class c_file {
protected:
    std::FILE* m_handle;

public:
    c_file (std::string_view const p, std::string_view const mode) noexcept :
    m_handle { std::fopen(p.data(), mode.data()) }
    {}

    ~c_file () noexcept {
        const auto r = std::fclose(m_handle);
        /// try print
    }

    [[nodiscard]]
    auto is_open () { return m_handle != nullptr; }

    auto read (void* buf, std::size_t const sz, std::size_t const cnt) noexcept {
        return std::fread(buf, sz, cnt, m_handle);
    }

    auto write(void const* buffer, std::size_t const sz, std::size_t const cnt) noexcept -> std::size_t {
        return std::fwrite(buffer, sz, cnt, m_handle);
    }

    template <typename T>
    auto read (T* buf, std::size_t cnt) noexcept {
        return read(buf, sizeof(T), cnt);
    }
    
    template <typename T, std::size_t Sz>
    auto read (kcppt::c_array::c_array<T, Sz>& arr, std::size_t const cnt) noexcept {
        if (cnt > Sz) {
            return 0; /// or throw?
        }
        return read(arr, sizeof(T), cnt);
    }
    
    template <typename T, std::size_t Sz>
    auto read (kcppt::c_array::c_array<T, Sz>& arr) noexcept {
        return read(arr.data(), sizeof(T), Sz);
    }
    
    template <typename T, std::size_t Sz>
    auto read (std::array<T, Sz>& arr) noexcept {
        return read(arr.data(), sizeof(T), Sz);
    }
    
    template <typename T>
    auto read (std::vector<T>& vec, std::size_t const cnt) noexcept {
        return read(vec.data(), sizeof(T), cnt);
    }
    
    template <typename T>
    auto read (std::vector<T>& vec) noexcept {
        return read(vec.data(), sizeof(T), vec.size());
    }

    template <typename T>
    auto write (T const* buf, std::size_t const cnt) noexcept {
        return write(buf, sizeof(T), cnt);
    }

    template <typename T, std::size_t Sz>
    auto write (kcppt::c_array::c_array<T, Sz> const& arr) noexcept {
        return write(arr.data(), sizeof(T), Sz);
    }

    template <typename T, std::size_t Sz>
    auto write (std::array<T, Sz> const& arr, std::size_t const cnt) noexcept {
        if (cnt > Sz) {
            return 0; /// or throw?
        }
        return write(arr.data(), sizeof(T), cnt);
    }

    template <typename T, std::size_t Sz>
    auto write (std::array<T, Sz> const& arr) noexcept {
        return read(arr.data(), sizeof(T), Sz);
    }

    template <typename T>
    auto write (std::vector<T> const& vec, std::size_t const cnt) noexcept {
        return read(vec.data(), sizeof(T), cnt);
    }

    template <typename T>
    auto write (std::vector<T> const& vec) noexcept {
        return write(vec.data(), sizeof(T), vec.size());
    }

    auto flush () noexcept { return std::fflush(m_handle); }
    
    auto tell () noexcept { return std::ftell(m_handle); }
    
    auto getpos (std::fpos_t& pos) noexcept { return std::fgetpos(m_handle, &pos); }
    
    auto setpos (std::fpos_t const pos) noexcept { return std::fsetpos(m_handle, &pos); }
    
    enum class origin : int { begin = SEEK_SET, cur = SEEK_CUR, end = SEEK_END };
    
    auto seek (long const offs, origin const o) noexcept { return std::fseek(m_handle, offs, static_cast<int>(o)); }
    
    auto rewind (std::fpos_t const offs) noexcept {
        auto pos = std::fpos_t {};
        getpos(pos);
        setpos(pos - offs);
    }
    
    auto rewind () noexcept { return std::rewind(m_handle); }

//    [[nodiscard]]
//    auto size () noexcept -> std::size_t;
    
    [[nodiscard]]
    static auto size (const std::filesystem::path& p) noexcept {
        return std::filesystem::file_size(p);
    }

};


}

#endif /// NONSTD_C_FILE_HPP
