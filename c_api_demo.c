#include <stdio.h>

#include "mystring_c.h"

// Author: Sviatoslav Mandzyuk.
int main(void) {
    my_str_handle* greeting = my_str_create_from_cstr("Hello");
    if (greeting == NULL || my_str_append(greeting, " from C") != MY_STR_OK) {
        my_str_destroy(greeting);
        return 1;
    }
    puts(my_str_c_str(greeting));
    my_str_destroy(greeting);
    return 0;
}
