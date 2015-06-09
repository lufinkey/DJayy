
#include "FilesystemPlayable.h"
#include "FilesystemMediaSource.h"

namespace djayy
{
	FilesystemPlayable::FilesystemPlayable(const std::string& filepath, FilesystemMediaSource*media_source, const TrackInfo& track_info) : Playable(media_source, track_info),
		musicFile(nullptr)
	{
		musicFile = new MusicFile();
		bool opened = musicFile->openFromFile(filepath);
		if(!opened)
		{
			delete musicFile;
			musicFile = nullptr;
		}
	}
	
	FilesystemPlayable::~FilesystemPlayable()
	{
		if(musicFile != nullptr)
		{
			musicFile->close();
			delete musicFile;
		}
	}
	
	bool FilesystemPlayable::loaded() const
	{
		if(musicFile == nullptr)
		{
			return false;
		}
		return true;
	}
	
	void FilesystemPlayable::play()
	{
		if(musicFile == nullptr)
		{
			return;
		}
		musicFile->play();
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			listeners[i]->onPlay(this);
		}
		//TODO add onfinish listener
	}
	
	void FilesystemPlayable::pause()
	{
		if(musicFile == nullptr)
		{
			return;
		}
		musicFile->pause();
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			listeners[i]->onPause(this);
		}
	}
	
	void FilesystemPlayable::stop()
	{
		if(musicFile == nullptr)
		{
			return;
		}
		musicFile->stop();
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			listeners[i]->onStop(this);
		}
	}
	
	void FilesystemPlayable::setPosition(double pos)
	{
		if(musicFile == nullptr)
		{
			return;
		}
		musicFile->setPosition(pos);
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			listeners[i]->onSeek(this, pos);
		}
	}
	
	double FilesystemPlayable::getPosition() const
	{
		if(musicFile == nullptr)
		{
			return 0;
		}
		return musicFile->getPosition();
	}
}
