
#include "Playable.h"

namespace djayy
{
	Playable::Playable(MediaSource*media_source, const TrackInfo& track_info)
		: media_source(media_source),
		track_info(track_info)
	{
		//
	}
	
	void Playable::addPlayableListener(PlayableListener* listener)
	{
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			if(listener == listeners[i])
			{
				throw std::invalid_argument("listener: already added");
			}
		}
		listeners.push_back(listener);
	}
	
	void Playable::removePlayableListener(PlayableListener* listener)
	{
		size_t listeners_size = listeners.size();
		for(size_t i=0; i<listeners_size; i++)
		{
			if(listener == listeners[i])
			{
				listeners.erase(listeners.begin()+i);
				return;
			}
		}
		throw std::invalid_argument("listener: not added");
	}
	
	MediaSource* Playable::getMediaSource() const
	{
		return media_source;
	}
	
	TrackInfo Playable::getTrackInfo() const
	{
		return track_info;
	}
}
