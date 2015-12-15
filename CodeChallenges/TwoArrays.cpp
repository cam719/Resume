#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{
	int T = 0;
	cin >> T;

	while(T > 0)
	{
		int n, k;
		cin >> n >> k;
		vector<int> A;
		vector<int> B;
		for(int i = 0; i < n; i++)
		{
			int num; cin >> num;
			A.push_back(num);
		}
		for(int i = 0; i < n; i++)
		{
			int num; cin >> num;
			B.push_back(num);
		}
		sort(A.begin(), A.end(), greater<int>());
		sort(B.begin(), B.end());
		bool no = false; 
		for(int i = 0; i < n; i++)
		{
			if((A[i] + B[i]) < k)
			{
				cout << "NO" << endl;
				no = true;
				break;
			}
		}
		if(!no)
		{
			cout << "YES" << endl;
		}


		T--;
	}


	return 0;
}
