#include "UserRatings.h"
#include "SongRating.h"
#include "Cluster.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
int printPredict(char *outputfile, vector<UserRatings> &users, vector<SongRating> &songs);
bool containsBlankLine(string line);
int countLines(char *filename);
int readSongFile(char *song_filename, vector<SongRating> &songs);
int readRatingsFile(char *rating_filename, vector<UserRatings> &users, int num_songs);
int printSimArray(char *outputfile, vector<vector<double> > simArray);
int printCluster(char *outputfile, Cluster &c);
int printMerged(char *outputfile, vector<pair<double,string> > &merged);
