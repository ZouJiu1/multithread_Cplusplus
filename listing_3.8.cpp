//Download by www.cctry.com
#include <mutex>
#include <stdexcept>
#include <climits>
class hierarchical_mutex {
    std::mutex internal_mutex; //内部的信号量类，internal mutex
    unsigned long const hierarchy_value; // this mutex instance hierarchy，这个信号量实例所处的层级
    unsigned long previous_hierarchy_value; //thread hierarchy previous，该线程之前的层级
// one thread, one value no matter how many instances，stand for hierarchy of a thread currently
// 一个线程只有一个值，不管有多少实例，代表当前线程所处的层级
    static thread_local unsigned long this_thread_hierarchy_value; //该线程当前的层级
    void check_for_hierarchy_violation() {
// check thread hierarchy current，and mutex hierarchy.
// 检查当前线程所处的层级，以及 信号量的层级，是否满足要求的
        if(this_thread_hierarchy_value <= hierarchy_value) {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value() {
// thread hierarchy current，marked as previous
// 临时存放当前线程所处的层级，标记成之前的层级
        previous_hierarchy_value=this_thread_hierarchy_value;
// thread hierarchy current = mutex hierarchy
//现在线程的层级就是当前信号量的层级
        this_thread_hierarchy_value=hierarchy_value;
    }
public:
    explicit hierarchical_mutex(unsigned long value): hierarchy_value(value), previous_hierarchy_value(0) {}
    void lock() {
//check hierarchy of mutex and hierarchy of thread
        check_for_hierarchy_violation();//检查信号量的层级，和线程的层级
        internal_mutex.lock();
        update_hierarchy_value();//修改线程的层级，并保存之前的层级
    }
    void unlock() {
// restore thread hierarchy to previous
// 恢复线程的层级到之前
        this_thread_hierarchy_value=previous_hierarchy_value;
        internal_mutex.unlock();
    }
    bool try_lock() {
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())  return false;
        update_hierarchy_value();
        return true;
    }
};
// thread hierarchy current = maximum，该线程的层级初始化最大
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);
int main() {
    hierarchical_mutex m1(42);
    hierarchical_mutex m2(2000);
}