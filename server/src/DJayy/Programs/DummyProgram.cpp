
#include "DummyProgram.h"

namespace DJayy
{
	ArrayList<QueueTrack> DummyProgram::getQueue()
	{
		QueueTrack track1;
		track1.id = "aa3";
		track1.title = "Power";
		track1.artist = "Kanye West";
		track1.album = "My Beautiful Dark Twisted Fantasy";
		track1.votes = 0;

		QueueTrack track2;
		track2.id = "bc2";
		track2.title = "Somatic Serenade";
		track2.artist = "Bluetech";
		track2.album = "Matt please add album name";
		track2.votes = 0;

		QueueTrack track3;
		track3.id = "7e2";
		track3.title = "Kick the Rock!";
		track3.artist = "Hunnid-P";
		track3.album = "Sonic Adventure 2 Multi-Dimensional Original Soundtrack";
		track3.votes = 0;

		ArrayList<QueueTrack> tracks;
		tracks.add(track1);
		tracks.add(track2);
		tracks.add(track3);
		return tracks;
	}
}
