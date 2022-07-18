#include "P_Audio.h"

void Audio_Init()
{
	//Initialize the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	//Load module for background sound
	mmLoad(MOD_BG_MUSIC);
	//Load punch / smack sound effect effect
	mmLoadEffect(SFX_SMACK);
	mmLoadEffect(SFX_BOXING_HIT);
}

void Audio_PlaySoundEX( int i )
{
	//Declare a sound effect
	mm_sound_effect sound;
	//Set the id of the sound effect with the input parameter
	sound.id = i;
	//Set the rate to the default one (1024)
	sound.rate = 1024;
	//Set the volume to the maximum (range 0...255)
	sound.volume = 255;
	//Set the panning depending on the effect (0-left....255-right)
	if(i == SFX_SMACK)
		sound.panning = 0;
	if(i == SFX_BOXING_HIT)
		sound.panning = 255;

	//Play the effect using the sound structure
	mmEffectEx(&sound);
}

void Audio_PlayMusic()
{
	//Start playing background music in a loop
	mmStart(MOD_BG_MUSIC, MM_PLAY_LOOP);
	//Set module volume to 50% : 512 (range 0...1024)
	mmSetModuleVolume(512);
}
