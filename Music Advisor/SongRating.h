/*
 * PA1.h
 *
 *  Created on: Sep 4, 2014
 *      Author: x43
 */

#ifndef PA1_H_
#define PA1_H_
#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::ifstream;
using std::string;
using std::ofstream;
using std::cout;
using std::endl;

typedef int error; 

class SongRating {


public:
SongRating()  
{
	currentK = -1;
}
~SongRating()  {}

inline string getTitle() const {return title;}
inline vector<double> getRatings() const {return ratings;}
inline double getRating(int i) const {return ratings[i];}
inline double getMean() const {return mean;}
inline double getSTD() const {return stdDev;}
inline bool invalidMean() const {return undefM;}
inline bool invalidSTD() const {return undefSTD;}
inline void setTitle(string new_value) {title = new_value;}
inline int getK() const {return currentK;}
inline void setK(int val) {currentK = val;}
inline void addRating(double rating){ratings.push_back(rating);}
inline int ratingsSize() const {return ratings.size();}
void calculateMean();
void calculateStdDev();
bool containsBlankLine(string line);
bool operator==(const SongRating &other) const {return this->getTitle() == other.getTitle() && this->ratings == other.ratings;}
SongRating( const SongRating& other ) :
     currentK(other.currentK), undefM(other.undefM), undefSTD(other.undefSTD), stdDev(other.stdDev), title(other.title), ratings(other.ratings)
  {}

private:

  int currentK;
  bool undefM, undefSTD;
  double mean;       
  double stdDev;  
  string title;
  vector<double> ratings;

};



#endif /* PA1_H_ */
