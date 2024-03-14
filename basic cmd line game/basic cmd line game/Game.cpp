#include "Game.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight) {
    screen = Screen(screenWidth, screenHeight - 1);

    player = Player(1, 1);
    player.getInventory().addItem(new Item("diamond", "wow shiny"), itemDatabase);
    player.getInventory().addItem(new FoodItem("apple pie", "wow yummy", 30), itemDatabase);
    player.getInventory().addItem(new Item("knife", "wow sharp"), itemDatabase);
    player.getInventory().addItem(new Item("knife", "wow sharp"), itemDatabase);
    player.getInventory().addItem(new Item("knife", "wow sharp"), itemDatabase);
    
    rooms[0][0] = Room("There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("fancy sword", "I look fancy") }, itemDatabase));
    rooms[0][1] = Room("It's cold in here.", ItemList(2, new Item*[2]{ new Item("ice cube", "I'm a block of ice"), new Item("gold coin", "I'm a golden circle") }, itemDatabase));
    rooms[0][2] = Room("There's a wombat in here.");
    rooms[1][1] = Room("This is the room you started in.");
    rooms[1][0] = Room("It's a large room with training mannequins.", ItemList(1, new Item*[1]{ new Item("training mannequin", "It's a straw and cotton humanlike figure with slash marks") }, itemDatabase));
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
    screen.text(String("Player stats:\n\nHealth: ") + toString(player.getHealth()) + "\n\nCoordinates: x:" + toString(player.x) + ", y : " + toString(player.y) + "\n\nInventory:\n" + toString(player.getInventory().getCount()) + " items", x, y);
    for (int i = 0; i < player.getInventory().getCount(); i++) {
        screen.text(player.getInventory()[i]->getName(), x, y + 7 + i * 3);
        screen.text(player.getInventory()[i]->getDescription(), x + 2, y + 7 + i * 3 + 1);
    }
}

void Game::showRoomInfo(int x, int y) {
    screen.text(rooms[player.y][player.x].getDescription(), x, y);
}

void Game::showMap(int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (rooms[i][j].doesExist()) {
                drawRoom('x', x - 4 - 13 + 13 * j, y - 4 - 11 + 11 * i, 8, 8);
                //screen.rect(' ', x - 5 - 13 + 13 * j, y - 1 - 11 + 11 * i, 2, 2);
            }
        }
    }
    screen.rect('=', x - 1 - 13 + 13 * player.x, y - 1 - 11 + 11 * player.y, 2, 2);
}

void Game::showCommandLine(int x, int y) {
    screen.text("Move 'north', 'east', 'south', 'west'", x, y);
    screen.text(response, x, y + 2);
}

void Game::inputLine() {
    std::cout << std::endl << "     ";
    userInput.ReadFromConsole();
}

void Game::processInput() {
    response = "";
    if (userInput.ToLower() == "eat") {
        response = player.getInventory()[1]->use(player) + " | " + player.getInventory()[1]->getName() + "  " + typeid(*player.getInventory()[1]).name();
    }
    else if (userInput.ToLower() == "north") {
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
    else {
        response = "invalid input";
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