#include "mauplay.h"

#include <sqlite3.h>
#include <sndfile.h>
#include <stb_ds.h>

static sqlite3* db;

int db_exec(const char* s) {
	sqlite3_stmt* stmt;
	int	      st = 0;

	if(sqlite3_prepare_v2(db, s, -1, &stmt, NULL) != SQLITE_OK) {
		return 1;
	}

	if(sqlite3_step(stmt) != SQLITE_DONE) {
		st = 1;
	}

	if(sqlite3_finalize(stmt) != SQLITE_OK) {
		st = 1;
	}

	return st;
}

int db_init(void) {
	struct passwd* pwd = getpwuid(getuid());
	char*	       dir = malloc(strlen(pwd->pw_dir) + 1 + strlen(".config/mauplay") + 1);
	char*	       path;
	int	       st = 0;

	strcpy(dir, pwd->pw_dir);
	strcat(dir, "/.config/mauplay");

	MDEDirectoryCreate(dir, 0755);

	path = malloc(strlen(dir) + 1 + strlen("mauplay.db") + 1);
	strcpy(path, dir);
	strcat(path, "/mauplay.db");

	free(dir);

	if(sqlite3_open(path, &db) != SQLITE_OK) {
		free(path);
		return 1;
	}

	free(path);

	if((st = db_exec("CREATE TABLE IF NOT EXISTS cache (path TEXT PRIMARY KEY, title TEXT, artist TEXT, album TEXT, genre TEXT, length INTEGER, mtime INTEGER)")) != 0) {
		sqlite3_close(db);
		return st;
	}

	return st;
}

static int db_bind(sqlite3_stmt* stmt, const char* path) {
	SF_INFO	    sfi;
	SNDFILE*    sf = sf_open(path, SFM_READ, &sfi);
	char*	    p;
	const char* s_title;
	const char* s_artist;
	const char* s_album;
	const char* s_genre;
	int	    s_length;
	struct stat s;
	if(sf == NULL) return 1;

	s_title	 = sf_get_string(sf, SF_STR_TITLE);
	s_artist = sf_get_string(sf, SF_STR_ARTIST);
	s_album	 = sf_get_string(sf, SF_STR_ALBUM);
	s_genre	 = sf_get_string(sf, SF_STR_GENRE);
	s_length = sfi.frames / sfi.samplerate;

	if(s_title == NULL) s_title = path;
	if(s_artist == NULL) s_artist = "<unknown>";
	if(s_album == NULL) s_album = "<unknown>";
	if(s_genre == NULL) s_genre = "<unknown>";

	p = MDEFileAbsolutePath(path);

	stat(p, &s);

	sqlite3_bind_text(stmt, 1, p, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 2, s_title, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, s_artist, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 4, s_album, -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 5, s_genre, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 6, s_length);
	sqlite3_bind_int64(stmt, 7, s.st_mtime);

	sf_close(sf);

	free(p);

	return 0;
}

void db_add(const char* path) {
	sqlite3_stmt* stmt;

	if(sqlite3_prepare_v2(db, "INSERT OR REPLACE INTO cache VALUES(?,?,?,?,?,?,?)", -1, &stmt, NULL) != SQLITE_OK) {
		return;
	}

	if(db_bind(stmt, path) == 0) {
		sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
}

void db_scan(void) {
	sqlite3_stmt* stmt;

	if(sqlite3_prepare_v2(db, "SELECT * FROM cache", -1, &stmt, NULL) != SQLITE_OK) {
		return;
	}

	while(sqlite3_step(stmt) == SQLITE_ROW) {
		printf("!\n");
	}

	sqlite3_finalize(stmt);
}
