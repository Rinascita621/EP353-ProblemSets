#include <stdio.h>
#include <math.h>

//function prototype
float midi_to_frequency(int a);
void print_chord_frequencies(int chord[], int size);


//define function

float midi_to_frequency(int a){
    return 440.0 * pow(2.0, (a - 69) / 12.0);
}

void print_chord_frequencies(int chord[], int size){
    for(int i = 0; i < size; i++){
        float frequency = midi_to_frequency(chord[i]);
        printf("The frequency of MIDI note %d is %.2f Hz.\n", chord[i], frequency);
    }

}

int main(){
    int size;
    
    printf("Enter the number of MIDI note: ");
    scanf("%d", &size);

    int chord[size];
    printf("Enter the MIDI note seperated by spaces: ");
    for(int i = 0; i < size; i++){
        scanf("%d", &chord[i]);
    }


//call the function 
print_chord_frequencies(chord, size);

return 0;
}
