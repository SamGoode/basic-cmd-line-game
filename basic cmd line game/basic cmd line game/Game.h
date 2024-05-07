#pragma once
#include "Screen.h"
#include "Player.h"
#include "Room.h"
#include "Enemy.h"

class Game {
    private:
        struct Config {
            struct UISettings {
                int x;
                int y;
            };

            UISettings playerInfo;
            UISettings roomInfo;
            UISettings map;
            UISettings combat;
            UISettings details;
            UISettings commandConsole;
        };

    private:
        Screen screen;

        bool gameRunning;
        int tickRate;

        Config config;

        bool isAnimating;
        int animID;
        int animCount;
        int startX;
        int startY;

        ItemList itemMasterList;
        SpellList spellMasterList;

        Player player;

        Enemy dummy;
        
        Room rooms[5][5];

        int inputState;
        String userInput;
        String response;

    public:
        Game(int screenWidth, int screenHeight, int tickRate);

        ~Game();

        Room& getCurrentRoom();
        Room& getRoom(int x, int y);

        int getInputState();

        void drawRoom(char chr, int x, int y, int width, int height);
        
        void drawPlayer(int x, int y);
        void drawDuck(int x, int y);
        void drawTeleport(int x, int y, int width, int height);

        void drawBorder(int x, int y, int width, int height, bool isThick);
        void drawUIWindow(int x, int y, int width, int height);

        void background();

        void showPlayerInfo(int x, int y);

        void showRoomInfo(int x, int y);

        void showMap(int x, int y);

        void showCombat(int x, int y);

        void showDetails(int x, int y);

        void showCommandConsole(int x, int y);
        void inputLine(int x, int y);
        void processInput();

        void startAnimation(int ID, int startX, int startY);
        void runAnimation(int ID);
        void endAnimation(int ID);

        void run();
};