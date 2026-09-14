#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "mystring.hpp"
#include "mystring_c.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Test failed: " << message << '\n';
        return false;
    }
    return true;
}

bool test_construction_and_assignment() {
    my_str_t empty;
    my_str_t letters(3, 'a');
    my_str_t from_c_string("hello");
    my_str_t from_std_string(std::string("world"));
    my_str_t copied(from_c_string);
    my_str_t moved(std::move(from_std_string));

    if (!check(empty.size() == 0, "default constructor creates an empty string")) {
        return false;
    }
    if (!check(letters == "aaa", "fill constructor repeats its character")) {
        return false;
    }
    if (!check(copied == "hello", "copy constructor copies text")) {
        return false;
    }
    if (!check(moved == "world", "move constructor keeps the original text")) {
        return false;
    }
    if (!check(from_std_string.size() == 0, "moved-from string is empty")) {
        return false;
    }

    copied = letters;
    moved = my_str_t("new value");
    copied.swap(moved);
    const my_str_t constant("read");
    return check(copied == "new value", "copy assignment and swap work") &&
           check(moved == "aaa", "move assignment works") &&
           check(constant[0] == 'r', "const indexing works");
}

bool test_access_and_capacity() {
    my_str_t text("cat");
    text[0] = 'C';

    if (!check(text.at(0) == 'C', "indexing and at access characters")) {
        return false;
    }

    bool caught_out_of_range = false;
    try {
        text.at(10);
    } catch (const std::out_of_range&) {
        caught_out_of_range = true;
    }
    if (!check(caught_out_of_range, "at rejects an invalid index")) {
        return false;
    }

    text.reserve(20);
    if (!check(text.capacity() >= 20, "reserve grows capacity")) {
        return false;
    }

    text.resize(5, '!');
    if (!check(text == "Cat!!", "resize adds fill characters")) {
        return false;
    }

    text.resize(2);
    text.shrink_to_fit();
    if (!check(text == "Ca", "resize can shrink a string")) {
        return false;
    }

    text.clear();
    return check(text.size() == 0 && std::string(text.c_str()).empty(),
                 "clear restores an empty C string");
}

bool test_changes_and_search() {
    my_str_t text("hello");
    text.insert(5, '!');
    text.insert(0, "Say ");
    text.insert(0, my_str_t("X"));
    text.append('!');
    text.append(" end");
    text.append(my_str_t("."));
    text.erase(0, 1);

    if (!check(text == "Say hello!! end.", "insert, append, and erase change text")) {
        return false;
    }
    if (!check(text.find('h') == 4, "find locates one character")) {
        return false;
    }
    if (!check(text.find("hello") == 4, "find locates a C string")) {
        return false;
    }
    if (!check(text.find(std::string("hello")) == 4, "find locates std::string text")) {
        return false;
    }
    return check(text.substr(0, 5) == "Say h", "substr returns part of a string");
}

bool test_operators_and_streams() {
    my_str_t text("ab");
    text += "c";
    text += 'd';
    text += my_str_t("e");

    if (!check(text == "abcde", "operator += concatenates")) {
        return false;
    }
    if (!check(my_str_t("a") + my_str_t("b") == "ab", "string plus string works")) {
        return false;
    }
    if (!check(my_str_t("a") + "b" + 'c' == "abc", "operator + concatenates")) {
        return false;
    }
    if (!check("a" + my_str_t("b") == "ab", "C string plus string works")) {
        return false;
    }
    if (!check(my_str_t("a") + 'b' == "ab" && 'a' + my_str_t("b") == "ab",
               "character and string concatenation works")) {
        return false;
    }
    if (!check(my_str_t("ab") * 3 == "ababab" && 2 * my_str_t("x") == "xx",
               "operator * repeats strings")) {
        return false;
    }

    text *= 2;
    if (!check(text == "abcdeabcde", "operator *= repeats strings")) {
        return false;
    }
    if (!check(my_str_t("a") == my_str_t("a") && my_str_t("a") != my_str_t("b") &&
                   my_str_t("b") > my_str_t("a") && my_str_t("b") >= my_str_t("b") &&
                   my_str_t("a") < my_str_t("b") && my_str_t("a") <= my_str_t("a") &&
                   my_str_t("a") == "a" && my_str_t("a") != "b" && my_str_t("b") > "a" &&
                   my_str_t("b") >= "b" && my_str_t("a") < "b" && my_str_t("a") <= "a" &&
                   "a" == my_str_t("a") && "a" != my_str_t("b") && "b" > my_str_t("a") &&
                   "b" >= my_str_t("b") && "a" < my_str_t("b") && "a" <= my_str_t("a"),
               "comparison operators are lexicographical")) {
        return false;
    }

    std::ostringstream output;
    output << text;
    if (!check(output.str() == "abcdeabcde", "output stream writes the full string")) {
        return false;
    }

    std::istringstream input("  one two\nline");
    my_str_t read;
    input >> read;
    if (!check(read == "one", "input stream reads one word")) {
        return false;
    }
    readline(input, read);
    return check(read == " two", "readline reads up to a newline");
}

bool test_c_api() {
    my_str_handle* text = my_str_create_from_cstr("C");
    my_str_handle* suffix = my_str_create_from_cstr(" copy");
    if (!check(text != nullptr && suffix != nullptr, "C API creates handles")) {
        my_str_destroy(text);
        my_str_destroy(suffix);
        return false;
    }

    bool success = true;
    success = success && check(my_str_append(text, " API") == MY_STR_OK, "C API appends C strings");
    success =
        success && check(my_str_append_string(text, suffix) == MY_STR_OK, "C API appends handles");
    success =
        success && check(my_str_append_char(text, '!') == MY_STR_OK, "C API appends characters");
    success = success && check(my_str_insert(text, 0, "my ") == MY_STR_OK, "C API inserts text");
    success = success && check(my_str_erase(text, 0, 3) == MY_STR_OK, "C API erases text");
    success = success && check(my_str_resize(text, 7, '.') == MY_STR_OK, "C API resizes strings");
    success = success && check(my_str_repeat(text, 2) == MY_STR_OK, "C API repeats strings");

    char character = '\0';
    std::size_t position = 0;
    success = success &&
              check(my_str_at(text, 0, &character) == MY_STR_OK, "C API reads a checked character");
    success = success && check(my_str_set_at(text, 0, character) == MY_STR_OK,
                               "C API writes a checked character");
    success = success && check(my_str_find_char(text, 'A', 0, &position) == MY_STR_OK,
                               "C API searches for a character");
    success = success && check(my_str_append(nullptr, "invalid") == MY_STR_INVALID_ARGUMENT,
                               "C API reports null handles");

    my_str_destroy(text);
    my_str_destroy(suffix);
    return success;
}

}  // namespace

int main() {
    return test_construction_and_assignment() && test_access_and_capacity() &&
                   test_changes_and_search() && test_operators_and_streams() && test_c_api()
               ? 0
               : 1;
}
