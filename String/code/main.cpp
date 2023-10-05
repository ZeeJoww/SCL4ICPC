#include <iostream>
#include <random>
#include <chrono>


int main() {
    auto rd = std::random_device()();
    std::mt19937 mt(rd);
    int y = time(NULL);
    // std::cout << "x = " << x << ", y = " << y << '\n';
}

