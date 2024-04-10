#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) 
{
    _labyrinthWidth = 30;
    _labyrinthHeight = 30;
    _labyrinth = new char*[_labyrinthWidth];
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

    QImageReader reader("wall_image.png");
    _wallImage = reader.read();
    reader.setFileName("locker_image.png");
    _lockerImage = reader.read();
    reader.setFileName("jp_ok.png");
    _playerImage = reader.read();
    reader.setFileName("Alex_mad.png");
    _monsterImage = reader.read();
    reader.setFileName("door_image.png");
    _doorImage = reader.read();
    reader.setFileName("key.png");
    _keyImage = reader.read();
    reader.setFileName("dollar.png");
    _coinImage = reader.read();
    reader.setFileName("torch.png");
    _flashImage = reader.read();
    reader.setFileName("key.png");
    _keyImage = reader.read();
    reader.setFileName("vending-machine.png");
    _machineImage = reader.read();
    reader.setFileName("cerclevision1.png");
    _cerclevision1 = reader.read();
    reader.setFileName("cerclevision2.png");
    _cerclevision2 = reader.read();

    _viewOffsetX = 0;
    _viewOffsetY = 0;

}

MainWindow::~MainWindow()
{
    for (int i = 0; i < _labyrinthWidth; ++i)
    {
        delete[] _labyrinth[i];
    }
    delete[] _labyrinth;
}

// Add a method to add a wall to the labyrinth
void MainWindow::addMap(char m, int x, int y) {
    // Update your data model to include the new wall at position (x, y)
    if (x >= 0 && x < _labyrinthWidth && y >= 0 && y < _labyrinthHeight)
    {
        _labyrinth[x][y] = m;
    }
     // Assuming labyrinth is a 2D array indicating whether a cell contains a wall
}

void MainWindow::afficherMap()
{
    // Update the view to reflect the changes in the labyrinth
    update();
}

void MainWindow::setPlayerPosition(int x, int y)
{
    _playerX = x;
    _playerY = y;
}

void MainWindow::emptyMap()
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

void MainWindow::paintEvent(QPaintEvent *event) {
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
