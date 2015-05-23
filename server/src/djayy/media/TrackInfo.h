
#pragma once

#include <string>

namespace djayy
{
	class TrackInfo
	{
	public:
		std::string track_id;
		std::string source_id;
		
		std::string title;
		std::string artist;
		std::string album;
		std::string album_artist;
		std::string genre;
		unsigned int track_num;
		std::string coverart_url;
		
		TrackInfo();
		
		std::string toJSON() const;
	};
}
