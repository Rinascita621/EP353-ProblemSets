#include <iostream>

template <typename T>
void multiples(T &sum, T x, int n){
    for(int i = 1; i <= n; n++){
        sum += x * i;
    }
}

int main(){
    int sum = 0;
    multiples(sum, 1, 10);
    std::cout << sum << std::endl;
    return 0;
}