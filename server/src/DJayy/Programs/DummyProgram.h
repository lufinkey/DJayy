
#pragma once

#include "../ProgramInterface.h"

namespace DJayy
{
	class DummyProgram : public ProgramInterface
	{
	private:
		ArrayList<QueueTrack> queue;
		
	public:
		DummyProgram();
		
		virtual ArrayList<QueueTrack> getQueue() override;
		virtual QueueTrack DummyProgram::getQueueTrack(const String&queue_id) const override;
		virtual void vote(const String&queue_id, const String&user_id, signed char vote) override;
	};
}
