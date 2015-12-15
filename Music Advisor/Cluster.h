#ifndef Cluster_H_
#define Cluster_H_
#include "SongRating.h"
#include <vector>
#include <string>
#include <iostream> 
#include <algorithm>
#include <cmath>
using std::vector;
using std::ifstream;
using std::string;
using std::ofstream;
using std::cout;
using std::endl;
using std::pair;

class Cluster
{
	public:
		Cluster(vector<double> inc)
		{
			clusterAverge = inc;
			U = inc.size();
		}
		inline void addSong(SongRating song){clstrSongs.push_back(song);}
		inline double getAvg(int i){return clusterAverge[i];}
		inline vector<double> getAvgs() {return clusterAverge;}
		void print();
		void calculateAvg();
		double Distance(const vector <double> &a, const vector<double> &b);
		inline vector<SongRating> getSongs() {return clstrSongs;}
		void deleteSong(SongRating sObj);
		vector<pair<double,string> > calcPairs(SongRating sObj);

	private: 
		int U; // Number of cooperative users
		vector<double> clusterAverge;
		vector<SongRating> clstrSongs;
};

#endif
