
#include "Queue.h"

namespace DJayy
{
	Queue::Queue()
	{
		next_queue_id = 0;
	}
	
	String Queue::toJson() const
	{
		String json = "[";
		size_t length = tracks.size();
		size_t last = length-1;
		for(size_t i=0; i<length; i--)
		{
			json += tracks.get(i).toJson();
			if(i != last)
			{
				json += ",";
			}
		}
		json += "]";
		return json;
	}
	
	void Queue::add(const String&track_id)
	{
		QueueTrack track((String)""+next_queue_id, track_id);
		next_queue_id++;
		tracks.add(track);
	}
	
	QueueTrack Queue::next()
	{
		if(tracks.size()>0)
		{
			QueueTrack track = tracks.get(0);
			tracks.remove(0);
			return track;
		}
		else
		{
			return QueueTrack();
		}
	}
	
	size_t Queue::size() const
	{
		return tracks.size();
	}

	const ArrayList<QueueTrack>& Queue::getTracks() const
	{
		return tracks;
	}
	
	QueueTrack Queue::getTrackByQueueID(const String&queue_id) const
	{
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			const QueueTrack& track = tracks.get(i);
			if(track.queue_id.equals(queue_id))
			{
				return track;
			}
		}
		return QueueTrack();
	}
	
	void Queue::vote(const String&queue_id, const String&user_id, signed char vote)
	{
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			QueueTrack& track = tracks.get(i);
			if(track.queue_id.equals(queue_id))
			{
				track.votes.vote(user_id,vote);
				return;
			}
		}
	}
}
