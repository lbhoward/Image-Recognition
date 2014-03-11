//HOW10183346
//CMP2067M Assessment Component 2
//Task Two
#include "Matrix.h"
#include "ReadIn.h"
#include <iostream>
#include <string>
#include <fstream> // ifstream
#include <istream>
using namespace std;

void WheresWally(BinaryMatrix a, BinaryMatrix b, char* fileName);
void WheresWally(GreyscaleMatrix a, GreyscaleMatrix b, char* fileName);

int main()
{
	double* wally_grey = readTXT("DataFile/Wally_grey.txt", 49, 36);
	double* wally_bi = readTXT("DataFile/Wally_bi.txt", 49, 36);
	double* wally_envi = readTXT("DataFile/Cluttered_scene.txt", 768, 1024);
	double* wally_envi_bi = readTXT("DataFile/Cluttered_scene_bi.txt", 768, 1024);
	GreyscaleMatrix WallyTemp(49, 36, wally_grey);
	GreyscaleMatrix WallyProp(49, 36);
	GreyscaleMatrix WallyEnvi(768, 1024, wally_envi);

	BinaryMatrix WallyTempBi(49, 36, wally_bi);
	BinaryMatrix WallyEnviBi(768, 1024, wally_envi_bi);

	WheresWally(WallyTempBi, WallyEnviBi, "Wally_detected_bi.pgm");
	WheresWally(WallyTemp, WallyEnvi, "Wally_detected_grey.pgm");

	cin.get();

	return 0;
}

void WheresWally(BinaryMatrix a, BinaryMatrix b, char* fileName)
{
	double currentScore;
	int bestI, bestJ;
	double bestScore = 200000;
	for (int i = 0; i < b.getHeight() - a.getHeight(); i++)
	{
		cout << "Row: " << i << endl;
		for (int j = 0; j < b.getWidth() - a.getWidth(); j++)
		{
			BinaryMatrix wallyCutOut = a;
			BinaryMatrix tempB(49, 36);
			for (int y = 0; y < 49; y++)
			{
				for (int z = 0; z < 36; z++)
				{
					tempB.setNData(y,z, b.getRead(i+y, j+z));
				}
			}

			for (int q = 0; q < a.getHeight(); q++)
			{
				for (int r = 0; r < a.getWidth(); r++)
				{
					//Eliminate parts of the templates which aren't part of the template
					//Implement an alpha channel in the template in future?
					if (a.getRead(q,r) == 0)
						wallyCutOut.setNData(q,r, b.getRead(i+q,j+r));
				}
			}

			currentScore = wallyCutOut.SSD(tempB);

			if (currentScore < bestScore)
			{
				bestScore = currentScore;
				bestI = i;
				bestJ = j;
			}
		}
	}

	cout << "Wally is at - Row: " << bestI << " - Col: " << bestJ;
	for (int q = 0; q < a.getHeight(); q++)
			{
				for (int r = 0; r < a.getWidth(); r++)
				{
					//Invert Wally Location
					if (b.getRead(bestI+q,bestJ+r) == 0)
						b.setNData(bestI+q,bestJ+r, 1);
					else if (b.getRead(bestI+q,bestJ+r) == 1)
						b.setNData(bestI+q,bestJ+r, 0);
				}
			}
	int M = b.getHeight(); int N = b.getWidth();
	WritePGM(fileName, b.getData(), M, N, 1); 
}

void WheresWally(GreyscaleMatrix a, GreyscaleMatrix b, char* fileName)
{
	double currentScore;
	int bestI, bestJ;
	double bestScore = 200000;
	for (int i = 0; i < b.getHeight() - a.getHeight(); i++)
	{
		cout << "Row: " << i << endl;
		for (int j = 0; j < b.getWidth() - a.getWidth(); j++)
		{
			GreyscaleMatrix wallyCutOut = a;
			GreyscaleMatrix tempB(49, 36);
			for (int y = 0; y < 49; y++)
			{
				for (int z = 0; z < 36; z++)
				{
					tempB.setNData(y,z, b.getRead(i+y, j+z));
				}
			}

			for (int q = 0; q < a.getHeight(); q++)
			{
				for (int r = 0; r < a.getWidth(); r++)
				{
					//Eliminate parts of the templates which aren't part of the template
					//Implement an alpha channel in the template in future?
					if (a.getRead(q,r) == 255)
						wallyCutOut.setNData(q,r, b.getRead(i+q,j+r));
				}
			}

			currentScore = wallyCutOut.SSD(tempB);

			if (currentScore < bestScore)
			{
				bestScore = currentScore;
				bestI = i;
				bestJ = j;
			}
		}
	}

	cout << "Wally is at - Row: " << bestI << " - Col: " << bestJ;
	for (int q = 0; q < a.getHeight(); q++)
			{
				for (int r = 0; r < a.getWidth(); r++)
				{
					b.setNData(bestI+q,bestJ+r, 0);
				}
			}
	int M = b.getHeight(); int N = b.getWidth();
	WritePGM(fileName, b.getData(), M, N, 255); 
}