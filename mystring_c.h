#ifndef POK_LAB01_MYSTRING_C_H
#define POK_LAB01_MYSTRING_C_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct my_str_handle my_str_handle;

enum my_str_status {
    MY_STR_OK = 0,
    MY_STR_INVALID_ARGUMENT = 1,
    MY_STR_OUT_OF_RANGE = 2,
    MY_STR_ALLOCATION_FAILURE = 3,
    MY_STR_FAILURE = 4
};

/** @author Sviatoslav Mandzyuk */ my_str_handle* my_str_create(void);
/** @author Sviatoslav Mandzyuk */ my_str_handle* my_str_create_from_cstr(const char* value);
/** @author Sviatoslav Mandzyuk */ void my_str_destroy(my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ int my_str_assign(my_str_handle* string, const char* value);
/** @author Sviatoslav Mandzyuk */ int my_str_append(my_str_handle* string, const char* value);
/** @author Sviatoslav Mandzyuk */ int my_str_append_string(my_str_handle* string, const my_str_handle* value);
/** @author Sviatoslav Mandzyuk */ int my_str_append_char(my_str_handle* string, char value);
/** @author Sviatoslav Mandzyuk */ int my_str_insert(my_str_handle* string, size_t index, const char* value);
/** @author Sviatoslav Mandzyuk */ int my_str_insert_string(my_str_handle* string, size_t index, const my_str_handle* value);
/** @author Sviatoslav Mandzyuk */ int my_str_erase(my_str_handle* string, size_t begin, size_t count);
/** @author Sviatoslav Mandzyuk */ int my_str_resize(my_str_handle* string, size_t new_size, char fill);
/** @author Sviatoslav Mandzyuk */ int my_str_reserve(my_str_handle* string, size_t capacity);
/** @author Sviatoslav Mandzyuk */ int my_str_shrink_to_fit(my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ int my_str_clear(my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ int my_str_repeat(my_str_handle* string, size_t count);
/** @author Sviatoslav Mandzyuk */ int my_str_substr(const my_str_handle* string, size_t begin, size_t count, my_str_handle** result);
/** @author Sviatoslav Mandzyuk */ size_t my_str_size(const my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ size_t my_str_capacity(const my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ const char* my_str_c_str(const my_str_handle* string);
/** @author Sviatoslav Mandzyuk */ int my_str_at(const my_str_handle* string, size_t index, char* result);
/** @author Sviatoslav Mandzyuk */ int my_str_set_at(my_str_handle* string, size_t index, char value);
/** @author Sviatoslav Mandzyuk */ int my_str_find_char(const my_str_handle* string, char value, size_t index, size_t* result);
/** @author Sviatoslav Mandzyuk */ int my_str_find(const my_str_handle* string, const char* value, size_t index, size_t* result);
/** @author Sviatoslav Mandzyuk */ int my_str_compare(const my_str_handle* left, const my_str_handle* right, int* result);
/** @author Sviatoslav Mandzyuk */ int my_str_compare_cstr(const my_str_handle* left, const char* right, int* result);

#ifdef __cplusplus
}
#endif

#endif
