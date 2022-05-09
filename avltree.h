

struct Tree{
    char song_name[20];
    char song_genre[20];
    char album_name[20];
    char artist_name[20];
    int release_year;
    char release_date[20];
    struct Tree *list;
    struct Tree *left;
    struct Tree *right;
    int height;
};

struct Tree *readData(char []);
struct Tree *insertSong(struct Tree *, char [], char [], char [], char [], int, char []);
void displaySongs(struct Tree *);
void popularArtist(struct Tree *);
void oldestSong(struct Tree *);