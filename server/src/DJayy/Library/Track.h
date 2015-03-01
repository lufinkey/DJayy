
#pragma once

#include "../../Util/String.h"

namespace DJayy
{
	class Track
	{
	public:
		String track_id;
		String title;
		String artist;
		String album;
		String album_artist;
		unsigned int track_num;
		
		String path;
		
		Track();
		Track(const String&track_id, const String&title, const String&artist, const String&album, const String&album_artist, unsigned int track_num);
		
		bool isNull() const;
		String toJson() const;
	};
}
