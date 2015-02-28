
#pragma once

#include "../ProgramInterface.h"

namespace DJayy
{
	class DummyProgram : public ProgramInterface
	{
	public:
		DummyProgram();

		virtual void loadLibrary() override;
	};
}
