#include <chrono>
#include <mutex>

class RateLimiter {
private:
    const int max_tokens = 1000;  // maximum burst size (per second)
    double tokens;
    double fill_rate; // tokens added per second
    std::chrono::steady_clock::time_point last_check;
    std::mutex mtx;

public:
    RateLimiter(int rate_per_sec = 1000)
        : tokens(rate_per_sec), fill_rate(rate_per_sec),
          last_check(std::chrono::steady_clock::now()) {}

    bool allow_request() {
        std::lock_guard<std::mutex> lock(mtx);

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - last_check;
        last_check = now;

        // Add new tokens based on time passed
        tokens += elapsed.count() * fill_rate;
        if (tokens > max_tokens) {
            tokens = max_tokens;
        }

        if (tokens >= 1.0) {
            tokens -= 1.0;
            return true;
        }

        return false; // rate limit exceeded
    }
};
