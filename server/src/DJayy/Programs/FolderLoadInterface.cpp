
#include "FolderLoadInterface.h"
#include <dirent.h>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/toolkit/tpropertymap.h>

namespace DJayy
{
	FolderLoadInterface::FolderLoadInterface(const String&root, const ArrayList<String>& fileExtensions)
	{
		FolderLoadInterface::root = root;
		FolderLoadInterface::fileExtensions = fileExtensions;
	}
	
	void FolderLoadInterface::load()
	{
		std::cout << "loading library from folder: " << root << std::endl;
		loadFolder("");
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
				Track track(path,title,artist,album,album_artist,track_num);
				track.path = path;
				library.add(track);
			}
		}
	}
	
	Track FolderLoadInterface::getTrackByTrackID(const String&track_id) const
	{
		return Track(); //TODO add quick searching
	}
	
	TrackCollection FolderLoadInterface::search(const String&query, size_t startIndex, size_t endIndex) const
	{
		return TrackCollection();
	}
}
