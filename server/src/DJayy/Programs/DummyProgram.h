
#pragma once

#include "../ProgramInterface.h"

namespace DJayy
{
	class DummyProgram : public ProgramInterface
	{
		virtual ArrayList<QueueTrack> getQueue();
	};
}
