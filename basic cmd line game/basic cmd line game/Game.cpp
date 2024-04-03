#include "Game.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight) {
    screen = Screen(screenWidth, screenHeight - 1);

    player = Player(2, 2);
    player.getInventory() = ItemList(3, new Item*[3]{ new Item("diamond", "wow shiny"), new FoodItem("apple pie", "wow yummy", 30), new Item("knife", "wow sharp") }, itemDatabase);
    
    rooms[0][2] = Room("Boss room");
    rooms[1][3] = Room("It's cold in here.", ItemList(2, new Item*[2]{ new Item("ice cube", "I'm a block of ice"), new Item("gold coin", "I'm a golden circle") }, itemDatabase));
    rooms[2][2] = Room("This is the room you started in.");
    rooms[2][3] = Room("It's dark in here");
    rooms[3][1] = Room("There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("fancy sword", "I look fancy") }, itemDatabase));
    rooms[4][1] = Room("It's a large room with training mannequins.", ItemList(1, new Item*[1]{ new Item("training mannequin", "It's a straw and cotton humanlike figure with slash marks") }, itemDatabase));
    rooms[3][2] = Room("There's a wombat in here.");

    inputState = 0;
}

Game::~Game() {
    for (int i = 0; i < itemDatabase.getCount(); i++) {
        delete itemDatabase[i];
    }
}

void Game::drawRoom(char chr, int x, int y, int width, int height) {
    screen.rect(chr, x, y - 1, width, 2);
    screen.rect(chr, x - 1, y, 2, height);
    screen.rect(chr, x, y + height - 1, width, 2);
    screen.rect(chr, x + width - 1, y, 2, height);
}

void Game::showPlayerInfo(int x, int y) {
    screen.text(player.getDescription(), x, y);
}

void Game::showRoomInfo(int x, int y) {
    screen.text(rooms[player.y][player.x].getDescription(), x, y);
}

void Game::showMap(int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (rooms[i][j].doesExist()) {
                drawRoom('x', x - 4 + 13*(j - 2), y - 4 + 9 * (i - 2), 8, 6);
                //screen.rect(' ', x - 5 - 13 + 13 * j, y - 1 - 11 + 11 * i, 2, 2);
            }
        }
    }
    screen.rect('=', x - 1 + 13*(player.x - 2), y - 2 + 9*(player.y - 2), 2, 2);
}

void Game::showCommandLine(int x, int y) {
    switch (inputState) {
        case 0:
            screen.text("Choose an action 'move', 'eat', 'fight'", x, y);
            break;
        case 1:
            screen.text("Move 'north', 'east', 'south', 'west', or go 'back'", x, y);
            break;
    }

    screen.text(response, x, y + 2);
}

void Game::inputLine() {
    std::cout << std::endl << "     ";
    userInput.ReadFromConsole();
}

void Game::processInput() {
    response = "";
    switch (inputState) {
        case 0:
            if (userInput.ToLower() == "move") {
                inputState = 1;
            }
            else if (userInput.ToLower() == "eat") {
                response = "this doesn't work yet";//player.getInventory()[1]->use(player) + " | " + player.getInventory()[1]->getName() + "  " + typeid(*player.getInventory()[1]).name();
            }
            else if (userInput.ToLower() == "fight") {
                response = "this doesn't work yet";
            }
            else {
                response = "invalid input";
            }
            break;
        case 1:
            if (userInput.ToLower() == "north") {
                if (!rooms[player.y - 1][player.x].doesExist() || player.y == 0) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the north";
                player.y--;
            }
            else if (userInput.ToLower() == "east") {
                if (!rooms[player.y][player.x + 1].doesExist() || player.x == 2) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the east";
                player.x++;
            }
            else if (userInput.ToLower() == "south") {
                if (!rooms[player.y + 1][player.x].doesExist() || player.y == 2) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the south";
                player.y++;
            }
            else if (userInput.ToLower() == "west") {
                if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                    response = "room doesn't exist.";
                    return;
                }

                //rooms[0][1].addItem(Item("diamond", "this wasn't here before"));

                response = "You entered the room to the west";
                player.x--;
            }
            else if (userInput.ToLower() == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
    }
}

void Game::run() {
    screen.reset();

    showPlayerInfo(10, 3);

    showRoomInfo(screen.width - 50, 3);

    showMap(screen.width / 2, screen.height / 2);

    showCommandLine(5, screen.height - 5);

    screen.print();

    inputLine();

    processInput();
}