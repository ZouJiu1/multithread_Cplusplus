//Download by www.cctry.com
#include <mutex>
class Y {
private:
    int some_detail;
    mutable std::mutex m;
    int get_detail() const {
        std::lock_guard<std::mutex> lock_a(m);
        return some_detail;
    }
public:
    Y(int sd) : some_detail(sd) {}
    friend bool operator==(Y const& lhs, Y const& rhs) {
        if(&lhs==&rhs)
            return true;
        int const lhs_value=lhs.get_detail();
// another thread can modify lhs.some_detail，so this is wrong，should lock both simultaneously
// 其他的线程可能会修改lhs.some_detail, rhs.some_detail，所以是错误的，应该同时加锁
        int const rhs_value=rhs.get_detail();
        return lhs_value==rhs_value;
    }
};
int main() {}