#include <sstream> // stringstream
#include <iostream> // cout, cerr
#include <fstream> // ifstream
#include <istream>

using namespace std;

// This is the code to read .txt file in, which will convert
// the contents to an array of numbers in double
double* readTXT(char *fileName, int sizeR, int sizeC)
{
  double* data = new double[sizeR*sizeC];
  int i=0;
  ifstream myfile (fileName);
  if (myfile.is_open())
  {
	 
	while ( myfile.good())
    {
       if (i>sizeR*sizeC-1) break;
		 myfile >> *(data+i);
         //cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
	     i++;                                                             
	}
    myfile.close();
  }

  else cout << "Unable to open file";

  return data;
}


// This is the code to write to .pgm image, which will convert the data in doulbe to 
// an image in PGM format 
void WritePGM(char *filename, double *data, int& sizeR, int& sizeC, int Q)
{
 int i, j;
 unsigned char *image;
 ofstream myfile;

 image = (unsigned char *) new unsigned char [sizeR*sizeC];

 // convert the integer values to unsigned char
 
 for(i=0; i<sizeR*sizeC; i++)
	 image[i]=(unsigned char)data[i];

 myfile.open(filename, ios::out);

 if (!myfile) {
   cout << "Can't open file: " << filename << endl;
   exit(1);
 }

 myfile << "P5" << endl;
 myfile << sizeC << " " << sizeR << endl;
 myfile << Q << endl;

 myfile.write( reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

 if (myfile.fail()) {
   cout << "Can't write image " << filename << endl;
   exit(0);
 }

 myfile.close();

}

//int main()
//{
//	// This part will show you how to use the two ReadIn functions.
//	double* data = 0;
//	int M=0; int N=0; 
//	
//	cout << endl;
//	cout << "Data from text file -------------------------------------------" << endl;
//	M = 768; N = 1024; //M and N represent the size of the image, e.g. for task 1, M = 512, N = 512
//	char* fileName2 = "I:\\CMP2067\\DataFile\\DataFile\\Cluttered_scene.txt"; 
//	data = readTXT(fileName2, M, N);
//
//	char* fileName = "I:\\CMP2067\\DataFile\\DataFile\\Cluttered_scene_1.pgm";
//	int Q = 255; // Q is the maximum intensity value for your image, 255 for greyscale and 1 for binary.
//	// int Q = 1; // set Q to 1 if processing binary image
//	WritePGM(fileName, data, M, N, Q); 
//
//	return 0;
//}