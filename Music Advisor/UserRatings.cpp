#include "UserRatings.h"
#include "SongRating.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;


/*
These are the memeber functions of the class UserRatings below 
*/ 
// Calculates standard deviation for the object based on its scores, being careful not to include rating of 0 in calculation
// NOTE: calculateMean() must be called on the object before this is called on the object!!
void UserRatings::calculateStdDev()
{
	double sum = 0.0;
	int size = 0;
	
	for(unsigned int i = 0; i < ratings.size(); i++)
	{
		if(ratings[i] != 0)
		{
		//cout << "SUMMING : " << ratings[i] << endl;
		sum += (ratings[i] - mean) * (ratings[i] - mean);
		size++;
		}
	}
	//Lets check to make sure we won't divide by 0...
	if(size == 1 || size == 0)
	{		
		undefSTD = true;
		return;
	}
	// formula for standard deviation once we summed up the values
	stdDev = sqrt(sum / (size-1));
	//cout << "STDev " << stdDev << endl;

}


// Calculates mean for the object but is careful not to take 0 in account for the calculation
void UserRatings::calculateMean()
{
	double sum = 0, size = 0;

	for(unsigned int i = 0; i < ratings.size(); i++)
	{
		if(ratings[i] != 0)
		{
		//cout << "ADDING " << ratings[i] << endl;
		sum += ratings[i];
		size++;
		}
	}
	

	if(!ratings.size() || size == 0)
	{
		undefM = true;
	}

	
	mean = sum / size;
	//cout << "MEAN = " << mean << endl;

}
// Calculates zscore for the object NOTE: must be called after the two calls to calculate mean and stdev
// Accepts parameter of the z score to calculate on the given ith rating NOTE MUST BE IN ORDER TO MAINTAIN ORDER
void UserRatings::calculateZScore(int i)
{

	if(ratings[i] == 0)
	  {
	    undefZ.push_back(true);
	    zscore.push_back(0.0);
	    return;
	  }

	double result = (ratings[i] - mean)/stdDev;
	//cout << "ZSCORE = " << result << endl;
	undefZ.push_back(false);	
	zscore.push_back(result);
	


}

void UserRatings::addRating(int rating)
{
   ratings.push_back(rating); 
   if(rating == 0)
   {
    hasRanked.push_back(false);
   } else{
     hasRanked.push_back(true);
   }
}



