
#pragma once

#include "../Util/ArrayList.h"
#include "../Util/String.h"
#include "UserVote.h"

namespace DJayy
{
	class QueueTrack
	{
	public:
		String queue_id;
		String track_id;
		String title;
		String artist;
		String album;

		ArrayList<UserVote> votes;

		String toJson() const;

		long long getTotalVotes() const;
		void vote(const UserVote&vote);
		signed char getUserVote(const String&user_id) const;
	};
}
