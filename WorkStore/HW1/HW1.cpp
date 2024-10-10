#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>

using namespace std;

void input(string sMessage, string &sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;

	return;
}

void writeBackwardI(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	for ( int i = length - 1; i >= 0; i-- ) //倒著印出字串s
		cout << s[i];
}

void writeBackwardR1(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	cout << s[length - 1];
	writeBackwardR1( s.substr( 0, length - 1 ) );
	//sub 從第0格提取字串長度的字串
}

void writeBackwardR2(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	writeBackwardR2( s.substr( 1, length - 1 ) );
	cout << s[0];
}


int countI(string s, char c)// iteration,計算並回傳字串中所含某個字元的總數。
{
	int length = s.size(), num = 0;

	if ( length == 0 )  // base case 
		return;
	for ( int i = 0; i < length; i++ )
		if(s[i] = c)num++;
	return num;
}

int countR(string s, char c)// Recursion,計算並回傳字串中所含某個字元的總數。
{
	
	int length = s.size(), num = 0;

	if(length > 0)num = countR(s.substr(1,length),c);
	if(s[0] == c)
		return num+1;
	return num;
}

unsigned char findI(string s)
{
	int length = s.size(), min = 150;
	for ( int i = 0; i < length; i++ )
	{
		if(!isalpha(s[i]))
			continue;
		if(s[i] < min)
			min = s[i];
	}
	return min;
}

char findR(string s)
{
	int length = s.size(), min = 150;
	//cout << endl << "length:" << length << "s:" << s << endl;
	if(length > 1)min = findR(s.substr(1,length));
	if(s[0] < min && isalpha(s[0]))return s[0];
	return min;
}

string removeI(string s)
{
	int length = s.size();
	string str;
	if(length <= 1)return s;
	
	for(int i=0;i < length;i++)
	{
	    string str2 = s.substr(i,1);
		if(s[i]!=s[i+1])str.append(str2);
	}
	return str;
}

string removeR(string s) //'abcde' abcd abc ab a
{
	
	int length = s.size();
	printf("\t L:%d \tword:%c,%c\n",length,s[length-2] , s[length-1]);
    string str = s, c;
    if(length>2 )c = removeR(str.substr(0,length-1));
    	cout  << c ;
	if(s[length-1] != s[length-2])return s.substr(length-1,length-1);
	return "fail";
}

int TI( int m, int n)
{

	// add your code here

/* 
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + ... + m (n times), if m > n
	T(m, n) =  n + ... + n (m times), otherwise
*/
	
	return m * n;
}

int TR( int m, int n)
{
	// add your code here
/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + T( m, n - 1 ), if m > n
	T(m, n) =  n + T( m - 1, n ), otherwise
*/
		return m * n;
}

int main(int argc, char* argv[])
{
	string commandStr;	
	string inputStr, appendStr;
	char inputChr;
	int m, n;

	while (1) {
		input( "\nEnter command: "
			"\n I to input a string, A to append a string, B to write the string backward, "
			"\n C to count the given character , F to find the smallest character,"
			"\n R to remove the repeated characters, T to compute, and X to Exit", commandStr );
	
		if ( commandStr == "I"  || commandStr == "i" ) { //輸入字串
			cout << "\nInput the string: ";
			cin >> inputStr;
		}

		else if ( commandStr == "A"  || commandStr == "a" ) { //追加字串
			cout << "\nInput the string: ";
			cin >> appendStr;
			inputStr += appendStr;
			cout << "\nThe new string: " << inputStr << endl;
		}

		else if ( commandStr == "B" || commandStr == "b" ) { //反向寫入字串
			if ( inputStr.length() > 0 ) {
				cout << endl;
				writeBackwardI( inputStr );
				cout << endl;
				writeBackwardR1( inputStr );
				cout << endl;
				writeBackwardR2( inputStr );
				cout << endl;
			}
		}

		else	if ( commandStr == "C"  || commandStr == "c" ) { //計數指定的字元char
			if ( inputStr != "" ) {
				cout << "\nInput the character: ";
				cin >> inputChr;
				cout << "\nCount of " << inputChr <<": " << countI( inputStr, inputChr );
				cout << "\nCount of " << inputChr <<": " << countR( inputStr, inputChr ) << endl;
			}
		}

		else if ( commandStr == "R" || commandStr == "r" ) { //移除重複的字元
			if ( inputStr != "" ) {
				cout << endl << "Repeated characters removed: " << removeI( inputStr ) ;
				cout << endl << "Repeated characters removed: " << removeR( inputStr ) << endl;
			}
		}

		else if ( commandStr == "F" || commandStr == "f" ) { //找出最小的字元char
			if ( inputStr != "" ) {
				cout << endl << "Smallest character found: " << findI( inputStr );
				cout << endl << "Smallest character found: " << findR( inputStr ) << endl;
			}
		}

		else  if ( commandStr == "T" || commandStr == "t" ) //T用於計算
		{
			cout << "\nInput two values, m and n: ";
			cin >> m >> n;
			cout << endl << "The result is " << TI( m, n );
			cout << endl << "The result is " << TR( m, n ) << endl;
		}

		else  if ( commandStr == "X" || commandStr == "x" ) //X離開
			return 0;	
		else
			cout << "\nUnknown command!";
	}
  	return 0;
}
