#include "GameSetting.h"
#include "Define.h"

GameSetting *GameSetting::_instance = NULL;
GameSetting::GameSetting()
{
	settingValue[VOLUME] = 100;
	audio = SimpleAudioEngine::getInstance();
}
GameSetting * GameSetting::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameSetting();
	}
	return _instance;
}

void GameSetting::playEffectSoundMCJump()
{
	if (checkSound) 
	{
		switch (random(0, 1))
		{
			case 0: audio->playEffect("sounds/mc_jump1.wav"); 
				break;
			case 1: audio->playEffect("sounds/mc_jump2.wav"); 
				break;
		}
	}
}

void GameSetting::preLoadSounds()
{
	audio->preloadEffect("sounds/mc_jump2.wav");
	audio->preloadEffect("sounds/mc_jump1.wav");
	audio->preloadEffect("SoundsEffect/selectItem.wav");
	audio->preloadBackgroundMusic("sounds/ingameBegin.mp3");
	audio->preloadBackgroundMusic("sounds/ingameLV1.mp3");
	audio->preloadBackgroundMusic("sounds/ingameLV2.mp3");
	audio->preloadBackgroundMusic("sounds/sound_ingameLV3.mp3");
	audio->preloadBackgroundMusic("sounds/musicBG.mp3");
	audio->preloadBackgroundMusic("sounds/sound_intro.mp3");
	audio->preloadBackgroundMusic("sounds/sound_gunmaking.mp3");
	audio->preloadBackgroundMusic("sounds/sound_lastgame.mp3");
	audio->preloadEffect("sounds/sound_gamewin.mp3");
	audio->preloadEffect("sounds/vacham_physic.mp3");
	audio->preloadEffect("sounds/sound_gunFNSCAR.mp3");
	audio->preloadEffect("sounds/soundKnife.mp3");
	audio->preloadEffect("SoundsEffect/selectItem.wav");
	audio->preloadEffect("sounds/knifeLV1.mp3");
	audio->preloadBackgroundMusic("sounds/sound_intro.mp3");
	audio->preloadEffect("sounds/sound_gameover.mp3");
	audio->preloadEffect("sounds/sound_creategun.mp3");
	audio->preloadEffect("sounds/sound_changegun.mp3");
	audio->preloadEffect("sounds/sound_click.mp3");
	audio->preloadEffect("sounds/boomboom.mp3");
}

void GameSetting::playMenuSound()
{
	audio->playBackgroundMusic("sounds/musicBG.mp3", true);
}

void GameSetting::setBackgroundMusicVolum(float volum)
{
	audio->setBackgroundMusicVolume(volum);
}

void GameSetting::stopAllEffects()
{
	audio->stopAllEffects();
}

void GameSetting::pauseAllEffects(){
	audio->pauseAllEffects();
}

void GameSetting::resumeAllEffects()
{
	audio->resumeAllEffects();
}

void GameSetting::pauseBackgroundMusic()
{
	audio->pauseBackgroundMusic();
}

void GameSetting::resumeBackfroundMusic()
{
	audio->resumeBackgroundMusic();
}

void GameSetting::playBackgroundMusic(const char* pszFilePath)
{
	if (checkMusic)
		audio->playBackgroundMusic(pszFilePath, true);
}

void GameSetting::playSoundEffect(const char * pszFilePath)
{
	if (checkSound) {
		audio->playEffect(pszFilePath, false);
	}
}

void GameSetting::stopBackgroundMusic(const char * pszFilePath)
{
	audio->stopBackgroundMusic(pszFilePath);
}
bool GameSetting::getMusic()
{
	return checkMusic;
}
bool GameSetting::getSound()
{
	return checkSound;
}
void GameSetting::setVolume(int volume)
{
	settingValue[VOLUME] = volume;
}
int GameSetting::getVolume()
{
	return settingValue[VOLUME];
}