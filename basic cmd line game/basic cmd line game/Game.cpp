#include "Game.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight) {
    screen = Screen(screenWidth, screenHeight);

    config = {
        {2, 1},
        {screen.width - 80, screen.height - 18},
        {screen.width / 2 + 69, screen.height / 2 - 8},
        {2, 24},
        {70, screenHeight - 23}
    };

    isAnimating = false;
    animID = 0;
    animCount = 0;
    animX = 0;
    animY = 0;

    player = Player(*this, 2, 2);
    player.getInventory() = ItemList(3, new Item*[3]{ new FoodItem("apple pie", "Wow yummy", 30), new Item("diamond", "Wow shiny"), new Item("knife", "Wow sharp") }, itemDatabase);
    
    rooms[0][2] = Room(*this, "Boss room");
    rooms[1][0] = Room(*this, "This room is undergoing construction.");
    rooms[1][3] = Room(*this, "It's cold in here.", ItemList(2, new Item*[2]{ new Item("gold coin", "I'm a golden circle"), new Item("ice cube", "I'm a block of ice") }, itemDatabase));
    rooms[2][0] = Room(*this, "This room is undergoing construction.");
    rooms[2][1] = Room(*this, "This room is undergoing construction.");
    rooms[2][2] = Room(*this, "This is the room you started in.");
    rooms[2][3] = Room(*this, "It's dark in here");
    rooms[2][4] = Room(*this, "This room is undergoing construction.");
    rooms[3][0] = Room(*this, "This room is undergoing construction.");
    rooms[3][2] = Room(*this, "There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("fancy sword", "I look fancy") }, itemDatabase));
    rooms[3][4] = Room(*this, "This room is undergoing construction.");
    rooms[4][1] = Room(*this, "It's a large room with training mannequins.", ItemList(1, new Item*[1]{ new Item("training dummy", "It's covered in slash marks") }, itemDatabase));
    rooms[4][2] = Room(*this, "There's a wombat in here.");
    rooms[4][3] = Room(*this, "This room is undergoing construction.");
    rooms[4][4] = Room(*this, "This room is undergoing construction.");

    inputState = 0;
}

Game::~Game() {
    for (int i = 0; i < itemDatabase.getCount(); i++) {
        delete itemDatabase[i];
    }

    for (int i = 0; i < 3;i++) {
        delete player.getSpellBook()[i];
    }
    delete[] player.getSpellBook();
}

int Game::getInputState() {
    return inputState;
}

void Game::drawRoom(char chr, int x, int y, int width, int height) {
    screen.rect(chr, x, y, width, 1);
    screen.rect(chr, x, y + height - 1, width, 1);
    screen.rect(chr, x, y + 1, 2, height - 2);
    screen.rect(chr, x + width - 2, y + 1, 2, height - 2);
    screen.rect(' ', x + 2, y + 1, width - 4, height - 2);
}

void Game::drawPlayer(int x, int y) {
    screen.text("(O0)\n/|\\\\", x, y);
}

void Game::drawDuck(int x, int y) {
    screen.text("  _ \n(__)", x, y);
    screen.input(247, x, y);
    screen.input(233, x + 1, y);
}

void Game::drawBorder(int x, int y, int width, int height, bool isThick) {
    if (isThick) {
        screen.input(201, x, y);
        screen.input(200, x, y + height + 1);
        screen.input(187, x + width + 1, y);
        screen.input(188, x + width + 1, y + height + 1);

        screen.rect(205, x + 1, y, width, 1);
        screen.rect(205, x + 1, y + height + 1, width, 1);
        screen.rect(186, x, y + 1, 1, height);
        screen.rect(186, x + width + 1, y + 1, 1, height);
    }
    else {
        screen.input(218, x, y);
        screen.input(192, x, y + height + 1);
        screen.input(191, x + width + 1, y);
        screen.input(217, x + width + 1, y + height + 1);

        screen.rect(196, x + 1, y, width, 1);
        screen.rect(196, x + 1, y + height + 1, width, 1);
        screen.rect(179, x, y + 1, 1, height);
        screen.rect(179, x + width + 1, y + 1, 1, height);
    }
}

void Game::drawUIWindow(int x, int y, int width, int height) {
    drawBorder(x, y, width, height, false);
    drawBorder(x, y, width, 1, true);
    
    screen.input(186, x, y + height);
    screen.input(200, x, y + height + 1);
    screen.input(205, x + 1, y + height + 1);
    screen.input(205, x + 2, y + height + 1);

    screen.input(186, x + width + 1, y + height);
    screen.input(188, x + width + 1, y + height + 1);
    screen.input(205, x + width, y + height + 1);
    screen.input(205, x + width - 1, y + height + 1);
}

void Game::showPlayerInfo(int x, int y) {
    drawUIWindow(x, y, 40, 20);
    screen.text("Player Profile", x + 14, y + 1);
    
    drawBorder(x + 31, y + 3, 6, 2, false);
    drawPlayer(x + 33, y + 4);

    screen.text(player.getDescription(), x+2, y+4);
}

void Game::showRoomInfo(int x, int y) {
    drawUIWindow(x, y, 76, 15);
    screen.text("Room Info", x + 34, y + 1);

    screen.text(rooms[player.y][player.x].getDescription(), x+3, y+4);
}

void Game::showMap(int x, int y) {
    drawBorder(x - 39, y - 21, 76, 38, true);
    screen.rect(177, x - 38, y - 20, 76, 38);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (rooms[i][j].doesExist()) {
                drawRoom(' ', (x - 6) + 14 * (j - 2), (y - 4) + 7 * (i - 2), 12, 6);

                if (rooms[i][j + 1].doesExist() && j < 4) {
                    screen.rect(' ', (x + 6) + 14 * (j - 2), (y - 2) + 7 * (i - 2), 2, 2);
                }
                if (rooms[i + 1][j].doesExist() && i < 4) {
                    screen.rect(' ', (x - 2) + 14 * (j - 2), (y + 2) + 7 * (i - 2), 4, 1);
                }
            }
        }
    }
    
    drawDuck((x - 2) + 14 * (0), (y - 2) + 7 * (-2));
    drawPlayer((x - 2) + 14 * (player.x - 2) + animX, (y - 2) + 7 * (player.y - 2) + animY);
}

void Game::showDetails(int x, int y) {
    drawUIWindow(x, y, 40, 20);
    screen.text("Details", x + 17, y + 1);

    switch (inputState) {
        case 2:
            screen.text("Item:\n" + player.getItem()->getName() + "\n\nDescription:\n" + player.getItem()->getDescription(), x + 3, y + 4);
            break;
        case 3:
            screen.text("Spell:\n" + player.getSpell()->getName() + "\n\nDescription:\n" + player.getSpell()->getDescription(), x + 3, y + 4);
            break;
        case 4:
            if (rooms[player.y][player.x].getItems().getCount() == 0) {
                screen.text("This room has no items", x + 3, y + 4);
                return;
            }

            screen.text("Item:\n" + rooms[player.y][player.x].getItem()->getName() + "\n\nDescription:\n" + rooms[player.y][player.x].getItem()->getDescription(), x + 3, y + 4);
            break;
    }
}

void Game::showCommandLine(int x, int y) {
    drawUIWindow(x, y, 40, 20);
    screen.text("Input Console", x + 14, y + 1);

    switch (inputState) {
        case 0:
            screen.text("[move]   [inventory]   [fight]\n\n[room]   [spellbook]", x+6, y+10);
            break;
        case 1:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);
            
            screen.text("       [north]\n\n          ^\n[west]  < + >  [east]\n          v\n\n       [south]", x + 10, y + 6);
            break;
        case 2:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);

            screen.text("[use] current selected item\n\nselect different item by\n\nscrolling [up] [down]\n[select]ing based on index\n[search]ing by name", x + 6, y + 6);
            break;
        case 3:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);
            
            screen.text("[cast] current selected spell\n\nselect different spell by\n\nscrolling [up] [down]\n[select]ing based on index\n[search]ing by name", x + 6, y + 6);
            break;
        case 4:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);

            screen.text("[take] current selected item\n\nselect different item by\n\nscrolling [up] [down]", x + 6, y + 6);
            break;
    }

    screen.text(response, x + 5, y + 17);

    screen.input(175, x + 3, y + 19);
}

void Game::inputLine(int x, int y) {
    std::cout << "\x1b[" + toString(y+1) + ";" + toString(x+1) + "H";
    userInput.ReadFromConsole();
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
            else if (userInput.ToLower() == "room") {
                inputState = 4;
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
                startAnimation(0);
            }
            else if (userInput.ToLower() == "east") {
                if (!rooms[player.y][player.x + 1].doesExist() || player.x == 4) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the east";
                player.x++;
                startAnimation(1);
            }
            else if (userInput.ToLower() == "south") {
                if (!rooms[player.y + 1][player.x].doesExist() || player.y == 4) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the south";
                player.y++;
                startAnimation(2);
            }
            else if (userInput.ToLower() == "west") {
                if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                    response = "room doesn't exist.";
                    return;
                }

                response = "You entered the room to the west";
                player.x--;
                startAnimation(3);
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
                response = player.useItem() + "\nDebug: " + player.getItem()->getName() + "|" + typeid(*player.getItem()).name();
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
                response = "tried to go to " + toString(toInt(userInput));
                player.setInvIndex(toInt(userInput));
            }
            else if (userInput.ToLower().Find("search ") == 0) {
                userInput.Replace("search ", "");

                int searchResult = player.getInventory().findItemIndex(userInput);
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
            if (userInput.ToLower() == "cast") {
                response = player.castSpell() + "\nDebug: " + player.getSpell()->getName() + "|" + typeid(*player.getSpell()).name();
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
                response = "tried to go to " + toString(toInt(userInput));
                player.setSpellIndex(toInt(userInput));
            }
            else if (userInput.ToLower().Find("search ") == 0) {
                userInput.Replace("search ", "");

                int searchResult = player.findSpellIndex(userInput);
                if (searchResult == -1) {
                    response = "'" + userInput + "' not found";
                }
                else {
                    response = "'" + userInput + "' found at index " + toString(searchResult);
                    player.setSpellIndex(searchResult);
                }
            }
            else if (userInput.ToLower() == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 4:
            if (userInput.ToLower() == "take") {
                if (rooms[player.y][player.x].getItems().getCount() == 0) {
                    response = "this room has no items to take";
                    return;
                }

                response = "You took the " + rooms[player.y][player.x].getItem()->getName() + "\nDebug: " + typeid(*rooms[player.y][player.x].getItem()).name();
                //rooms[player.y][player.x].removeItem();
                player.takeItem(rooms[player.y][player.x]);
            }
            else if (userInput.ToLower() == "up") {
                rooms[player.y][player.x].shiftItemsIndex(-1);
            }
            else if (userInput.ToLower() == "down") {
                rooms[player.y][player.x].shiftItemsIndex(1);
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

void Game::startAnimation(int ID) {
    isAnimating = true;
    animID = ID;
    tempStr = response;
    response = "";

    switch (ID) {
        case 0:
            player.y++;
            break;
        case 1:
            player.x--;
            break;
        case 2:
            player.y--;
            break;
        case 3:
            player.x++;
            break;
    }
}

void Game::runAnimation(int ID) {
    switch (ID) {
        case 0:
            if (animCount % 5 == 0) {
                animY -= 1;
            }

            animCount++;

            if (animCount > 34) {
                endAnimation(ID);
            }
            break;
        case 1:
            if (animCount % 5 == 0) {
                animX += 2;
            }

            animCount++;

            if (animCount > 34) {
                endAnimation(ID);
            }
            break;
        case 2:
            if (animCount % 5 == 0) {
                animY += 1;
            }

            animCount++;

            if (animCount > 34) {
                endAnimation(ID);
            }
            break;
        case 3:
            if (animCount % 5 == 0) {
                animX -= 2;
            }

            animCount++;

            if (animCount > 34) {
                endAnimation(ID);
            }
            break;
    }
}

void Game::endAnimation(int ID) {
    isAnimating = false;
    animCount = 0;
    animX = 0;
    animY = 0;
    response = tempStr;

    switch (ID) {
        case 0:
            player.y--;
            break;
        case 1:
            player.x++;
            break;
        case 2:
            player.y++;
            break;
        case 3:
            player.x--;
            break;
    }
}

void Game::run() {
    screen.reset();

    showPlayerInfo(config.playerInfo.x, config.playerInfo.y);
    
    showRoomInfo(config.roomInfo.x, config.roomInfo.y);

    showMap(config.map.x, config.map.y);

    if (inputState > 1) {
        showDetails(config.details.x, config.details.y);
    }
    
    showCommandLine(config.commandLine.x, config.commandLine.y);
    
    screen.print();

    if (isAnimating) {
        runAnimation(animID);
        
        return;
    }

    inputLine(config.commandLine.x + 5, config.commandLine.y + 19);

    processInput();
}