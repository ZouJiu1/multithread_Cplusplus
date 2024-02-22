//Download by www.cctry.com
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
struct empty_stack: std::exception { //public derive 
//https://stackoverflow.com/questions/22493294/what-is-the-meaning-of-this-header-virtual-const-char-what-const-throw?r=SearchResults
// const throw() = noexcept
// what return const char *
    const char* what() const throw() {
        return "empty stack";
    }
};
template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data; // original stack，non-thread safe，最开始的栈，非线程安全
    mutable std::mutex m;
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other) { //constructor
        std::lock_guard<std::mutex> lock(other.m); // auto lock and unlock
        data=other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete; // delete assignment operator function
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack(); // 实例化，抛出异常的，throw what
// std::make_shared在动态内存中分配一个对象然后初始化它，最后返回指向此对象的shared_ptr
        std::shared_ptr<T> const res(std::make_shared<T>(data.top())); //实例化
        data.pop();
        return res; // 返回智能指针的
    }
    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        value=data.top(); // 将值赋给引用变量
        data.pop();
    }
    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
int main() {
    threadsafe_stack<int> si;
    si.push(5);
    si.push(6);
    si.pop();
    if(!si.empty()) {
        int x; //实例化保存结果的引用变量
        si.pop(x); // 参数是引用，所以传递引用，而不是引用的副本
    }
}