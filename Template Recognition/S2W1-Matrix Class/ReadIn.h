#pragma once

double* readTXT(char *fileName, int sizeR, int sizeC);
void WritePGM(char *filename, double *data, int& sizeR, int& sizeC, int Q);