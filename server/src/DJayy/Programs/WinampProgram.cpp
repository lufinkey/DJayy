
#include "WinampProgram.h"
#include "WinampChecker.h"
#include <iostream>

namespace DJayy
{
	WinampProgram::WinampProgram(WebServer*server, const String&root, const ArrayList<String>&fileExtensions) : FolderLoadInterface(server, root, fileExtensions)
	{
		checker = new WinampChecker(this);
		whwnd = nullptr;
	}

	WinampProgram::~WinampProgram()
	{
		delete checker;
	}
	
	void WinampProgram::load()
	{
		std::cout << "starting winamp..." << std::endl;
		system("start winamp");
		std::cout << "winamp started" << std::endl;
		FolderLoadInterface::load();
		while(whwnd==nullptr)
		{
			whwnd=FindWindow("Winamp v1.x",NULL);
		}
		checker->start();
	}
	
	Track WinampProgram::getTrackByTrackID(const String&track_id) const
	{
		return FolderLoadInterface::getTrackByTrackID(track_id);
	}
	
	TrackCollection WinampProgram::search(const String&query, size_t startIndex, size_t endIndex) const
	{
		return FolderLoadInterface::search(query, startIndex, endIndex);
	}
}
