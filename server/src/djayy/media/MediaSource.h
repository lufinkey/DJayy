
#pragma once

#include "Playable.h"

namespace djayy
{
	class MediaSource
	{
	public:
		virtual ~MediaSource(){}

		virtual void load() = 0;
		virtual std::vector<TrackInfo> search(const std::string& query) = 0;
		virtual Playable* getTrack(const std::string& track_id) = 0;
	};
}
