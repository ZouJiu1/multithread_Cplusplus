//Download by www.cctry.com

#include <string>
#include <future>
struct X {
    void foo(int,std::string const&);
    std::string bar(std::string const&);
};
X x;
//  调用了p->foo(42,"hello")，p是x的指针
auto f1=std::async(&X::foo,&x,42,"hello"); //Calls p->foo(42,"hello") where p is &x
//  调用了tmpx.bar("goodbye")，tmpx是x的副本
auto f2=std::async(&X::bar,x,"goodbye"); //Calls tmpx.bar("goodbye") where tmpx is a copy of x
struct Y {
    double operator()(double);
};
Y y;
//调用了tmpy(3.141)，tmpy是移动构造函数来的Y()
auto f3=std::async(Y(),3.141); // Calls tmpy(3.141) where tmpy is move-constructed from Y()
//调用了y(2.718)，std::ref是引用
auto f4=std::async(std::ref(y),2.718); //  Calls y(2.718)
X baz(X&);
//调用了复制构造函数；
auto f6=std::async(baz,std::ref(x)); // Calls baz(x)
class move_only {
public:
    move_only();
    move_only(move_only&&);
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&);
    move_only& operator=(move_only const&) = delete;
    void operator()();
};
//调用了tmp()，tmp从std::move(move_only())构造而来的
auto f5=std::async(move_only()); // Calls tmp() where tmp is constructed from std::move(move_only())