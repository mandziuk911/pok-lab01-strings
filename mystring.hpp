#ifndef POK_LAB01_MYSTRING_HPP
#define POK_LAB01_MYSTRING_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

// Invariant: data_m has capacity_m + 1 bytes and data_m[size_m] is always '\0'.
class my_str_t {
   public:
    static constexpr std::size_t not_found = static_cast<std::size_t>(-1);

    my_str_t();
    my_str_t(std::size_t size, char initial);
    my_str_t(const char* cstr);
    my_str_t(const std::string& str);
    my_str_t(const my_str_t& other);
    my_str_t(my_str_t&& other);
    my_str_t& operator=(const my_str_t& other);
    my_str_t& operator=(my_str_t&& other);
    ~my_str_t();

    void swap(my_str_t& other) noexcept;
    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;
    char& at(std::size_t index);
    const char& at(std::size_t index) const;
    void reserve(std::size_t new_capacity);
    void shrink_to_fit();
    void resize(std::size_t new_size, char new_char = ' ');
    void clear() noexcept;
    void insert(std::size_t index, const my_str_t& str);
    void insert(std::size_t index, char character);
    void insert(std::size_t index, const char* cstr);
    void append(const my_str_t& str);
    void append(char character);
    void append(const char* cstr);
    void erase(std::size_t begin, std::size_t count);
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    const char* c_str() const noexcept;
    std::size_t find(char character, std::size_t index = 0) const;
    std::size_t find(const std::string& str, std::size_t index = 0) const;
    std::size_t find(const char* cstr, std::size_t index = 0) const;
    my_str_t substr(std::size_t begin, std::size_t count) const;

    my_str_t& operator+=(const my_str_t& rhs);
    my_str_t& operator+=(const char* rhs);
    my_str_t& operator+=(char rhs);
    my_str_t& operator*=(std::size_t count);

   private:
    char* data_m;
    std::size_t capacity_m;
    std::size_t size_m;

    static std::size_t cstring_length(const char* cstr);
    static char* make_empty_buffer();
    void ensure_capacity(std::size_t required);
};

std::ostream& operator<<(std::ostream& stream, const my_str_t& str);
std::istream& operator>>(std::istream& stream, my_str_t& str);
std::istream& readline(std::istream& stream, my_str_t& str);

bool operator==(const my_str_t& lhs, const my_str_t& rhs);
bool operator!=(const my_str_t& lhs, const my_str_t& rhs);
bool operator<(const my_str_t& lhs, const my_str_t& rhs);
bool operator<=(const my_str_t& lhs, const my_str_t& rhs);
bool operator>(const my_str_t& lhs, const my_str_t& rhs);
bool operator>=(const my_str_t& lhs, const my_str_t& rhs);

bool operator==(const my_str_t& lhs, const char* rhs);
bool operator!=(const my_str_t& lhs, const char* rhs);
bool operator<(const my_str_t& lhs, const char* rhs);
bool operator<=(const my_str_t& lhs, const char* rhs);
bool operator>(const my_str_t& lhs, const char* rhs);
bool operator>=(const my_str_t& lhs, const char* rhs);
bool operator==(const char* lhs, const my_str_t& rhs);
bool operator!=(const char* lhs, const my_str_t& rhs);
bool operator<(const char* lhs, const my_str_t& rhs);
bool operator<=(const char* lhs, const my_str_t& rhs);
bool operator>(const char* lhs, const my_str_t& rhs);
bool operator>=(const char* lhs, const my_str_t& rhs);

my_str_t operator+(const my_str_t& lhs, const my_str_t& rhs);
my_str_t operator+(const my_str_t& lhs, const char* rhs);
my_str_t operator+(const char* lhs, const my_str_t& rhs);
my_str_t operator+(const my_str_t& lhs, char rhs);
my_str_t operator+(char lhs, const my_str_t& rhs);
my_str_t operator*(const my_str_t& str, std::size_t count);
my_str_t operator*(std::size_t count, const my_str_t& str);

#endif
