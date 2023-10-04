#include <stdio.h>

int main(){
    char* intervalname[]= {"unison", "minor second", "major second", "minor third", "major third", "perfect fourth","tritone", "perfect fifth", "minor sixth", "major sixth", "minor seventh", "major seventh"};

    printf("Enter a interval:\n");

    int semitones = 12;
    for (int note1 = 0; note1 < semitones; note1++){
        printf("From %c", 'A' + note1);
        for (int note2 = 0; note2 < semitones; note2++){
            int interval = (note2 - note1 + 12) % 12;

            switch(interval){
                case 0:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[0]);
                break;
                case 1:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[1]);
                break;
                case 2:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[2]);
                break;
                case 3:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[3]);
                break;
                case 4:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[4]);
                break;
                case 5:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[5]);
                break;
                case 6:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[6]);
                break;
                case 7:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[7]);
                break;
                case 8:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[8]);
                break;
                case 9:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[9]);
                break;
                case 10:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[10]);
                break;
                case 11:
                printf("The interval from %d to %d is a %s.\n", note1, note2, intervalname[11]);
                break;
        }
    }
    }
   return 0; 
}