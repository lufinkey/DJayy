
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
	
	void ProgramInterface::setNowPlaying(const Track&track)
	{
		nowplaying = track;
	}
	
	const Track& ProgramInterface::getNowPlaying() const
	{
		return nowplaying;
	}
}
