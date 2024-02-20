//Download by www.cctry.com
#include <thread>
#include <utility>
#include <stdexcept>

class scoped_thread
{
    std::thread t;
public:
    // constructor，显式构造函数
    explicit scoped_thread(std::thread t_): // when calling constructor，transfer ownership to the augment，调用时转移所有权给函数的参数
        t(std::move(t_))      // transfer ownership from augment to a private variable，转移所有权，从参数到私有成员变量
    {
        if(!t.joinable())  //看线程是否已经被join
            throw std::logic_error("No thread");
    }
    // deconstructor，析构函数的
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(scoped_thread const&)=delete; //删除
    scoped_thread& operator=(scoped_thread const&)=delete;// 删除赋值操作符重载函数=
};

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
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
    int some_local_state;
    scoped_thread t(std::thread(func(some_local_state)));
        
    do_something_in_current_thread();
}

int main()
{
    f();
}
