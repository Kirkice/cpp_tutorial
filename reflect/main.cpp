#include <iostream>

struct AnyType {
    template <typename T>
    operator T();
};

template <typename T>
consteval size_t CountMember(auto&&... Args) {
    if constexpr (! requires { T{ Args... }; }) { // (1)
        return sizeof...(Args) - 1;
    } else {
        return CountMember<T>(Args..., AnyType{}); // (2)
    }
}

int main(int argc, char** argv) {
    struct Test { int a; int b; int c; int d; };
    printf("%zu\n", CountMember<Test>());
}