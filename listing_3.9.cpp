//Download by www.cctry.com
#include <mutex>
class some_big_object {};
void swap(some_big_object& lhs,some_big_object& rhs) {}
class X {
private:
    some_big_object some_detail;
    mutable std::mutex m;
public:
    X(some_big_object const& sd):some_detail(sd) {} // constructor
    friend void swap(X& lhs, X& rhs) { // 友元函数的
        if(&lhs==&rhs)
            return;
        std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock);  // 不加锁, not lock，之后可以同时加锁避免了deadlock
        std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);  // 不加锁，not lock，之后可以同时加锁避免了deadlock
// 同时加锁的，避免了deadlock，信号量组，lock simultaneously，avoiding deadlock, group of mutex
        std::lock(lock_a, lock_b);
        swap(lhs.some_detail,rhs.some_detail);
    }
};
int main() {}