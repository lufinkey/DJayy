
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
	
	String ProgramInterface::addToQueue(const String&track_id)
	{
		return queue.add(track_id);
	}
}
