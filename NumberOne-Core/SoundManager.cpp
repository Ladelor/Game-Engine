#include "SoundManager.h"

namespace NumberOne {
	namespace Sound {

		SoundManager::SoundManager(unsigned int maxChannels)
			: sm_maxChannels(maxChannels), sm_numSounds(0)
		{
			if (FMOD::System_Create(&sm_System) != FMOD_OK)
			{
				// Report Error
				std::cout << "Error";
				return;
			}
			int driverCount = 0;
			sm_System->getNumDrivers(&driverCount);

			if (driverCount == 0)
			{
				std::cout << "Error";
				return;
			}

			// Initialize our Instance
			if (sm_System->init(sm_maxChannels, FMOD_INIT_NORMAL, NULL))
			{
				std::cout << "Error";
				return;
			}

			if (sm_System->createChannelGroup("Group", &sm_ChannelGroup))
			{
				std::cout << "Error";
				return;
			}
		}

		SoundManager::~SoundManager()
		{
			clearSounds();
			sm_ChannelGroup->release();
			sm_Channels.clear();
			sm_System->close();
			if (sm_System->release())
				std::cout << "Error";
		}

		void SoundManager::addSound(std::string filePath, bool play, bool loop)
		{
			FMOD::Sound* sound;
			int Loop = (int)loop;
			if (Loop) Loop++;
			sm_System->createStream(filePath.c_str(), Loop, 0, &sound);
			sm_Sounds.push_back(sound);
			FMOD::Channel* temp;
			sm_Channels.push_back(temp);
			sm_numSounds++;
			sm_System->playSound(sound, sm_ChannelGroup, play, &sm_Channels[sm_Channels.size() - 1]);
		}

		bool SoundManager::removeSound(int sound)
		{
			if (sound > sm_numSounds)
				//error
				return true;
			FMOD::Sound* tempSound;
			tempSound = *(sm_Sounds.begin() + (sound - 1));
			tempSound->release();
			sm_Sounds.erase(sm_Sounds.begin() + (sound - 1));
			sm_Channels.erase(sm_Channels.begin() + (sound - 1));
			sm_numSounds--;
			return false;
		}

		void SoundManager::clearSounds()
		{
			for (FMOD::Sound* sound : sm_Sounds)
			{
				sound->release();
			}
			sm_Sounds.clear();
			sm_Channels.clear();
			sm_numSounds = 0;
		}

		bool SoundManager::playSound(int sound, int loop)
		{
			if (sound > sm_numSounds)
				//error
				return true;
			if (loop != 0)
				sm_Sounds[sound - 1]->setLoopCount(loop);
			if (sm_System->playSound(sm_Sounds[sound - 1], sm_ChannelGroup, false, &sm_Channels[sound - 1]))
				std::cout << "Error";
			return false;
		}

		bool SoundManager::pauseSound(int sound, bool deleteSound)
		{
			if (sound > sm_numSounds)
				return true;
			if (deleteSound)
			{
				sm_Sounds[sound - 1]->release();				
			}
			sm_Channels[sound - 1]->setPaused(true);
			return false;
		}

		bool SoundManager::resumeSound(int sound)
		{
			if (sound > sm_numSounds)
				//error
				return true;
			sm_Channels[sound - 1]->setPaused(false);
			return false;
		}

		bool SoundManager::setVolume(int sound, float volume)
		{
			if (sound > sm_numSounds)
				//error
				return true;
			sm_Channels[sound - 1]->setVolume(volume);
			return false;
		}

		void SoundManager::setAllVolumes(float volume)
		{
			sm_ChannelGroup->setVolume(volume);
		}

		void SoundManager::resumeAllSounds()
		{
			sm_ChannelGroup->setPaused(false);
		}

		void SoundManager::pauseAllSounds(bool deleteSounds)
		{
			sm_ChannelGroup->setPaused(true);
		}

		bool SoundManager::rampingVolume(int sound, int time, float startVolume, float finalVolume)
		{
			if (sound > sm_numSounds)
				return true;
			unsigned long long parentClock;
			sm_Channels[sound - 1]->getDSPClock(NULL, &parentClock);
			sm_Channels[sound - 1]->addFadePoint(parentClock, startVolume);
			sm_Channels[sound - 1]->addFadePoint(parentClock + (time * 48000), finalVolume);
			return false;
		}

	}
}