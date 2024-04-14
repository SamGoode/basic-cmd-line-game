#include "Game.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight) {
    screen = Screen(screenWidth, screenHeight);

    player = Player(*this, 2, 2);
    player.getInventory() = ItemList(3, new Item*[3]{ new FoodItem("apple pie", "wow yummy", 30), new Item("diamond", "wow shiny"), new Item("knife", "wow sharp") }, itemDatabase);
    
    rooms[0][2] = Room("Boss room");
    rooms[1][0] = Room("This room is undergoing construction.");
    rooms[1][3] = Room("It's cold in here.", ItemList(2, new Item*[2]{ new Item("gold coin", "I'm a golden circle"), new Item("ice cube", "I'm a block of ice") }, itemDatabase));
    rooms[2][0] = Room("This room is undergoing construction.");
    rooms[2][1] = Room("This room is undergoing construction.");
    rooms[2][2] = Room("This is the room you started in.");
    rooms[2][3] = Room("It's dark in here");
    rooms[2][4] = Room("This room is undergoing construction.");
    rooms[3][0] = Room("This room is undergoing construction.");
    rooms[3][2] = Room("There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("fancy sword", "I look fancy") }, itemDatabase));
    rooms[3][4] = Room("This room is undergoing construction.");
    rooms[4][2] = Room("There's a wombat in here.");
    rooms[4][1] = Room("It's a large room with training mannequins.", ItemList(1, new Item*[1]{ new Item("training dummy", "It's covered in slash marks") }, itemDatabase));

    inputState = 0;
}

Game::~Game() {
    for (int i = 0; i < itemDatabase.getCount(); i++) {
        delete itemDatabase[i];
    }
}

void Game::drawRoom(char chr, int x, int y, int width, int height) {
    screen.rect(chr, x, y, width, 1);
    screen.rect(chr, x, y + height - 1, width, 1);
    screen.rect(chr, x, y + 1, 2, height - 2);
    screen.rect(chr, x + width - 2, y + 1, 2, height - 2);
}

void Game::drawPlayer(int x, int y) {
    screen.text("(O0)\n/|\\\\", x, y);
}

void Game::drawBorder(int x, int y, int width, int height) {
    screen.input(201, x, y);
    screen.input(200, x, y+height+1);
    screen.input(187, x+width+1, y);
    screen.input(188, x+width+1, y+height+1);

    screen.rect(205, x + 1, y, width, 1);
    screen.rect(205, x + 1, y + height + 1, width, 1);
    screen.rect(186, x, y + 1, 1, height);
    screen.rect(186, x + width + 1, y + 1, 1, height);
}

void Game::showPlayerInfo(int x, int y) {
    drawBorder(x, y, 40, 20);
    
    drawBorder(x + 31, y + 1, 6, 2);
    drawPlayer(x + 33, y + 2);

    screen.text(player.getDescription(), x+2, y+2);
}

void Game::showRoomInfo(int x, int y) {
    drawBorder(x, y, 76, 15);

    screen.text(rooms[player.y][player.x].getDescription(), x+3, y+2);
}

void Game::showMap(int x, int y) {
    drawBorder(x - 39, y - 21, 76, 38);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (rooms[i][j].doesExist()) {
                drawRoom(177, x - 6 + 14 * (j - 2), y - 4 + 7 * (i - 2), 12, 6);
                //177screen.rect(' ', x - 5 - 13 + 13 * j, y - 1 - 11 + 11 * i, 2, 2);
            }
        }
    }

    drawPlayer(x - 2 + 14 * (player.x - 2), y - 2 + 7 * (player.y - 2));
}

void Game::showCommandLine(int x, int y) {
    drawBorder(x, y, 40, 20);

    switch (inputState) {
        case 0:
            screen.text("[move]   [inventory]   [fight]\n\n         [spellbook]", x+6, y+10);
            break;
        case 1:
            screen.text("       [north]\n\n          ^\n[west]  < + >  [east]\n          v\n\n       [south]", x + 10, y + 6);
            screen.text(" [back] ", x + 1, y + 1);
            
            screen.rect(196, x + 1, y + 2, 8, 1);
            screen.rect(179, x + 9, y + 1, 1, 1);

            screen.input(209, x + 9, y);
            screen.input(199, x, y + 2);
            screen.input(217, x + 9, y + 2);
            break;
        case 2:
            screen.text("[use] current selected item\n\nselect different item by\n\nscrolling [up] [down]\n          or\n[select]ing based on index\n[search]ing by name", x+6, y+5);
            screen.text(" [back] ", x + 1, y + 1);

            screen.rect(196, x + 1, y + 2, 8, 1);
            screen.rect(179, x + 9, y + 1, 1, 1);

            screen.input(209, x + 9, y);
            screen.input(199, x, y + 2);
            screen.input(217, x + 9, y + 2);
            break;
        case 3:
            screen.text("[use] current selected item\n\nselect different spell by\n\nscrolling [up] [down]\n          or\n[select]ing based on index\n[search]ing by name", x + 6, y + 5);
            screen.text(" [back] ", x + 1, y + 1);

            screen.rect(196, x + 1, y + 2, 8, 1);
            screen.rect(179, x + 9, y + 1, 1, 1);

            screen.input(209, x + 9, y);
            screen.input(199, x, y + 2);
            screen.input(217, x + 9, y + 2);
    }

    screen.text(response, x+4, y + 17);

    screen.input(175, x + 2, y + 19);
}

void Game::inputLine(int x, int y) {
    std::cout << "\x1b[" + toString(y+1) + ";" + toString(x+1) + "H";
    userInput.ReadFromConsole();
}

int Game::getInputState() {
    return inputState;
}

void Game::processInput() {
    response = "";
    switch (inputState) {
        case 0:
            if (userInput.ToLower() == "move") {
                inputState = 1;
            }
            else if (userInput.ToLower() == "inventory") {
                inputState = 2;
            }
            else if (userInput.ToLower() == "fight") {
                response = "this doesn't work yet";
            }
            else if (userInput.ToLower() == "spellbook") {
                inputState = 3;
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
                if (!rooms[player.y][player.x + 1].doesExist() || player.x == 4) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the east";
                player.x++;
            }
            else if (userInput.ToLower() == "south") {
                if (!rooms[player.y + 1][player.x].doesExist() || player.y == 4) {
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
        case 2:
            if (userInput.ToLower() == "use") {
                response = player.useItem() + " | " + player.getItem()->getName() + "\nDebug: " + typeid(*player.getItem()).name();
            }
            else if (userInput.ToLower() == "up") {
                player.shiftInvIndex(-1);
            }
            else if (userInput.ToLower() == "down") {
                player.shiftInvIndex(1);
            }
            else if (userInput.ToLower().Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                player.setInvIndex(toInt(userInput));
            }
            else if (userInput.ToLower().Find("search ") == 0) {
                userInput.Replace("search ", "");

                int searchResult = player.findItemIndex(userInput);
                if (searchResult == -1) {
                    response = "'" + userInput + "' not found";
                }
                else {
                    response = "'" + userInput + "' found at index " + toString(searchResult);
                    player.setInvIndex(searchResult);
                }
            }
            else if (userInput.ToLower() == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 3:
            if (userInput.ToLower() == "use") {
                response = player.useSpell();
            }
            else if (userInput.ToLower() == "up") {
                player.shiftSpellIndex(-1);
            }
            else if (userInput.ToLower() == "down") {
                player.shiftSpellIndex(1);
            }
            else if (userInput.ToLower().Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                player.setSpellIndex(toInt(userInput));
            }
            else if (userInput.ToLower().Find("search ") == 0) {
                userInput.Replace("search ", "");

                response = "doesn't work yet";
                return;

                int searchResult = player.findItemIndex(userInput);
                if (searchResult == -1) {
                    response = "'" + userInput + "' not found";
                }
                else {
                    response = "'" + userInput + "' found at index " + toString(searchResult);
                    player.setInvIndex(searchResult);
                }
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

    showPlayerInfo(2, 1);

    showRoomInfo(screen.width - 80, screen.height-18);

    showMap(screen.width / 2 + 69, screen.height / 2 - 8);

    showCommandLine(2, screen.height - 23);

    screen.print();

    inputLine(6, screen.height - 4);

    processInput();
}