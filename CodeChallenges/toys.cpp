#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



int main() 
{
    int num_toys = 0;
    long long n, k; cin >> n >> k;
    vector<int> prices;
    for(int i = 0; i < n; i++)
    {
        int p; cin >> p;
        prices.push_back(p);
    }
    
    sort(prices.begin(), prices.end());
    int count = 0;
    while(k > 0 && count < n)
    {
        if((k - prices[count]) >= 0)
        {
              k -= prices[count];
              num_toys++;
        }
        count++;
    }
    // Write the code for computing the final answer using n,k,prices
    
    cout << num_toys << endl;
    
    return 0;
}
