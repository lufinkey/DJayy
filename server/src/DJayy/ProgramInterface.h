
#pragma once

#include "Queue/Queue.h"
#include "Library/Library.h"

namespace DJayy
{
	class ProgramInterface
	{
	public:
		virtual ~ProgramInterface(){}

		virtual void loadLibrary() = 0;
		
		Queue& getQueue();
		const Queue& getQueue() const;
		const Library& getLibrary() const;
		
		void addToQueue(const String&track_id);
		
	protected:
		Library library;
		Queue queue;
	};
}
