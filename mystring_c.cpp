#include "mystring_c.h"
#include "mystring.hpp"

#include <new>
#include <stdexcept>

// All functions in this file were authored by Sviatoslav Mandzyuk.
struct my_str_handle { my_str_t value; };
namespace {
int translate_exception() {
    try { throw; }
    catch (const std::bad_alloc&) { return MY_STR_ALLOCATION_FAILURE; }
    catch (const std::out_of_range&) { return MY_STR_OUT_OF_RANGE; }
    catch (const std::invalid_argument&) { return MY_STR_INVALID_ARGUMENT; }
    catch (...) { return MY_STR_FAILURE; }
}
bool valid(const my_str_handle* string) { return string != nullptr; }
}
extern "C" {
my_str_handle* my_str_create(void) { try { return new my_str_handle; } catch (...) { return nullptr; } }
my_str_handle* my_str_create_from_cstr(const char* value) { if (value == nullptr) return nullptr; try { return new my_str_handle{my_str_t(value)}; } catch (...) { return nullptr; } }
void my_str_destroy(my_str_handle* string) { delete string; }
int my_str_assign(my_str_handle* string, const char* value) { if (!valid(string) || value == nullptr) return MY_STR_INVALID_ARGUMENT; try { string->value = my_str_t(value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_append(my_str_handle* string, const char* value) { if (!valid(string) || value == nullptr) return MY_STR_INVALID_ARGUMENT; try { string->value.append(value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_append_string(my_str_handle* string, const my_str_handle* value) { if (!valid(string) || !valid(value)) return MY_STR_INVALID_ARGUMENT; try { string->value.append(value->value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_append_char(my_str_handle* string, char value) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.append(value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_insert(my_str_handle* string, size_t index, const char* value) { if (!valid(string) || value == nullptr) return MY_STR_INVALID_ARGUMENT; try { string->value.insert(index, value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_insert_string(my_str_handle* string, size_t index, const my_str_handle* value) { if (!valid(string) || !valid(value)) return MY_STR_INVALID_ARGUMENT; try { string->value.insert(index, value->value); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_erase(my_str_handle* string, size_t begin, size_t count) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.erase(begin, count); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_resize(my_str_handle* string, size_t new_size, char fill) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.resize(new_size, fill); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_reserve(my_str_handle* string, size_t capacity) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.reserve(capacity); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_shrink_to_fit(my_str_handle* string) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.shrink_to_fit(); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_clear(my_str_handle* string) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; string->value.clear(); return MY_STR_OK; }
int my_str_repeat(my_str_handle* string, size_t count) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value *= count; return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_substr(const my_str_handle* string, size_t begin, size_t count, my_str_handle** result) { if (!valid(string) || result == nullptr) return MY_STR_INVALID_ARGUMENT; *result = nullptr; try { *result = new my_str_handle{string->value.substr(begin, count)}; return MY_STR_OK; } catch (...) { return translate_exception(); } }
size_t my_str_size(const my_str_handle* string) { return valid(string) ? string->value.size() : 0; }
size_t my_str_capacity(const my_str_handle* string) { return valid(string) ? string->value.capacity() : 0; }
const char* my_str_c_str(const my_str_handle* string) { return valid(string) ? string->value.c_str() : nullptr; }
int my_str_at(const my_str_handle* string, size_t index, char* result) { if (!valid(string) || result == nullptr) return MY_STR_INVALID_ARGUMENT; try { *result = string->value.at(index); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_set_at(my_str_handle* string, size_t index, char value) { if (!valid(string)) return MY_STR_INVALID_ARGUMENT; try { string->value.at(index) = value; return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_find_char(const my_str_handle* string, char value, size_t index, size_t* result) { if (!valid(string) || result == nullptr) return MY_STR_INVALID_ARGUMENT; try { *result = string->value.find(value, index); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_find(const my_str_handle* string, const char* value, size_t index, size_t* result) { if (!valid(string) || value == nullptr || result == nullptr) return MY_STR_INVALID_ARGUMENT; try { *result = string->value.find(value, index); return MY_STR_OK; } catch (...) { return translate_exception(); } }
int my_str_compare(const my_str_handle* left, const my_str_handle* right, int* result) { if (!valid(left) || !valid(right) || result == nullptr) return MY_STR_INVALID_ARGUMENT; *result = left->value < right->value ? -1 : (left->value > right->value ? 1 : 0); return MY_STR_OK; }
int my_str_compare_cstr(const my_str_handle* left, const char* right, int* result) { if (!valid(left) || right == nullptr || result == nullptr) return MY_STR_INVALID_ARGUMENT; try { *result = left->value < right ? -1 : (left->value > right ? 1 : 0); return MY_STR_OK; } catch (...) { return translate_exception(); } }
}
