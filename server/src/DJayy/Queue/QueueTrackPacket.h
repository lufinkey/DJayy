
#pragma once

#include "QueueTrack.h"
#include "../Library/Library.h"

namespace DJayy
{
	class QueueTrackPacket
	{
	public:
		String queue_id;
		String track_id;
		UserVoteList votes;
		String title;
		String artist;
		String album;
		String album_artist;
		unsigned int track_num;
		
		QueueTrackPacket(const QueueTrack&queuetrack, const Library&library);

		String toJson() const;
	};
}
