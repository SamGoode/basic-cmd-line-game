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

        Config config;

        bool isAnimating;
        int animID;
        int animCount;
        int animX;
        int animY;
        String tempStr;

        Player player;
        Room rooms[5][5];
        ItemList itemMasterList;
        SpellList spellMasterList;
        int inputState;
        String userInput;
        String response;

        Enemy dummy;

    public:
        Game(int screenWidth, int screenHeight);

        ~Game();

        Room& getCurrentRoom();
        Room& getRoom(int x, int y);

        int getInputState();

        void drawRoom(char chr, int x, int y, int width, int height);
        
        void drawPlayer(int x, int y);
        void drawDuck(int x, int y);

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

        void startAnimation(int ID);
        void runAnimation(int ID);
        void endAnimation(int ID);

        void run();
};