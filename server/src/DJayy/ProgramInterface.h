
#pragma once

#include "Queue/Queue.h"
#include "Library/TrackCollection.h"

namespace DJayy
{
	class ProgramInterface
	{
	public:
		virtual ~ProgramInterface(){}

		virtual void loadLibrary() = 0;
		
		Queue& getQueue();
		const Queue& getQueue() const;
		
		void addToQueue(const String&track_id);
		
		virtual Track getTrackByTrackID(const String&track_id) const = 0;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const = 0;
		
	protected:
		Queue queue;
	};
}
