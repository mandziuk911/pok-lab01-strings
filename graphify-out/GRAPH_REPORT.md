# Graph Report - pok-lab01-strings  (2026-09-14)

## Corpus Check
- Corpus is ~3,466 words - fits in a single context window. You may not need a graph.

## Summary
- 74 nodes · 218 edges · 9 communities
- Extraction: 82% EXTRACTED · 18% INFERRED · 0% AMBIGUOUS · INFERRED: 39 edges (avg confidence: 0.85)
- Token cost: 0 input · 32,600 output

## Community Hubs (Navigation)
- C API Core
- C API Operations
- Build and Documentation
- Capacity Management
- C++ String Utilities
- API Usage Tests
- Class Interface
- String Manipulation
- Constructors and Headers

## God Nodes (most connected - your core abstractions)
1. `my_str_t` - 29 edges
2. `my_str_handle` - 29 edges
3. `main()` - 26 edges
4. `valid()` - 24 edges
5. `translate_exception()` - 18 edges
6. `insert` - 7 edges
7. `my_str_t::my_str_t()` - 6 edges
8. `ensure_capacity` - 6 edges
9. `my_str_assign()` - 6 edges
10. `my_str_append()` - 6 edges

## Surprising Connections (you probably didn't know these)
- `main()` --calls--> `my_str_append()`  [INFERRED]
  c_api_demo.c → mystring_c.cpp
- `main()` --calls--> `my_str_c_str()`  [INFERRED]
  c_api_demo.c → mystring_c.cpp
- `my_str_t::my_str_t()` --calls--> `append`  [INFERRED]
  mystring.cpp → mystring.hpp
- `main()` --calls--> `my_str_t`  [INFERRED]
  tests.cpp → mystring.hpp
- `main()` --calls--> `my_str_create_from_cstr()`  [INFERRED]
  tests.cpp → mystring_c.cpp

## Import Cycles
- None detected.

## Communities (9 total, 0 thin omitted)

### Community 0 - "C API Core"
Cohesion: 0.31
Nodes (16): my_str_append_char(), my_str_append_string(), my_str_c_str(), my_str_capacity(), my_str_clear(), my_str_compare(), my_str_create(), my_str_handle (+8 more)

### Community 1 - "C API Operations"
Cohesion: 0.30
Nodes (12): my_str_append(), my_str_assign(), my_str_at(), my_str_compare_cstr(), my_str_erase(), my_str_find(), my_str_find_char(), my_str_insert_string() (+4 more)

### Community 2 - "Build and Documentation"
Cohesion: 0.31
Nodes (9): c_api_demo, CMake build configuration, mystring, string_tests, C ABI exception boundary, C API binding, Manual dynamic-string memory management, my_str_t (+1 more)

### Community 3 - "Capacity Management"
Cohesion: 0.29
Nodes (8): size_t, capacity, ensure_capacity, erase, growth_capacity, resize, size, substr

### Community 4 - "C++ String Utilities"
Cohesion: 0.33
Nodes (6): compare_strings(), c_str, clear, shrink_to_fit, swap, operator==()

### Community 5 - "API Usage Tests"
Cohesion: 0.33
Nodes (3): main(), my_str_create_from_cstr(), my_str_destroy()

### Community 6 - "Class Interface"
Cohesion: 0.33
Nodes (6): size_t, my_str_t, capacity_m, data_m, not_found, size_m

### Community 7 - "String Manipulation"
Cohesion: 0.40
Nodes (5): checked_add(), append, cstring_length, find, insert

### Community 8 - "Constructors and Headers"
Cohesion: 0.50
Nodes (3): my_str_t::my_str_t(), reserve, string

## Knowledge Gaps
- **5 isolated node(s):** `not_found`, `data_m`, `capacity_m`, `size_m`, `value`
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 8 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `my_str_t` connect `Class Interface` to `C API Core`, `C API Operations`, `Capacity Management`, `C++ String Utilities`, `API Usage Tests`, `String Manipulation`, `Constructors and Headers`?**
  _High betweenness centrality (0.420) - this node is a cross-community bridge._
- **Why does `my_str_handle` connect `C API Core` to `C API Operations`, `API Usage Tests`, `Class Interface`?**
  _High betweenness centrality (0.186) - this node is a cross-community bridge._
- **Why does `main()` connect `C API Operations` to `C API Core`, `API Usage Tests`, `Class Interface`?**
  _High betweenness centrality (0.158) - this node is a cross-community bridge._
- **Are the 25 inferred relationships involving `main()` (e.g. with `my_str_append()` and `my_str_append_char()`) actually correct?**
  _`main()` has 25 INFERRED edges - model-reasoned connections that need verification._
- **What connects `not_found`, `data_m`, `capacity_m` to the rest of the system?**
  _5 weakly-connected nodes found - possible documentation gaps or missing edges._