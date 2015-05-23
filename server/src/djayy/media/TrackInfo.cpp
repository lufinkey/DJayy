
#include "TrackInfo.h"
#include "../WebUtils.h"

namespace djayy
{
	TrackInfo::TrackInfo()
		: track_num(0)
	{
		//
	}
	
	std::string TrackInfo::toJSON() const
	{
		return std::string("{")
			+"\"track_id\":\""+webutils::string_replaceall(track_id, "\"", "\\\"")+"\","
			+"\"source_id\":\""+webutils::string_replaceall(source_id, "\"", "\\\"")+"\","
			+"\"title\":\""+webutils::string_replaceall(title, "\"", "\\\"")+"\","
			+"\"artist\":\""+webutils::string_replaceall(artist, "\"", "\\\"")+"\","
			+"\"album\":\""+webutils::string_replaceall(album, "\"", "\\\"")+"\","
			+"\"album_artist\":\""+webutils::string_replaceall(album_artist, "\"", "\\\"")+"\","
			+"\"genre\":\""+webutils::string_replaceall(genre, "\"", "\\\"")+"\","
			+"\"track_num\":"+std::to_string(track_num)+","
			+"\"coverart_url\":\""+webutils::string_replaceall(coverart_url, "\"", "\\\"")+"\""
		+"}";
	}
}
