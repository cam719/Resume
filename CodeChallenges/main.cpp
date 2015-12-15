#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class BigInt {
public:
	BigInt()
	{
		number = "0";
	}
	BigInt(string incNum)
	{
		if((char)incNum[0] == '-')
		{
			number = incNum;
			sign = true;
		}
		else
		{
			number = incNum;
		}
	}
	unsigned int inline getSize() const {return number.size();}
	string inline getNumber() const {return number;}
	void inline setNumber(string incString) {number = incString;}
	void resize(string &x, string &y);
	string add(string &x, string &y);

	//Operators 
	BigInt (const BigInt& other);
	BigInt operator= (const BigInt &y);
	BigInt operator += (const BigInt &y);
	BigInt operator +(const BigInt &y);
	BigInt operator -(const BigInt &y);
	BigInt operator /(const BigInt &y);
	bool operator==(const BigInt &incNum);

private:
	string number;
	bool sign; 
};

BigInt::BigInt(const BigInt& other)
{
	string temp = other.getNumber();
	number = temp;
}
BigInt BigInt::operator= (const BigInt &y)
{
	number = y.getNumber();
	return *this;
}
bool BigInt::operator==(const BigInt &incNum)
{
	return this->getNumber() == incNum.getNumber();
}

void BigInt::resize(string &x, string &y)
{
	if(x.size() < y.size())
 	{
 		while(x.size() < y.size())
 		{
 			x.insert(0, "0");
 		}
 	}
 	else if(y.size() < x.size())
 	{
 		while(y.size() < x.size())
 		{
 			y.insert(0, "0");
 		}
 	}
}
BigInt BigInt::operator +(const BigInt &incNum)
{

	string newNum = "";
	string x = this->getNumber();
 	string y = incNum.getNumber();
 	string carry = "0";

 	resize(x,y);
 	for(int i = (x.length()-1); i >= 0; i--)
 	{
 		int a = x[i]-'0'; // ASCII TO INTEGER
 		cout << "x[i] = " << x[i] << endl;
 		int b = y[i]-'0'; // ASCII TO INTEGER
 	    int c = carry[0]-'0';
 		int sum = (a + b + c);
 		if(sum >= 10)
 		{
 			sum -= 10;
 			carry = "1";
 		}
 		else
 		{
 			carry = "0";
 		}
 		stringstream ss;
 		ss << sum;
 		newNum.insert(0, ss.str());
 	}
	return BigInt(newNum);
}

string BigInt::add(string &x, string &y)
{
	string result = "";
	int xlen = x.length();
 	int ylen = y.length();
	resize(x, y);
	result = x;
	for(int i = (x.length()-1); i >= 0; i--)
	{
		int a = x[i]-'0';
		int b = y[i]-'0';
		int diff = a - b;
		if(a < b && (x.length() != 1))
		{
			a += 10;
			int d = x[i-1]-'0';
			d--;
			x[i-1] = d + '0';
		}
		cout << "DIFFERENCE = " << diff << endl;
		stringstream ss;
 		ss << diff;
 		string s = ss.str();
 		cout << "SS = " << ss.str() << endl;
		result[i] = s[0];
		cout << "RESULT = " << result << endl;
	}
	
	return result;
}


BigInt BigInt::operator -(const BigInt &rhs)
{
	return BigInt("0");
	
}


