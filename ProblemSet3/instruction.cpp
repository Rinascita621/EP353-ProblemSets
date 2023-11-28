#include <stdio.h>

//parent class 
class guitar {
    public:void play(){
        std::cout<< "play!" << std::endl;
    }
    protected:
    void strum(){
        std::cout << "strum!" << std::endl;

    }
};

//child class
class classicalguitar : public guitar{
    public:
    classicalguitar(){
        strum();
        soundHoleSize = 12;
    }
    void print_soundHoleSize(){
        std::cout << soundHoleSize << std::endl;
    }

    private:
    int soundHoleSize;

    int main(){
        guitar. print_soundHoleSize;
    }

};