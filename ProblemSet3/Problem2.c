#include <stdio.h>

typedef enum Mode {
    Ionian, Dorian, Phrygian
} Mode;

typedef struct Note {
  unsigned char pitch;
  unsigned char velocity;
  unsigned char channel;
} Note;

typedef struct Scale {
  Note notes[7];
  unsigned char rootNote;
} Scale;

int main() {
 
  Scale ionian ={{
    {0, 127, 1},
    {2, 127, 1},
    {4, 127, 1},
    {5, 127, 1},
    {7, 127, 1},
    {9, 127, 1},
    {11, 127, 1}},
    60};
  Scale dorian = {{
    {0, 127, 1},
    {2, 127, 1},
    {3, 127, 1},
    {5, 127, 1},
    {7, 127, 1},
    {9, 127, 1},
    {10, 127, 1}},
    60};
  Scale phrygian = {{
    {0, 127, 1},
    {1, 127, 1},
    {3, 127, 1},
    {5, 127, 1},
    {7, 127, 1},
    {8, 127, 1},
    {10, 127, 1}},
    60};

  //ask the user to enter which mode they want to print out with integers between 0 ~ 2.
  int scalemode;
    printf("Select the scale mode(0 for Ionian, 1 for Dorian, 2 for Phrygian):");
    scanf("%i", &scalemode);
  
  //choose the mode to use using the Scale structure defined above using the switch statement.
  Scale selectedScale;
  switch(scalemode){
    case Ionian:
      selectedScale = ionian;
      break;
    case Dorian:
      selectedScale = dorian;
      break;
    case Phrygian:
      selectedScale = phrygian;
      break;
    default:
      printf("Invalid mode selected\n");
      return 1;
  }
  //ask the user what root note they want (0 ~ 127) and assign it to the rootNote member of the scale structure.
  printf("Enter the rootNote(0 ~ 127):");
  scanf("%hhu", &selectedScale.rootNote);

  //print out the seven pitches in the selected mode by adding the selected root note. You must use for-loop for this step.
  printf("Notes: ");
  for (int i = 0; i < 7; i++) {
    printf("%d ", selectedScale.notes[i].pitch + selectedScale.rootNote);
  }
  printf("\n");

  return 0;
}