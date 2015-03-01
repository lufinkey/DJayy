
#pragma once

#include "WinampProgram.h"
#include <thread>

namespace DJayy
{
	class WinampChecker
	{
		friend void WinampCheckerThread(void*);
	public:
		WinampChecker(WinampProgram*program);
		virtual ~WinampChecker();

		virtual void start();
		virtual void stop();

	protected:
		bool isStopped();
		String getWinampPath();
		
		void nextTrack();
		
	private:
		WinampProgram* program;
		std::thread*thread;
		bool running;
	};
}
