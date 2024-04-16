#pragma once
#include "Screen.h"
#include "Player.h"
#include "Room.h"

struct Config {
    int x;
    int y;
};

class Game {
    private:
        Screen screen;
        Config config;
        Player player;
        Room rooms[5][5];
        ItemList itemDatabase;
        int inputState;
        String userInput;
        String response;

    public:
        Game(int screenWidth, int screenHeight);

        ~Game();

        void drawRoom(char chr, int x, int y, int width, int height);
        
        void drawPlayer(int x, int y);

        void drawDuck(int x, int y);

        void drawBorder(int x, int y, int width, int height, bool isThick);

        void showPlayerInfo(int x, int y);

        void showRoomInfo(int x, int y);

        void showMap(int x, int y);

        void showDetails(int x, int y);

        void showCommandLine(int x, int y);

        void inputLine(int x, int y);

        int getInputState();

        void processInput();

        void run();
};