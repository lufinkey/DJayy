
#pragma once

#include "../../Util/String.h"

namespace DJayy
{
	class UserVote
	{
	public:
		String user_id;
		signed char vote;
		
		UserVote();
		UserVote(const String&user_id, signed char vote);
		
		bool isNull() const;
		String toJson() const;
	};
}
