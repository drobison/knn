// Author	David Robison
// Date		4/20/2013

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

float Ax[100], Ay[100];
int Acount = 0;
float Bx[100], By[100];
int Bcount = 0;

float Ix[100], Iy[100];
int Icount = 0;
int correctClass[100];

int correct, incorrect, aCorrect, bCorrect;

ifstream infile;
ofstream outfile;

float calculateDistance(float x, float y, float x1, float y1);
void knn( float x, float y, int correctClass, int k);
void resetCounters();
void printResults();

int main()
{
	float x, y;
	correct, incorrect = 0;

	string classA = "1.txt";
	string classB = "2.txt";
	string input = "input.txt";
	string output = "output.txt";

	// Read in Class A
	infile.open(classA.c_str());
	if (!infile)
	{
		cout << "Unable to open class A"<< endl;
	}
	while(!infile.eof())		
	{
		infile >> Ax[Acount] >> Ay[Acount];
		Acount++;
	}
	infile.close();

	// Read in Class B
	infile.open(classB.c_str());
	if (!infile)
	{
		cout << "Unable to open class B"<< endl;
	}
	while(!infile.eof())		
	{
		infile >> Bx[Bcount] >> By[Bcount];
		Bcount++;
	}
	infile.close();

	// Open output
	outfile.open(output.c_str());

	// Open input
	infile.open(input.c_str());
	if (!infile)
	{
		cout << "Unable to open output"<< endl;
	}
	while(!infile.eof())		
	{
		infile >> Ix[Icount] >> Iy[Icount] >> correctClass[Icount];
		Icount++;	
	}

	

	// K = 1
	resetCounters();
	for( int i=0; i<Icount; i++)
	{
		knn(Ix[i], Iy[i], correctClass[i], 1);
	} 
	outfile << "k = 1" << endl;
	printResults();


	// K = 3
	resetCounters();
	for( int i=0; i<Icount; i++)
	{
		knn(Ix[i], Iy[i], correctClass[i], 3);
	} 

	outfile << "k = 3" << endl;
	printResults();



	// K = 5
	resetCounters();
	for( int i=0; i<Icount; i++)
	{
		knn(Ix[i], Iy[i], correctClass[i], 5);
	} 

	outfile << "k = 5" << endl;
	printResults();


	// K = 7
	resetCounters();
	for( int i=0; i<Icount; i++)
	{
		knn(Ix[i], Iy[i], correctClass[i], 7);
	}

	outfile << "k = 7" << endl;
	printResults();


	infile.close();

	outfile.close();
}

float calculateDistance(float x, float y, float x1, float y1)
{
	float part1 = (x - x1) * (x - x1);
	float part2 = (y - y1) * (y - y1);
	float answer = sqrt(part1+part2);

	return answer;
}

void knn( float x, float y, int correctClass, int k)
{

	int classifiedAs=1;
	float smallA[100];
	float smallB[100];
	fill_n(smallA, 100, 100);
	fill_n(smallB, 100, 100);

	for( int i=0; i<Acount; i++)
	{
		smallA[i] = calculateDistance(x, y, Ax[i], Ay[i]);
	}
	for( int i=0; i<Bcount; i++)
	{
		smallB[i] = calculateDistance(x, y, Bx[i], By[i]);
	}
	sort(begin(smallA), end(smallA));
	sort(begin(smallB), end(smallB));
	int currentA = 0;
	int currentB = 0;
	while (currentA+currentB  < k )
	{
		if( smallA[currentA] < smallB[currentB] )
			currentA++;
		else
			currentB++;
	}
		if( currentA > currentB)
			classifiedAs = 1;
		else
			classifiedAs = 2;
		if(correctClass == classifiedAs)
		{
			correct++;
			if( correctClass == 1 )
				aCorrect++;
			else
				bCorrect++;
		}
		else
			incorrect++;
}

void resetCounters()
{
	correct = 0;
	incorrect = 0;
	aCorrect = 0;
	bCorrect = 0;
}

void printResults()
{
	outfile << "Total Correct - " << correct << endl;
	outfile << "Total Incorrect - " << incorrect << endl;
	outfile << "Class 1 Correct - " << aCorrect << endl;
	outfile << "Class 2 Correct - " << bCorrect << endl;
	outfile << endl;
}