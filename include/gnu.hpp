#ifndef __GNU_HPP__
#define __GNU_HPP__

#ifndef __cplusplus
    #error You must use C++ since this is a wrapper around gnulibc.
#endif

#if __cplusplus < 201703L
    #error You must use C++17 in order to use this wrapper.
#endif

#include <ctime>
#include <string_view>

namespace gnu {
    using ::std::time_t;
    using ::std::clock_t;

    using tm_t = ::std::tm;

    class unix_time {
    protected:
        time_t _unix_time;

    public:
        constexpr unix_time() noexcept : _unix_time(0) {}
        constexpr unix_time(time_t time) noexcept : _unix_time(time) {}

        constexpr unix_time(const unix_time &other) noexcept : _unix_time(other._unix_time) {}
        constexpr unix_time(unix_time &&other) = delete; // well let const unix_time & be this, since there's nothing to move from.

        constexpr unix_time &operator+=(const unix_time &other) noexcept {
            _unix_time += other._unix_time;

            return *this;
        }

        constexpr unix_time &operator-=(const unix_time &other) noexcept {
            _unix_time -= other._unix_time;

            return *this;
        }
        
        constexpr unix_time &operator+=(time_t multiplier) noexcept {
            _unix_time *= multiplier;

            return *this;
        }

        constexpr unix_time &operator-=(time_t diviser) noexcept {
            _unix_time /= diviser;

            return *this;
        }

        constexpr unix_time operator+(const unix_time& other) const noexcept {
            return unix_time(_unix_time + other._unix_time);
        }
        
        constexpr unix_time operator-(const unix_time& other) const noexcept {
            return unix_time(_unix_time - other._unix_time);
        }

        constexpr unix_time operator*(time_t multiplier) const noexcept {
            return unix_time(_unix_time * multiplier);
        }
        
        constexpr unix_time operator/(time_t diviser) const noexcept {
            return unix_time(_unix_time / diviser);
        }

        constexpr time_t operator*() const noexcept {
            return _unix_time;
        }

        constexpr operator time_t() const noexcept {
            return this->operator*();
        }

        constexpr bool operator<(const unix_time &other) const noexcept {
            return _unix_time < other._unix_time;
        }
        
        constexpr bool operator>(const unix_time &other) const noexcept {
            return _unix_time > other._unix_time;
        }
        
        constexpr bool operator<=(const unix_time &other) const noexcept {
            return _unix_time <= other._unix_time;
        }
        
        constexpr bool operator>=(const unix_time &other) const noexcept {
            return _unix_time >= other._unix_time;
        }

        constexpr bool operator==(const unix_time &other) const noexcept {
            return _unix_time == other._unix_time;
        }
        
        constexpr bool operator!=(const unix_time &other) const noexcept {
            return _unix_time != other._unix_time;
        }

        constexpr bool is_nil() const noexcept {
            return _unix_time == 0;
        }

        inline tm_t *local_time() const {
            return std::localtime(&_unix_time);
        }

        inline tm_t *utc_time() const {
            return std::gmtime(&_unix_time);
        }

        // just a pretty name
        inline tm_t *absolute_time() const {
            return this->utc_time();
        }

        inline std::string_view format() const {
            return std::string_view { std::ctime(&_unix_time) };
        }
    };

    inline unix_time time() noexcept {
        return unix_time { std::time(nullptr) };
    }
}

#endif

