/* H2OExtractor.cpp */
#include "H2OExtractor.h"

int main(int argc, char* argv[])
{
	printf("H2OExtractor\n============================\n");
	Archive h2o("Input.H2O");

	DB::debugLog("\nPress Any Key to Extract Files", "\n", NULL);
	getchar();

	h2o.extractAll();

	DB::debugLog("\nPress Any Key to Exist", "\n", NULL);
	getchar();

	return 0;
}