#include <stdio.h>

struct MIDINote{
  int pitch;
  int velocity;
  int channel;
};


void print_note(struct MIDINote note){
  printf("%d, %d, %d\n", note.pitch, note.velocity, note.channel);
}

int main(){
  struct MIDINote note;

  printf("Enter the pitch: ");
  scanf("%d", &note.pitch);
  printf("Enter the velocity: ");
  scanf("%d", &note.velocity);
  printf("Enter the channel: ");
  scanf("%d", &note.channel);

  int *pitch;
  int *velocity;
  int *channel;
  
  print_note(note);

  return 0;
}


