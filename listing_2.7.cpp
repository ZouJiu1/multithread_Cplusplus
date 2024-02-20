//Download by www.cctry.com
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
void do_work(unsigned id) {}
void f() {
    //containers of thread object，容纳线程的容器，支持move转移所有权
    std::vector<std::thread> threads;
    for(unsigned i=0;i<20;++i) {
        // push thread to container, transfer ownership to element of the container, 转移所有权到容器的element中
        threads.push_back(std::thread(do_work,i)); 
    }
    //apply join to every thread，对每个正在运行的线程调用join函数
    std::for_each(threads.begin(),threads.end(), std::mem_fn(&std::thread::join));
}
int main() {
    f();
}