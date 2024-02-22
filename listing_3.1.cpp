//Download by www.cctry.com
#include <list>
#include <mutex>
#include <iostream>
#include <algorithm>
std::list<int> some_list; //双向链表的
std::mutex some_mutex; //信号量
void add_to_list(int new_value) {
    /*
    guard mutex，auto lock and unlock，constructor lock and deconstructor unlock
    守护信号量，自动加锁和解锁，构造加锁析构解锁
    */
    std::lock_guard<std::mutex> guard(some_mutex); // auto lock
    some_list.push_back(new_value); // list add value
} //exit function, auto unlock
bool list_contains(int value_to_find) {
    std::lock_guard<std::mutex> guard(some_mutex);  // auto lock
    return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();  //exit function, auto unlock
}
int main() {
    add_to_list(42);
    std::cout<<"contains(1)="<<list_contains(1)<<", contains(42)="<<list_contains(42)<<std::endl;
}
