
#include "FileIO.h"
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;


int printMerged(char *outputfile, vector<pair<double,string> > &merged)
{
	ofstream output(outputfile);
	for(unsigned int i = 0; i < merged.size(); i++)
	{
		output << merged[i].second << endl;
		if(i == 19)
		{
			return 0;
		}
	}

	return 0;
}
int printCluster(char *outputfile, Cluster &c)
{

	ofstream output(outputfile);
	vector<SongRating> clst = c.getSongs();
	for(unsigned int i = 0; i < clst.size(); i++)
	{
		output << clst[i].getTitle() << endl;
	}

	return 0;

}

int printPredict(char *outputfile, vector<UserRatings> &users, vector<SongRating> &songs)
{

 	ofstream output(outputfile);

	if(!output)
	{
		std::cerr << "ERROR: failed to open file " << outputfile << endl;
		return -1;
	}

	for(unsigned int i = 0; i < songs.size(); i++)
	{
	for(unsigned int j = 0; j < users.size(); j++)
	{
	 output << users[j].getRating(i) << " ";
	}
	 output << endl;
		
	}

	return 0;

}

// prints NxN simularity matrix to given output file
int printSimArray(char *outputfile, vector<vector<double> > simArray)
{
	ofstream output(outputfile);

	if(!output)
	{
		std::cerr << "ERROR: failed to open file " << outputfile << endl;
		return -1;
	}


	for(unsigned int i = 0; i < simArray.size(); i++)
	{

		for(unsigned int j = 0; j < simArray.size(); j++)
		{

		 output << simArray[i][j] << " "; 
		}
	
		output << endl;
	}

	output.close();
	return 0;

}

/*
 * readRatingsFile() accepts a file name and then opens a file stream buffer
 * it then reads the input file line by line, putting each line in a string
 * buffer. Comments on error handling the stringbuffer below for specific errors
 */

int readRatingsFile(char *filename, vector<UserRatings> &users, int num_songs)
{
	int num, userCol = 0, num_users = 0;
	int line_num = 1;
	string line = "";
	ifstream input(filename);

	if(!input)
		{
			std::cerr << "ERROR: failed to open file " << filename << endl;
			return -1;
		}

	while(getline(input, line))
	{

	    // If we have a blank line then we probably hould exit because this isnt valid...
	    if(containsBlankLine(line) && line_num < num_songs)
	    {
	       std::cerr << "File: " << filename << " contains blank line on line number: " << line_num << endl;
	       return -1;

	    }
		// Make sure userCol is set to 0
	        userCol = 0;

		stringstream convert(line);
		while(!(convert>>num).fail())
		{
			if(num > 5 || num < 0)
			{
			std::cerr << "ERROR: Invalid input on line #" << line_num << " in file " << filename << endl;
			return -1;
			
			}
			
			/* If we are on the first line we need to instanciate a userObject for every column on the first line
			 * and then we push this object onto the vector of users
			 */ 
				
			if(line_num == 1)
			{
			  UserRatings userObject;
			  users.push_back(userObject);
			  num_users++;
			}

			// Checks to make sure we are not out of bounds for the number of defined users from line 1
			if(userCol > (num_users-1))
			{
			  std::cerr << "ERROR: Invalid input (extra user) on line #" << line_num << " in file " << filename << endl;
			  return -1;
			}
			
			// add rating into the user object for the column we are in
			users[userCol].addRating(num);
			userCol++;
		}

		/*
		 * if convert fails we could be at the end of the stringstream,
		 * however we could also be encountering an error. This is why I'm
		 * checking to see if we are also not at the end of the stringstream
		 */
		if(convert.fail() && !convert.eof())
		{
			std::cerr << "ERROR: Invalid input on line #" << line_num << " in file " << filename << endl;
			return -1;
		}
		/*At the end of parsing every line in the user ratings file, the num_users should be equal to the number of columns
		  else we have an undefined user rating, we must have a 0 if it is meant to be undefined" 
		 */ 

		if(userCol != num_users && line != "")
		{
			std::cerr << "ERROR: Undefined user rating on line #" << line_num << " in file " << filename << endl;
			return -1;
		}
		line_num++;

		
	}
	input.close();
	return line_num;
}

int countLines(char *filename)
{
	ifstream input(filename);
	if(!input)
	{
	std::cerr << "ERROR: failed to open file " << filename << endl;
	return -1;
	}

	int lines = 0;
	string line;
	string temp;
	while(getline(input, line))
	{

	temp = line;

		lines++;
	 
		

	}

	
	if(containsBlankLine(temp))	
	{
	  lines--;
	}

	input.close();
	return lines;
}

/*
 * readSongFile() accepts a file name and then opens a file stream buffer
 * it then reads the input file line by line, putting each line in a string
 * buffer. Comments on error handling the stringbuffer below
 */
int readSongFile(char *filename, vector<SongRating> &songs)
{
	int line_num = 1;
	string line = "";
	ifstream input(filename);

	if(!input)
		{
			std::cerr << "ERROR: failed to open file " << filename << endl;
			return -1;
		}

	while(getline(input, line))
	{
	  if(containsBlankLine(line))
	    {
	       std::cerr << "File: " << filename << " contains blank line on line number: " << line_num << endl;
	       return -1;

	    }
	
	SongRating songObject;
	songObject.setTitle(line);
	songs.push_back(songObject);	
	line_num++;
      }
	input.close();
	return line_num;
}

bool containsBlankLine(string line)
{
	for(unsigned int i = 0; i < line.size(); i++)
		{
		  if(!isspace(line[i]))
		    {
			return false;
		    }
		}
	return true;
}
