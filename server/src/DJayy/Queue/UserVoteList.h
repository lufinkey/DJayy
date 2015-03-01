
#pragma once

#include "../../Util/ArrayList.h"
#include "UserVote.h"

namespace DJayy
{
	class UserVoteList
	{
	public:
		UserVoteList();
		
		String toJson() const;
		void clear();
		
		signed char vote(const String&user_id, signed char vote);
		signed char getVote(const String&user_id) const;
		long long sum() const;
		
	private:
		ArrayList<UserVote> votes;
	};
}
