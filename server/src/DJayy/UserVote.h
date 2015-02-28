
#pragma once

#include "../Util/String.h"

namespace DJayy
{
	class UserVote
	{
	public:
		UserVote()
		{
			vote = 0;
		}

		UserVote(const String&user_id, signed char vote) : user_id(user_id), vote(vote)
		{
			//
		}

		String user_id;
		signed char vote;
	};
}
