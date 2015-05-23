
#pragma once

#include "TrackInfo.h"
#include <vector>

namespace djayy
{
	class MediaSource;
	class PlayableListener;
	
	class Playable
	{
	public:
		virtual void play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;
		
		virtual double getLength() = 0; //seconds
		virtual void setPosition(double seconds) = 0;
		virtual double getPosition() const = 0;
		
		void addPlayableListener(PlayableListener* listener);
		void removePlayableListener(PlayableListener* listener);
		
		MediaSource* getMediaSource() const;
		TrackInfo getTrackInfo() const;
		
	protected:
		Playable(MediaSource*media_source, const TrackInfo& track_info);
		
	private:
		MediaSource* media_source;
		TrackInfo track_info;
		
		std::vector<PlayableListener*> listeners;
	};
}
