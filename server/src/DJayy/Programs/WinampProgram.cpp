
#define _CRT_SECURE_NO_WARNINGS

#include "WinampProgram.h"
#include <Psapi.h>

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
		//
	}
	
	void WinampProgram::load()
	{
		FolderLoadInterface::load();
		whwnd=FindWindow("Winamp v1.x",NULL);
	}
	
	Track WinampProgram::getTrackByTrackID(const String&track_id) const
	{
		return Track();
	}
	
	TrackCollection WinampProgram::search(const String&query, size_t startIndex, size_t endIndex) const
	{
		return TrackCollection();
	}
	
	bool WinampProgram::isStopped()
	{
		int ret=SendMessage(whwnd,WM_USER, 0, 104);
		if(ret != 1 && ret != 3)
		{
			return true;
		}
		return false;
	}
	
	String WinampProgram::getWinampPath()
	{
		DWORD processID;
		GetWindowThreadProcessId(whwnd,&processID);
		HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
		char buffer[FILENAME_MAX];
		GetModuleFileNameEx(processHandle,NULL,buffer,FILENAME_MAX);
		return buffer;
	}
}
