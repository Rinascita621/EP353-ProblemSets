#include <iostream>

template <typename T>
class SineWave{
    public:
    SineWave(T freq, T amp, T phase): 
        frequency(freq), amplitude(amp), phase(phase){}

    void printparameters(){
        std::cout << frequency << ", " << amplitude << ", " << phase << std:: endl;
    }
private:
    T frequency;
    T amplitude;
    T phase;
};

int main(){
    SineWave<int> sineWave(440, 2, 3);
    sineWave.printparameters();
    return 0;
}
