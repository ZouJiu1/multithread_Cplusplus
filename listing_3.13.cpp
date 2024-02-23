//Download by www.cctry.com
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
// #include <boost/thread/shared_mutex.hpp>
class dns_entry {};
class dns_cache {
    std::map<std::string,dns_entry> entries;
    std::shared_mutex entry_mutex; // member mutex variable
public:
    dns_entry find_entry(std::string const& domain) {
/*
find_entry() uses an instance of boost::shared_lock<> to protect it
for shared, read-only access; multiple threads can therefore call find_entry()
simultaneously without problems
不需要更新修改的话，可以直接使用 boost::shared_lock 实例，多个线程并发同时访问，boost::shared_lock<>共享访问的
boost::shared_lock只需要有一个线程加锁就行，其它线程仍然可以访问
*/
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        //boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
        std::map<std::string,dns_entry>::const_iterator const it = entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }
    void update_or_add_entry(std::string const& domain, dns_entry const& dns_details) {
/*
On the other hand, update_or_add_entry() uses
an instance of std::lock_guard<> to provide exclusive access while the table is
updated; not only are other threads prevented from doing updates in a call update_
or_add_entry(), but threads that call find_entry() are blocked too
 std::lock_guard<>排斥性访问，会阻止其它线程做更新或者读取操作
*/
        std::lock_guard<std::shared_mutex> lk(entry_mutex);
        entries[domain]=dns_details;
    }
};
int main() {}