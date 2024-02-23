//Download by www.cctry.com
#include <mutex>
struct connection_info {};
struct data_packet {};
struct connection_handle {
    void send_data(data_packet const&) {}
    data_packet receive_data() {
        return data_packet();
    }
};

struct remote_connection_manager {
    connection_handle open(connection_info const&) {
        return connection_handle();
    }
} connection_manager;
class X {
private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;
    void open_connection() {
        connection=connection_manager.open(connection_details);
    }
public:
    X(connection_info const& connection_details_):
        connection_details(connection_details_) {}
    void send_data(data_packet const& data) {
    // pass object pointer->this，member function pointer，only one thread call once，no need to connect secondly
// 需要成员函数指针，作用域解析运算符，以及对象自身的指针(connection_details)
// 连接只被某个线程调用一次，连接以后不需要第二次连接
        std::call_once(connection_init_flag,&X::open_connection,this);
        connection.send_data(data);
    }
    data_packet receive_data() {
//only one thread call once，no need to connect secondly，连接只被某个线程调用一次，连接以后不需要第二次连接
        std::call_once(connection_init_flag,&X::open_connection,this);
        return connection.receive_data();
    }
};
int main() {}