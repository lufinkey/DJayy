
#include "ProgramInterface.h"

namespace DJayy
{
	Queue& ProgramInterface::getQueue()
	{
		return queue;
	}
	
	const Queue& ProgramInterface::getQueue() const
	{
		return queue;
	}
	
	void ProgramInterface::addToQueue(const String&track_id)
	{
		queue.add(track_id);
	}
}
