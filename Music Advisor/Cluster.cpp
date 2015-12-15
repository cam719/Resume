#include "Cluster.h"

// for debugging
void Cluster::print()
{
	cout << "OBJECT = " << endl;
	for(unsigned int i = 0; i < clusterAverge.size(); i++)
	{
		
		cout << clusterAverge[i] << " ";

	}
	cout << endl;

	cout << "SONGS = ";
	for(unsigned int i = 0; i < clstrSongs.size(); i++)
	{
		cout << clstrSongs[i].getTitle() << " ";
	}

	cout << endl;
	
}

double Cluster::Distance(const vector <double> &a, const vector<double> &b)
{
	double result = 0;
	for(unsigned int i = 0; i < a.size(); i++)
	{
		//cout << "DEBUG: ai - bi = " << a[i] << "-" << b[i] << endl;
		result += ((a[i] - b[i]) * (a[i] - b[i]));
	}

	return sqrt(result);
}
void Cluster::calculateAvg()
{
	if(clstrSongs.size() == 0)
	{
		return;
	}
	clusterAverge.clear();
	clusterAverge.resize(U);

	//cout << "U = " << U << endl;
	//cout << "S = " << clstrSongs.size() << endl;
	// Add every rating to every index since it represents the column
	// J is = songs and then we add the rating of that  ith song to the average column, 
	// and then dived by the total amount of songs at the end
	for(unsigned int j = 0; j < clstrSongs.size(); j++)
	{
		for(int i = 0; i < U; i++)
		{
		
	  		clusterAverge[i] += clstrSongs[j].getRating(i);
	
		}
	}
	//cout << "DEUBUG CLUSTER AVG:  ";
	for(unsigned int i = 0; i < clusterAverge.size(); i++)
	{
		clusterAverge[i] /= clstrSongs.size();
		//cout << clusterAverge[i] << " ";
	}
	//cout << endl;
}

void Cluster::deleteSong(SongRating sObj)
{
	int position = 0;
	for(unsigned int i = 0; i < clstrSongs.size(); i++)
	{
		if(clstrSongs[i] == sObj)
		{
			position = i;
			break; 
		}


	}
	//cout << "DELETING SONG index " << position << endl;
	clstrSongs.erase(clstrSongs.begin()+position);

}

vector<pair<double,string> > Cluster::calcPairs(SongRating sObj)
{
	vector<pair<double,string> > pairedSongs; // paired songs vector
	double d = 0; // distance variable to be placed in pair

	for(unsigned int i = 0; i < clstrSongs.size(); i++)
	{
		if(!(clstrSongs[i] == sObj))
		{
			d = 1 / (Distance(clstrSongs[i].getRatings(), sObj.getRatings()));
			//cout << "D = " << d << endl;
			pair<double, string> temp(d, clstrSongs[i].getTitle());
			pairedSongs.push_back(temp);
			sort(pairedSongs.begin(), pairedSongs.end());
		}

	}

	return pairedSongs;

}
