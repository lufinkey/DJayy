
#include "Track.h"

namespace DJayy
{
	Track::Track()
	{
		track_num = 0;
	}
	
	Track::Track(const String&track_id, const String&title, const String&artist, const String&album, const String&album_artist, unsigned int track_num)
	{
		Track::track_id = track_id;
		Track::title = title;
		Track::artist = artist;
		Track::album = album;
		Track::album_artist = album_artist;
		Track::track_num = track_num;
	}
	
	bool Track::isNull() const
	{
		if(track_id.length() == 0)
		{
			return true;
		}
		return false;
	}
	
	String Track::toJson() const
	{
		return "{\"track_id\":\"" + track_id + "\",\"title\":\"" + title + "\",\"artist\":\"" + artist + "\",\"album\":\"" + album + "\",\"album_artist\":\"" + album_artist + "\",\"track_num\":" + track_num + "}";
	}
}
