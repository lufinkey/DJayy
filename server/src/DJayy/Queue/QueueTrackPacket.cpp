
#include "QueueTrackPacket.h"

namespace DJayy
{
	QueueTrackPacket::QueueTrackPacket(const QueueTrack&queuetrack, const Library&library)
	{
		queue_id = queuetrack.queue_id;
		track_id = queuetrack.track_id;
		votes = queuetrack.votes;
		
		Track track = library.getTrackByTrackID(track_id);
		if(!track.isNull())
		{
			title = track.title;
			artist = track.artist;
			album = track.album;
			album_artist = track.album_artist;
			track_num = track.track_num;
		}
	}
	
	String QueueTrackPacket::toJson() const
	{
		return "{\"queue_id\":\"" + queue_id + "\",\"track_id\":\"" + track_id + "\",\"votes\":" + votes.sum() + ",\"title\":\"" + title + "\",\"artist\":\"" + artist + "\",\"album\":\"" + album + "\",\"album_artist\":\"" + album_artist + "\",\"track_num\":" + track_num + "}";
	}
}
