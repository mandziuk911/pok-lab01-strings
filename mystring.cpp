#include "mystring.hpp"

#include <cctype>
#include <cstring>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>


namespace {
std::size_t checked_add(std::size_t left, std::size_t right) {
    if (right > std::numeric_limits<std::size_t>::max() - left) throw std::length_error("string size overflow");
    return left + right;
}
int compare_strings(const my_str_t& lhs, const my_str_t& rhs) {
    const std::size_t common = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    for (std::size_t i = 0; i < common; ++i) {
        const unsigned char left = static_cast<unsigned char>(lhs[i]);
        const unsigned char right = static_cast<unsigned char>(rhs[i]);
        if (left < right) return -1;
        if (left > right) return 1;
    }
    if (lhs.size() < rhs.size()) return -1;
    if (lhs.size() > rhs.size()) return 1;
    return 0;
}
}

my_str_t::my_str_t() : data_m(new char[2]), capacity_m(1), size_m(0) { data_m[0] = '\0'; }
my_str_t::my_str_t(std::size_t size, char initial) : data_m(nullptr), capacity_m(growth_capacity(size)), size_m(size) { if (capacity_m == std::numeric_limits<std::size_t>::max()) throw std::length_error("string size overflow"); data_m = new char[capacity_m + 1]; for (std::size_t i = 0; i < size_m; ++i) data_m[i] = initial; data_m[size_m] = '\0'; }
my_str_t::my_str_t(const char* cstr) : my_str_t() { if (cstr == nullptr) throw std::invalid_argument("null C string"); append(cstr); }
my_str_t::my_str_t(const std::string& str) : my_str_t() { reserve(str.size()); for (std::size_t i = 0; i < str.size(); ++i) data_m[i] = str[i]; size_m = str.size(); data_m[size_m] = '\0'; }
my_str_t::my_str_t(const my_str_t& other) : my_str_t() { reserve(other.size_m); std::memcpy(data_m, other.data_m, other.size_m + 1); size_m = other.size_m; }
my_str_t::my_str_t(my_str_t&& other) : data_m(other.data_m), capacity_m(other.capacity_m), size_m(other.size_m) { other.data_m = new char[2]; other.data_m[0] = '\0'; other.capacity_m = 1; other.size_m = 0; }
my_str_t& my_str_t::operator=(const my_str_t& other) { if (this != &other) { my_str_t copy(other); swap(copy); } return *this; }
my_str_t& my_str_t::operator=(my_str_t&& other) { if (this != &other) { char* replacement = new char[2]; replacement[0] = '\0'; delete[] data_m; data_m = other.data_m; capacity_m = other.capacity_m; size_m = other.size_m; other.data_m = replacement; other.capacity_m = 1; other.size_m = 0; } return *this; }
my_str_t::~my_str_t() { delete[] data_m; }
void my_str_t::swap(my_str_t& other) noexcept { using std::swap; swap(data_m, other.data_m); swap(capacity_m, other.capacity_m); swap(size_m, other.size_m); }
char& my_str_t::operator[](std::size_t index) { return data_m[index]; }
const char& my_str_t::operator[](std::size_t index) const { return data_m[index]; }
char& my_str_t::at(std::size_t index) { if (index >= size_m) throw std::out_of_range("string index out of range"); return data_m[index]; }
const char& my_str_t::at(std::size_t index) const { if (index >= size_m) throw std::out_of_range("string index out of range"); return data_m[index]; }
void my_str_t::reserve(std::size_t new_capacity) { if (new_capacity <= capacity_m) return; if (new_capacity == std::numeric_limits<std::size_t>::max()) throw std::length_error("string size overflow"); char* data = new char[new_capacity + 1]; std::memcpy(data, data_m, size_m + 1); delete[] data_m; data_m = data; capacity_m = new_capacity; }
void my_str_t::shrink_to_fit() { if (capacity_m == size_m) return; char* data = new char[size_m + 1]; std::memcpy(data, data_m, size_m + 1); delete[] data_m; data_m = data; capacity_m = size_m; }
void my_str_t::resize(std::size_t new_size, char new_char) { ensure_capacity(new_size); for (std::size_t i = size_m; i < new_size; ++i) data_m[i] = new_char; size_m = new_size; data_m[size_m] = '\0'; }
void my_str_t::clear() noexcept { size_m = 0; data_m[0] = '\0'; }
void my_str_t::insert(std::size_t index, const my_str_t& str) { if (index > size_m) throw std::out_of_range("string insertion index out of range"); if (&str == this) { my_str_t copy(str); insert(index, copy); return; } if (str.size_m == 0) return; const std::size_t old_size = size_m; ensure_capacity(checked_add(old_size, str.size_m)); std::memmove(data_m + index + str.size_m, data_m + index, old_size - index + 1); std::memcpy(data_m + index, str.data_m, str.size_m); size_m = checked_add(old_size, str.size_m); }
void my_str_t::insert(std::size_t index, char character) { if (index > size_m) throw std::out_of_range("string insertion index out of range"); ensure_capacity(checked_add(size_m, 1)); std::memmove(data_m + index + 1, data_m + index, size_m - index + 1); data_m[index] = character; ++size_m; }
void my_str_t::insert(std::size_t index, const char* cstr) { if (cstr == nullptr) throw std::invalid_argument("null C string"); if (index > size_m) throw std::out_of_range("string insertion index out of range"); for (std::size_t offset = 0; offset <= size_m; ++offset) { if (cstr == data_m + offset) { my_str_t copy(cstr); insert(index, copy); return; } } const std::size_t inserted_size = cstring_length(cstr); if (inserted_size == 0) return; const std::size_t old_size = size_m; ensure_capacity(checked_add(old_size, inserted_size)); std::memmove(data_m + index + inserted_size, data_m + index, old_size - index + 1); std::memcpy(data_m + index, cstr, inserted_size); size_m = checked_add(old_size, inserted_size); }
void my_str_t::append(const my_str_t& str) { insert(size_m, str); }
void my_str_t::append(char character) { insert(size_m, character); }
void my_str_t::append(const char* cstr) { insert(size_m, cstr); }
void my_str_t::erase(std::size_t begin, std::size_t count) { if (begin > size_m) throw std::out_of_range("string erasure index out of range"); const std::size_t removed = count < size_m - begin ? count : size_m - begin; std::memmove(data_m + begin, data_m + begin + removed, size_m - begin - removed + 1); size_m -= removed; }
std::size_t my_str_t::size() const noexcept { return size_m; }
std::size_t my_str_t::capacity() const noexcept { return capacity_m; }
const char* my_str_t::c_str() const noexcept { return data_m; }
std::size_t my_str_t::find(char character, std::size_t index) const { if (index > size_m) throw std::out_of_range("string find index out of range"); for (std::size_t i = index; i < size_m; ++i) if (data_m[i] == character) return i; return not_found; }
std::size_t my_str_t::find(const std::string& str, std::size_t index) const { return find(str.c_str(), index); }
std::size_t my_str_t::find(const char* cstr, std::size_t index) const { if (cstr == nullptr) throw std::invalid_argument("null C string"); if (index > size_m) throw std::out_of_range("string find index out of range"); const std::size_t needle_size = cstring_length(cstr); if (needle_size == 0) return index; if (needle_size > size_m - index) return not_found; for (std::size_t i = index; i + needle_size <= size_m; ++i) { std::size_t j = 0; while (j < needle_size && data_m[i + j] == cstr[j]) ++j; if (j == needle_size) return i; } return not_found; }
my_str_t my_str_t::substr(std::size_t begin, std::size_t count) const { if (begin > size_m) throw std::out_of_range("substring index out of range"); const std::size_t result_size = count < size_m - begin ? count : size_m - begin; my_str_t result(result_size, ' '); if (result_size != 0) std::memcpy(result.data_m, data_m + begin, result_size); result.data_m[result_size] = '\0'; return result; }
my_str_t& my_str_t::operator+=(const my_str_t& rhs) { append(rhs); return *this; }
my_str_t& my_str_t::operator+=(const char* rhs) { append(rhs); return *this; }
my_str_t& my_str_t::operator+=(char rhs) { append(rhs); return *this; }
my_str_t& my_str_t::operator*=(std::size_t count) { if (count == 0) { clear(); return *this; } if (size_m != 0 && count > std::numeric_limits<std::size_t>::max() / size_m) throw std::length_error("string multiplication overflow"); const std::size_t original_size = size_m; const std::size_t final_size = original_size * count; ensure_capacity(final_size); for (std::size_t copy = 1; copy < count; ++copy) std::memcpy(data_m + copy * original_size, data_m, original_size); size_m = final_size; data_m[size_m] = '\0'; return *this; }
std::size_t my_str_t::cstring_length(const char* cstr) { std::size_t length = 0; while (cstr[length] != '\0') ++length; return length; }
std::size_t my_str_t::growth_capacity(std::size_t required) { return required < 1 ? 1 : required; }
void my_str_t::ensure_capacity(std::size_t required) { if (required <= capacity_m) return; if (required > std::numeric_limits<std::size_t>::max() / 2) { reserve(required); return; } std::size_t doubled = capacity_m * 2; reserve(doubled > required ? doubled : required); }

std::ostream& operator<<(std::ostream& stream, const my_str_t& str) { stream.write(str.c_str(), static_cast<std::streamsize>(str.size())); return stream; }
std::istream& operator>>(std::istream& stream, my_str_t& str) { str.clear(); char character = '\0'; while (stream.get(character) && std::isspace(static_cast<unsigned char>(character))) {} if (!stream) return stream; do { str.append(character); } while (stream.get(character) && !std::isspace(static_cast<unsigned char>(character))); if (stream && std::isspace(static_cast<unsigned char>(character))) stream.unget(); return stream; }
std::istream& readline(std::istream& stream, my_str_t& str) { str.clear(); char character = '\0'; while (stream.get(character) && character != '\n') str.append(character); return stream; }
bool operator==(const my_str_t& lhs, const my_str_t& rhs) { return compare_strings(lhs, rhs) == 0; }
bool operator!=(const my_str_t& lhs, const my_str_t& rhs) { return !(lhs == rhs); }
bool operator<(const my_str_t& lhs, const my_str_t& rhs) { return compare_strings(lhs, rhs) < 0; }
bool operator<=(const my_str_t& lhs, const my_str_t& rhs) { return compare_strings(lhs, rhs) <= 0; }
bool operator>(const my_str_t& lhs, const my_str_t& rhs) { return compare_strings(lhs, rhs) > 0; }
bool operator>=(const my_str_t& lhs, const my_str_t& rhs) { return compare_strings(lhs, rhs) >= 0; }
bool operator==(const my_str_t& lhs, const char* rhs) { return lhs == my_str_t(rhs); }
bool operator!=(const my_str_t& lhs, const char* rhs) { return !(lhs == rhs); }
bool operator<(const my_str_t& lhs, const char* rhs) { return lhs < my_str_t(rhs); }
bool operator<=(const my_str_t& lhs, const char* rhs) { return lhs <= my_str_t(rhs); }
bool operator>(const my_str_t& lhs, const char* rhs) { return lhs > my_str_t(rhs); }
bool operator>=(const my_str_t& lhs, const char* rhs) { return lhs >= my_str_t(rhs); }
bool operator==(const char* lhs, const my_str_t& rhs) { return my_str_t(lhs) == rhs; }
bool operator!=(const char* lhs, const my_str_t& rhs) { return !(lhs == rhs); }
bool operator<(const char* lhs, const my_str_t& rhs) { return my_str_t(lhs) < rhs; }
bool operator<=(const char* lhs, const my_str_t& rhs) { return my_str_t(lhs) <= rhs; }
bool operator>(const char* lhs, const my_str_t& rhs) { return my_str_t(lhs) > rhs; }
bool operator>=(const char* lhs, const my_str_t& rhs) { return my_str_t(lhs) >= rhs; }
my_str_t operator+(const my_str_t& lhs, const my_str_t& rhs) { my_str_t result(lhs); result += rhs; return result; }
my_str_t operator+(const my_str_t& lhs, const char* rhs) { my_str_t result(lhs); result += rhs; return result; }
my_str_t operator+(const char* lhs, const my_str_t& rhs) { my_str_t result(lhs); result += rhs; return result; }
my_str_t operator+(const my_str_t& lhs, char rhs) { my_str_t result(lhs); result += rhs; return result; }
my_str_t operator+(char lhs, const my_str_t& rhs) { my_str_t result(1, lhs); result += rhs; return result; }
my_str_t operator*(const my_str_t& str, std::size_t count) { my_str_t result(str); result *= count; return result; }
my_str_t operator*(std::size_t count, const my_str_t& str) { return str * count; }
