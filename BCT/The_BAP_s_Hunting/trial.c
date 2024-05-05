#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#define INITIAL_PLAYER_HEALTH 200

// void Draw(char[], char[], char[], char[], int, int, int);
void Start();
void Draw();
void DrawLine()
{
    int i;
    printf("\n\t ");
    for (i = 0; i < 103; i++)
        printf("-");
}
void DrawMonsterStats();
void DrawSpace() { printf("\n\t|%103s|", " "); }
void GoCrimsonValley();
void GoInfernia();
void GoShadowVale();
// void GoJungle();
void GoStore();
void UpgradeWeapon();
void BuyPotion();
void FightMonster(int);
void Attack();
void UseHealthPotion();
void Run();
void MonsterAttack();
void Death();
void Win();
void WaitForOneCLick();
void ChangeHealthBarColor(float);
void Intro();
void AddPlayer();
void DisplayRecord();
void SaveState();
void LoadState();
void UpdateRecord(int);

enum colors
{
    red,
    green,
    yellow,
    originalColor
};

void ChangeFontColor(enum colors);

int currentLocationIndex, currentMonsterIndex, currentWeaponIndex, currentPlayerUID;
int health, monsterHealth, gold, xp, maxHealth, potionsCount, playersCount;
int isFighting, showPlayerControls, isFirstTime;
char description[1000], playerName[30] = "Prabin";
FILE *recordFile, *gameManager, *cacheFile;

typedef struct location
{
    char name[25];
    char option1[30];
    char option2[30];
    char option3[30];
    char description[1000];
} location;
// location jungle = {.name = "Jungle", .option1 = "Fight Zombie", .option2 = "Fight Skeleton", .option3 = "Go Back To Home", .description = "Jungle", .deathMessage = "You were found by a Woodcutter who was cutting trees nearby."};

// location infernia = {.name = "The Infernia Dimension", .option1 = "Fight Magma Titan", .option2 = "Fight Ember", .option3 = "Go Back To Crimson Valley", .description = "\t As you step through the threshold into \x1b[38;2;255;77;0mThe INFERNIA\x1b[0m, a wave of intense heat washes over you, searing your\n\t senses with its fiery embrace. Amidst the jagged landscape, you catch glimpses of two ominous figures:\n\t The Ember and The Magma Titans. \x1b[38;2;255;77;0mThe Ember\x1b[0m, wreathed in flames, floats effortlessly above pools of\n\t molten lava, its fiery gaze fixated upon INTRUDERS with an unrelenting hunger. Nearby, \x1b[38;2;255;77;0mThe Magma Titan\x1b[0m\n\t roams with an eerie purpose, its corrupted form a haunting reminder of a once-mortal existence. Their\n\t presence adds to the palpable tension, serving as guardians of this fiery realm, ready to defend it from\n\t any who dare to CHALLANGE its dominion."};

location crimsonValley = {.name = "CrimsonValley", .option1 = "Go to Store", .option2 = "Go To The Infernia", .option3 = "Go To The ShadowVale", .description = "\tCrimson Valley, a peaceful place where colorful flowers bloom, gentle streams flow, and sunlight warms.\n\tNearby is a hunter store and you see two paths: one leading to the fiercy \x1b[38;2;255;77;0mINFERNIA\x1b[0m dimension and another\n\tto the dark \x1b[38;2;76;0;153mSHADOWVALE\x1b[0m dimension. What is your choice?"};
location store = {.name = "Store", .option1 = "Upgrade Weapon", .option2 = "Buy Potion", .option3 = "Go Outside", .description = "\tYou entered the store.\n\t-->Upgrade Weapons\n\t\t-->Ember Blade - 100 gold\n\t\t-->StormCaller - 200 gold\n\t\t-->InfernoEdge - 500 gold\n\t\t-->ThunderStrike - 800 gold\n\t-->Buy Potion - 20 gold\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: How may I assist you sir?"};
location infernia = {.name = "The Infernia Dimension", .option1 = "Fight Magma Titan", .option2 = "Fight Ember", .option3 = "Go Back To Crimson Valley", .description = "\t As you step through the threshold into \x1b[38;2;255;77;0mThe INFERNIA\x1b[0m, a wave of intense heat washes over you, searing your\n\t senses with its fiery embrace. Amidst the jagged landscape, you catch glimpses of two ominous figures:\n\t The Ember and The Magma Titans. \x1b[38;2;255;77;0mThe Ember\x1b[0m, wreathed in flames, floats effortlessly above pools of\n\t molten lava, its fiery gaze fixated upon INTRUDERS with an unrelenting hunger. Nearby, \x1b[38;2;255;77;0mThe Magma Titan\x1b[0m\n\t roams with an eerie purpose, its corrupted form a haunting reminder of a once-mortal existence. Their\n\t presence adds to the palpable tension, serving as guardians of this fiery realm, ready to defend it from\n\t any who dare to CHALLANGE its dominion."};
location shadowvale = {.name = "The Shadowvale Dimension", .option1 = "Fight Nightstalker", .option2 = "Fight NYX - The Dragon", .option3 = "Go Back To Crimson Valley", .description = "\tIn the chilling void of \x1b[38;2;76;0;153mThe SHADOWVALE\x1b[0m, where darkness reigns supreme, the player stands amidst the haunting \n\twhispers of \x1b[38;2;76;0;153mThe Nightstalker\x1b[0m, their glowing eyes piercing through the abyss. Yet, looming above them all, \n\tthe colossal silhouette of \x1b[38;2;76;0;153mNYX - The Dragon\x1b[0m casts a shadow of dread, its unearthly roars echoing through \n\tthe desolate expanse as the final showdown between mortal and otherworldly forces draws near"};
location fighting = {.name = "Fighting Zone", .option1 = "Attack", .option2 = "Use Health Potion", .option3 = "Run"};
location locationArray[5];

typedef struct monster
{
    char name[50];
    int maxHealth;
    int level;
    int power;
    char deathMessage[1000];
    char attackMessage[150];
    char intro[500];
} monster;
// monster zombie = {.name = "Zombie", .maxHealth = 40, .level = 5, .power = 3};
// monster skeleton = {.name = "Skeleton", .maxHealth = 70, .level = 10, .power = 10};
// monster magmaTitan = {.name = "Magma Titan", .maxHealth = 150, .level = 20, .power = 20,
// .intro="\tFacing the towering \x1b[38;2;255;0;0mMagma Titan\x1b[0m, the player feels the intense heat radiating from its molten form. With\n\tevery earth-shaking step, the Titan unleashes waves of scorching energy, forcing the player to dance between\n\tfiery eruptions as they seek to topple the elemental giant.",
// .attackMessage="\n\tAs the Magma Titan's fury ignites, The player's defenses falter due to searing heat \x1b[38;2;255;0;0m(-20)\x1b[0m"};
monster magmaTitan = {.name = "Magma Titan", .maxHealth = 150, .level = 20, .power = 20, .intro = "\tFacing the towering \x1b[38;2;255;0;0mMagma Titan\x1b[0m, you felt the intense heat radiating from its molten form. \n\tYou are now facing the Magma Titan", .attackMessage = "\n\tAs the Magma Titan's fury ignites, The player's defenses falter due to searing heat \x1b[38;2;255;0;0m(-20)\x1b[0m", .deathMessage = "\n\t\x1b[38;2;255;0;0mYOU LOST\x1b[0m. The Magma Titan crushed you to the ground with a sinister laugh in his face and you fell unconscious.\n\t\n\tBut miraculously you were \x1b[38;2;0;255;0mrevived\x1b[0m by mysterious life force and found \n\tyourself lying in bed in your house. Better be prepared well next time."};

monster ember = {.name = "Ember", .maxHealth = 200, .level = 25, .power = 40, .attackMessage = "\n\tThe Ember attacks with flames, hitting the player relentlessly \x1b[38;2;255;0;0m(-40)\x1b[0m", .intro = "\n\tAs you venture deeper into the Infernia's fiery domain, the air thickens with the ominous crackle \n\tof flames, and shadows dance with the flickering light of \x1b[38;2;255;0;0mEmber\x1b[0m lurking ahead.\n\tYou are now facing \x1b[38;2;255;0;0mThe Ember\x1b[0m", .deathMessage = "\n\t\x1b[38;2;255;0;0mYOU LOST\x1b[0m. In the end you couldn't fend of the fiercy attack of The Ember and fall unconscious. \n\tBut miraculously you were \x1b[38;2;0;255;0mrevived\x1b[0m by mysterious life force and found \n\tyourself lying in bed in your house. Better be prepared well next time."};

monster nightstalker = {.name = "NightStalker", .maxHealth = 300, .level = 35, .power = 70, .attackMessage = "\n\tThe NightStalker fires a viscious laser beam from its eye. You felt like a rod piercing your head. \x1b[38;2;255;0;0m(-70)\x1b[0m", .intro = "\n\tAs you gaze upon The NightStalker, he traveled at supersonic speed and stand in front of you ready to launch \n\tan attack. You are now facing \x1b[38;2;76;0;153mThe Nightstalker\x1b[0m", .deathMessage = "\n\t\x1b[38;2;255;0;0mYOU LOST\x1b[0m. You couldn't stand the piercing pain and fall at the hand of \x1b[38;2;76;0;153mThe Nightstalker\x1b[0m.\n\tBut miraculously you were \x1b[38;2;0;255;0mrevived\x1b[0m by mysterious life force and found \n\tyourself lying in bed in your house. Better be prepared well next time."};
monster nyx = {.name = "NYX - The Dragon", .maxHealth = 600, .level = 55, .power = 100, .attackMessage = "\n\tAs Nyx, the dread wyrm, unleashes its wrath upon you, you saw actual death in front of you. \x1b[38;2;255;0;0m(-100)\x1b[0m", .intro = "\n\tAs the ominous silhouette of \x1b[38;2;76;0;153mNYX, The Shadow Wyrm\x1b[0m, looms over the horizon, darkness spreads like a sinister \n\tveil across the land.With every beat of its colossal wings, the very fabric of reality shudders, signaling \n\tthe beginning of a harrowing journey into the heart of darkness. You are now facing \x1b[38;2;76;0;153mNYX - The Dragon\x1b[0m", .deathMessage = "\n\t\x1b[38;2;255;0;0mYOU LOST\x1b[0m. As the player's valiant efforts falter beneath the overwhelming might of \x1b[38;2;76;0;153mNYX, The Shadow Wyrm\x1b[0m,the chilling embrace of the \n\tdragon's breath consumes them, their spirit fading into the eternal night, a testament to the formidable \n\tpower of the ancient beast.\n\tBut miraculously you were \x1b[38;2;0;255;0mrevived\x1b[0m by mysterious life force and found \n\tyourself lying in bed in your house. Better be prepared well next time."};
monster monsterArray[4];

typedef struct weapons
{
    char name[50];
    int power;
    int cost;
    char attackMessage[200];
} weapon;
weapon frostFang = {.name = "FrostFang", .power = 20, .cost = 50, .attackMessage = "\n\tWielding only the FrostFang, the player bravely strikes at the monstrous creature, hoping to fend off their assaults\x1b[38;2;0;255;0m(-20)\x1b[0m"};
weapon emberblade = {.name = "Emberblade", .power = 50, .cost = 100, .attackMessage = "\n\tWith a determined grip on their EmberBlade, the player faces the enemy, poised \n\tto defend against the relentless assault with steadfast resolve.\x1b[38;2;0;255;0m(-50)\x1b[0m"};
weapon stormcaller = {.name = "Stormcaller", .power = 100, .cost = 200, .attackMessage = "\n\tWith the StormCaller gripped tightly, the player plunges into combat against the Monster.\x1b[38;2;0;255;0m(-100)\x1b[0m"};
weapon infernoEdge = {.name = "Inferno Edge", .power = 300, .cost = 500, .attackMessage = "\n\tWith an Inferno Edge tightly, the player plunges into combat against the Monster.\x1b[38;2;0;255;0m(-300)\x1b[0m"};
weapon thunderstrike = {.name = "Thunderstrike", .power = 500, .cost = 800, .attackMessage = "\n\tWith a gleaming \x1b[38;2;0;255;255mThunderStrike\x1b[0m, the player charges into the fray against the Monster with unwavering determination.\x1b[38;2;0;255;0m(-500)\x1b[0m"};
weapon weaponArray[5];

int main()
{
    int input, i;
    int validInputFlag;
    Start();
    Intro();
    for (i = 0;; i++)
    {
        Draw();
        validInputFlag = 0;
        while (validInputFlag == 0)
        {
            scanf("%d", &input);
            // To Finish Game In Debugging Process5
            if (input == 52)
                exit(0);

            if (input > 0 && input < 4)
                validInputFlag = 1;
            else
            {
                strcpy(description, "Invalid Input! Please Try again!!");
                Draw();
            }
        }

        switch (currentLocationIndex)
        {
        case 0:
            switch (input)
            {
            case 1:
                GoStore();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 2:
                GoInfernia();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 3:
                GoShadowVale();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;
            }
            break;

        case 1:
            switch (input)
            {
            case 1:
                UpgradeWeapon();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 2:
                BuyPotion();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 3:
                GoCrimsonValley();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;
            }
            break;

        case 2:
            switch (input)
            {
            case 1:
                FightMonster(0);
                // strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 2:
                FightMonster(1);
                // strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 3:
                GoCrimsonValley();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;
            }
            break;

        case 3:
            switch (input)
            {
            case 1:
                FightMonster(2);
                // strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 2:
                FightMonster(3);
                // strcpy(description, locationArray[currentLocationIndex].description);
                break;

            case 3:
                GoCrimsonValley();
                strcpy(description, locationArray[currentLocationIndex].description);
                break;
            }
            break;

        case 4:
            switch (input)
            {
            case 1:
                Attack();
                break;

            case 2:
                UseHealthPotion();
                break;

            case 3:
                Run();
                strcpy(description, "You Coward");
                break;
            }
            break;
        }
    }
    return 0;
}

void Start()
{
    locationArray[0] = crimsonValley;
    // locationArray[1] = jungle;
    locationArray[1] = store;
    locationArray[2] = infernia;
    locationArray[3] = shadowvale;
    locationArray[4] = fighting;

    // monsterArray[0] = zombie;
    // monsterArray[1] = skeleton;
    monsterArray[0] = magmaTitan;
    monsterArray[1] = ember;
    monsterArray[2] = nightstalker;
    monsterArray[3] = nyx;

    weaponArray[0] = frostFang;
    weaponArray[1] = emberblade;
    weaponArray[2] = stormcaller;
    weaponArray[3] = infernoEdge;
    weaponArray[4] = thunderstrike;

    playersCount = 1;
    potionsCount = 0;
    isFighting = 0;
    isFirstTime = 1;
    showPlayerControls = 1;
    maxHealth = INITIAL_PLAYER_HEALTH;
    currentMonsterIndex = 0;
    currentLocationIndex = 0;
    currentWeaponIndex = 0;
    strcpy(description, locationArray[currentLocationIndex].description);
    monsterHealth = 20;
    health = INITIAL_PLAYER_HEALTH;
    gold = 5000;
    xp = 0;

    LoadState();
}

// void Draw(char option1[50], char option2[50], char option3[50], char description[2000], int health, int gold, int xp)
void Draw()
{
    // char healthText[20] = "Health: ", goldText[20] = "Gold: ", xpText[20] = "Exp: ", healthString[5], goldString[5], xpString[5];

    // code for player health bar calculation
    char progressBar[21] = "";
    float healthRatio;
    int j;
    // healthRatio = ceil(((float)health / maxHealth) * 20);
    healthRatio = ceil(((float)health / maxHealth) * 20);
    // printf("%d", healthRatio);
    for (j = 0; j < 20; j++)
    {
        if (j < healthRatio)
            strcat(progressBar, "#");
        else
            strcat(progressBar, "=");
    }

    // sprintf(healthString, "%d", health);
    // sprintf(goldString, "%d", gold);
    // sprintf(xpString, "%d", xp);
    // strcat(healthText, healthString);
    // strcat(goldText, goldString);
    // strcat(xpText, xpString);
    UpdateRecord(currentPlayerUID);
    system("cls");
    printf("\n\n%75s\n\n", "The BAP's Hunting");

    // Drawing The Player Stats
    // printf("\x1b[38;2;0;255;43m");
    // printf("\x1b[38;5;13m");
    ChangeFontColor(green);
    DrawLine();
    printf("\n\t|\t%s %-24d%s %-24d%s %-24d\t|\n\t|", "Health:", health, "Gold:", gold, "Exp:", xp);
    ChangeHealthBarColor((float)health / maxHealth);
    printf("\t%-31s", progressBar);
    ChangeFontColor(green);
    printf("%-31s%s %-23d\t|", " ", "Potions:", potionsCount);
    // printf("\t%-31s\x1b[38;2;0;255;43m%-31s%s %-23d\t|", progressBar, " ", "Potions:", potionsCount);
    printf("\n\t|\t%-31s%-31s%s %-23s\t|", " ", " ", "Weapon:", weaponArray[currentWeaponIndex].name);
    DrawLine();

    // MOnster Draws Here
    if (isFighting == 1)
    {
        // printf("\x1b[38;2;255;77;0m");
        ChangeFontColor(red);
        DrawMonsterStats();
    }

    // Description
    //  printf("\x1b[0m");
    ChangeFontColor(originalColor);
    printf("\n\n%65s\n", locationArray[currentLocationIndex].name);
    printf("\n\n%s\n", description);
    // Drawing Player Controls
    // printf("\x1b[38;2;247;255;0m");
    ChangeFontColor(yellow);
    if (showPlayerControls == 1)
    {
        DrawLine();
        printf("\n\t|%56s%47s|", "Choose An Option!!", " ");
        DrawLine();
        DrawSpace();
        printf("\n\t|\t1.%-28s2.%-28s3.%-28s\t|", locationArray[currentLocationIndex].option1, locationArray[currentLocationIndex].option2, locationArray[currentLocationIndex].option3);
        DrawSpace();
        DrawLine();
        ChangeFontColor(originalColor);
        printf("\n\tEnter Your Option Here --> ");
    }
}

// void DrawMonsterStats(char monsterName[], int monsterHealth, int monsterLevel)
void DrawMonsterStats()
{
    // char healthText[20] = "Health: ", levelText[20] = "Level: ", healthString[5], levelString[5];

    // code for health bar calculation
    char progressBar[21] = "";
    int healthRatio, i;
    healthRatio = ceil(((float)monsterHealth / monsterArray[currentMonsterIndex].maxHealth) * 20);
    for (i = 0; i < 20; i++)
    {
        if (i < healthRatio)
            strcat(progressBar, "#");
        else
            strcat(progressBar, "=");
    }

    // sprintf(healthString, "%d", monsterHealth);
    // sprintf(levelString, "%d", monsterLevel);
    // strcat(healthText, healthString);
    // strcat(levelText, levelString);

    // Drawing Monster Stats
    DrawLine();
    printf("\n\t|%56s%47s|", monsterArray[currentMonsterIndex].name, " ");
    DrawLine();
    DrawSpace();
    printf("\n\t|\t%s %-24d%-31s%s %-24d\t|\n\t|", "Health:", monsterHealth, " ", "Level:", monsterArray[currentMonsterIndex].level);
    ChangeHealthBarColor((float)monsterHealth / monsterArray[currentMonsterIndex].maxHealth);
    printf("\t%-31s\x1b[38;2;255;77;0m%-31s%-31s\t|", progressBar, " ", " ");
    DrawSpace();
    DrawLine();
}

void GoCrimsonValley() { currentLocationIndex = 0; }
// void GoJungle() { currentLocationIndex = 1; }
void GoStore() { currentLocationIndex = 1; }
void GoInfernia() { currentLocationIndex = 2; }
void GoShadowVale() { currentLocationIndex = 3; }

void FightMonster(int monsterIndex)
{
    isFighting = 1;
    currentLocationIndex = 4;
    currentMonsterIndex = monsterIndex;
    monsterHealth = monsterArray[currentMonsterIndex].maxHealth;
    strcpy(description, monsterArray[currentMonsterIndex].intro);
}

void Attack()
{
    monsterHealth -= weaponArray[currentWeaponIndex].power;
    if (monsterHealth <= 0)
        Win();
    else
    {
        strcpy(description, weaponArray[currentWeaponIndex].attackMessage);
        WaitForOneCLick();
        MonsterAttack();
    }
}

void UseHealthPotion()
{
    if (potionsCount <= 0)
    {
        strcat(description, "\n--> You are out of potions!!");
        WaitForOneCLick();
        return;
    }
    health += 60;
    potionsCount--;
    if (health > maxHealth)
        maxHealth = health;
    strcpy(description, "You restored 60 hp");
    WaitForOneCLick();
    MonsterAttack();
}

void Run()
{
    currentLocationIndex = 0;
    isFighting = 0;
}

void Win()
{
    monsterHealth = 0;
    xp += monsterArray[currentMonsterIndex].level;
    gold += monsterArray[currentMonsterIndex].power;
    if (currentMonsterIndex == 5)
    {
        strcpy(description, "--> HERO");
        WaitForOneCLick();
    }
    else
    {
        strcpy(description, "\n\t \x1b[38;2;0;255;0mCongratulation!! You killed that monster.\x1b[0m");
        WaitForOneCLick();
    }
    currentLocationIndex = 0;
    isFighting = 0;
    strcpy(description, locationArray[currentLocationIndex].description);
}

void MonsterAttack()
{
    health -= monsterArray[currentMonsterIndex].power;
    Beep(600, 300);
    strcat(description, monsterArray[currentMonsterIndex].attackMessage);
    WaitForOneCLick();
    if (health <= 0)
    {
        Beep(600, 1000);
        Death();
    }
}

void Death()
{

    gold -= 30;
    strcpy(description, monsterArray[currentMonsterIndex].deathMessage);
    // Draw();

    WaitForOneCLick();
    currentLocationIndex = 0;
    isFighting = 0;
    health = INITIAL_PLAYER_HEALTH;
    maxHealth = INITIAL_PLAYER_HEALTH;
    if (gold <= 0)
    {
        gold = 0;
        strcat(description, "\n--> You lost all your money.");
        WaitForOneCLick();
    }
    else
        strcat(description, "\n--> You lost some money.");
}

void WaitForOneCLick()
{
    showPlayerControls = 0;
    strcat(description, "\t\x1b[38;2;255;255;0m(Press Any Key )\x1b[0m");
    Draw();
    getch();
    showPlayerControls = 1;
}

void UpgradeWeapon()
{
    if (currentWeaponIndex >= 4)
    {
        strcat(description, "\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: Your Weapon is Maxed Out!");
        WaitForOneCLick();
    }
    else if (gold < weaponArray[currentWeaponIndex + 1].cost)
    {
        strcat(description, "\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: Sorry sir, You dont have enough money.");
        WaitForOneCLick();
    }
    else
    {
        strcat(description, "\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: Congratulations sir!! Upgrade Successful");
        WaitForOneCLick();
        gold -= weaponArray[currentWeaponIndex + 1].cost;
        currentWeaponIndex++;
    }
}

void BuyPotion()
{
    if (gold < 20)
    {
        strcat(description, "\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: Sorry sir! You Don't have enough money.");
        WaitForOneCLick();
    }
    else
    {
        gold -= 20;
        potionsCount++;
        strcat(description, "\n\t\x1b[38;2;0;0;255mStoreguy\x1b[0m: Here is your potion sir.");
    }
}

void ChangeFontColor(enum colors fontColor)
{
    switch (fontColor)
    {
    case red:
        printf("\x1b[38;2;255;77;0m");
        break;

    case green:
        printf("\x1b[38;2;0;255;43m");
        break;

    case yellow:
        printf("\x1b[38;2;247;255;0m");
        break;

    case originalColor:
        printf("\x1b[0m");
        break;
    }
}

void ChangeHealthBarColor(float healthRatio)
{
    int health;
    health = floor(healthRatio * 1000);
    if (health <= 200)
        printf("\x1b[38;2;255;0;0m");
    else if (health <= 400)
        printf("\x1b[38;2;255;127;0m");
    else if (health <= 600)
        printf("\x1b[38;2;255;255;0m");
    else if (health <= 800)
        printf("\x1b[38;2;127;255;0m");
    else
        printf("\x1b[38;2;0;255;0m");
}

void Intro()
{
    int fUID, fExp, fGold, fWeapon, fpotions, fhealth;
    char fFname[25], fLname[25];
    recordFile = fopen("recordFile.txt", "r");
    int a;

    system("cls");

    printf("1. New Player.\n");
    DisplayRecord();
    printf("Choose Yourself:");

IntroAgain:
    scanf("%d", &a);
    if (a == 1)
        AddPlayer();
    else if (a > playersCount)
    {
        printf("Invalid Input: \nChoose Again: ");
        goto IntroAgain;
    }
    else
    {
        fseek(recordFile, 0L, SEEK_SET);
        while (fscanf(recordFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", &fUID, fFname, fLname, &fExp, &fGold, &fWeapon, &fpotions, &fhealth) != EOF)
        {
            if (fUID == a)
            {
                printf("Welcome %s. Let's continue our journey!!!!\tPress any key to continue", fFname);
                strcpy(playerName, fFname);
                xp = fExp;
                gold = fGold;
                currentWeaponIndex = fWeapon;
                currentPlayerUID = fUID;
                potionsCount = fpotions;
                health = fhealth;
                break;
            }
        }
        getch();
        fclose(recordFile);
    }
}

void UpdateRecord(int UID)
{
    int fUID, fExp, fGold, fWeapon, fpotions, fhealth;
    char fFname[25], fLname[25];
    int a, i = 1;

    recordFile = fopen("recordFile.txt", "r");
    cacheFile = fopen("cacheFile.txt", "w");

    while (fscanf(recordFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", &fUID, fFname, fLname, &fExp, &fGold, &fWeapon, &fpotions, &fhealth) != EOF)
    {
        if (fUID == UID)
        {
            fprintf(cacheFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", fUID, fFname, fLname, xp, gold, currentWeaponIndex, potionsCount, health);
        }
        else
        {
            fprintf(cacheFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", fUID, fFname, fLname, fExp, fGold, fWeapon, fpotions, fhealth);
        }
    }
    fclose(recordFile);
    fclose(cacheFile);

    recordFile = fopen("recordFile.txt", "w");
    cacheFile = fopen("cacheFile.txt", "r");

    while (fscanf(cacheFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", &fUID, fFname, fLname, &fExp, &fGold, &fWeapon, &fpotions, &fhealth) != EOF)
    {
        fprintf(recordFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", fUID, fFname, fLname, fExp, fGold, fWeapon, fpotions, fhealth);
    }

    fclose(recordFile);
    fclose(cacheFile);
}

void AddPlayer()
{
    recordFile = fopen("recordFile.txt", "a");
    char fname[25], lname[25];
    const int initialGold = 20;

    printf("Enter your full name: ");
    scanf("%s%s", fname, lname);

    fprintf(recordFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", playersCount + 1, fname, lname, 0, initialGold, 0, 0, INITIAL_PLAYER_HEALTH);
    fclose(recordFile);

    playersCount++;
    SaveState();

    printf("Welcome to this accursed world %s. You Have a tough journey ahead!!!!\tPress any key to continue", fname);
    strcpy(playerName, fname);
    xp = 0;
    gold = initialGold;
    currentWeaponIndex = 0;
    currentPlayerUID = playersCount;
    potionsCount = 0;
    health = INITIAL_PLAYER_HEALTH;
    getch();
}

void DisplayRecord()
{
    int fUID, fExp, fGold, fWeapon, fpotions, fhealth;
    char fFname[25], fLname[25];
    recordFile = fopen("recordFile.txt", "r");

    while (fscanf(recordFile, "UID:%d. fName:%s lName:%s Exp:%d, Gold:%d, Weapon:%d, Potions:%d, Health:%d\n", &fUID, fFname, fLname, &fExp, &fGold, &fWeapon, &fpotions, &fhealth) != EOF)
        printf("%d.%s %s | Exp:%d, Gold:%d, Weapon:%s, Potions:%d, Health:%d\n", fUID, fFname, fLname, fExp, fGold, weaponArray[fWeapon].name, fpotions, fhealth);
}

void SaveState()
{
    gameManager = fopen("GameManager.txt", "w");
    fprintf(gameManager, "PlayerCount:%d\n", playersCount);
    fclose(gameManager);
}

void LoadState()
{
    gameManager = fopen("GameManager.txt", "r");
    fscanf(gameManager, "PlayerCount:%d\n", &playersCount);
    fclose(gameManager);
}