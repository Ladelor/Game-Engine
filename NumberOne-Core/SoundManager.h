#pragma once

#include <fmod.hpp>
#include <vector>
#include <iostream>

namespace NumberOne {
	namespace Sound {

		class SoundManager
		{
		private:
			int sm_numSounds;
			std::vector<FMOD::Sound*> sm_Sounds;
			FMOD::System* sm_System;
			std::vector<FMOD::Channel*> sm_Channels;
			FMOD::ChannelGroup* sm_ChannelGroup;
			unsigned int sm_maxChannels;

		public:
			SoundManager(unsigned int maxChannels);
			~SoundManager();
			void addSound(std::string filePath, bool play = true, bool loop = false);
			//returns false if succesful, true if sound at soundNumber does not exist
			bool removeSound(int sound);
			void clearSounds();
			//loop -1 to loop infinitely
			//returns false if succesful, true if sound at soundNumber does not exist
			bool playSound(int sound, int loop = 0);
			//returns false if succesful, true if sound at soundNumber does not exist
			bool pauseSound(int sound, bool deleteSound = false);
			//returns false if succesful, true if sound at soundNumber does not exist
			bool resumeSound(int sound);
			//returns false if succesful, true if sound at soundNumber does not exist
			bool setVolume(int sound, float volume);
			void setAllVolumes(float volume);
			void resumeAllSounds();
			void pauseAllSounds(bool deleteSounds = false);
			//returns false if succesful, true if sound at soundNumber does not exist
			bool rampingVolume(int sound, int time, float startVolume, float finalVolume);
		};

	}
}
 // !SOUNDMANAGER_H
