#include "mauplay.h"

static void* play_queue;
static void* all_music;
static void* albums;
static void* artists;
static void* genres;
static void* playlists;

void ui_list_reset(void) {
	void* p;

	MwListBoxReset(list);

	p = MwListBoxCreatePacket();
	MwListBoxPacketInsert(p, -1);
	MwListBoxPacketSet(p, 0, 0, "#");
	MwListBoxPacketSet(p, 0, 1, "Title");
	MwListBoxPacketSet(p, 0, 2, "Artist");
	MwListBoxPacketSet(p, 0, 3, "Length");

	MwListBoxInsert(list, -1, p);
	MwListBoxDestroyPacket(p);

	MwListBoxSetWidth(list, 0, 48);
	MwListBoxSetWidth(list, 1, -48 - 128);
	MwListBoxSetWidth(list, 2, 64);
	MwListBoxSetWidth(list, 3, 64);

	MwListBoxSetAlignment(list, 0, MwALIGNMENT_CENTER);
	MwListBoxSetAlignment(list, 2, MwALIGNMENT_END);
	MwListBoxSetAlignment(list, 3, MwALIGNMENT_END);
}

void ui_tree_reset(void) {
	void* t;

	MwTreeViewReset(tree);

	play_queue = MwTreeViewAdd(tree, NULL, NULL, "Play Queue (?)");

	t	  = MwTreeViewAdd(tree, NULL, NULL, "Library");
	all_music = MwTreeViewAdd(tree, t, NULL, "All Music (?)");
	albums	  = MwTreeViewAdd(tree, t, NULL, "Albums (?)");
	artists	  = MwTreeViewAdd(tree, t, NULL, "Artists (?)");
	genres	  = MwTreeViewAdd(tree, t, NULL, "Genres (?)");

	playlists = MwTreeViewAdd(tree, NULL, NULL, "Playlists (?)");
}

void ui_set_play_queue(int v) {
	char buf[64];
	sprintf(buf, "Play Queue (%d)", v);
	MwTreeViewSetLabel(tree, play_queue, buf);
}

void ui_set_all_music(int v) {
	char buf[64];
	sprintf(buf, "All Music (%d)", v);
	MwTreeViewSetLabel(tree, all_music, buf);
}

void ui_set_albums(int v) {
	char buf[64];
	sprintf(buf, "Albums (%d)", v);
	MwTreeViewSetLabel(tree, albums, buf);
}

void ui_set_artists(int v) {
	char buf[64];
	sprintf(buf, "Artists (%d)", v);
	MwTreeViewSetLabel(tree, artists, buf);
}

void ui_set_genres(int v) {
	char buf[64];
	sprintf(buf, "Genres (%d)", v);
	MwTreeViewSetLabel(tree, genres, buf);
}

void ui_set_playlists(int v) {
	char buf[64];
	sprintf(buf, "Playlists (%d)", v);
	MwTreeViewSetLabel(tree, playlists, buf);
}

void ui_init(void) {
	ui_list_reset();
	ui_tree_reset();

	ui_set_play_queue(0);
	ui_set_all_music(0);
	ui_set_albums(0);
	ui_set_artists(0);
	ui_set_genres(0);
	ui_set_playlists(0);
}
