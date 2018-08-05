Test code for splitting std::tuple:

```cpp
int i = -1;
double j = .5;
std::string str1{ "abc" }, str2{ "xyz" };
std::tuple<int, std::string, std::string, double> tpl{ i, str1, str2, j };
std::tuple<int, std::string, std::string> tpl1;
std::tuple<std::string, double> tpl2;
head(tpl1) = tpl;
tail(tpl2) = tpl;
assert(i == std::get<0>(tpl1) );
assert(str1 == std::get<1>(tpl1) );
assert(str2 == std::get<2>(tpl1) );
assert(str2 == std::get<0>(tpl2) );
assert(j == std::get<1>(tpl2) );
```
