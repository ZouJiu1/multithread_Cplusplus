//Download by www.cctry.com
#include <mutex>
class some_data {//数据类
    int a;
    std::string b;
public:
    void do_something() {}
};
class data_wrapper {
private:
    some_data data;//被保护数据的
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func) {
//use mutex guard to lock and unlock automatically，protect data (private)
//构造加锁析构解锁的智能信号量
        std::lock_guard<std::mutex> l(m);
// pointer to data (private)，调用malicious_function函数，通过引用将被保护数据的地址交给全局变量
        func(data);
    }
};
some_data* unprotected; // class pointer
void malicious_function(some_data& protected_data) {  // reference to protected data，传递引用的
    unprotected=&protected_data; // pointer to protected data，将被保护数据的地址交给全局指针变量
}
data_wrapper x;
void foo() {
    x.process_data(malicious_function); //模板函数在调用时会自动匹配类型，不需要使用“<>”来指定类型
// wrong!!!!!!，use pointer of protected data without mutex
// 全局指针变量，可以直接访问被保护的数据，没有使用信号量，会出错，直接修改了保护变量，没有考虑到其他线程
    unprotected->do_something();
}
int main() {
    foo();
}