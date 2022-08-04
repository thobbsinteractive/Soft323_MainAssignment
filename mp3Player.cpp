#include "mp3Player.h"

// http://www.gamedev.net/reference/articles/article2053.asp

mp3Player::mp3Player()
{
	playing = false;
}

mp3Player::~mp3Player()
{
}

void mp3Player::load(char _fileName[])
{
	fileName = _fileName;

	std::string szCommand = "open \"" + fileName + "\" type mpegvideo alias " + fileName;
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);

	//Parameter Description
	//'open' 	     - Inform MCI we'd like to load the resource in 'szFileName'
	//'szFileName' - This is the resource we'd like to open for playback.
	//'type mpegvideo' - Informing MCI what type of audio/video device we're working with.
	//'alias ***'  - The string we pass after alias is the character-based handle we're assigning to	
	//	this resource. Any future operations on this resource should use this name. 
}

void mp3Player::unLoad()
{
	if(playing == true)
	{
		stop();
	}

	std::string szCommand = "close " + fileName;
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);
}

void mp3Player::play()
{
	std::string szCommand = "play " + fileName + " from 0";
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);
	playing = true;
}

bool mp3Player::isPlaying()
{
	return playing;
}
void mp3Player::pause()
{
	std::string szCommand = "pause " + fileName;
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);
	playing = false;
}

void mp3Player::unPause()
{
	std::string szCommand = "resume " + fileName;
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);
	playing = true;
}

void mp3Player::stop()
{
	std::string szCommand = "stop " + fileName;
	mciSendString((LPCWSTR)szCommand.c_str(), NULL, 0, 0);
	playing = false;
}