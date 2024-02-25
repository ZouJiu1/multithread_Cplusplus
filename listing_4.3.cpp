//Download by www.cctry.com
#include <memory>
template<typename T>
class threadsafe_queue {
public:
    threadsafe_queue();
    threadsafe_queue(const threadsafe_queue&);
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;
    void push(T new_value);
    bool try_pop(T& value); // result saved in reference，结果保存在引用
    std::shared_ptr<T> try_pop(); // return pointer，返回结果的指针
    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    bool empty() const;
};
int main() {}