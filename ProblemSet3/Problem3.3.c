#include <stdio.h>
#include <math.h>

//function prototype
float midi_to_frequency(int a);
void frequencies_of_chord(int* chord, int size, float* frequencies);

//define the function

float midi_to_frequency(int a){
    return 440.0 * pow(2.0, (a - 69) / 12.0);
}

void frequencies_of_chord(int* chord, int size, float* frequencies){
    for(int i = 0; i < size; i++){
        frequencies[i] = midi_to_frequency(chord[i]);
    }
}

int main(){
    int size;

    printf("Enter the number of MIDI note: ");
    scanf("%d", &size);

    int chord[size];
    float frequencies[size];

    printf("Enter the MIDI note seperated by spaces: ");
    for(int i = 0; i < size; i++){
        scanf("%d", &chord[i]);
    }

    frequencies_of_chord(chord, size, frequencies);

    for(int i = 0; i < size; i++){
    printf("The frequencies of MIDI note %d is %.2f Hz.\n", chord[i], frequencies[i]);
    }
    
    return 0;
}

