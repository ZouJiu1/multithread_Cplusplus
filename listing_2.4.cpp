//Download by www.cctry.com
#include <thread>
#include <string>

void open_document_and_display_gui(std::string const& filename) {}

bool done_editing() {
    return true;
}

/*
enum, one element
枚举类型的，可指定数值，没有指定的在前面指定的+1，默认从0开始，enum num{h, m, a=10, b, c=20, d, e}
那么h=0, m=1, a=10, b=11, c=20, d=21, e=22
下面是C++11以前的声明方式，C++11是enum class num{}，C++11需要用 解析运算符::来指定，num::h, num::a
*/
enum command_type {
    open_new_document
};


struct user_command {
    command_type type; // enum

    user_command(): 
    // constructor，list initialization
    // 构造函数，列表赋值的
        type(open_new_document)
    {}
};

user_command get_user_input() {
    return user_command();
}

std::string get_filename_from_user() {
    return "foo.doc";
}

void process_user_input(user_command const& cmd) {}

void edit_document(std::string const& filename) {
    open_document_and_display_gui(filename);      // do nothing
    while(!done_editing())  //do nothing
    {
        user_command cmd=get_user_input();
        // open_new_document，launch a thread with detach
        // 开启另一个文档，启动另一个线程，并detach
        if(cmd.type==open_new_document)  
        {
            std::string const new_name=get_filename_from_user();
            std::thread t(edit_document,new_name);// launch a thread and pass a argument
            t.detach();
        }
        else
        {
            process_user_input(cmd);
        }
    }
}

int main() {
    edit_document("bar.doc");
}
