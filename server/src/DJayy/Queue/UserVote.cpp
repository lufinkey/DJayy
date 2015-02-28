
#include "UserVote.h"

namespace DJayy
{
	UserVote::UserVote()
	{
		vote = 0;
	}
	
	UserVote::UserVote(const String&user_id, signed char vote)
	{
		UserVote::user_id = user_id;
		UserVote::vote = vote;
	}
	
	bool UserVote::isNull() const
	{
		if(user_id.length() == 0)
		{
			return true;
		}
		return false;
	}

	String UserVote::toJson() const
	{
		return "{\"user_id\":\"" + user_id + "\",\"vote\":" + ((int)vote) + "}";
	}
}
