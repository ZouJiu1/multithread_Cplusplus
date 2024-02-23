//Download by www.cctry.com
#include <mutex>
class some_big_object {};
void swap(some_big_object& lhs,some_big_object& rhs) {}
class X {
private:
    some_big_object some_detail;
    mutable std::mutex m;
public:
    X(some_big_object const& sd):some_detail(sd) {}
    friend void swap(X& lhs, X& rhs) {
        if(&lhs==&rhs) return;
// 同时加锁的，要么都加锁，要么都不加锁，lock all or none
        std::lock(lhs.m,rhs.m);
// transfer ownership to lock_guard，don't lock again，constructor，deconstructor unlock automatically
// 将信号量所有权转交给lock_guard，不会再次加锁，构造函数的，析构自动解锁
        std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);
        swap(lhs.some_detail,rhs.some_detail);
    }
};
int main() {}