//Download by www.cctry.com
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
std::mutex m;
std::deque<std::packaged_task<void()> > tasks;
bool gui_shutdown_message_received();
void get_and_process_gui_message();
void gui_thread() {
    while(!gui_shutdown_message_received()) {
        get_and_process_gui_message();
        std::packaged_task<void()> task; 
        {
            std::lock_guard<std::mutex> lk(m);
            if(tasks.empty())
                continue;
            task=std::move(tasks.front());//左值变右值
            tasks.pop_front();
        }
//The future associated with the task will then be made ready when the task completes.
        task();
    }
}
std::thread gui_bg_thread(gui_thread);
/*
The code that posted the message to the GUI thread can then
 wait for the future if it needs to know that the task has been completed, or it can discard
 the future if it doesn’t need to know
*/
template<typename Func>
std::future<void> post_task_for_gui_thread(Func f) {
    std::packaged_task<void()> task(f);
    std::future<void> res=task.get_future(); //get future
    std::lock_guard<std::mutex> lk(m);
    tasks.push_back(std::move(task)); //std::move左值变右值引用，push右值引用的
    return res;
}