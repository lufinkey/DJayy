
#include "FilesystemMediaSource.h"
#include "FilesystemPlayable.h"

namespace djayy
{
	FilesystemMediaSource::FilesystemMediaSource()
	{
		//
	}
	
	FilesystemMediaSource::~FilesystemMediaSource()
	{
		//
	}
	
	void FilesystemMediaSource::load()
	{
		//TODO prepare sqlite database, begin library refresh
	}
	
	std::vector<TrackInfo> FilesystemMediaSource::search(const std::string& query)
	{
		//TODO make sqlite database query
		return std::vector<TrackInfo>();
	}
	
	Playable* FilesystemMediaSource::getTrack(const std::string& track_id)
	{
		//TODO query sqlite database for track, return new FilesystemPlayable if track exists, otherwise return null
		return nullptr;
	}
}
