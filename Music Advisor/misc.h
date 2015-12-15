#ifndef MISC_H_
#define MISC_H_


#include "UserRatings.h"
#include "SongRating.h"
#include "Cluster.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
void initClusters(vector<SongRating> &songs, vector<Cluster> &clusters, int k);
void removeUnrankedSongs(vector<UserRatings> &users, vector<SongRating> &songs);
void deleteSong(int i, vector<UserRatings> &users);
void removeUncpUsers(vector<UserRatings> &users);
int rankSongs(vector<UserRatings> &users, vector<SongRating> &songs);
bool hasUniqueRatings(vector<int> &ratings);
void deleteUser(vector<UserRatings> &users, int index);
vector<vector<double> > calcSongSim(vector<SongRating> &songs, int colSize);
vector<vector<double> > calcUserSim(vector<UserRatings> &users, int colSize);
double predictRating(unsigned int user, int song, vector<vector<double> > simArray, vector<UserRatings> &users);
void replaceZeros(vector<UserRatings> &users, vector<SongRating> &songs, vector<vector<double> > simArray);
void initSongs(vector<SongRating> &songs, vector<UserRatings> &users);
double eDistance(const vector <double> &a, const vector<double> &b);
void kMeans(vector<SongRating> &songs, vector<Cluster> &clusters);

#endif /* MISC_H_ */
