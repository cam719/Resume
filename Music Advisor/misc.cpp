#include "UserRatings.h"
#include "SongRating.h"
#include "misc.h"
#include <math.h>

// Miscelaneaous functions go here that dont belong to a class

		


vector<vector<double> > calcSongSim(vector<SongRating> &songs, int colSize)
{
	int size = songs.size();
	vector<vector<double> > sim(size, vector<double>(size));

	for(unsigned int i = 0; i < songs.size(); i++)
	   {
	   for(unsigned int k = 0; k < songs.size(); k++)
	      {

		double sum = 0;
		for(int j = 0; j < colSize; j++)
		{
		 
		  sum += songs[i].getRating(j) * songs[k].getRating(j);
	
		}
			
		sim[i][k] = sum;
	
	      }
	   }

return sim;
}

vector<vector<double> > calcUserSim(vector<UserRatings> &users, int colSize)
{
	int size = users.size();
	vector<vector<double> > sim(size, vector<double>(size));

	for(unsigned int i = 0; i < users.size(); i++)
	   {
	   for(unsigned int k = 0; k < users.size(); k++)
	      {

		double sum = 0;
		for(int j = 0; j < colSize; j++)
		{
		 
		  sum += users[i].getZScore(j) * users[k].getZScore(j);
		 
		}
			
		sim[i][k] = sum;
	
	      }
	   }

return sim;
}





// removes users that only ranks songs the same
void removeUncpUsers(vector<UserRatings> &users)
{
	vector<int> ratings;
	for(unsigned int i = 0; i < users.size(); i++)
	   {
	     // get the ratings for this user then check to see if they are unique
	     ratings = users[i].getRatings();
	     bool cond = hasUniqueRatings(ratings);
	    //if the ratings for the user are not unique then we will delete the user because this is defined as uncooperative
	     if(!cond)
	     {
		users.erase(users.begin()+i);
		i--; // no f**king clue why you have to do this, but if u don't deleting doesn't 
	     }
	    
	   }

}


// hasUniqueRatings checks to make sure the ratings vector has more than one rating asociated with it, not counting the 0
// Returns false if the ratings vector does not have more than 1 unique rating, meaning they are all the same

bool hasUniqueRatings(vector<int> &ratings)
{
	int uniqueRating = -1, numUniqueRatings = 0;
	for(unsigned int i = 0; i < ratings.size(); i++)
	{
	  if(ratings[i] != 0 && ratings[i] != uniqueRating)
	    {
	     uniqueRating = ratings[i];
	     numUniqueRatings++;
	    }
	
	}

	// If we have observed 0 or 1 unique value then we return false because it does not have unique ratings
	if(numUniqueRatings == 0 || numUniqueRatings == 1)
	{
	 return false;
	}
	else
	{
	 return true;
	}
}


/* calculates the mean, stdev, and zscores for the users, 
* and then copies the scores over to the song object, corresponding to the rows
*/
int rankSongs(vector<UserRatings> &users, vector<SongRating> &songs)
{

	//calculate mean and std first for every USER object

	for(unsigned int i = 0; i < users.size(); i++)
	{
	      users[i].calculateMean();
	      users[i].calculateStdDev();

	}
	// calculate the zscore for the ith song
	for(unsigned int i = 0; i < songs.size(); i++)
	{
	   // For every user j, calculate the zscore for the ranking corresponding to the ith song for the user
	   for(unsigned int j = 0; j < users.size(); j++)
	    {   
	      users[j].calculateZScore(i);
	    } 
	}
	
	return 0;
}



void deleteSong(int i, vector<UserRatings> &users)
{
 for(unsigned int j = 0; j < users.size(); j++)
{
  users[j].deleteRating(i); 
}

}

//Removes all songs with 0's for ratings
void removeUnrankedSongs(vector<UserRatings> &users, vector<SongRating> &songs)
{

//cout << "ENTERING UNRAKING OF SONGS" << endl;
for(unsigned int i = 0; i < songs.size(); i++)
{
 unsigned int numZeros = 0;
 for(unsigned int j = 0; j < users.size(); j++)
    {
	if(users[j].getRating(i) == 0)
	{
	numZeros++;
	}
    }


//cout << "NUMBER OF ZEROS = " << numZeros << " NUM SONGS " << songs.size() << endl;
if(numZeros == users.size())
	{
	//cout << "DELETING SONG " << i << endl;
	deleteSong(i, users);
	songs.erase(songs.begin()+i);
	i--;
	}
}
}

double predictRating(unsigned int user, int song, vector<vector<double> > sims, vector<UserRatings> &users)
{

double currentMax = -10000;
vector<int> most; // stores index of most common users

//IN 2D example make sure i!= user!!!!! else its fine to place in most common users
for(unsigned int i = 0; i < sims.size(); i++)
{

//cout << "SIMS = " << sims[user][i] << "!!! and hasrated = " << users[i].hasRated(song) << "AND currentmax - current = " << currentMax << endl;
  if(sims[user][i] > currentMax && users[i].hasRated(song) && i != user)
    {
	most.clear();
	currentMax = sims[user][i];
	//Push back the most simular user
//	cout << "ADDING i in if " << endl;	
	most.push_back(i);
    }
  else if(currentMax == sims[user][i]  && users[i].hasRated(song) && i != user)
   {
 //   cout << "ADDING i in else if" << endl;
    most.push_back(i);
   }
  else if(((currentMax - sims[user][i]) <= 0.0000001) && i != user && users[i].hasRated(song))
  {
  // currentMax = sims[user][i];
 //  cout << "ITS ONE ADDING " << i << endl;
   most.push_back(i);
  }


}

double sum = 0;
for(unsigned int i = 0; i < most.size(); i++)
{

int u = most[i];
//cout << "MOST USER z = " << most[i] << "AND Z SCORE = " << users[u].getZScore(song) << " MEAN/STD = " << users[user].getMean() << " " << users[user].getSTD()  << endl;
sum += users[u].getZScore(song);

}
// Calculate the avg z score for the most common users, then multiply this 
double avgZ = sum / most.size();

//PA6 we dont un-normalize
//double result = avgZ * users[user].getSTD();
//result += users[user].getMean();

//cout << "AVRG Z SCORE = " << avgZ << endl; 

//cout << "RESULT = " << floor(result+0.5) << endl; 
return avgZ;
}


void replaceZeros(vector<UserRatings> &users, vector<SongRating> &songs, vector<vector<double> > simArray)
{

for(unsigned int i = 0; i < songs.size(); i++)
{
	for(unsigned int j = 0; j < users.size(); j++)
	{
	  if(users[j].getRating(i) == 0)
	   {
	     //cout << "REPLACING 0 for user " << j << "SONG " << i << endl;
	     double z = predictRating(j, i, simArray, users);
	     users[j].replaceZ(i, z);
	    // cout << "PREDICTED " << num << endl;
	   }
	}
}

}

// Copies over all the zscores from UserObject after they have been predictied

void initSongs(vector<SongRating> &songs, vector<UserRatings> &users)
{
	for(unsigned int i = 0; i < songs.size(); i++)
	{
		for(unsigned int j = 0; j < users.size(); j++)
		{
			double z = users[j].getZScore(i);
			songs[i].addRating(z);

		}
	}
}

// Eucelidean distance
double eDistance(const vector <double> &a, const vector<double> &b)
{
	double result = 0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		//cout << "DEBUG: ai - bi = " << a[i] << "-" << b[i] << endl;
		result += ((a[i] - b[i]) * (a[i] - b[i]));
	}

	return sqrt(result);
}

void initClusters(vector<SongRating> &songs, vector<Cluster> &clusters, int k)
{
	for(int i = 0; i < k; i++)
	{
		clusters.push_back(Cluster(songs[i].getRatings()));
	}

}

void kMeans(vector<SongRating> &songs, vector<Cluster> &clusters)
{
	// while(iteration < 10)
	//for every song measure the distance from cluster, 
		// update a closest vector that holds the postion of the cluster j
		// delete the current cluster from the song object if iteration != 0
		// set the new current cluster from the song object
	// update the cluster object average

	int iteration = 0;

	while(iteration < 10)
	{
		for(unsigned int i = 0; i < songs.size(); i++)
		{
			double smallest = 10000000000;
			vector<int> closest;
			for(unsigned int j = 0; j < clusters.size(); j++)
			{
				double current = eDistance(songs[i].getRatings(), clusters[j].getAvgs());
				if(current < smallest)
				{
					smallest = current;
					closest.clear();
					closest.push_back(j);
				}
			//	cout << "SONG " << i << " cluster " << j << "distance = " << eDistance(songs[i].getRatings(), clusters[j].getAvgs()) << endl;
				
			}
			//cout << "Iteration =" << iteration << endl;
			//cout << "Closest for song " << i << "is cluster " << closest[0] << endl;
			int c = closest[0];
			if(iteration != 0 && c != songs[i].getK())
			{
			//	cout << "DELETING ";
				int currentC = songs[i].getK(); // get the current cluster the song is in so we can delete it
				//cout << "currentC = " << currentC << endl;
				clusters[currentC].deleteSong(songs[i]);
				songs[i].setK(c);
				clusters[c].addSong(songs[i]);
			}
			else if(iteration == 0)
			{
				songs[i].setK(c);
				clusters[c].addSong(songs[i]);

			}

		}

		for(unsigned int i = 0; i < clusters.size(); i++)
		{
			clusters[i].calculateAvg();
		}

		iteration++;
	}

}
