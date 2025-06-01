#include <iostream>
#include <algorithm>

int main(){
    auto add = [](int a, int b) -> int { return a + b;};
    int sum = add(20, 10);
    auto print_sum = [sum]() -> void {
        std::cout << sum << std::endl;
    };
    print_sum();
    return 0;
}