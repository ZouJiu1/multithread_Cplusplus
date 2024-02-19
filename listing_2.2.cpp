//Download by www.cctry.com
#include <thread>

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){} // construct function，构造函数，列表初始化

    void operator()() // reload ()，重载符号括号()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};

void do_something_in_current_thread()
{}

void f()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try
    {
        do_something_in_current_thread();
    }
    catch(...)
    {// exception happened，waiting for t thread exit, join()
    //发生了异常，等待线程结束 join()
        t.join();
        throw;
    }
    //no exception happened, 没有发生异常，正常等待线程结束 join()
    t.join();
}

int main()
{
    f();
}
