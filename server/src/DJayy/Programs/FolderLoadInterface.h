
#pragma once

#include "../ProgramInterface.h"
#include <sqlite3.h>

namespace DJayy
{
	class FolderLoadInterface : public ProgramInterface
	{
	public:
		FolderLoadInterface(WebServer*server, const String&root, const ArrayList<String>& fileExtensions);
		virtual ~FolderLoadInterface();
		
		virtual void load() override;
		
		virtual Track getTrackByTrackID(const String&track_id) const;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const;

		const String& getRootFolder() const;
		
	protected:
		void loadFolder(const String&path);
		void loadFile(const String&path);
		bool file_exists(const String&path);
		
	private:
		String root;
		ArrayList<String> fileExtensions;
		sqlite3*library;
		unsigned long long current_track_id;
	};
}
