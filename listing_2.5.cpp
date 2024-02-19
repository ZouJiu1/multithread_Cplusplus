//Download by www.cctry.com
#include <thread>

void some_function()
{}

void some_other_function(int)
{}

std::thread f() // return temp thread object，transfer ownership，返回thread临时对象的，涉及到所有权的转移
{
    void some_function();
    return std::thread(some_function);
}
std::thread g() // return thread object，transfer ownership，返回thread临时对象的，涉及到所有权的转移
{
    void some_other_function(int);
    std::thread t(some_other_function,42);
    return t;
}

int main()
{
    std::thread t1=f();
    t1.join();
    std::thread t2=g();
    t2.join();
}
