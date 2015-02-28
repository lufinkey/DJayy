
#pragma once

#include "Track.h"
#include "../../Util/ArrayList.h"

namespace DJayy
{
	class Library
	{
	public:
		Library();
		Library(const ArrayList<Track>& tracks);
		
		String toJson() const;
		
		void add(const Track&track);
		
		Track getTrackByTrackID(const String&track_id) const;
		ArrayList<Track> getTracksByArtist(const String&artist) const;
		ArrayList<Track> getTracksByAlbum(const String&album, const String&album_artist) const;
		ArrayList<Track> getTracksByAlbumArtist(const String&album_artist) const;

	private:
		ArrayList<Track> tracks;
	};
}
