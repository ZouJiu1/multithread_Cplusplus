#include <future>
#include <cmath>
#include <iostream>
double square_root(double x) {
    if(x<0)
    {
        throw std::out_of_range("x<0");
    }
    return sqrt(x);
 }
int main(void) {
    std::future<double> f = std::async(square_root, -1);
    double ret = f.get();
    // square_root(-1);
    return EXIT_SUCCESS;
}