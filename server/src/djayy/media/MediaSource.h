
#pragma once

#include "Playable.h"

namespace djayy
{
	class MediaSource
	{
	public:
		virtual ~MediaSource(){}

		virtual bool load() = 0;
		virtual std::string getSourceID() const = 0;
		
		virtual std::vector<TrackInfo> search(const std::string& query) = 0;
		virtual Playable* getTrack(const std::string& track_id) = 0;
	};
}
