
#include "QueueTrack.h"

namespace DJayy
{
	String QueueTrack::toJson() const
	{
		return "{\"queue_id\":\"" + queue_id + "\",\"track_id\":\"" + track_id + "\",\"title\":\"" + title + "\",\"artist\":\"" + artist + "\",\"album\":\"" + album + "\",\"votes\":" + getTotalVotes() + "}";
	}
	
	long long QueueTrack::getTotalVotes() const
	{
		long long totalVotes = 0;
		for(size_t i=0; i<votes.size(); i++)
		{
			totalVotes += votes.get(i).vote;
		}
		return totalVotes;
	}
	
	void QueueTrack::vote(const UserVote&vote)
	{
		for(size_t i=0; i<votes.size(); i++)
		{
			UserVote& usrVote = votes.get(i);
			if(usrVote.user_id.equals(vote.user_id))
			{
				if(vote.vote == 0)
				{
					votes.remove(i);
					return;
				}
				else if(vote.vote == usrVote.vote)
				{
					votes.remove(i);
					return;
				}
				else
				{
					usrVote.vote = vote.vote;
					return;
				}
			}
		}
		votes.add(vote);
	}
	
	signed char QueueTrack::getUserVote(const String&user_id) const
	{
		for(size_t i=0; i<votes.size(); i++)
		{
			const UserVote& usrVote = votes.get(i);
			if(usrVote.user_id.equals(user_id))
			{
				return usrVote.vote;
			}
		}
		return 0;
	}
}
