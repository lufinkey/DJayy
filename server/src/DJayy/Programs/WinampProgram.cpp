
#define _CRT_SECURE_NO_WARNINGS

#include "WinampProgram.h"
#include "WinampChecker.h"
#include <iostream>

namespace DJayy
{
	String extensions[] = {(String)"mp3"};
#ifdef _WIN32
	#define HOMEPATH getenv("HOMEPATH")
#else
	#define HOMEPATH getenv("HOME")
#endif

	WinampProgram::WinampProgram() : FolderLoadInterface((String)"" + HOMEPATH + "/Music", ArrayList<String>(extensions,1))
	{
		checker = new WinampChecker(this);
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
		whwnd=FindWindow("Winamp v1.x",NULL);
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
