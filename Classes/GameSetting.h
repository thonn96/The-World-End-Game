#ifndef _GAME_SETTING_H_
#define _GAME_SETTING_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

class GameSetting {
private:
	int settingValue[12];
	GameSetting();
	static GameSetting* _instance;
	SimpleAudioEngine* audio;
public:
	bool checkSound = true;
	bool checkMusic = true;
	static GameSetting* getInstance();
	void playEffectSoundMCJump();
	void preLoadSounds();
	void playMenuSound();
	void setBackgroundMusicVolum(float volum);
	void stopAllEffects();
	void resumeAllEffects();
	void pauseBackgroundMusic();
	void resumeBackfroundMusic();
	void playBackgroundMusic(const char* pszFilePath);
	void playSoundEffect(const char* pszFilePath);
	void stopBackgroundMusic(const char * pszFilePath);
	void pauseAllEffects();
	bool getMusic();
	bool getSound();
	void setVolume(int volume);
	int getVolume();
};
#endif // !_GAME_SETTING_H_

