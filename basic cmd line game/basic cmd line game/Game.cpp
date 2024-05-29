#include "Game.h"
#include <iostream>
#include <windows.h>

Game::Game(int screenWidth, int screenHeight, int tickRate) {
    screen = Screen(screenWidth, screenHeight);

    gameRunning = true;
    this->tickRate = tickRate;

    config = {
        {3, 1},
        {screen.width - 81, screen.height - 18},
        {screen.width / 2 + 68, screen.height / 2 - 8},
        {50, 2},
        {3, 30},
        {59, screenHeight - 23}
    };

    isAnimating = false;
    animID = 0;
    animCount = 0;
    startX = 0;
    startY = 0;

    player = Player(*this, 2, 2);
    player.getInventory() = ItemList(3, new Item*[3]{ new FoodItem("Apple pie", "Wow yummy", 30), new Item("Diamond", "Wow shiny"), new FoodItem("Knife", "Wow sharp AND yummy", -50) }, itemMasterList);
    player.getSpellBook() = SpellList(3, new SpellBase*[3]{ new SpellBase("Conjure fist", "Conjures a fist to punch an enemy", 1, 5), new SpellBase("DUmMy sPElL", "Doesn't do anything"), new SpellBase("Hiya", "I don't actually do anything") }, spellMasterList);
    
    dummy = Enemy("dummy duck", 200, 50, 5);

    rooms[0][2] = Room(*this, "Boss room");
    rooms[1][0] = Room(*this, "There is a stone altar in the middle of the room. You see a tattered\nscroll on top of it.", ItemList(1, new Item*[1]{ new ScrollItem("Teleport scroll", "This scroll contains knowledge of\nthe teleport spell.", new TeleportSpell(), spellMasterList) }, itemMasterList));
    rooms[1][3] = Room(*this, "It's cold in here.", ItemList(2, new Item*[2]{ new Item("Gold coin", "I'm a golden circle"), new Item("Ice cube", "I'm a block of ice") }, itemMasterList));
    rooms[2][0] = Room(*this, "Something about this room isn't right.");
    rooms[2][1] = Room(*this, "The room is littered with old training mannequins.", ItemList(1, new Item*[1]{ new Item("Training dummy", "It's covered in slash marks") }, itemMasterList));
    rooms[2][2] = Room(*this, "This is the room you started in.");
    rooms[2][3] = Room(*this, "It's dark in here");
    rooms[2][4] = Room(*this, "This room is undergoing construction.");
    rooms[3][0] = Room(*this, "This room is undergoing construction.");
    rooms[3][2] = Room(*this, "There's a sword stuck in a large boulder.", ItemList(1, new Item*[1]{ new Item("Fancy sword", "I look fancy") }, itemMasterList));
    rooms[3][4] = Room(*this, "This room is undergoing construction.");
    rooms[4][1] = Room(*this, "This room is undergoing construction.");
    rooms[4][2] = Room(*this, "There's a wombat in here.");
    rooms[4][3] = Room(*this, "This room is undergoing construction.");
    rooms[4][4] = Room(*this, "You sense powerful magic within the room. As you take a closer look\n you see a red object in the corner of the room.", ItemList(1, new Item*[1]{ new Item("Red herring", "This seems very important") }, itemMasterList));

    inputState = 0;
}

Game::~Game() {
    //this is a quite a wacky way of handling it
    //using shared_ptr would be better but if I went down that route, 
    //then I'd prefer to make my own shared_ptr class
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

void Game::drawTeleport(int x, int y, int width, int height) {
    screen.input(201, x, y);
    screen.input(200, x, y + height + 1);
    screen.input(187, x + width + 1, y);
    screen.input(188, x + width + 1, y + height + 1);

    screen.rect(196, x + 1, y, width, 1);
    screen.rect(196, x + 1, y + height + 1, width, 1);
    screen.rect(179, x, y + 1, 1, height);
    screen.rect(179, x + width + 1, y + 1, 1, height);
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

void Game::background() {
    for (int i = 0; i < screen.width; i++) {
        for (int j = 0; j < screen.width; j++) {
            if ((i + j) % 4 < 2) {
                screen.input(176, j, i);
            }
        }
    }
}

void Game::showPlayerInfo(int x, int y) {
    drawUIWindow(x, y, 40, 25);
    screen.text("Player Profile", x + 14, y + 1);
    
    drawBorder(x + 31, y + 3, 6, 2, false);
    drawPlayer(x + 33, y + 4);

    screen.text(player.Description(), x+2, y+4);
}

void Game::showRoomInfo(int x, int y) {
    drawUIWindow(x, y, 76, 15);
    screen.text("Room Info", x + 34, y + 1);

    screen.text(getCurrentRoom().Description(), x + 3, y + 4);
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
    drawPlayer((x - 2) + 14 * (player.getX() - 2), (y - 2) + 7 * (player.getY() - 2));
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

    screen.text(dummy.getDescription(), x + 5, y + 5);

    drawBorder(x + 20, y + 28, 8, 1, false);
    screen.text("SPELLS", x + 22, y + 29);

    drawBorder(x + 37, y + 28, 7, 1, false);
    screen.text("ITEMS", x + 39, y + 29);

    drawBorder(x + 55, y + 28, 5, 1, false);
    screen.text("RUN", x + 57, y + 29);

    screen.text("THIS WINDOW IS JUST FOR SHOW\nCOMBAT HAS NOT BEEN IMPLEMENTED", x + 26, y + 14);
}

void Game::showDetails(int x, int y) {
    drawUIWindow(x, y, 40, 20);
    screen.text("Details", x + 17, y + 1);

    switch (inputState) {
        case 2:
            screen.text("Item:\n" + player.getItem()->getName() + "\n\nDescription:\n" + player.getItem()->Description(), x + 3, y + 4);
            break;
        case 3:
            screen.text("Spell:\n" + player.getSpell()->getName() + "\n\nCost: " + toString(player.getSpell()->getCost()) + " mana\nDamage: " + toString(player.getSpell()->getDamage()) + "\n\nDescription:\n" + player.getSpell()->getDescription(), x + 3, y + 4);
            break;
        case 4:
            if (getCurrentRoom().getItems().getCount() == 0) {
                screen.text("This room has no items", x + 3, y + 4);
                return;
            }

            screen.text("Item:\n" + getCurrentRoom().getItem()->getName() + "\n\nDescription:\n" + getCurrentRoom().getItem()->Description(), x + 3, y + 4);
            break;
        /* combat system code
        case 6:
            screen.text("Spell:\n" + player.getSpell()->getName() + "\n\nCost: " + toString(player.getSpell()->getCost()) + " mana\nDamage: " + toString(player.getSpell()->getDamage()) + "\n\nDescription:\n" + player.getSpell()->getDescription(), x + 3, y + 4);
            break;
        case 7:
            screen.text("Item:\n" + player.getItem()->getName() + "\n\nDescription:\n" + player.getItem()->Description(), x + 3, y + 4);
            break;
        */
    }
}

void Game::showCommandConsole(int x, int y) {
    drawUIWindow(x, y, 64, 20);
    screen.text("Input Console", x + 26, y + 1);

    switch (inputState) {
        case 0:
            screen.text("[move]   [inventory]   [fight]\n\n     [room]   [spellbook]", x + 17, y + 10);
            break;
        case 1:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);
            
            screen.text("        [north]\n\n           ^\n[west]   < + >   [east]\n           v\n\n        [south]", x + 21, y + 8);
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
        
        /* combat system code
        case 5:
            screen.text("[spells]   [items]   [run]", x + 18, y + 10);
            break;
        case 6:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);

            screen.text("[cast] current selected spell\n\nselect different spell by\n\nscrolling [up] [down]\n[select]ing based on index\n[search]ing by name", x + 6, y + 6);
            break;
        case 7:
            screen.rect(196, x + 1, y + 4, 8, 1);
            screen.rect(179, x + 9, y + 3, 1, 1);

            screen.input(195, x, y + 4);
            screen.input(217, x + 9, y + 4);

            screen.text("[back]", x + 2, y + 3);

            screen.text("[use] current selected item\n\nselect different item by\n\nscrolling [up] [down]\n[select]ing based on index\n[search]ing by name", x + 6, y + 6);
            break;
        */
    }

    screen.text(response, x + 5, y + 17);

    screen.input(175, x + 3, y + 19);
}

void Game::inputLine(int x, int y) {
    std::cout << "\x1b[?25h";
    std::cout << "\x1b[" + toString(y+1) + ";" + toString(x+1) + "H";
    
    userInput.ReadFromConsole();
}

void Game::processInput() {
    response = "";
    userInput.ToLower();

    switch (inputState) {
        case 0:
            if (userInput == "move") {
                inputState = 1;
            }
            else if (userInput == "inventory") {
                inputState = 2;
            }
            else if (userInput == "spellbook") {
                inputState = 3;
            }
            else if (userInput == "room") {
                inputState = 4;
            }
            else if (userInput == "fight") {
                response = "combat has been disabled";
                //inputState = 5;
            }
            else {
                response = "invalid input";
            }
            break;
        case 1:
            startX = player.getX();
            startY = player.getY();

            if (userInput == "north") {
                switch (player.shiftPos(0, -1)) {
                    case 0:
                        response = "You entered the room to the north";
                        startAnimation(0, startX, startY);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput == "east") {
                switch (player.shiftPos(1, 0)) {
                    case 0:
                        response = "You entered the room to the east";
                        startAnimation(0, startX, startY);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput == "south") {
                switch (player.shiftPos(0, 1)) {
                    case 0:
                        response = "You entered the room to the south";
                        startAnimation(0, startX, startY);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput == "west") {
                switch (player.shiftPos(-1, 0)) {
                    case 0:
                        response = "You entered the room to the west";
                        startAnimation(0, startX, startY);
                        break;
                    case 1:
                        response = "You can't go outside of the map";
                        break;
                    case 2:
                        response = "Room doesn't exist";
                        break;
                }
            }
            else if (userInput == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 2:
            if (userInput == "use") {
                response = player.useItem() + "\nDebug: " + player.getItem()->getName() + "|" + typeid(*player.getItem()).name();
            }
            else if (userInput == "up") {
                player.shiftInvIndex(-1);
            }
            else if (userInput == "down") {
                player.shiftInvIndex(1);
            }
            else if (userInput.Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                response = "tried to go to " + toString(toInt(userInput));
                player.setInvIndex(toInt(userInput));
            }
            else if (userInput.Find("search ") == 0) {
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
            else if (userInput == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 3:
            if (userInput.Find("cast") == 0) {
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
            else if (userInput == "up") {
                player.shiftSpellIndex(-1);
            }
            else if (userInput == "down") {
                player.shiftSpellIndex(1);
            }
            else if (userInput.Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                response = "tried to go to " + toString(toInt(userInput));
                player.setSpellIndex(toInt(userInput));
            }
            else if (userInput.Find("search ") == 0) {
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
            else if (userInput == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 4:
            if (userInput == "take") {
                if (getCurrentRoom().getItems().getCount() == 0) {
                    response = "this room has no items to take";
                    return;
                }

                response = "You took the " + getCurrentRoom().getItem()->getName() + "\nDebug: " + typeid(*getCurrentRoom().getItem()).name();
                player.takeItem(getCurrentRoom());
            }
            else if (userInput == "up") {
                getCurrentRoom().shiftItemsIndex(-1);
            }
            else if (userInput == "down") {
                getCurrentRoom().shiftItemsIndex(1);
            }
            else if (userInput == "back") {
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        
        /* combat system code
        case 5:
            if (userInput == "spells") {
                //dummy.shiftHealth(-5);
                inputState = 6;
            }
            else if (userInput == "items") {
                inputState = 7;
            }
            else if (userInput == "run") {
                response = "You managed to run away";
                inputState = 0;
            }
            else {
                response = "invalid input";
            }
            break;
        case 6:
            if (userInput.Find("cast") == 0) {
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
            else if (userInput == "up") {
                player.shiftSpellIndex(-1);
            }
            else if (userInput == "down") {
                player.shiftSpellIndex(1);
            }
            else if (userInput.Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                response = "tried to go to " + toString(toInt(userInput));
                player.setSpellIndex(toInt(userInput));
            }
            else if (userInput.Find("search ") == 0) {
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
            else if (userInput == "back") {
                inputState = 5;
            }
            else {
                response = "invalid input";
            }
            break;
        case 7:
            if (userInput == "use") {
                response = player.useItem() + "\nDebug: " + player.getItem()->getName() + "|" + typeid(*player.getItem()).name();
            }
            else if (userInput == "up") {
                player.shiftInvIndex(-1);
            }
            else if (userInput == "down") {
                player.shiftInvIndex(1);
            }
            else if (userInput.Find("select ") == 0) {
                //this is some unreliable parsing
                userInput.Replace("select ", "");
                response = "tried to go to " + toString(toInt(userInput));
                player.setInvIndex(toInt(userInput));
            }
            else if (userInput.Find("search ") == 0) {
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
            else if (userInput == "back") {
                inputState = 5;
            }
            else {
                response = "invalid input";
            }
            break;
        */
    }
}

void Game::startAnimation(int ID, int startX, int startY) {
    isAnimating = true;
    animID = ID;
    this->startX = startX;
    this->startY = startY;
}

void Game::runAnimation(int ID) {
    animCount++;

    switch (ID) {
        case 0:
            screen.rect(' ', (config.map.x - 2) + 14 * (player.getX() - 2), (config.map.y - 2) + 7 * (player.getY() - 2), 4, 2);
            drawPlayer((config.map.x - 2) + 14 * (startX - 2) + (2 * (player.getX() - startX) * (animCount/5)), (config.map.y - 2) + 7 * (startY - 2) + ((player.getY() - startY) * (animCount / 5)));

            if (animCount > 35) {
                endAnimation(ID);
            }
            break;
        case 1:
            if (animCount < 40) {
                screen.rect(' ', (config.map.x - 2) + 14 * (player.getX() - 2), (config.map.y - 2) + 7 * (player.getY() - 2), 4, 2);
            }

            if (animCount < 10) {
                drawPlayer((config.map.x - 2) + 14 * (startX - 2), (config.map.y - 2) + 7 * (startY - 2));
                drawTeleport((config.map.x - 2) + 14 * (startX - 2) - 3, (config.map.y - 2) + 7 * (startY - 2) - 2, 8, 4);
            }
            else if (animCount < 20) {
                drawPlayer((config.map.x - 2) + 14 * (startX - 2), (config.map.y - 2) + 7 * (startY - 2));
                drawTeleport((config.map.x - 2) + 14 * (startX - 2) - 2, (config.map.y - 2) + 7 * (startY - 2) - 1, 6, 2);
            }
            else if (animCount < 30) {
                drawTeleport((config.map.x - 2) + 14 * (startX - 2), (config.map.y - 2) + 7 * (startY - 2), 2, 0);
            }
            else if (animCount < 40) {
                drawTeleport((config.map.x - 2) + 14 * (player.getX() - 2), (config.map.y - 2) + 7 * (player.getY() - 2), 2, 0);
            }
            else if (animCount < 50) {
                drawTeleport((config.map.x - 2) + 14 * (player.getX() - 2) - 2, (config.map.y - 2) + 7 * (player.getY() - 2) - 1, 6, 2);
            }
            else if (animCount < 60) {
                drawTeleport((config.map.x - 2) + 14 * (player.getX() - 2) - 3, (config.map.y - 2) + 7 * (player.getY() - 2) - 2, 8, 4);
            }

            if (animCount > 60) {
                endAnimation(ID);
            }
            break;
    }
}

void Game::endAnimation(int ID) {
    isAnimating = false;
    animCount = 0;
}

void Game::run() {
    while (gameRunning) {
        screen.reset();

        background();

        showPlayerInfo(config.playerInfo.x, config.playerInfo.y);

        showRoomInfo(config.roomInfo.x, config.roomInfo.y);

        showMap(config.map.x, config.map.y);

        showCombat(config.combat.x, config.combat.y);

        if (inputState > 1 && inputState < 5) {
            showDetails(config.details.x, config.details.y);
        }

        showCommandConsole(config.commandConsole.x, config.commandConsole.y);

        if (isAnimating) {
            runAnimation(animID);
        }

        //temporary win condition
        if (player.getX() == 2 && player.getY() == 0 && !isAnimating) {
            drawBorder((screen.width / 2) - 20, (screen.height / 2) - 2, 40, 5, true);
            screen.text("YOU'VE WON", (screen.width / 2) - 4, screen.height / 2);
            screen.text("press enter to exit.", (screen.width / 2) - 10, (screen.height / 2) + 2);

            gameRunning = false;
        }

        screen.print();

        if (!isAnimating) {
            inputLine(config.commandConsole.x + 5, config.commandConsole.y + 19);

            processInput();
        }

        Sleep(1000 / tickRate);
    }
}