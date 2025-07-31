#include <iostream>
#include <thread>
#include "rateLimiter.cpp"

int main() {
    RateLimiter limiter(1000); // 1000 requests per second

    int accepted = 0, rejected = 0;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 2000; ++i) {
        if (limiter.allow_request()) {
            ++accepted;
        } else {
            ++rejected;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Accepted: " << accepted << ", Rejected: " << rejected << "\n";
    std::cout << "Time taken: " << duration.count() << " seconds\n";

    return 0;
}
