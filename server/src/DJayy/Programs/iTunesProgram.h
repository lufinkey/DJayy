
#pragma once

#include "../ProgramInterface.h"

#include <iTunesCOMInterface.h>

namespace DJayy
{
	class iTunesProgram : public ProgramInterface
	{
	public:
		iTunesProgram();
		virtual ~iTunesProgram();

		virtual void loadLibrary() override;
		
	private:
		IiTunes *iITunes;
		IITTrackCollection* trackCollection;
	};
}
