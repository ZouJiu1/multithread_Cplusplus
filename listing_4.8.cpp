//Download by www.cctry.com
#include <string>
#include <vector>
#include <future>
/*
std::string(std::vector<char>*,int)，该函数返回类型是std::string
输入参数列表是std::vector<char>* 和 int
*/
template<>
class packaged_task<std::string(std::vector<char>*,int)> {
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);
    std::future<std::string> get_future(); // 拿到运行结果，get return result
    void operator()(std::vector<char>*,int); // reload，运算符被重载了
};