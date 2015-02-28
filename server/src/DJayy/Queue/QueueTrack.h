
#pragma once

#include "UserVoteList.h"

namespace DJayy
{
	class QueueTrack
	{
	public:
		String queue_id;
		String track_id;
		UserVoteList votes;
		
		QueueTrack();
		QueueTrack(const String&queue_id, const String&track_id);
		
		bool isNull() const;
		String toJson() const;
	};
}
