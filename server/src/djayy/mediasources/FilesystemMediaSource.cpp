
#include "FilesystemMediaSource.h"
#include "FilesystemPlayable.h"
#include <iostream>

namespace djayy
{
	FilesystemMediaSource::FilesystemMediaSource()
		: database(nullptr)
	{
		//
	}
	
	FilesystemMediaSource::~FilesystemMediaSource()
	{
		db_mutex.lock();
		if(database != nullptr)
		{
			sqlite3_close_v2(database);
			database = nullptr;
		}
		db_mutex.unlock();
	}
	
	bool FilesystemMediaSource::load(std::string* error)
	{
		//TODO prepare sqlite database, begin library refresh
		db_mutex.lock();
		int opened = sqlite3_open("music-library.db", &database);
		if(opened != SQLITE_OK)
		{
			if(error!=nullptr)
			{
				*error = "error while opening database: " + std::to_string(opened) + ": " + sqlite3_errmsg(database);
			}
			db_mutex.unlock();
			return false;
		}
		std::string query =
				"CREATE TABLE IF NOT EXISTS music("
					"track_id int not null unique,"
					"title text(30),"
					"artist text(30),"
					"album text(30),"
					"album_artist text(30),"
					"track_num int,"
					"path varchar(1024),"
					"primary key(track_id));";
		sqlite3_stmt* stmt = nullptr;
		int prepared = sqlite3_prepare_v2(database, query.c_str(), (int)query.length(), &stmt, nullptr);
		if(prepared != SQLITE_OK)
		{
			if(error!=nullptr)
			{
				*error = "error while creating creating music table: " + std::to_string(prepared) + ": " + sqlite3_errmsg(database);
			}
			if(stmt != nullptr)
			{
				sqlite3_finalize(stmt);
			}
			sqlite3_close_v2(database);
			database = nullptr;
			db_mutex.unlock();
			return false;
		}
		int stepped = sqlite3_step(stmt);
		while(stepped == SQLITE_OK)
		{
			stepped = sqlite3_step(stmt);
		}
		if(stepped != SQLITE_DONE)
		{
			if(error!=nullptr)
			{
				*error = "error while creating music table: " + std::to_string(stepped) + ", " + sqlite3_errmsg(database);
			}
			sqlite3_finalize(stmt);
			sqlite3_close_v2(database);
			database = nullptr;
			db_mutex.unlock();
			return false;
		}
		sqlite3_finalize(stmt);
		db_mutex.unlock();
		return true;
	}
	
	std::string FilesystemMediaSource::getSourceID() const
	{
		return "filesystem";
	}
	
	std::vector<TrackInfo> FilesystemMediaSource::search(const std::string& query)
	{
		db_mutex.lock();
		//TODO make sqlite database query
		db_mutex.unlock();
		return std::vector<TrackInfo>();
	}
	
	Playable* FilesystemMediaSource::getTrack(const std::string& track_id)
	{
		//TODO query sqlite database for track, return new FilesystemPlayable if track exists, otherwise return null
		if(!is_numeric(track_id))
		{
			return nullptr;
		}
		std::string query = "SELECT * FROM music WHERE track_id="+track_id;
		db_mutex.lock();
		sqlite3_stmt* stmt = nullptr;
		int prepared = sqlite3_prepare_v2(database, query.c_str(), (int)query.length(), &stmt, nullptr);
		if(prepared != SQLITE_OK)
		{
			if(stmt != nullptr)
			{
				sqlite3_finalize(stmt);
			}
			db_mutex.unlock();
			return nullptr;
		}
		int stepped = sqlite3_step(stmt);
		Playable* playable = nullptr;
		if(stepped==SQLITE_ROW)
		{
			TrackInfo trackInfo;
			trackInfo.source_id = getSourceID();
			trackInfo.track_id = std::to_string(sqlite3_column_int(stmt,0));
			trackInfo.title = (const char*)sqlite3_column_text(stmt,1);
			trackInfo.artist = (const char*)sqlite3_column_text(stmt,2);
			trackInfo.album = (const char*)sqlite3_column_text(stmt,3);
			trackInfo.album_artist = (const char*)sqlite3_column_text(stmt,4);
			trackInfo.genre = (const char*)sqlite3_column_text(stmt,5);
			trackInfo.track_num = (unsigned int)sqlite3_column_int(stmt,6);
			trackInfo.coverart_url = (const char*)sqlite3_column_text(stmt, 7);
			std::string filepath = (const char*)sqlite3_column_text(stmt, 8);
			playable = new FilesystemPlayable(filepath, this, trackInfo);
		}
		sqlite3_finalize(stmt);
		db_mutex.unlock();
		return playable;
	}
	
	bool FilesystemMediaSource::is_numeric(const std::string& num)
	{
		size_t num_length = num.length();
		for(size_t i=0; i<num_length; i++)
		{
			char c = num.at(i);
			if(c < '0' || c > '9')
			{
				return false;
			}
		}
		return true;
	}
}
