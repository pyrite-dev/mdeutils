#include "mauplay.h"

#include <stb_ds.h>
#include <ini.h>

typedef struct song {
	int   key;
	char* value;
} song_t;

song_t* songs = NULL;
int	count = 0;

static int dumper(void* user, const char* section, const char* key, const char* value) {
	if(strcmp(section, "playlist") != 0) return 1;
	if(strcmp(key, "NumberOfEntries") == 0) {
		count = atoi(value);
	}
	if(strlen(key) > 4 && memcmp(key, "File", 4) == 0) {
		song_t s;
		s.key	= atoi(key + 4);
		s.value = MDEStringDuplicate(value);
		hmputs(songs, s);
	}

	return 1;
}

void playlist_add(const char* path) {
	int i;
	ini_parse(path, dumper, NULL);

	for(i = 0; i < count; i++) {
		int ind = hmgeti(songs, i + 1);
		if(ind == -1) continue;

		db_add(songs[ind].value);
	}
	for(i = 0; i < hmlen(songs); i++) {
		free(songs[i].value);
	}
	hmfree(songs);
	db_scan();
}
