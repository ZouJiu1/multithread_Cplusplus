//Download by www.cctry.com
#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

// template parameter，模板结构体
template<typename Iterator, typename T>
struct accumulate_block {
    //reload () operator, the third augment is reference, 重载运算符()，最后一个参数是引用
    void operator()(Iterator first, Iterator last, T& result) {
        result=std::accumulate(first, last, result); //累加
    }
};

// 模板函数的，template function
template<typename Iterator, typename T>
T parallel_accumulate(Iterator first,Iterator last,T init) {
    //equal to vector<int>::size()，number of elements，算出元素的个数
    unsigned long const length=std::distance(first,last);

    if(!length) return init; // number=0

    // calculate the number of thread of applying，计算能用的线程数量，和指定线程数量
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1) / min_per_thread;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads=
        std::min(hardware_threads !=0 ? hardware_threads:2,max_threads);

//each thread process how many element, 每个线程要处理的数据量个数
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread>  threads(num_threads - 1);

    Iterator block_start = first;
    for(unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        //move pointer with fixed number = block_size，移动指针步长固定
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator,T>(), block_start, block_end, std::ref(results[i])); //启动线程的，launch thread
        block_start = block_end;
    }
    // the remain elements，let the last thread to deal with，最后一个线程处理剩下的数据
    accumulate_block<Iterator,T>()(block_start,last,results[num_threads-1]);
    
    std::for_each(threads.begin(),threads.end(),
        std::mem_fn(&std::thread::join)); // join each thread

    return std::accumulate(results.begin(),results.end(),init); // 累加最后的结果
}

int main()
{
    std::vector<int> vi;
    for(int i=0;i<10000;++i)
    {
        vi.push_back(10);
    }
    int sum=parallel_accumulate(vi.begin(),vi.end(),6);
    std::cout<<"sum="<<sum<<std::endl;
}
