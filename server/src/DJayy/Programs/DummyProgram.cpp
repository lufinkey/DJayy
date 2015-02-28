
#include "DummyProgram.h"

namespace DJayy
{
	DummyProgram::DummyProgram()
	{
		QueueTrack track1;
		track1.queue_id = "01";
		track1.track_id = "aa3";
		track1.title = "Power";
		track1.artist = "Kanye West";
		track1.album = "My Beautiful Dark Twisted Fantasy";

		QueueTrack track2;
		track2.queue_id = "02";
		track2.track_id = "bc2";
		track2.title = "Somatic Serenade";
		track2.artist = "Bluetech";
		track2.album = "Matt please add album name";

		QueueTrack track3;
		track3.queue_id = "03";
		track3.track_id = "7e2";
		track3.title = "Kick the Rock!";
		track3.artist = "Hunnid-P";
		track3.album = "Sonic Adventure 2 Multi-Dimensional Original Soundtrack";

		queue.add(track1);
		queue.add(track2);
		queue.add(track3);
	}

	ArrayList<QueueTrack> DummyProgram::getQueue()
	{
		return queue;
	}
	
	QueueTrack DummyProgram::getQueueTrack(const String&queue_id) const
	{
		for(size_t i=0; i<queue.size(); i++)
		{
			const QueueTrack& track = queue.get(i);
			if(track.queue_id.equals(queue_id))
			{
				return track;
			}
		}
		return QueueTrack();
	}

	void DummyProgram::vote(const String&queue_id, const String&user_id, signed char vote)
	{
		for(size_t i=0; i<queue.size(); i++)
		{
			QueueTrack& track = queue.get(i);
			if(track.queue_id.equals(queue_id))
			{
				track.vote(UserVote(user_id,vote));
				return;
			}
		}
	}
}
