
#include "Library.h"

namespace DJayy
{
	Library::Library()
	{
		//
	}
	
	Library::Library(const ArrayList<Track>&tracks)
	{
		Library::tracks = tracks;
	}
	
	String Library::toJson() const
	{
		String json = "[";
		size_t length = tracks.size();
		size_t last = tracks.size()-1;
		for(size_t i=0; i<length; i++)
		{
			json += tracks.get(i).toJson();
			if(i != last)
			{
				json += ",";
			}
		}
		json += "]";
		return json;
	}
	
	void Library::add(const Track&track)
	{
		tracks.add(track);
	}
	
	Track Library::getTrackByTrackID(const String&track_id) const
	{
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			const Track& track = tracks.get(i);
			if(track.track_id.equals(track_id))
			{
				return track;
			}
		}
		return Track();
	}
	
	ArrayList<Track> Library::getTracksByArtist(const String&artist) const
	{
		ArrayList<Track> artist_tracks;
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			const Track& track = tracks.get(i);
			if(track.album_artist.equals(artist))
			{
				artist_tracks.add(track);
			}
		}
		return artist_tracks;
	}
	
	ArrayList<Track> Library::getTracksByAlbum(const String&album, const String&album_artist) const
	{
		ArrayList<Track> album_tracks;
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			const Track& track = tracks.get(i);
			if(track.album.equals(album) && track.album_artist.equals(album_artist))
			{
				album_tracks.add(track);
			}
		}
		return album_tracks;
	}
	
	ArrayList<Track> Library::getTracksByAlbumArtist(const String&album_artist) const
	{
		ArrayList<Track> album_artist_tracks;
		size_t length = tracks.size();
		for(size_t i=0; i<length; i++)
		{
			const Track& track = tracks.get(i);
			if(track.album_artist.equals(album_artist))
			{
				album_artist_tracks.add(track);
			}
		}
		return album_artist_tracks;
	}
}
