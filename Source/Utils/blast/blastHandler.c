/* blastHandler.c */
#include "blastHandler.h"

unsigned fileblastin(void *how, unsigned char **buf) {
	struct blastprogress_t *p = (struct blastprogress_t*)how;
	uint32 n = p->inbytesavail - p->inbytesread;
	if (n > p->bufsize)
		n = p->bufsize;
	n = fread(p->buffer, 1, n, p->infile);
	p->inbytesread += n;
	*buf = p->buffer;		
	return n;
}

int fileblastout(void *how, unsigned char *buf, unsigned len) {
	struct blastprogress_t *p = (struct blastprogress_t*)how;
	int n = fwrite(buf, 1, len, p->outfile);
	p->outbyteswritten += n;
	p->checksum = crc32(buf, len, p->checksum);
	return 0;
}

unsigned memblastin(void* how, unsigned char** buf) {
	struct blastprogress_t *p = (struct blastprogress_t*)how;
	*buf = p->inbuffer;
	p->inbytesread += p->inbytesavail;
	return p->inbytesavail;
}

int memblastout(void* how, unsigned char* buf, unsigned len) {
	struct blastprogress_t *p = (struct blastprogress_t*)how;
	memcpy(p->outbuffer + p->outbyteswritten, buf, (size_t)len);
	p->outbyteswritten += len;
	p->checksum = crc32(buf, len, p->checksum);
	return 0;
}

int runblast(struct blastprogress_t *p, blast_in infun, blast_out outfun, uint32 expected_checksum) {
	blast(infun, (void*)p, outfun, (void*)p);
	p->checksum = ~p->checksum;
	return (p->checksum == expected_checksum);
}

int runblast_mem2mem(void* in, uint32 insize, void* out, uint32 expected_checksum) {
	struct blastprogress_t p;
	p.inbytesavail = insize;
	p.inbytesread = 0;
	p.inbuffer = in;
	p.checksum = CRC32_INITIAL_VALUE;
	p.outbyteswritten = 0;
	p.outbuffer = out;
	return runblast(&p, memblastin, memblastout, expected_checksum);
}

int runblast_file2mem(FILE* infile, uint32 insize, void* out, uint32 expected_checksum) {
	struct blastprogress_t p;
	int val;
	p.inbytesavail = insize;
	p.inbytesread = 0;
	p.infile = infile;
	p.bufsize = BATCH_SIZE;
	p.buffer = (uint8*)malloc(p.bufsize);
	p.checksum = CRC32_INITIAL_VALUE;
	p.outbyteswritten = 0;
	p.outbuffer = out;
	
	val = runblast(&p, fileblastin, memblastout, expected_checksum);
	free(p.buffer);
	return val;
}

int runblast_file2file(FILE* infile, uint32 insize, FILE* outfile, uint32 expected_checksum) {
	struct blastprogress_t p;
	int val;
	p.inbytesavail = insize;
	p.inbytesread = 0;
	p.infile = infile;
	p.bufsize = BATCH_SIZE;
	p.buffer = (uint8*)malloc(p.bufsize);
	p.checksum = CRC32_INITIAL_VALUE;
	p.outbyteswritten = 0;
	p.outfile = outfile;
	val = runblast(&p, fileblastin, fileblastout, expected_checksum);
	free(p.buffer);
	return val;
}
