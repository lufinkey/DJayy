
#pragma once

#include "QueueTrack.h"

namespace DJayy
{
	class Queue
	{
	private:
		ArrayList<QueueTrack> tracks;
		unsigned long long next_queue_id;
		
	public:
		Queue();
		
		String toJson() const;
		
		String add(const String&track_id);
		QueueTrack next();
		void boost(const String&queue_id);
		void remove(const String&queue_id);
		size_t size() const;
		
		const ArrayList<QueueTrack>& getTracks() const;
		
		QueueTrack getTrackByQueueID(const String&queue_id) const;
		void vote(const String&queue_id, const String&user_id, signed char vote);
	};
}
