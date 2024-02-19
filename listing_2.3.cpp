//Download by www.cctry.com
#include <thread>

class thread_guard
{
    std::thread& t;
public:
/*
//constructor function，explicit copy constructor，list initialization，can calling explicit，not inexplicit
构造函数的，显式复制构造函数，列表初始化，不能隐式调用，只能显式调用
*/
    explicit thread_guard(std::thread& t_):
        t(t_)
    {} // do nothing，just copy the std::thread object

    // provide a class that does the join() in its destructor
    // 析构函数会自动调用join()函数，若是发生了exception，也会自动调用析构函数，所以不需要多次调用join
    // waiting for the thread execution finished，等待线程执行完毕的
    ~thread_guard()  //destructor
    {// check whether thread has been joined or exit，necessarily because join() can be called only once for a given thread of execution
    // 检查线程是否已经被join或者已经退出，执行的线程只能调用一次join函数

        if(t.joinable())
        {
            t.join();
        }
    }
    // delete copy constructor，delete operator = function
    // 删除复制构造函数，删除重载运算符 “=”
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
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
    func my_func(some_local_state);
// claim a object of std::thread，transfer a pointer of function as a parameter
// 初始化一个对象，传递参数-函数指针的
    std::thread t(my_func); 
// construct a class，auto-calling destructor
// 构造一个类的，并自动调用析构函数
    thread_guard g(t);
        
    do_something_in_current_thread();
}

int main()
{
    f();
}