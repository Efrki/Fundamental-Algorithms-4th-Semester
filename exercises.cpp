#include <iostream>
#include <string>
#include <cmath>
// #include <vector>

// class Student {
//     private:
//     std::string name;
//     std::vector<int> grades;
//     public:
//     int calculateAverage(){
//         int av = 0;
//         for (range-declaration : range-expression) {
        
//         }
//         std::cout<<std::endl;
//     }
// }

int main(){
    double sum = 0;
    int n = 0;
    std::cin >> n;
    int sign = -1;
    
    for (int i = 1; i <= n; ++i){
        sum += static_cast<double>((pow(-1,i+1) / i));
    }
    std::cout << sum;
    return 0;
}