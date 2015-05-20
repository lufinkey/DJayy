
#include "FolderLoadInterface.h"
#include <dirent.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/toolkit/tpropertymap.h>

namespace DJayy
{
	FolderLoadInterface::FolderLoadInterface(WebServer*server, const String&root, const ArrayList<String>& fileExtensions) : ProgramInterface(server)
	{
		FolderLoadInterface::root = root;
		FolderLoadInterface::fileExtensions = fileExtensions;
		library = nullptr;
		current_track_id = 0;
	}

	FolderLoadInterface::~FolderLoadInterface()
	{
		if(library != nullptr)
		{
			sqlite3_free(library);
		}
	}
	
	void FolderLoadInterface::load()
	{
		bool load_folder_inital = false;
		if(!file_exists("music-library.db"))
		{
			load_folder_inital = true;
		}
		int ret = sqlite3_open("music-library.db", &library);
		if(ret != SQLITE_OK)
		{
			std::cout << "error while creating committing database: " << ret << ", " << sqlite3_errmsg(library) << std::endl;
			return;
		}
		if(load_folder_inital)
		{
			sqlite3_stmt* stmt = nullptr;
			String query = "CREATE TABLE music("
				"track_id int not null unique,"
				"title text(30),"
				"artist text(30),"
				"album text(30),"
				"album_artist text(30),"
				"track_num int,"
				"path text(1024),"
				"primary key(track_id));";
			sqlite3_prepare_v2(library,query,(int)query.length(),&stmt, nullptr);
			int ret = sqlite3_step(stmt);
			while(ret == SQLITE_OK)
			{
				int ret = sqlite3_step(stmt);
			}
			if(ret != SQLITE_DONE)
			{
				std::cout << "error while creating committing database: " << ret << ", " << sqlite3_errmsg(library) << std::endl;
			}
			sqlite3_finalize(stmt);
			loadFolder("");
			
			stmt = nullptr;
			query = "commit;";
			sqlite3_prepare_v2(library,query,(int)query.length(),&stmt, nullptr);
			ret = sqlite3_step(stmt);
			while(ret == SQLITE_OK)
			{
				int ret = sqlite3_step(stmt);
			}
			if(ret != SQLITE_DONE)
			{
				std::cout << "error while creating committing database: " << ret << ", " << sqlite3_errmsg(library) << std::endl;
			}
			sqlite3_finalize(stmt);
		}
	}
	
	void FolderLoadInterface::loadFolder(const String&path)
	{
		String fullpath;
		if(path.length() == 0)
		{
			fullpath = root;
		}
		else
		{
			fullpath = root + '/' + path;
		}
		DIR*dir = opendir(root + '/' + path);
		if(dir==NULL)
		{
			return;
		}
		struct dirent *entry = readdir(dir);
		while (entry != NULL)
		{
			String name = entry->d_name;
			if(!name.equals(".") && !name.equals(".."))
			{
				switch(entry->d_type)
				{
					case DT_REG:
					{
						String filepath;
						if(path.length() == 0)
						{
							filepath = name;
						}
						else
						{
							filepath = path + '/' + name;
						}
						loadFile(filepath);
					}
					break;
					
					case DT_DIR:
					{
						String folderpath;
						if(path.length() == 0)
						{
							folderpath = name;
						}
						else
						{
							folderpath = path + '/' + name;
						}
						loadFolder(folderpath);
					}
					break;
				}
			}
			entry = readdir(dir);
		}
		closedir(dir);
	}

	String FolderLoadInterface::real_escape_string(const String&str)
	{
		return str.replace("\"","\\\"");
	}
	
	void FolderLoadInterface::loadFile(const String&path)
	{
		size_t lastDotIndex = path.lastIndexOf('.');
		if(lastDotIndex != STRING_NOTFOUND)
		{
			String extension = path.substring(lastDotIndex+1, path.length());
			if(fileExtensions.contains(extension))
			{
				TagLib::FileRef f((const char*)(root + '/' + path));
				String title = f.tag()->title().toCString();
				if(title.equals(""))
				{
					size_t lastSlashIndex = path.lastIndexOf('/');
					if(lastSlashIndex == STRING_NOTFOUND)
					{
						lastSlashIndex = path.lastIndexOf('\\');
					}
					if(lastSlashIndex == STRING_NOTFOUND)
					{
						title = path.substring(0,lastDotIndex);
					}
					else
					{
						title = path.substring(lastSlashIndex+1, lastDotIndex);
					}
				}
				String artist = f.tag()->artist().toCString();
				String album = f.tag()->album().toCString();
				String album_artist;//TODO add loading of album artist somehow
				unsigned int track_num = f.tag()->track();
				
				sqlite3_stmt* stmt = nullptr;
				String query = (String)"insert into music (track_id,title,artist,album,album_artist,track_num,path) values("
					+ current_track_id + ",\"" + real_escape_string(title) + "\",\"" + real_escape_string(artist) + "\",\"" + real_escape_string(album) + "\",\"" + real_escape_string(album_artist) + "\"," + track_num + ",\"" + real_escape_string(path) + "\");";
				current_track_id++;
				sqlite3_prepare_v2(library,query,(int)query.length(),&stmt, nullptr);
				int ret = sqlite3_step(stmt);
				while(ret == SQLITE_OK)
				{
					int ret = sqlite3_step(stmt);
				}
				if(ret != SQLITE_DONE)
				{
					std::cout << "error while creating committing database: " << ret << ", " << sqlite3_errmsg(library) << std::endl;
				}
				sqlite3_finalize(stmt);
			}
		}
	}
	
	bool FolderLoadInterface::file_exists(const String& name)
	{
		struct stat buffer;
		return (stat(name, &buffer) == 0); 
	}
	
	const String& FolderLoadInterface::getRootFolder() const
	{
		return root;
	}
	
	Track FolderLoadInterface::getTrackByTrackID(const String&track_id) const
	{
		sqlite3_stmt* stmt = nullptr;
		String query = "select title, artist, album, album_artist, track_num, path from music where track_id = " + track_id + ";";
		sqlite3_prepare_v2(library,query,(int)query.length(),&stmt, nullptr);
		int ret = sqlite3_step(stmt);
		if(ret == SQLITE_ROW)
		{
			String title = (const char*)sqlite3_column_text(stmt,0);
			String artist = (const char*)sqlite3_column_text(stmt,1);
			String album = (const char*)sqlite3_column_text(stmt,2);
			String album_artist = (const char*)sqlite3_column_text(stmt,3);
			unsigned int track_num = (unsigned int)sqlite3_column_int(stmt,4);
			String path = (const char*)sqlite3_column_text(stmt,5);
			Track track(track_id,title,artist,album,album_artist,track_num);
			track.path = path;
			
			sqlite3_finalize(stmt);
			return track;
		}
		else
		{
			sqlite3_finalize(stmt);
			return Track();
		}
	}
	
	TrackCollection FolderLoadInterface::search(const String&searchQuery, size_t startIndex, size_t endIndex) const
	{
		TrackCollection tracks;
		if(startIndex == endIndex)
		{
			return tracks;
		}
		sqlite3_stmt* stmt = nullptr;
		String query = (String)"select track_id, title, artist, album, album_artist, track_num, path "
			+ "from music "
			+ "where upper(title) like \"%\" || upper(\"" + searchQuery + "\") || \"%\" "
			+ "or upper(artist) like \"%\" || upper(\"" + searchQuery + "\") || \"%\" "
			+ "or upper(album) like \"%\" || upper(\"" + searchQuery + "\") || \"%\" "
			+ "or upper(album_artist) like \"%\" || upper(\"" + searchQuery + "\") || \"%\";";
		sqlite3_prepare_v2(library,query,(int)query.length(),&stmt, nullptr);
		size_t matchCounter = 0;
		int ret = sqlite3_step(stmt);
		while(ret == SQLITE_ROW)
		{
			if(matchCounter >= startIndex)
			{
				String track_id = (String)"" + sqlite3_column_int(stmt,0);
				String title = (const char*)sqlite3_column_text(stmt,1);
				String artist = (const char*)sqlite3_column_text(stmt,2);
				String album = (const char*)sqlite3_column_text(stmt,3);
				String album_artist = (const char*)sqlite3_column_text(stmt,4);
				unsigned int track_num = (unsigned int)sqlite3_column_int(stmt,5);
				String path = (const char*)sqlite3_column_text(stmt,6);
				Track track(track_id,title,artist,album,album_artist,track_num);
				track.path = path;
				tracks.add(track);
			}
			matchCounter++;
			if(matchCounter >= endIndex)
			{
				sqlite3_finalize(stmt);
				return tracks;
			}
			else
			{
				ret = sqlite3_step(stmt);
			}
		}
		if(ret != SQLITE_DONE)
		{
			std::cout << "error while searching database: " << ret << ", " << sqlite3_errmsg(library) << std::endl;
		}
		sqlite3_finalize(stmt);
		return tracks;
	}
}
