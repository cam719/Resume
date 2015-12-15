/*
 * PA1.h
 *
 *  Created on: Sep 4, 2014
 *      Author: x43
 */

#ifndef PA2_H_
#define PA2_H_
#include "SongRating.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using std::vector;
using std::ifstream;
using std::string;
using std::ofstream;
using std::cout;
using std::endl;

typedef int error; 

class UserRatings {


public:
UserRatings()  {}
~UserRatings()  {}


inline vector<int> getRatings() const {return ratings;}
inline int getRating(int index) const {return ratings[index];}
inline double getMean() const {return mean;}
inline double getSTD() const {return stdDev;}
inline double getZScore(unsigned int index) const {return zscore[index];}
inline bool invalidMean() const {return undefM;}
inline bool invalidSTD() const {return undefSTD;}
inline bool invalidZ(unsigned int index) const {return undefZ[index];}
inline bool hasRated(unsigned int index) const {return hasRanked[index];}
inline void replaceRating(int i, int val) { ratings[i] = val;}
inline void replaceZ(int i, double val) { zscore[i] = val;}
void addRating(int rating);




inline void deleteRating(int i){
//cout << "!!!!!TEST " << endl;
//cout << "!!!!!I BEFORE " << i << endl;
ratings.erase(ratings.begin()+i);
hasRanked.erase(hasRanked.begin()+i);
//cout << "!!!!!I AFTER " << i << endl;
}
void calculateMean();
void calculateStdDev();
void calculateZScore(int i);

private:

  bool undefM, undefSTD;
  double mean;       
  double stdDev;  
  vector <double> zscore;
  vector <bool> undefZ;
  vector <bool> hasRanked;
  vector<int> ratings;

};




#endif /* PA1_H_ */
