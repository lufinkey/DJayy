
#pragma once

#include "FolderLoadInterface.h"
#include <windows.h>

namespace DJayy
{
	class WinampChecker;
	
	class WinampProgram : public FolderLoadInterface
	{
		friend class WinampChecker;
	public:
		WinampProgram(WebServer*server, const String&musicRoot, const ArrayList<String>&fileExtensions);
		virtual ~WinampProgram();

		virtual void load() override;

		virtual Track getTrackByTrackID(const String&track_id) const override;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const override;

	private:
		HWND whwnd;
		WinampChecker* checker;
	};
}
