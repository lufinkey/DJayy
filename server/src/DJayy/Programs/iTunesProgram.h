
#pragma once

#include "../ProgramInterface.h"

#include <iTunesCOMInterface.h>

namespace DJayy
{
	class iTunesProgram : public ProgramInterface
	{
	public:
		iTunesProgram(WebServer*server);
		virtual ~iTunesProgram();

		virtual void load() override;
		
		virtual Track getTrackByTrackID(const String&track_id) const override;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const override;
		
	private:
		IiTunes *iTunes;
		_IiTunesEvents* events;
		IITLibraryPlaylist* library;
	};
}
