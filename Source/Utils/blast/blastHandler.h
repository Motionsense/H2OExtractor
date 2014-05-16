/* blastHandler.h -- A wrapper for the blast library */
#ifndef BLAST_HANDLER_H_
#define BLAST_HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "crc32.h"
#include "blast.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BATCH_SIZE 65536

struct blastprogress_t {
	uint32 inbytesavail;
	uint32 inbytesread;
	uint8 *inbuffer;
	FILE *infile;
	
	uint8 *buffer;
	uint32 bufsize;
	uint32 checksum;
	
	uint32 outbyteswritten;
	uint8 *outbuffer;
	FILE *outfile;
};

extern unsigned fileblastin(void *how, unsigned char **buf);

extern int fileblastout(void *how, unsigned char *buf, unsigned len);

extern unsigned memblastin(void* how, unsigned char** buf);

extern int memblastout(void* how, unsigned char* buf, unsigned len);

extern int runblast(struct blastprogress_t *p, blast_in infun, blast_out outfun, uint32 expected_checksum);

extern int runblast_mem2mem(void* in, uint32 insize, void* out, uint32 expected_checksum);

extern int runblast_file2mem(FILE* infile, uint32 insize, void* out, uint32 expected_checksum);

extern int runblast_file2file(FILE* infile, uint32 insize, FILE* outfile, uint32 expected_checksum);
 
#ifdef __cplusplus
}
#endif

#endif /*BLAST_HANDLER_H_*/