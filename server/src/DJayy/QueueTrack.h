
#pragma once

#include "../Util/String.h"

namespace DJayy
{
	class QueueTrack
	{
	public:
		String id;
		String title;
		String artist;
		String album;
		long long votes;

		String toJson() const;
	};
}
