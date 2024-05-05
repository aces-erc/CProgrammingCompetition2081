// Writess movies to file if the movies are not initially in the file i.e default movies are loaded into the file.
void initializeMoviesFile() {
    FILE *fp = fopen("movies.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    int numMovies = 5; // Number of default movies
    struct movie default_movies[5] = {
        {"Avengers: Endgame", 2, 180, 28, "April", "action, drama", "Russo Brothers", {0}, 60},
        {"Inception", 5, 148, 29, "April", "Sci-fi, adventure", "Christopher Nolan", {0}, 60},
        {"FightClub", 8, 139, 29, "April", "Drama", "David Fincher", {0}, 60}, 
        {"Tumbbad", 6, 104, 28, "April", "Fantasy, Horror, Drama", "Rahi Anil Barve", {0}, 60},
        {"Whiplash", 2, 106, 30, "April", "Drama, Music", "Damien Cazelle", {0}, 60}
    };

    fwrite(&numMovies, sizeof(numMovies), 1, fp); // Write number of movies
    fwrite(default_movies, sizeof(struct movie), numMovies, fp); // Write default movies data
    fclose(fp);
}

// Saves movies into the file.
int saveMoviesToFile(struct movie film[], int numMovies)
{
    FILE *fp = fopen("movies.txt", "w");
    if (fp == NULL)
    {
        printf("\tError opening file.\n");
        return 1;
    }
    fwrite(&numMovies, sizeof(numMovies), 1, fp); // Write number of movies
    fwrite(film, sizeof(struct movie), numMovies, fp); // Write movies data
    fclose(fp);
    return 0;
}

// Loads movie from the file.
int loadMoviesFromFile(struct movie film[], int *numMovies) 
{
    FILE *fp = fopen("movies.txt", "r");
    if (fp == NULL) {
        printf("\tError opening file.\n");
        return 1;
    }
    fread(numMovies, sizeof(*numMovies), 1, fp); // Read number of movies
    fread(film, sizeof(struct movie), *numMovies, fp); // Read movies data
    fclose(fp);
    return 0;
}


int saveReservationToFile(struct reservation reserve[], int reservationCount)
{
    FILE *fp = fopen("reserve.txt", "w");
    if (fp == NULL)
    {
        printf("\tError opening file.\n");
        return 1;
    }
    fwrite(&reservationCount, sizeof(reservationCount), 1, fp);     // Writes number of reservation.
    fwrite(reserve, sizeof(struct reservation), reservationCount, fp);
    fclose(fp);
    return 0;
}

int loadReservationFromFile(struct reservation reserve[], int *reservationCount)
{
    FILE *fp = fopen("reserve.txt", "r");
    if (fp == NULL)
    {
        printf("\tError opening file.\n");
        return 1;
    }
    fread(reservationCount, sizeof(*reservationCount), 1, fp);
    fread(reserve, sizeof(struct reservation), *reservationCount, fp);
    fclose(fp);
    return 0;
}