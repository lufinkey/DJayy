
#include "WinampChecker.h"
#include <Psapi.h>

namespace DJayy
{
	void WinampCheckerThread(void*data)
	{
		WinampChecker*checker = (WinampChecker*)data;
		while(checker->running)
		{
			if(checker->isStopped())
			{
				checker->nextTrack();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
	
	WinampChecker::WinampChecker(WinampProgram*program)
	{
		WinampChecker::program = program;
		thread = nullptr;
		running = false;
	}

	WinampChecker::~WinampChecker()
	{
		if(running)
		{
			stop();
		}
	}
	
	void WinampChecker::start()
	{
		if(!running)
		{
			thread = new std::thread(WinampCheckerThread,this);
		}
	}
	
	void WinampChecker::stop()
	{
		if(running)
		{
			running = false;
			thread->join();
			delete thread;
			thread = nullptr;
		}
	}
	
	bool WinampChecker::isStopped()
	{
		int ret=SendMessage(program->whwnd,WM_USER, 0, 104);
		if(ret != 1 && ret != 3)
		{
			return true;
		}
		return false;
	}
	
	String WinampChecker::getWinampPath()
	{
		DWORD processID;
		GetWindowThreadProcessId(program->whwnd,&processID);
		HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
		char buffer[FILENAME_MAX];
		GetModuleFileNameEx(processHandle,NULL,buffer,FILENAME_MAX);
		return buffer;
	}
	
	void WinampChecker::nextTrack()
	{
		QueueTrack queueTrack = program->getQueue().next();
		if(!queueTrack.isNull())
		{
			Track track = program->getTrackByTrackID(queueTrack.track_id);
			if(!track.isNull())
			{
				//TODO send notification that next track is happening
				String winampPath = getWinampPath();
				system("\"" + winampPath + "\" \"" + program->getRootFolder() + '/' + track.path + "\"");
			}
		}
	}
}
