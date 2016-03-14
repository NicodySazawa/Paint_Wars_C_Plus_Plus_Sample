#ifndef SFML_SOUND_PROVIDER_H
#define SFML_SOUND_PROVIDER_H

#include <string>
#include "SFML/Audio.hpp"
#include "iaudioprovider.h"
#include "soundfilecache.h"

class SFMLSoundProvider : public IAudioProvider
{
public:
  SFMLSoundProvider();

  virtual void PlaySound(std::string filename);
  virtual void PlaySong(std::string filename, bool looping);
  virtual void StopAllSounds();

  virtual bool IsSoundPlaying();
  virtual bool IsSongPlaying();

private:
  static const int MAX_SOUND_CHANNELS = 5;
  
  SoundFileCache _soundFileCache;
  sf::Sound _currentSounds[MAX_SOUND_CHANNELS];
  std::string _currentSongName;
};

#endif
