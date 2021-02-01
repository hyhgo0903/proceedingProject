#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
	: _system(nullptr), 
	_channel(nullptr),
	_sound(nullptr)
{
}

soundManager::~soundManager()
{
}

HRESULT soundManager::init()
{
	//FMOD 엔진 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	_bgmVolume = 1.0f;
	_effectVolume = 1.0f;
	return S_OK;
}

void soundManager::release()
{
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

	delete[] _sound;
	delete[] _channel;
}

void soundManager::update()
{
	_system->update();
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_vBgmKey.push_back(keyName);
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_vBgmKey.push_back(keyName);
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
	}
	_latestAdded = soundName;
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

// 볼륨은 알아서 쓰도록했음
void soundManager::play(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드가 계속 재생하려다보니까 끊키고 안나와요!
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			bool isBgm = false;
			for (int i = 0; i < _vBgmKey.size(); ++i)
			{
				if (iter->first == _vBgmKey[i])
				{
					_channel[count]->setVolume(_bgmVolume);
					isBgm = true;
					break;
				}
			}
			if (!isBgm) _channel[count]->setVolume(_effectVolume);
		}
	}
}

void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void soundManager::setBgmVolume(float volume)
{
	_bgmVolume = volume;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		for (int i = 0; i < _vBgmKey.size(); ++i)
		{
			if (iter->first == _vBgmKey[i])
			{
				_channel[count]->setVolume(_bgmVolume);
				break;
			}
		}
	}
}

void soundManager::setEffectVolume(float volume)
{
	_effectVolume = volume;
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		bool isBgm = false;
		for (int i = 0; i < _vBgmKey.size(); ++i)
		{
			if (iter->first == _vBgmKey[i])
			{
				isBgm = true;
				break;
			}
		}
		if (!isBgm) _channel[count]->setVolume(_effectVolume);
	}
}
