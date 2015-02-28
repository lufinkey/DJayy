
#include "QueueTrack.h"

namespace DJayy
{
	QueueTrack::QueueTrack()
	{
		//
	}
	
	QueueTrack::QueueTrack(const String&queue_id, const String&track_id)
	{
		QueueTrack::queue_id = queue_id;
		QueueTrack::track_id = track_id;
	}
	
	bool QueueTrack::isNull() const
	{
		if(track_id.length()==0)
		{
			return true;
		}
		return false;
	}
	
	String QueueTrack::toJson() const
	{
		return "{\"queue_id\":\"" + queue_id + "\",\"track_id\":\"" + track_id + "\",\"votes\":" + votes.sum() + "}";
	}
}
