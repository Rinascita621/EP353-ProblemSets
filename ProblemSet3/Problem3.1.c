#include <stdio.h>
#include <math.h>

//function prototype
float midi_to_frequency(int a);

//define function
float midi_to_frequency(int a){
    return 440.0 * pow(2.0, (a - 69) / 12.0);
}

int main(){
    int midi;
    printf("enter the midi note: ");
    scanf("%d", &midi);

    // call the function
    float frequency = midi_to_frequency(midi);
    
    printf("The frequency of MIDI note %d is %.2f Hz.\n", midi, frequency);

    return 0;
}
