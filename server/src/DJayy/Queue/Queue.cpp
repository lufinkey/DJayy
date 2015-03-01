
#include "Queue.h"

namespace DJayy
{
#define QUEUE_BOOST_POINT 5
#define QUEUE_LOWEST_VOTE -5
	
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
	
	String Queue::add(const String&track_id)
	{
		String queue_id = (String)""+next_queue_id;
		QueueTrack track(queue_id, track_id);
		next_queue_id++;
		tracks.add(track);
		return queue_id;
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
	
	void Queue::boost(const String&queue_id)
	{
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			QueueTrack track = tracks.get(i);
			if(track.queue_id.equals(queue_id))
			{
				if(i == 0)
				{
					return;
				}
				tracks.remove(i);
				tracks.add(i-1, track);
			}
		}
	}
	
	void Queue::remove(const String&queue_id)
	{

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
				signed char trueVote = track.votes.vote(user_id,vote);
				long long totalVotes = track.votes.sum();
				if(trueVote==1 && (totalVotes%QUEUE_BOOST_POINT)==0 && totalVotes>=QUEUE_BOOST_POINT)
				{
					boost(queue_id);
				}
				else if(trueVote == -1 && (totalVotes <= QUEUE_LOWEST_VOTE))
				{
					remove(queue_id);
				}
				return;
			}
		}
	}
}
