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


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    /*
    transfer control to initial thread（main），don't wait for my_thread
    将控制权交给初始线程main，不等待my_thread，继续执行后面的codes
    */
    my_thread.detach();
}

int main()
{
    oops();
}
