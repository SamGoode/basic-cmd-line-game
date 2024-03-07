#pragma once
#include "Screen.h"
#include "Player.h"
#include "Room.h"

class Game {
    private:
        Screen screen;
        Player player;
        Room rooms[3][3];
        String userInput;
        String response;

    public:
        Game(int screenWidth, int screenHeight);

        void drawRoom(char chr, int x, int y, int width, int height);

        void showPlayerInfo(int x, int y);

        void showRoomInfo(int x, int y);

        void showMap(int x, int y);

        void showCommandLine(int x, int y);

        void inputLine();

        void processInput();

        void run();
};