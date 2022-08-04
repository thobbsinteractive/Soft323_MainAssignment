#ifndef INC_MP3PLAYER_H
#define INC_MP3PLAYER_H

#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>

class mp3Player
{
public:
	mp3Player();
	~mp3Player();
	void load(char _fileName[]);
	void unLoad();
	void play();
	void pause();
	void unPause();
	void stop();
	bool isPlaying();

private:
	std::string fileName;
	bool playing;
};

#endif //INC_MP3PLAYER_H