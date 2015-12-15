#include <stdlib.h>
#include <iostream> 
#include <string>
#include <ostream>
#include "UserRatings.h"
#include "misc.h"
#include "FileIO.h"
#include "Cluster.h"


using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;


int main(int argc, char* argv[])
{

	if(argc < 6)
	{
		std::cerr << "ERROR: Usage not correct USAGE: " << argv[0] << " <Song filename> <Ratings filename> <Number of clusters> <output file> <songs1,...,song1" << endl;
		return -1;
	}
	unsigned int k = atoi(argv[3]);
	//unsigned int n = atoi(argv[4]);
	vector<int> ratings, indices;
	int numSongs = 0, numRatings = 0;
	vector<UserRatings> users;
	vector<SongRating> songs;
	vector<Cluster> clusterCenter;
	vector<pair<double,string> > merged;
	vector<vector<pair<double,string> > > all;

	//cout << "K = " << k << " N = " << n << endl;

	
		
	int sLines=0, rLines = 0;
	if((sLines = countLines(argv[1])) == -1)
	{
	 std::cerr << "ERROR reading songs" << endl;
	 return -1;
	}
	if((rLines = countLines(argv[2])) == -1)
	{
	 std::cerr << "ERROR reading ratings" << endl;
	 return -1;
	}

	if(sLines != rLines)
	{
	        std::cerr << "ERROR DIFFERENT AMOUT OF LINES. EXITING" << endl;
		return -1;
	}


	numSongs = readSongFile(argv[1], songs);


	if(numSongs == -1 || songs.size() == 1)
	{
		std::cerr << "ERROR in songs file" << endl;
		return -1;
	}
		
	numRatings = readRatingsFile(argv[2], users, songs.size());
	
	if(numRatings == -1)
	{
		return -1;
	}
	
	//removes uncooperative users then rank the zscore for each user and averages users scores's persong for each different user
	removeUncpUsers(users);
	if(users.size() == 0)
	{
	  std::cerr << "ERROR: no cooperative users" << endl;
	  return -1;
	}
	if(users.size() == 1)
	{
	  std::cerr << "ERROR: only 1 cooperative user" << endl;
	  return -1;
	}
	
	// Calculate zscores then copy them over to the song object 
	removeUnrankedSongs(users,songs);	
	rankSongs(users, songs);

	// Check to make sure k doesn't exceed song size
	if(k == 0)
	{
		std::cerr << "Error K cannot be 0!!!" << endl;
		return -1;
	}
	if(k > songs.size())
	{
		std::cerr << "Error K cannot be bigger than the number of songs!!!" << endl;
		return -1;	
	}


	/*cout << "NEW RATINGS = " << endl;
	for(unsigned int i = 0; i < songs.size(); i++)
	{
	for(unsigned int j = 0; j < users.size(); j++)
	{
	 cout << users[j].hasRated(i) << " ";
	}
	cout << endl;
		
	}*/

	//Calculate simularity matricies for both songs and users, according to the zscores
	//vector<vector<double> > songSim = calcSongSim(songs, users.size());
	vector<vector<double> > userSim = calcUserSim(users, songs.size());


	
	
	
	replaceZeros(users, songs, userSim);
	initSongs(songs, users);

	//initatie cluster object
	initClusters(songs, clusterCenter, k);

	/*cout << "DEBUG AFTER INITIALIZING DEBUG" << endl;
	clusterCenter[0].addSong(songs[0]);
	clusterCenter[0].addSong(songs[3]);
	clusterCenter[0].caclulateAvg();
	clusterCenter[1].caclulateAvg(); */


	kMeans(songs, clusterCenter);
	int status = 0;
	//status = printCluster(argv[5], clusterCenter[n-1]);
	
	if(status == -1)
	{
		return -1;
	}
	for(int i = 5; i < argc; i++)
	{
		//cout << argv[i] << " " << endl;
		indices.push_back(atoi(argv[i]));
	}

	for(unsigned int i = 0; i < indices.size(); i++)
	{	
		unsigned int num = indices[i];
		if((num-1) < 0 || (num-1) >= songs.size())
		{
			std::cerr << "INVALID SONG LIKED " << endl;
			return -1;
		}
		int k = songs[num-1].getK();
		vector<pair<double,string> > temp = clusterCenter[k].calcPairs(songs[num-1]);
		all.push_back(temp);


	}
	//vector<pair<double,string> > temp = clusterCenter[0].calcPairs(songs[0]);
	
	for(unsigned int i = 0; i < all.size(); i++)
	{
		vector<pair<double,string> > temp = all[i];
		merged.reserve(temp.size() + merged.size());
		merged.insert(merged.end(), temp.begin(), temp.end());
		


	}
	sort(merged.begin(), merged.end());
	std::reverse(merged.begin(),merged.end());
	printMerged(argv[4], merged);
	return 0;
}
