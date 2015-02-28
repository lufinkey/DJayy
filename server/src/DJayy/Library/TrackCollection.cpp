
#include "TrackCollection.h"

namespace DJayy
{
	TrackCollection::TrackCollection()
	{
		//
	}
	
	TrackCollection::TrackCollection(const ArrayList<Track>&tracks)
	{
		TrackCollection::tracks = tracks;
	}
	
	String TrackCollection::toJson() const
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
	
	void TrackCollection::add(const Track&track)
	{
		tracks.add(track);
	}
	
	size_t TrackCollection::size() const
	{
		return tracks.size();
	}
	
	Track TrackCollection::getTrackByIndex(size_t index) const
	{
		return tracks.get(index);
	}
	
	Track TrackCollection::getTrackByTrackID(const String&track_id) const
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
	
	ArrayList<Track> TrackCollection::getTracksByArtist(const String&artist) const
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
	
	ArrayList<Track> TrackCollection::getTracksByAlbum(const String&album, const String&album_artist) const
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
	
	ArrayList<Track> TrackCollection::getTracksByAlbumArtist(const String&album_artist) const
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
