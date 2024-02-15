#include<iostream>
#include<ostream>
#include<string>
using namespace std;

template<typename value_type>
class AA
{
private:
    double dl;
public:
    explicit AA(double kk);
    AA(int k) = delete;
    virtual ~AA() {};
    void pf(ostream & os, value_type & tr) noexcept
    {
        os<<tr<<" "<<dl<<endl;
    }
};

template<typename value_type>
AA<value_type>::AA(double kk) : dl(kk)
{
}
int main(void) {
    AA cla = AA<string>(1.23);
    string hello = "hello world!";
    cla.pf(cout, hello);
    return EXIT_SUCCESS;
}