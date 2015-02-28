
#include "iTunesProgram.h"

namespace DJayy
{
	iTunesProgram::iTunesProgram()
	{
		iITunes = nullptr;
		trackCollection = nullptr;
		CoInitialize(0);
	}
	
	iTunesProgram::~iTunesProgram()
	{
		CoUninitialize();
	}
	
	void iTunesProgram::loadLibrary()
	{
		HRESULT hRes;
		BSTR bstrURL = nullptr;
		
		hRes = ::CoCreateInstance(CLSID_iTunesApp, nullptr, CLSCTX_LOCAL_SERVER, IID_IiTunes, (PVOID*)&iITunes);
		
		if(hRes==S_OK && iITunes!=nullptr)
		{
			IITLibraryPlaylist* mainLibrary = nullptr;
			iITunes->get_LibraryPlaylist(&mainLibrary);
			
			mainLibrary->get_Tracks(&trackCollection);
			
			long length = 0;
			trackCollection->get_Count(&length);
			for(long i=1; i<=length; i++)
			{
				IITTrack* itunes_track = nullptr;
				trackCollection->get_Item(i, &itunes_track);
				
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
					long track_id = 0;
					BSTR track_title = nullptr;
					BSTR track_artist = nullptr;
					BSTR track_album = nullptr;
					BSTR track_album_artist = nullptr;
					long track_number = 0;
					
					IITFileOrCDTrack* itunes_file_track = nullptr;
					itunes_track->QueryInterface<IITFileOrCDTrack>(&itunes_file_track);
					
					itunes_track->get_TrackDatabaseID(&track_id);
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
					
					Track track((String)""+track_id, title, artist, album, album_artist, (unsigned int)track_number);
					library.add(track);
				}
			}
		}
		else
		{
			throw std::exception("error initializing itunes");
		}
	}
}
