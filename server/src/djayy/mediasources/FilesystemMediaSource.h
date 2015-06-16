
#pragma once

#include "../media/MediaSource.h"
#include <mutex>
#include <sqlite3.h>

namespace djayy
{
	class FilesystemMediaSource : public MediaSource
	{
	public:
		FilesystemMediaSource();
		virtual ~FilesystemMediaSource();
		
		virtual bool load(std::string*error=nullptr) override;
		virtual std::string getSourceID() const override;
		
		virtual std::vector<TrackInfo> search(const std::string& query) override;
		virtual Playable* getTrack(const std::string& track_id) override;
		
	private:
		sqlite3* database;
		std::mutex db_mutex;
		
		static bool is_numeric(const std::string& num);
	};
}
