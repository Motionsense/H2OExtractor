/* H2OExtractor.cpp */
#include "H2OExtractor.h"

int main(int argc, char* argv[])
{
	printf("H2OExtractor\n============================\n");
	Archive h2o("Input.H2O");

	getchar();
	DB::debugLog("\nExtracting files...", "\n", NULL);
	h2o.extractAll();
	return 0;
}