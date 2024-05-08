#include <SDL.h>
#include <stdio.h>
#include <conio.h>
#include<string.h>
struct Admin {
    char name[30];
    char password[20];
};
float speed = 100.0f; // Speed in pixels per second
float xspeed = 170.0f;
float yspeed = 170.0f;
float elapsed;
int flag = 0;
int Score1 = 0, Score2 = 0;
struct MyRect {
    float x;
    float y;
    int w;
    int h;
};
struct Player {
    float x;
    float y;
    int w;
    int h;
};
void updatepl1score(int pl1score) {
    Score1 += pl1score;

}
void updatepl2score(int pl2score) {
    Score2 += pl2score;
}
void animateball(struct MyRect* rect) {
    if (flag) {
        rect->x += xspeed * elapsed;
        rect->y += yspeed * elapsed;
        if (rect->x <= 0 || rect->x >= 630)
        {
            xspeed = -xspeed;
            if (rect->x <= 0)
            {
                updatepl2score(1);
            }
            else {
                updatepl1score(1);
            }
        }
        if (rect->y <= 0 || rect->y >= 470)
        {
            yspeed = -yspeed;
        }
    }
}
void moveplayer(struct Player* player1, struct Player* player2) {
    const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
    if (keyboardstate[SDL_SCANCODE_W] && player1->y >= 0)
    {
        player1->y -= speed * elapsed;
    }
    if (keyboardstate[SDL_SCANCODE_S] && player1->y <= 380)
    {
        player1->y += speed * elapsed;
    }
    if (keyboardstate[SDL_SCANCODE_UP] && player2->y >= 0)
    {
        player2->y -= speed * elapsed;
    }
    if (keyboardstate[SDL_SCANCODE_DOWN] && player2->y <= 380)
    {
        player2->y += speed * elapsed;
    }


}

int main() {
    struct Admin admin;
    FILE* fp;
    char adminName[30];
    char password[20];
    errno_t err;

    err = fopen_s(&fp, "verify.txt", "r");
    if (err != 0) {
        err = fopen_s(&fp, "verify.txt", "w");
        if (err != 0) {
            printf("Failed to open file for writing.\n");
            return 1; // Return an error code
        }

        printf("Set Admin: ");
        fgets(admin.name, sizeof(admin.name), stdin);
        admin.name[strcspn(admin.name, "\n")] = '\0'; // Remove newline character
        printf("Set Password: ");
        fgets(admin.password, sizeof(admin.password), stdin);
        admin.password[strcspn(admin.password, "\n")] = '\0'; // Remove newline character

        fwrite(&admin, sizeof(struct Admin), 1, fp);
        fclose(fp);
    }
    else {
        fread(&admin, sizeof(struct Admin), 1, fp);
        fclose(fp);
    }

    do {
        system("cls");
        printf("Admin: ");
        scanf_s("%29s", adminName, sizeof(adminName)); // Limit input to 29 characters
        printf("\nPassword: ");
        scanf_s("%19s", password, sizeof(password)); // Limit input to 19 characters
    } while (!(strcmp(admin.name, adminName) == 0 && strcmp(admin.password, password) == 0));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Enable vsync for smooth rendering
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();
    int running = 1;

    
    struct MyRect rect = { 320 - 5.0f, 240 - 5.0f, 10, 10 };
    struct Player player1 = { 20.0f,240 - 25.0f,20,100 };
    struct Player player2 = { 640 - 40.0f,240 - 50.0f,20,100 };


    while (running) {
        Uint32 currentTick = SDL_GetTicks();
        elapsed = (currentTick - lastTick) / 1000.0f; // Convert milliseconds to seconds
        lastTick = currentTick;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        moveplayer(&player1, &player2);


        // Render a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
        SDL_RenderClear(renderer); // Clear the renderer with black color

        // Draw the white rectangle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set color to white
        SDL_Rect sdlRect = { (int)rect.x, (int)rect.y, rect.w, rect.h }; // Convert MyRect to SDL_Rect
        SDL_RenderFillRect(renderer, &sdlRect); // Fill the rectangle with white color

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect sdlPlayer1 = { (int)player1.x,(int)player1.y,player1.w,player1.h };
        SDL_RenderFillRect(renderer, &sdlPlayer1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect sdlPlayer2 = { (int)player2.x,(int)player2.y,player2.w,player2.h };
        SDL_RenderFillRect(renderer, &sdlPlayer2);

        if (SDL_HasIntersection(&sdlRect, &sdlPlayer1)) {
            xspeed = -xspeed;

        }
        if (SDL_HasIntersection(&sdlRect, &sdlPlayer2)) {
            xspeed = -xspeed;

        }
        const Uint8* keyboardstate = SDL_GetKeyboardState(NULL);
        if (keyboardstate[SDL_SCANCODE_SPACE]) {
            flag = 1;
        }
        if (rect.x <= 0 || rect.x >= 630.0f)
        {
            flag = 0;
            rect.x = 310.0f;
            rect.y = 230.0f;

        }
        if (Score1 >= 3 || Score2 >= 3) {
            running = 0;
            printf("Game Over\n");
            if (Score1 >= 3)
            {
                printf("Player1 Wins");
            }
            else {
                printf("Player2 Wins");
            }

        }
        animateball(&rect);
        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
