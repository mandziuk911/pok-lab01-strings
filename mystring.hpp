#ifndef POK_LAB01_MYSTRING_HPP
#define POK_LAB01_MYSTRING_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

class my_str_t {
public:
    static constexpr std::size_t not_found = static_cast<std::size_t>(-1);

    /** @author Sviatoslav Mandzyuk */
    my_str_t();
    /** @author Sviatoslav Mandzyuk */
    my_str_t(std::size_t size, char initial);
    /** @author Sviatoslav Mandzyuk */
    my_str_t(const char* cstr);
    /** @author Sviatoslav Mandzyuk */
    my_str_t(const std::string& str);
    /** @author Sviatoslav Mandzyuk */
    my_str_t(const my_str_t& other);
    /** @author Sviatoslav Mandzyuk */
    my_str_t(my_str_t&& other);
    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator=(const my_str_t& other);
    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator=(my_str_t&& other);
    /** @author Sviatoslav Mandzyuk */
    ~my_str_t();

    /** @author Sviatoslav Mandzyuk */
    void swap(my_str_t& other) noexcept;
    /** @author Sviatoslav Mandzyuk */
    char& operator[](std::size_t index);
    /** @author Sviatoslav Mandzyuk */
    const char& operator[](std::size_t index) const;
    /** @author Sviatoslav Mandzyuk */
    char& at(std::size_t index);
    /** @author Sviatoslav Mandzyuk */
    const char& at(std::size_t index) const;
    /** @author Sviatoslav Mandzyuk */
    void reserve(std::size_t new_capacity);
    /** @author Sviatoslav Mandzyuk */
    void shrink_to_fit();
    /** @author Sviatoslav Mandzyuk */
    void resize(std::size_t new_size, char new_char = ' ');
    /** @author Sviatoslav Mandzyuk */
    void clear() noexcept;
    /** @author Sviatoslav Mandzyuk */
    void insert(std::size_t index, const my_str_t& str);
    /** @author Sviatoslav Mandzyuk */
    void insert(std::size_t index, char character);
    /** @author Sviatoslav Mandzyuk */
    void insert(std::size_t index, const char* cstr);
    /** @author Sviatoslav Mandzyuk */
    void append(const my_str_t& str);
    /** @author Sviatoslav Mandzyuk */
    void append(char character);
    /** @author Sviatoslav Mandzyuk */
    void append(const char* cstr);
    /** @author Sviatoslav Mandzyuk */
    void erase(std::size_t begin, std::size_t count);
    /** @author Sviatoslav Mandzyuk */
    std::size_t size() const noexcept;
    /** @author Sviatoslav Mandzyuk */
    std::size_t capacity() const noexcept;
    /** @author Sviatoslav Mandzyuk */
    const char* c_str() const noexcept;
    /** @author Sviatoslav Mandzyuk */
    std::size_t find(char character, std::size_t index = 0) const;
    /** @author Sviatoslav Mandzyuk */
    std::size_t find(const std::string& str, std::size_t index = 0) const;
    /** @author Sviatoslav Mandzyuk */
    std::size_t find(const char* cstr, std::size_t index = 0) const;
    /** @author Sviatoslav Mandzyuk */
    my_str_t substr(std::size_t begin, std::size_t count) const;

    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator+=(const my_str_t& rhs);
    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator+=(const char* rhs);
    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator+=(char rhs);
    /** @author Sviatoslav Mandzyuk */
    my_str_t& operator*=(std::size_t count);

private:
    char* data_m;
    std::size_t capacity_m;
    std::size_t size_m;

    /** @author Sviatoslav Mandzyuk */
    static std::size_t cstring_length(const char* cstr);
    /** @author Sviatoslav Mandzyuk */
    static std::size_t growth_capacity(std::size_t required);
    /** @author Sviatoslav Mandzyuk */
    void ensure_capacity(std::size_t required);
};

/** @author Sviatoslav Mandzyuk */
std::ostream& operator<<(std::ostream& stream, const my_str_t& str);
/** @author Sviatoslav Mandzyuk */
std::istream& operator>>(std::istream& stream, my_str_t& str);
/** @author Sviatoslav Mandzyuk */
std::istream& readline(std::istream& stream, my_str_t& str);

/** @author Sviatoslav Mandzyuk */
bool operator==(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator!=(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<=(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>=(const my_str_t& lhs, const my_str_t& rhs);

/** @author Sviatoslav Mandzyuk */
bool operator==(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator!=(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<=(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>=(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
bool operator==(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator!=(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator<=(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
bool operator>=(const char* lhs, const my_str_t& rhs);

/** @author Sviatoslav Mandzyuk */
my_str_t operator+(const my_str_t& lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
my_str_t operator+(const my_str_t& lhs, const char* rhs);
/** @author Sviatoslav Mandzyuk */
my_str_t operator+(const char* lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
my_str_t operator+(const my_str_t& lhs, char rhs);
/** @author Sviatoslav Mandzyuk */
my_str_t operator+(char lhs, const my_str_t& rhs);
/** @author Sviatoslav Mandzyuk */
my_str_t operator*(const my_str_t& str, std::size_t count);
/** @author Sviatoslav Mandzyuk */
my_str_t operator*(std::size_t count, const my_str_t& str);

#endif
