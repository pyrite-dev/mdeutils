#include "mauplay.h"

unsigned char* id3_findimage(const char* path, size_t* size) {
	size_t fsz;
	unsigned char* buffer = MDEID3GetTag(path, "APIC", &fsz);
	unsigned char* d = NULL;
	int	       i;
	if(buffer == NULL) return NULL;
	for(i = 1; i < fsz; i++) {
		if(buffer[i] == 0) break;
	}
	i++;
	/* XXX: 0 is technically Other - am not sure if this should be done... */
	if(buffer[i] == 0 || buffer[i] == 3) {
		int count = (buffer[0] == 1 || buffer[0] == 2) ? 2 : 1;

		i++;

		for(; i < fsz; i++) {
			if(buffer[i] == 0) count--;
			if(count == 0) break;
		}
		i++;
		d = malloc(fsz - i);
		memcpy(d, buffer + i, fsz - i);
		*size = fsz - i;
	}
	free(buffer);

	return d;
}
