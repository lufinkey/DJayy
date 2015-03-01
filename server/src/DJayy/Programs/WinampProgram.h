
#pragma once

#include "FolderLoadInterface.h"
#include <windows.h>

namespace DJayy
{
	class WinampProgram : public FolderLoadInterface
	{
	public:
		WinampProgram();

		virtual void load() override;

		virtual Track getTrackByTrackID(const String&track_id) const override;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const override;
		
	protected:
		bool isStopped();
		String getWinampPath();

	private:
		HWND whwnd;
	};
}
