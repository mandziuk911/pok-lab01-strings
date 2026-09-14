#include <cassert>
#include <sstream>
#include <string>
#include <utility>

#include "mystring.hpp"
#include "mystring_c.h"

int main() {
    my_str_t empty;
    assert(empty.size() == 0 && empty.capacity() >= 1);
    my_str_t filled(3, 'a');
    my_str_t from_cstr("hello");
    my_str_t from_std(std::string("world"));
    my_str_t copied(from_cstr);
    my_str_t moved(std::move(from_std));
    assert(from_std.size() == 0 && std::string(from_std.c_str()).empty());
    from_std.append('x');
    assert(from_std == "x");
    copied = filled;
    moved = my_str_t("move");
    filled.swap(copied);
    filled[0] = 'A';
    assert(filled.at(0) == 'A');
    bool caught = false;
    try {
        filled.at(100);
    } catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);
    filled.reserve(30);
    assert(filled.capacity() >= 30);
    filled.resize(5, 'z');
    filled.resize(2);
    filled.shrink_to_fit();
    filled.clear();
    from_cstr.insert(5, '!');
    from_cstr.insert(0, "Say ");
    from_cstr.insert(0, my_str_t("X"));
    from_cstr.append('!');
    from_cstr.append(" end");
    from_cstr.append(my_str_t("."));
    from_cstr.erase(0, 1);
    // Exercise aliasing paths that would otherwise leave a c_str pointer dangling.
    my_str_t self_reference("abc");
    self_reference.append(self_reference.c_str());
    assert(self_reference == "abcabc");
    self_reference.insert(3, self_reference);
    assert(self_reference == "abcabcabcabc");
    assert(from_cstr.find('h') != my_str_t::not_found);
    assert(from_cstr.find("hello") != my_str_t::not_found);
    assert(from_cstr.find(std::string("hello")) != my_str_t::not_found);
    assert(from_cstr.substr(0, 5) == "Say h");
    assert(from_cstr.c_str() != nullptr);
    assert(my_str_t("a") < my_str_t("b") && my_str_t("a") <= "a" && "b" > my_str_t("a"));
    assert(my_str_t("a") != "b" && "a" == my_str_t("a") && "a" <= my_str_t("a"));
    my_str_t ops("ab");
    ops += "c";
    ops += 'd';
    ops += my_str_t("e");
    assert(ops == "abcde");
    assert(my_str_t("a") + "b" + 'c' == "abc");
    assert('a' + my_str_t("b") == "ab");
    assert(my_str_t("ab") * 3 == "ababab" && 2 * my_str_t("x") == "xx");
    ops *= 2;
    assert(ops == "abcdeabcde");
    std::ostringstream output;
    output << ops;
    assert(output.str() == "abcdeabcde");
    std::istringstream input("  one two\nline");
    my_str_t read;
    input >> read;
    assert(read == "one");
    readline(input, read);
    assert(read == " two");

    // The C API is verified from C++ here; c_api_demo.c also compiles it as C.
    my_str_handle* c_string = my_str_create_from_cstr("C");
    assert(c_string != nullptr);
    my_str_handle* c_copy = my_str_create_from_cstr(" copy");
    assert(c_copy != nullptr);
    assert(my_str_append(c_string, " API") == MY_STR_OK);
    assert(my_str_append_string(c_string, c_copy) == MY_STR_OK);
    assert(my_str_append_char(c_string, '!') == MY_STR_OK);
    assert(my_str_insert(c_string, 0, "my ") == MY_STR_OK);
    assert(my_str_insert_string(c_string, 0, c_copy) == MY_STR_OK);
    assert(my_str_erase(c_string, 0, 3) == MY_STR_OK);
    assert(my_str_resize(c_string, 7, '.') == MY_STR_OK);
    assert(my_str_reserve(c_string, 20) == MY_STR_OK && my_str_capacity(c_string) >= 20);
    assert(my_str_repeat(c_string, 2) == MY_STR_OK);
    char character = '\0';
    assert(my_str_at(c_string, 0, &character) == MY_STR_OK);
    assert(my_str_set_at(c_string, 0, character) == MY_STR_OK);
    size_t position = 0;
    assert(my_str_find_char(c_string, 'A', 0, &position) == MY_STR_OK);
    assert(my_str_find(c_string, "API", 0, &position) == MY_STR_OK);
    my_str_handle* part = nullptr;
    assert(my_str_substr(c_string, 0, 1, &part) == MY_STR_OK);
    int comparison = 0;
    assert(my_str_compare(part, part, &comparison) == MY_STR_OK && comparison == 0);
    assert(my_str_shrink_to_fit(c_string) == MY_STR_OK);
    assert(my_str_clear(c_string) == MY_STR_OK && my_str_size(c_string) == 0);
    assert(my_str_assign(c_string, "done") == MY_STR_OK);
    assert(std::string(my_str_c_str(c_string)) == "done");
    assert(my_str_compare_cstr(c_string, "done", &comparison) == MY_STR_OK && comparison == 0);
    assert(my_str_append(nullptr, "invalid") == MY_STR_INVALID_ARGUMENT);
    my_str_destroy(part);
    my_str_destroy(c_copy);
    my_str_destroy(c_string);
}
