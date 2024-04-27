#include "Game.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight) {
    screen = Screen(screenWidth, screenHeight);

    config = {
        {3, 1},
        {screen.width - 81, screen.height - 18},
        {screen.width / 2 + 68, screen.height / 2 - 8},
        {50, 2},
        {3, 24},
        {59, screenHeight - 23}
    };

    isAnimating = false;
    animID = 0;
    animCount = 0;
    animX = 0;
    animY = 0;

    player = Player(*this, 2, 2);
    player.getInventory() = ItemList(3, new Item*[3]{ new FoodItem("apple pie", "Wow yummy", 30), new Item("diamond", "Wow shiny"), new Item("knife", "Wow sharp") }, itemMasterList);
    player.getSpellBook() = SpellList(4, new SpellBase*[4]{ new SpellBase("conjure fist", "Conjures a fist to punch an enemy", 1, 5), new SpellBase("dummy spell", "Doesn't do anything"), new SpellBase("hiya", "I don't actually do anything"), new TeleportSpell() }, spellMasterList);
    
    rooms[0][2] = Room(*this, "Boss room");
    rooms[1][0] = Room(*this, "This room is undergoing construction.");
    rooms[1][3] = Room(*this, "It's cold in here.", ItemList(2, new Item*[2]{ new Item("gold coin", "I'm a golden circle"), new Item("ice cube", "I'm a block of ice") }, itemMasterList));
    rooms[2][0] = Room(*this, "This room is undergoing construction.");
    rooms[2][1] = Room(*this, "This room is undergoing construction.");
    rooms[2][2] = Room(*this, "This is the room you started in.");
    rooms[2][3] = Room(*this, "It's dark in here");
    rooms[2][4] = Room(*this, "This room is undergoing construction.");
    rooms[3][0] = Room(*this, "This room is undergoing construction.");
    rooms[3][2] = Room(*this, "There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("fancy sword", "I look fancy") }, itemMasterList));
    rooms[3][4] = Room(*this, "This room is undergoing construction.");
    rooms[4][1] = Room(*this, "It's a large room with training mannequins.", ItemList(1, new Item*[1]{ new Item("training dummy", "It's covered in slash marks") }, itemMasterList));
    rooms[4][2] = Room(*this, "There's a wombat in here.");
    rooms[4][3] = Room(*this, "This room is undergoing construction.");
    rooms[4][4] = Room(*this, "This room is undergoing construction.");

    inputState = 0;
}

Game::~Game() {
    //this is a quite a wacky way of handling it
    //using shared_ptr would be better but if I went down that route, 
    //then I'd want to make my own shared_ptr class
    for (int i = 0; i < itemMasterList.getCount(); i++) {
        delete itemMasterList[i];
    }

    for (int i = 0; i < spellMasterList.getCount(); i++) {
        delete spellMasterList[i];
    }
}

Room& Game::getCurrentRoom() {
    return rooms[player.getY()][player.getX()];
}

Room& Game::getRoom(int x, int y) {
    return rooms[y][x];
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
    screen.rect(' ', x + 1, y + 1, width, height);

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

    screen.text(getCurrentRoom().getDescription(), x + 3, y + 4);
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
    drawPlayer((x - 2) + 14 * (player.getX() - 2) + animX, (y - 2) + 7 * (player.getY() - 2) + animY);
}

void Game::showCombat(int x, int y) {
    drawBorder(x, y, 82, 32, true);

    screen.rect('-', x + 11, y + 21, 12, 2);
    drawPlayer(x + 15, y + 20);

    screen.rect('-', x + 59, y + 6, 12, 2);
    drawDuck(x + 63, y + 5);

    screen.rect(196, x + 1, y + 25, 82, 1);
    screen.input(199, x, y + 25);
    screen.input(182, x + 83, y + 25);
}

void Game::showDetails(int x, int y) {
    drawUIWindow(x, y, 40, 20);
    screen.text("Details", x + 17, y + 1);

    switch (inputState) {
        case 2:
            screen.text("Item:\n" + player.getItem()->getName() + "\n\nDescription:\n" + player.getItem()->getDescription(), x + 3, y + 4);
            break;
        case 3:
            screen.text("Spell:\n" + player.getSpell()->getName() + "\n\nCost: " + toString(player.getSpell()->getCost()) + " mana\nDamage: " + toString(player.getSpell()->getDamage()) + "\n\nDescription:\n" + player.getSpell()->getDescription(), x + 3, y + 4);
            break;
        case 4:
            if (getCurrentRoom().getItems().getCount() == 0) {
                screen.text("This room has no items", x + 3, y + 4);
                return;
            }

            screen.text("Item:\n" + getCurrentRoom().getItem()->getName() + "\n\nDescription:\n" + getCurrentRoom().getItem()->getDescription(), x + 3, y + 4);
            break;
    }
}

void Game::showCommandConsole(int x, int y) {
    drawUIWindow(x, y, 64, 20);
    screen.text("Input Console", x + 26, y + 1);

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
                switch (player.shiftPos(0, -1)) {
                    case 0:
                        response = "You entered the room to the north";
                        startAnimation(0);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput.ToLower() == "east") {
                switch (player.shiftPos(1, 0)) {
                    case 0:
                        response = "You entered the room to the east";
                        startAnimation(1);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput.ToLower() == "south") {
                switch (player.shiftPos(0, 1)) {
                    case 0:
                        response = "You entered the room to the south";
                        startAnimation(2);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput.ToLower() == "west") {
                switch (player.shiftPos(-1, 0)) {
                    case 0:
                        response = "You entered the room to the west";
                        startAnimation(3);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
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
            if (userInput.ToLower().Find("cast") == 0) {
                userInput.Replace("cast", "");
                
                if (userInput.Find(" ") != 0) {
                    response = player.castSpell() + "\nDebug: " + player.getSpell()->getName() + "|" + typeid(*player.getSpell()).name();
                }

                //This is a super scuffed way of doing this
                int argCount = 0;
                for (int i = 0; i < userInput.Length(); i++) {
                    if (userInput[i] == ' ') {
                        argCount++;
                    }
                }

                userInput.Append(" ");

                int* args = new int[argCount];
                for (int i = 0; i < argCount; i++) {
                    userInput.Prepend("\x2");

                    String argStr;
                    int nextArgIndex = userInput.Find(2, " ");
                    for (int j = 0; j < nextArgIndex; j++) {
                        argStr.Append(userInput[j]);
                    }

                    userInput.Replace(argStr, "");
                    argStr.Replace("\x2 ", "");

                    if (toInt(argStr) == 0x80000000) {
                        delete[] args;
                        response = "invalid arguments";
                        return;
                    }

                    args[i] = toInt(argStr);
                }

                response = player.castSpell(argCount, args) + "\nDebug: " + player.getSpell()->getName() + "|" + typeid(*player.getSpell()).name();
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

                int searchResult = player.getSpellBook().findSpellIndex(userInput);
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
                if (getCurrentRoom().getItems().getCount() == 0) {
                    response = "this room has no items to take";
                    return;
                }

                response = "You took the " + getCurrentRoom().getItem()->getName() + "\nDebug: " + typeid(*getCurrentRoom().getItem()).name();
                player.takeItem(getCurrentRoom());
            }
            else if (userInput.ToLower() == "up") {
                getCurrentRoom().shiftItemsIndex(-1);
            }
            else if (userInput.ToLower() == "down") {
                getCurrentRoom().shiftItemsIndex(1);
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
            player.shiftPos(0, 1);
            break;
        case 1:
            player.shiftPos(-1, 0);
            break;
        case 2:
            player.shiftPos(0, -1);
            break;
        case 3:
            player.shiftPos(1, 0);
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
            player.shiftPos(0, -1);
            break;
        case 1:
            player.shiftPos(1, 0);
            break;
        case 2:
            player.shiftPos(0, 1);
            break;
        case 3:
            player.shiftPos(-1, 0);
            break;
    }
}

void Game::run() {
    screen.reset();

    for (int i = 0; i < screen.width; i++) {
        for (int j = 0; j < screen.width; j++) {
            if ((i+j) % 4 < 2) {
                screen.input(176, j, i);
            }
        }
    }

    showPlayerInfo(config.playerInfo.x, config.playerInfo.y);
    
    showRoomInfo(config.roomInfo.x, config.roomInfo.y);

    showMap(config.map.x, config.map.y);

    showCombat(config.combat.x, config.combat.y);

    if (inputState > 1) {
        showDetails(config.details.x, config.details.y);
    }
    
    showCommandConsole(config.commandConsole.x, config.commandConsole.y);
    
    screen.print();

    if (isAnimating) {
        runAnimation(animID);
        
        return;
    }

    inputLine(config.commandConsole.x + 5, config.commandConsole.y + 19);

    processInput();
}