//Download by www.cctry.com
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
bool more_data_to_prepare() {
    return false;
}
struct data_chunk {};
data_chunk prepare_data() {
    return data_chunk();
}
void process(data_chunk&) {}
bool is_last_chunk(data_chunk&) {
    return true;
}
std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;
void data_preparation_thread() {
    while(more_data_to_prepare()) {
        data_chunk const data=prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
// data prepared, notify other threads which waiting for data
// 数据准备好了，条件变量通知其它正在等待数据的线程，------>>>>>>可以继续运行了
        data_cond.notify_one();
    }
}
void data_processing_thread() {
    while(true) {
        std::unique_lock<std::mutex> lk(mut);
// other threads are waiting for data using condition_variable，sleeping while waiting until waked up
// 其它线程正在等待另一个线程完成任务，等待期间睡眠，直到被唤醒
/*
data_cond.wait(lk,[]{return!data_queue.empty();}); 中的第二项是lambda表达式（匿名函数），也就是等待的条件。
wait函数会解锁信号量并将线程置等待或者阻塞状态，所以需要使用unique_lock，当条件变量被notify_one通知，
线程就被唤醒了，再次对信号量加锁。若线程睡眠时没有解锁信号量，那么数据准备线程就不能加锁信号量并准备数据，
等待线程永远不能运行因条件得不到满足。
*/
        data_cond.wait(lk,[]{return !data_queue.empty();});
        data_chunk data=data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        if(is_last_chunk(data))
            break;
    }
} 
int main() { // 初始线程启动main函数, initialized thread
    std::thread t1(data_preparation_thread); //启动第二个线程，launch second thread
    std::thread t2(data_processing_thread);  //启动第三个线程，launch third  thread
    t1.join();
    t2.join();
}