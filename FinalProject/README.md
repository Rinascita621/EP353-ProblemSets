# EP353-ProblemSets
 
### NewPlugin

## Reverb VST3 Plugin

# About Reverb

Reverberation (or reverb) describes the echos that are created when a sound hits a surface and reflects back to be heard by the listener. The sound of the reverb is dependent on various characteristics of the room or space that the sound is bouncing around, such as it’s size, it’s shape and the materials that the surfaces are made up of. A digital reverb plugin or hardware unit emulates this effect so that you can apply it to your audio, giving the listener the impression that it’s been recorded in a certain live space. The settings or parameters that you’ll find on your reverb can be controlled to shape the reverb to match the sound that you’re after. Some of these settings can be self explanatory in how they’re used, but others are less so.

# About NewPlugin

This reverb plugin has 4 parameters. When adjusting all parameters, there will be a digital box next to it to display the parameter size in real time. The adjustable range of each parameter is inconsistent in size. Parameter values are accurate to one decimal place

First is "Size". Size is used as a scalar for some/all of the delay lengths that make up the digital reverb network. A smaller Size value will reduce the length of the delays in the reverb algorithm, while larger Size values increase the length of the delays. For a richer reverb sound, set the Size as big as you can get away with, until either the attack is too slow or you start hearing objectionable grain. Once your reach this point, turn the Size down to a slightly lower value, until the grain goes away. You can adjust the size parameter by turning the knob. Default value of size parameter is 50.0.

Second is "Width", which is the stereo width of the reverb effect. Most of the time we want a reverb to be in stereo, emulating a realistic sounding acoustic space. However, reducing the width of the reverb or making it mono can be useful too. It focuses the space on the sound, giving it a more direct tone. With 0% being the most narrow and larger percentages widening the effect. The width could also be affected by the stereo panning settings within your DAW. Default value of width is 20.0.

Third one is "Damp". Damping is the absorption of high frequencies in the reverb. Low damping values yield less high-frequency absorption, whereas high damping values produce more absorption of high frequencies. Damping describes how ‘padded’ the emulated room comes across. More damping tends to make for a warmer tone as the higher frequency reflections are dampened, similarly to how a low-pass filter would sound. The reverb tails will lose high frequencies as they bounce around, producing a warmer sound with less “edge.” If your reverb has an artificial-sounding high end, add damping to create a warmer sound. Damping affects overall tone, so setting it “oppositely” often works well. The default value of damp is 30.0.

The last one is "Dry/Wet". The original, unprocessed audio is dry signal, while the processed audio with reverberation is wet signal. The dry/wet control allows you to alter the balance between the untreated (dry) track and the track after reverb is applied. This is more useful for if you’re applying reverb directly to a track, as opposed to using an effects bus. If the reverb serves as an insert effect, set this for the desired blend. If the reverb is a send effect, this is usually set to reverb only, with the return control determing the overall reverb level in the mix. Usually the unit of dry/wet is %, which means the proportion of dry and wet signals in the final output signal. 50% is the original signal and the reverb signal half and half, and 100% is the completely wet signal output. The default value is 50.0%.

If you want to compare the difference with and without reverb, you can bypass this reverb effect by ticking the bypassed check box.