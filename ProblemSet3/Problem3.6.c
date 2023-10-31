#include <stdio.h>

struct MIDINote{
  int pitch;
  int velocity;
  int channel;
};

//define function
void transpose_notes(struct MIDINote* notes, int size, int steps){
  for(int i = 0; i < size; i++){
    notes[i].pitch += steps;
  }
}

int main(){
  int size, steps;

  printf("Enter the number of midi note: ");
  scanf("%d", &size);

  //store the midi notes
  struct MIDINote notes[size];

  for(int i = 0; i < size; i++){
    printf("Enter MIDI note %d (pitch velocity channel): ", i + 1);
    scanf("%d %d %d", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);
  }
  

    printf("Enter the number of steps to transpose(0~11): ");
    scanf("%d", &steps);
  
  // call the function
  transpose_notes(notes, size, steps);

  printf("Transpose MIDI notes: \n");
  for(int i = 0; i < size; i++){
    printf("The MIDI note has pitch %d, velocity %d, channel %d\n", notes[i].pitch, notes[i].velocity, notes[i].channel);

  }

  return 0;

}