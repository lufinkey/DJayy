
#include "QueueTrack.h"

namespace DJayy
{
	String QueueTrack::toJson() const
	{
		return "{\"id\":\"" + id + "\",\"title\":\"" + title + "\",\"artist\":\"" + artist + "\",\"album\":\"" + album + "\",\"votes\":" + votes + "}";
	}
}
