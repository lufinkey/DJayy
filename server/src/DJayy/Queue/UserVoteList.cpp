
#include "UserVoteList.h"

namespace DJayy
{
	UserVoteList::UserVoteList()
	{
		//
	}
	
	String UserVoteList::toJson() const
	{
		String json = "[";
		size_t length = votes.size();
		size_t last = votes.size()-1;
		for(size_t i=0; i<length; i++)
		{
			json += votes.get(i).toJson();
			if(i != last)
			{
				json += ",";
			}
		}
		json += "]";
		return json;
	}
	
	void UserVoteList::clear()
	{
		votes.clear();
	}
	
	void UserVoteList::vote(const String&user_id, signed char vote)
	{
		size_t length = votes.size();
		for(size_t i=0; i<length; i++)
		{
			UserVote& usrVote = votes.get(i);
			if(usrVote.user_id.equals(user_id))
			{
				if(vote == 0)
				{
					votes.remove(i);
					return;
				}
				else if(vote == usrVote.vote)
				{
					votes.remove(i);
					return;
				}
				else
				{
					usrVote.vote = vote;
					return;
				}
			}
		}
		votes.add(UserVote(user_id,vote));
	}
	
	signed char UserVoteList::getVote(const String&user_id) const
	{
		size_t length = votes.size();
		for(size_t i=0; i<length; i++)
		{
			const UserVote& usrVote = votes.get(i);
			if(usrVote.user_id.equals(user_id))
			{
				return usrVote.vote;
			}
		}
		return 0;
	}
	
	long long UserVoteList::sum() const
	{
		long long total = 0;
		size_t length = votes.size();
		for(size_t i=0; i<length; i++)
		{
			total += votes.get(i).vote;
		}
		return total;
	}
}
