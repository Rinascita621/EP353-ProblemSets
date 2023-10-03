#include <stdio.h>

int main(){
    int midipitch;

    printf("Enter a MIDI pitch: ");
    scanf("%d", &midipitch);

   
    if(midipitch < 0 || midipitch > 127){
    printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
    else {
        int octave = (midipitch / 12) - 1;
        int notenumber = midipitch % 12;
        char noteName;
 
    switch(notenumber){
        case 0: noteName = "C"; break;
        case 1: noteName = "C#"; break;
        case 2: noteName = "D"; break;
        case 3: noteName = "D#"; break;
        case 4: noteName = "E"; break;
        case 5: noteName = "F"; break;
        case 6: noteName = "F#"; break;
        case 7: noteName = "G"; break;
        case 8: noteName = "G#"; break;
        case 9: noteName = "A"; break;
        case 10: noteName = "A#"; break;
        case 11: noteName = "B"; break;
        default: noteName = "Invalid";
    }
    
    printf("The MIDI pitch %d is %c%d\n", midipitch, noteName, octave);
    return 0;
    }