# cpp_zip_iterator

A python-style zip function for C++.

## usage

Example:

```
#include "zip.hpp"

int main() {
  std::vector<int> a = {1,2,3};
  std::array<float, 5> b = {4.4, 5.5, 6.6, 7.7, 8.8};
  std::list<char> c = {'a', 'b', 'c', 'd'};
  std::forward_list<std::string> d = {"lorem", "ipsum", "hello_world"};

  for (auto i : zip::zip(a, b, c, d)) {
    // `i` is a tuple with the values from a, b, c and d
    std::cout << i << std::endl;
  }
}
```

Possible output (assuming there's an overload to print tuples to cout):

```
1, 4.4, a, lorem
2, 5.5, b, ipsum
3, 6.6, c, hello_world
```

