
#pragma once

#include "../media/MediaSource.h"

namespace djayy
{
	class FilesystemMediaSource : public MediaSource
	{
	public:
		FilesystemMediaSource();
		virtual ~FilesystemMediaSource();
		
		virtual void load() override;
		virtual std::vector<TrackInfo> search(const std::string& query) override;
		virtual Playable* getTrack(const std::string& track_id) override;
	};
}
