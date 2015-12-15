#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include "UserRatings.h"
#include <math.h> 
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;


void SongRating::calculateStdDev()
{
	double sdev = 0.0;
	double sum2 = 0.0;
	
	//Lets check to make sure we won't divide by 0...
	if(ratings.size() == 1 || ratings.size() == 0)
	{		
		undefSTD = true;
		return;
	}
	for(unsigned int i = 0; i < ratings.size(); i++)
	{
		sum2 = (ratings[i] - mean);
		sdev += sum2 * sum2;
	}
	

	
	stdDev = sqrt(sdev / (ratings.size()-1));
	
}

void SongRating::calculateMean()
{
	double sum = 0;

	for(unsigned int i = 0; i < ratings.size(); i++)
	{
		sum += ratings[i];
	}

	if(!ratings.size())
	{
		undefM = true;
	}

	
	mean = sum / ratings.size();
}

