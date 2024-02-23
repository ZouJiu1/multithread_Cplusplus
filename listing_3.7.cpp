//Download by www.cctry.com
#include <mutex>
//下面的线程并没有记录使用了哪些信号量，只对信号量做了赋值层级操作
/*
thread_a可以正常运行，因先对high_level_mutex加锁，然后对low_level_mutex加锁，正常。
但是thread_b()不能运行的，因先对other_mutex层级是100加锁，然后对high_level_mutex层级是10000加锁，
根据层级规则，这是不允许的操作，所以thread_b不能运行的。
*/
class hierarchical_mutex {  // using class to mark level
public: // constructor，layer level ------> level，给层级赋值的
    explicit hierarchical_mutex(unsigned level) {} 
    void lock() {}
    void unlock() {}
};
hierarchical_mutex high_level_mutex(10000); //
hierarchical_mutex low_level_mutex(5000);
int do_low_level_stuff() {
    return 42;
}
int low_level_func() {
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}
void high_level_stuff(int some_param) {}
void high_level_func() {
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
}
//running normally，firstly lock high_level_mutex, secondly lock low_level_mutex
void thread_a() { 
    high_level_func();
}
hierarchical_mutex other_mutex(100);
void do_other_stuff() {}
void other_stuff() {
    high_level_func();
    do_other_stuff();
}
//can not run，because firstly lock other_mutex=100 < high_level_mutex=100000
void thread_b() {
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}
int main() {}