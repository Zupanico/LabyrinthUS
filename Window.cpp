#include "Window.h"

Window::Window(QWidget *parent) : QMainWindow(parent) 
{
    window = qobject_cast<Window*>(parent);
    MenuJeu();
}

Window::~Window()
{
    for (int i = 0; i < _labyrinthWidth; ++i)
    {
        delete[] _labyrinth[i];
    }
    delete[] _labyrinth;
}

void Window::MenuJeu()
{
    _labyrinthWidth = 30;
    _labyrinthHeight = 30;
    _labyrinth = new char* [_labyrinthWidth];

    for (int i = 0; i < _labyrinthWidth; i++)
    {
        _labyrinth[i] = new char[_labyrinthHeight];
    }

    for (int i = 0; i < _labyrinthWidth; i++)
    {
        for (int j = 0; j < _labyrinthHeight; j++)
        {
            _labyrinth[i][j] = ' ';
        }
    }

    QImageReader reader(":/images/wall_image.png");
    _wallImage = reader.read();
    reader.setFileName(":/images/locker_image.png");
    _lockerImage = reader.read();
    reader.setFileName(":/images/jp_ok.png");
    _playerImage = reader.read();
    reader.setFileName(":/images/Alex_mad.png");
    _monsterImage = reader.read();
    reader.setFileName(":/images/door_image.png");
    _doorImage = reader.read();
    reader.setFileName(":/images/dollar.png");
    _coinImage = reader.read();
    reader.setFileName(":/images/torch.png");
    _flashImage = reader.read();
    reader.setFileName(":/images/key.png");
    _keyImage = reader.read();
    reader.setFileName(":/images/vending-machine.png");
    _machineImage = reader.read();
    reader.setFileName(":/images/cerclevision1.png");
    _cerclevision1 = reader.read();
    reader.setFileName(":/images/cerclevision2.png");
    _cerclevision2 = reader.read();

    _viewOffsetX = 0;
    _viewOffsetY = 0;
}

// Add a method to add a wall to the labyrinth
void Window::addMap(char m, int x, int y) {
    // Update your data model to include the new wall at position (x, y)
    if (x >= 0 && x < _labyrinthWidth && y >= 0 && y < _labyrinthHeight)
    {
        _labyrinth[x][y] = m;
    }
     // Assuming labyrinth is a 2D array indicating whether a cell contains a wall
}

void Window::afficherMap()
{
    // Update the view to reflect the changes in the labyrinth
    update();
}

void Window::setPlayerPosition(int x, int y)
{
    _playerX = x;
    _playerY = y;
}

void Window::emptyMap()
{
    // Clear the labyrinth
    for (int i = 0; i < _labyrinthWidth; i++)
    {
        for (int j = 0; j < _labyrinthHeight; j++)
        {
            _labyrinth[i][j] = ' ';
        }
    }
    // Update the view to reflect the changes in the labyrinth
}

void Window::paintEvent(QPaintEvent *event) 
{
    QMainWindow::paintEvent(event);

    int _imageWidth = width() / 10;

    QPainter painter(this);

    _viewOffsetX = _playerX * _imageWidth - width() / 2;
    _viewOffsetY = _playerY * _imageWidth - height() / 2;

    // Iterate through the entire area of the widget
    for (int i = 0; i < _labyrinthWidth; i++)
    {
        for (int j = 0; j < _labyrinthHeight; j++)
        {
            // Convert screen coordinates to labyrinth coordinates
            int x = i * _imageWidth - _viewOffsetX;
            int y = j* _imageWidth - _viewOffsetY;

                // Draw elements of the labyrinth
            if (_labyrinth[i][j] == 'w') {
                painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'l') {
                painter.drawImage(x, y, _lockerImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'd') {
                painter.drawImage(x, y, _doorImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'k') {
                painter.drawImage(x, y, _keyImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'c') {
                painter.drawImage(x, y, _coinImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'f') {
                painter.drawImage(x, y, _flashImage.scaled(_imageWidth, _imageWidth));
            } else if (_labyrinth[i][j] == 'm') {
                painter.drawImage(x, y, _machineImage.scaled(_imageWidth, _imageWidth));
            }
        }
    }
    // Draw the player
    painter.drawImage(width() / 2 , height() / 2 , _playerImage.scaled(_imageWidth, _imageWidth));

    painter.drawImage(0, 0, _cerclevision1.scaled(width(), height()));
}
