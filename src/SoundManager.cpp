#include "SoundManager.h"


SoundManager* SoundManager::m_pInstance = 0; //define the event handler instance

//returns the instance of the game main class
SoundManager* SoundManager::getInstance()
{
	//lazy intialization
	if (m_pInstance == 0)
		m_pInstance = new SoundManager;

	return m_pInstance;
}

//init SoundManager *CALL BEFORE PLAYING ANY AUDIO*
void SoundManager::Init()
{
	//Audio information
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	//Configure our audio device 
	Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	//Quick and dirty audio loading done here 

	////Load music file up
	m_music = Mix_LoadMUS("assets/sounds/moonlightsonata.mp3");

	//A new sound effect to load
	m_Sounds.resize(SFX_COUNT);
	AddSound(SFX_WALK, "assets/sounds/footsteps.wav");	
	AddSound(SFX_CLOCK, "assets/sounds/clock.wav");	
	AddSound(SFX_DRINK, "assets/sounds/drink.wav");	
	AddSound(SFX_LAMP, "assets/sounds/lamp.wav");	
	AddSound(SFX_PILLS, "assets/sounds/pills.wav");	
	AddSound(SFX_SINK, "assets/sounds/sink.wav");	
	AddSound(SFX_TV, "assets/sounds/tv_off.wav");	
	AddSound(SFX_UNPLUG, "assets/sounds/unplug.wav");	
	AddSound(SFX_TOASTER, "assets/sounds/toaster.wav");	
}

void SoundManager::AddSound(int type, const char * const file)
{
	tSoundEffect newSound;
	newSound.m_Sound = Mix_LoadWAV(file);
	newSound.m_nType = type;
	m_Sounds[type] = (newSound); //push sound effect into the list 	
}

void SoundManager::PlayMusic()
{

	Mix_PlayMusic(m_music, -1);
	//load a music file 
	//m_music = Mix_LoadMUS("assets/sounds/moonlight.mid");
}

int SoundManager::PlaySnd(unsigned int nEnum, int loops)
{
	//Check for a valid enum
	if(nEnum >= 0 && nEnum <= m_Sounds.size())
	{
		//play the sound file
		int Channel = Mix_PlayChannel(-1, m_Sounds[nEnum].m_Sound, loops);
		return Channel;
	}
}

void SoundManager::HaltSound(int channel)
{
	Mix_HaltChannel(channel);
}

