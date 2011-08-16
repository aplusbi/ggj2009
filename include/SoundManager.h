#ifndef _H_SOUNDMANAGER_
#define _H_SOUNDMANAGER_

#include "includes.h"
#include "common.h"

struct tSoundEffect
{
	Mix_Chunk * m_Sound; //pointer to the loaded sound file
	int m_nType;		 //Enum type of the sound file we are. For ease of playing later
};


class SoundManager
{

private:
	static SoundManager* m_pInstance;

	//Pointer to music information ( music seperated from sound effects in mixer )
	Mix_Music *m_music;
	//List of loaded sound effects 
	std::vector<tSoundEffect> m_Sounds;

	SoundManager(){}
	SoundManager& operator=(const SoundManager& ref){}
	SoundManager(const SoundManager& ref){}
	void AddSound(int type, const char * const file);
public:
	static SoundManager* getInstance();

	void Init();

	//Play the loaded Mix_Music file. 
	void PlayMusic();
	void PauseMusic() { Mix_PauseMusic(); }
	void ResumeMusic() { Mix_ResumeMusic(); }
	//Play the loaded sound with the type matching the passed in enum
	int PlaySnd(unsigned int nEnum, int loops = 0);

	void HaltSound(int channel);
	

};

#define SM SoundManager::getInstance()

#endif
