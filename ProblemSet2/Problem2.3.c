#include <stdio.h>

int main(){
    int midipitch;

    printf("Enter a MIDI pitch: ");
    scanf("%d", &midipitch);

    if(midipitch < 0 || midipitch > 127){
    printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
    else {
        int octave = midipitch / 12 - 1;
        printf("The octave for MIDI pitch %d is %d\n", midipitch, octave);
    }
}