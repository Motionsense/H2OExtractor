/* H2OExtractor.cpp */
#include "H2OExtractor.h"

int main(int argc, char* argv[])
{
	printf("H2OExtractor v1.0 - fucckz\n\n============================\n");
	
	// no command
	if (argc < 2) {
		printf("Usage:\n");
		printf("H2OExtractor <command> <archive_path>\n\n");
		printf("Command:\n");
		printf("extract - extract all file of archive to output dir\n");
		printf("info - display infomations about the archive\n");
		return 0;
	}

	// print archive's name
	char* cmd = argv[1];
	char* path = argv[2];
	printf("[%s]\n", path);

	// do stuff
	Archive h2o(path);
	if (strcmp(cmd, "info") == 0)
	{
		h2o.displayInfo();
	}
	else if (strcmp(cmd, "extract") == 0)
	{
		h2o.extractAll();
	}
	h2o.close();

	// end
	DB::debugLog("\nPress Any Key to Exist", "\n", NULL);
	getchar();
	return 0;
}