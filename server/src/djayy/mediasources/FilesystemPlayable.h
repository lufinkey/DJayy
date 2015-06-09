
#pragma once

#include "../media/Playable.h"
#include "../media/MusicFile.h"
#include <thread>

namespace djayy
{
	class FilesystemMediaSource;
	
	class FilesystemPlayable : public Playable
	{
	public:
		FilesystemPlayable(const std::string& filepath, FilesystemMediaSource*media_source, const TrackInfo& track_info);
		virtual ~FilesystemPlayable();
		
		virtual bool loaded() const override;
		virtual void play() override;
		virtual void pause() override;
		virtual void stop() override;
		
		virtual void setPosition(double pos) override;
		virtual double getPosition() const override;
		
	private:
		MusicFile* musicFile;
	};
}
