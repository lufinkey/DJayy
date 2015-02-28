
#pragma once

#include "../Util/ArrayList.h"
#include "QueueTrack.h"

namespace DJayy
{
	class ProgramInterface
	{
	public:
		virtual ~ProgramInterface(){}

		virtual ArrayList<QueueTrack> getQueue() = 0;
	};
}
