#include "personnage.h"

// Couleur du personnage
#define RESET "\033[0m"
#define VERT "\033[32m"

personnage::personnage()
{
}

personnage::~personnage()
{
}

int personnage::getX()
{
    return this->_x;
}

int personnage::getY()
{
    return this->_y;
}

void personnage::setX(int x)
{
    this->_x = x;
}

void personnage::setY(int y)
{
    this->_y = y;
}

void personnage::print(ostream &output) const
{
    // Initialize ncurses
    initscr();

    move(_x, _y);
    output << VERT << _cr;
    refresh();
    endwin();
}
