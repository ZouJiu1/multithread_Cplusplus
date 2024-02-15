#include <iostream>
#include <thread>
void hello() //线程运行的函数 initial function
{
    std::cout<<"Hello Concurrent World\n";
}

int main()  //应用的起始线程，the initial thread in an application，bringing the thread count to one
{
    /* 
    After the new thread has been launched d, the initial thread continues execution, 
    If it didn’t wait for the new thread to finish, it would merrily continue to the end of main() and thus end the program 
    在new线程启动以后，初始线程main不会等待而是继续执行，可能在new线程运行以前就结束了main的执行 
    */
    std::thread t(hello); //给这个函数产生一个线程，std::thread object named t has the new function hello() as its initial function，bringing the thread count to two
    std::thread tt(hello); //给这个函数产生第二个线程，bringing the thread count to three
    /*
    join() is there e—as described in chapter 2, this causes
 the calling thread (in main()) to wait for the thread associated with the std::thread
 object, in this case, t
 线程启动以后，控制权转交给main函数，接着执行其他codes，所以需要让main调用函数来等待线程执行完成，
 否则可能main函数执行完了，但是线程还没有执行完，main执行完以后会退出程序，会关闭所有线程。所以join等待操作是必须的。
    */
    t.join(); // join()函数会导致调用函数（这的话就是main）等待线程t执行完成
    tt.join();
    std::cin.get(); //防止CMD终端自动关闭，prohibit the cmd to close auto
    return 0;
}

// //Download by www.cctry.com
// #include <iostream>
// #include <thread>

// void hello()
// {
//     std::cout<<"Hello Concurrent World\n";
// }

// int main()
// {
//     std::thread t(hello);
//     t.join();
// }
