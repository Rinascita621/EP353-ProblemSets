#include <stdio.h>

struct MIDINote{
  int pitch;
  int velocity;
  int channel;
};

//define function
void print_notes(struct MIDINote notes[], int size) {
    for (int i = 0; i < size; i++) {
        printf("The MIDI note has pitch %d, velocity %d, and channel %d.\n", notes[i].pitch, notes[i].velocity, notes[i].channel);
    }
}

int main(){
  int size;

  printf("Enter the number of MIDI note: ");
  scanf("%d", &size);

  struct MIDINote notes[size];

  for (int i = 0; i < size; i++) {
        printf("Enter MIDI note %d (pitch velocity channel): ", i + 1);
        scanf("%d %d %d", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);
    }

    print_notes(notes, size);

  return 0;
}