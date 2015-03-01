
#pragma once

#include "../ProgramInterface.h"

namespace DJayy
{
	class FolderLoadInterface : public ProgramInterface
	{
	public:
		FolderLoadInterface(const String&root, const ArrayList<String>& fileExtensions);
		
		virtual void load() override;
		
		virtual Track getTrackByTrackID(const String&track_id) const;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const;

		const String& getRootFolder() const;
		
	protected:
		void loadFolder(const String&path);
		void loadFile(const String&path);
		
	private:
		String root;
		ArrayList<String> fileExtensions;
		
		TrackCollection library;
	};
}
