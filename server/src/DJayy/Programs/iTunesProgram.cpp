
#include "iTunesProgram.h"
#include <comutil.h>

namespace DJayy
{
	static const String default_playlist_name = "DJayy";
	
	iTunesProgram::iTunesProgram(WebServer*server) : ProgramInterface(server)
	{
		iTunes = nullptr;
		library = nullptr;
		CoInitialize(0);
	}
	
	iTunesProgram::~iTunesProgram()
	{
		CoUninitialize();
	}
	
	void iTunesProgram::load()
	{
		HRESULT hRes = ::CoCreateInstance(CLSID_iTunesApp, nullptr, CLSCTX_LOCAL_SERVER, IID_IiTunes, (PVOID*)&iTunes);
		
		if(hRes==S_OK && iTunes!=nullptr)
		{
			iTunes->get_LibraryPlaylist(&library);
		}
		else
		{
			throw std::exception("error initializing itunes");
		}
	}
	
	Track iTunesProgram::getTrackByTrackID(const String&track_id) const
	{
		size_t colonIndex = track_id.indexOf(':');
		long lowID = String::asLong(track_id.substring(0,colonIndex));
		long highID = String::asLong(track_id.substring(colonIndex+1, track_id.length()));
		
		IITTrackCollection* tracks = nullptr;
		library->get_Tracks(&tracks);
		IITTrack* itunes_track = nullptr;
		tracks->get_ItemByPersistentID(highID, lowID, &itunes_track);
		
		if(itunes_track == nullptr)
		{
			return Track();
		}
		
		IITFileOrCDTrack* itunes_file_track = nullptr;
		itunes_track->QueryInterface<IITFileOrCDTrack>(&itunes_file_track);
		
		BSTR track_title = nullptr;
		BSTR track_artist = nullptr;
		BSTR track_album = nullptr;
		BSTR track_album_artist = nullptr;
		long track_number = 0;
		
		itunes_track->get_Name(&track_title);
		itunes_track->get_Artist(&track_artist);
		itunes_track->get_Album(&track_album);
		itunes_file_track->get_AlbumArtist(&track_album_artist);
		itunes_track->get_TrackNumber(&track_number);
		
		String title;
		if(track_title != nullptr)
		{
			title = track_title;
		}
		String artist;
		if(track_artist != nullptr)
		{
			artist = track_artist;
		}
		String album;
		if(track_album != nullptr)
		{
			album = track_album;
		}
		String album_artist;
		if(track_album_artist != nullptr)
		{
			album_artist = track_album_artist;
		}
		
		return Track(track_id, title, artist, album, album_artist, (unsigned int)track_number);
	}
	
	TrackCollection iTunesProgram::search(const String&query, size_t startIndex, size_t endIndex) const
	{
		if(startIndex == endIndex)
		{
			return TrackCollection();
		}
		IITTrackCollection* results = NULL;
		std::wstring strq = query.wstring();
		BSTR strw =(BSTR)strq.c_str();
		HRESULT hRes = library->Search(strw, ITPlaylistSearchFieldAll, &results);
		if(results == nullptr)
		{
			return TrackCollection();
		}
		else
		{
			TrackCollection resultList;
			long songCounter = 0;
			long length = 0;
			results->get_Count(&length);
			for(long i=1; i<=length; i++)
			{
				IITTrack* itunes_track = nullptr;
				results->get_Item(i, &itunes_track);
				
				ITTrackKind kind;
				itunes_track->get_Kind(&kind);
				bool isSong = false;
				if(kind == ITTrackKindFile)
				{
					IITFileOrCDTrack* itunes_file_track = nullptr;
					itunes_track->QueryInterface<IITFileOrCDTrack>(&itunes_file_track);
					BSTR location = nullptr;
					itunes_file_track->get_Location(&location);
					if(location != nullptr)
					{
						String loc = location;
						size_t lastDot = loc.lastIndexOf('.');
						if(lastDot != STRING_NOTFOUND)
						{
							String extension = loc.substring(lastDot+1, loc.length());
							if(extension.equals("mp3") || extension.equals("aac") || extension.equals("m4a"))
							{
								isSong = true;
							}
						}
					}
				}
				
				if(isSong)
				{
					if(songCounter>=startIndex)
					{
						long lowID = 0;
						long highID = 0;
						VARIANT variant;
						VariantInit(&variant);
						variant.pdispVal = reinterpret_cast<IDispatch*>(itunes_track);
						variant.vt = VT_DISPATCH;
						iTunes->get_ITObjectPersistentIDLow(&variant, &lowID);
						iTunes->get_ITObjectPersistentIDHigh(&variant, &highID);
						
						String track_id = (String)"" + lowID + ":" + highID;
						BSTR track_title = nullptr;
						BSTR track_artist = nullptr;
						BSTR track_album = nullptr;
						BSTR track_album_artist = nullptr;
						long track_number = 0;
						
						IITFileOrCDTrack* itunes_file_track = nullptr;
						itunes_track->QueryInterface<IITFileOrCDTrack>(&itunes_file_track);
						
						//itunes_track->get_TrackDatabaseID(&track_id);
						itunes_track->get_Name(&track_title);
						itunes_track->get_Artist(&track_artist);
						itunes_track->get_Album(&track_album);
						itunes_file_track->get_AlbumArtist(&track_album_artist);
						itunes_track->get_TrackNumber(&track_number);
						
						String title;
						if(track_title != nullptr)
						{
							title = track_title;
						}
						String artist;
						if(track_artist != nullptr)
						{
							artist = track_artist;
						}
						String album;
						if(track_album != nullptr)
						{
							album = track_album;
						}
						String album_artist;
						if(track_album_artist != nullptr)
						{
							album_artist = track_album_artist;
						}
						
						Track track(track_id, title, artist, album, album_artist, (unsigned int)track_number);
						resultList.add(track);
					}
					songCounter++;
					if(songCounter>=endIndex)
					{
						return resultList;
					}
				}
			}
			return resultList;
		}
	}
}
