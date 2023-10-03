#include <stdio.h>
#include <math.h>

int main(){
    int a, b;
    a = 60;
    b = 69;

    double f1, f2;
    f1 = 440 * pow(2, (a-69)/12.0);
    f2 = 440 * pow(2, (b-69)/12.0);
    printf("The frequency for MIDI note %d is %f Hz\n", a, f1);
    printf("The frequency for MIDI note %d is %f Hz\n", b, f2);

    return 0;
}