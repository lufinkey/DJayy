
#pragma once

#include "QueueTrack.h"

namespace DJayy
{
	class ProgramInterface
	{
	public:
		virtual ~ProgramInterface(){}

		virtual ArrayList<QueueTrack> getQueue() = 0;
		virtual QueueTrack getQueueTrack(const String&queue_id) const = 0;
		virtual void vote(const String&queue_id, const String&user_id, signed char vote) = 0;
	};
}
