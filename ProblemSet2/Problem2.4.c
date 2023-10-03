#include <stdio.h>

int main() {
    int midipitch;

    printf("Enter a MIDI pitch: ");
    scanf("%d", &midipitch);

   
    if(midipitch < 0 || midipitch > 127){
    printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
    else {
        int octave = (midipitch / 12) - 1;
        int notenumber = midipitch % 12;
        char* notename;
 
    switch(notenumber) {
        case 0: notename = "C"; break;
        case 1: notename = "C#"; break;
        case 2: notename = "D"; break;
        case 3: notename = "D#"; break;
        case 4: notename = "E"; break;
        case 5: notename = "F"; break;
        case 6: notename = "F#"; break;
        case 7: notename = "G"; break;
        case 8: notename = "G#"; break;
        case 9: notename = "A"; break;
        case 10: notename = "A#"; break;
        case 11: notename = "B"; break;
        default: notename = "Invalid";
    }
    
    printf("The MIDI pitch %d is %s%d\n", midipitch, notename, octave);
    }

    return 0;
}