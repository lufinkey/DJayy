
#pragma once

#include "../ProgramInterface.h"

namespace DJayy
{
	class DummyProgram : public ProgramInterface
	{
	public:
		DummyProgram();

		virtual void load() override;
		
		virtual Track getTrackByTrackID(const String&track_id) const override;
		virtual TrackCollection search(const String&query, size_t startIndex, size_t endIndex) const override;
		
	private:
		TrackCollection library;
	};
}
