//HOW10183346
//CMP2067M Assessment Component 2
//Task One

#include "Matrix.h"
#include "ReadIn.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
using namespace std;

void Unshuffle(BinaryMatrix a, BinaryMatrix b, char* fileName);

int main()
{
	double* shuffled = readTXT("DataFile/logo_shuf.txt", 512, 512);
	double* noisy = readTXT("DataFile/logo_noisy.txt", 512, 512);
	double* sorted = readTXT("DataFile/logo_bi.txt", 512, 512);

	BinaryMatrix shuffledM(512, 512, shuffled);
	BinaryMatrix noisyM(512, 512, noisy);
	BinaryMatrix sortedM(512, 512, sorted);

	Unshuffle(sortedM, shuffledM, "Logo_restored.pgm");
	Unshuffle(noisyM, shuffledM, "Logo_restored_noisy.pgm");

	cin.get();

	return 0;
}


void Unshuffle(BinaryMatrix a, BinaryMatrix b, char* fileName)
{
	BinaryMatrix solved(512, 512);

	//Iterate through the 16 rows of the template image
	for (int i = 0; i < 16; i++)
	{
		cout << "\n\nRow: " << i;
		//Iterate through the 16 columns of the template image
		for (int j = 0; j < 16; j++)
		{
			//Initialise Matrices to hold a chunk of the template and unsorted images
			BinaryMatrix tempA(32,32);
			BinaryMatrix tempB(32,32);

			//Import the data from cell i,j of the template image
			BinaryMatrix bestTemp(32,32);
			for (int k = 0; k < 32; k++)
			{
				for (int l = 0; l < 32; l++)
				{
					tempA.setNData(k, l, a.getRead((i*32)+k, (j*32)+l));
				}
			}

			//Initialise the best score to an unachievable level of dissimalarity
			double bestScore = 200000;

			//Initialise the current score to 0
			double currentScore = 0;
			//Initialise boolean switch to allow for breaking if a perfect score is found
			bool perfectBreak = false;

			//Iterate through the 16 rows of the shuffled image
			for (int q = 0; q < 16 && !perfectBreak; q++)
			{
				//Iterate through the 16 columns of the shuffled image
				for (int r = 0; r < 16; r++)
				{
					//Import the data from cell i,j of the UNSHUFFLED image
					for (int k = 0; k < 32; k++)
					{
						for (int l = 0; l < 32; l++)
						{
							tempB.setNData(k, l, b.getRead((q*32)+k, (r*32)+l));
						}
					}
					//Set the current score for this similarity test
					currentScore = tempA.SSD(tempB);

					//If a perfect score is achieved (100% match)
					if (currentScore == 0)
					{
						//Store the pixel data of the best cell
						bestTemp = tempB;
						//Report success
						cout << "\nPERFECT MATCH";
						//Break the loop
						perfectBreak = true;
						break;
					}
					else if (currentScore < bestScore)
					{
						//Update bestScore to reflect this is the closest match so far
						bestScore = currentScore;
						//Store the pixel data of the best cell so far
						bestTemp = tempB;
						//Report a closer success
						cout << "\nCLOSER MATCH";
					}
				}
			}
			//Set the data for the best match into a blank matrice, to build the unshuffled image
			solved.InsertBlock(bestTemp, i*32, j*32, 32, 32);
		}
	}



	cout << "\nOpening '" << fileName << "'";

	int M = solved.getHeight(); int N = solved.getWidth();
	//Write the unshuffled image to a .PGM file in the same folder as the executable
	WritePGM(fileName, solved.getData(), M, N, 1);
}