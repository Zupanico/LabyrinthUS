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
    int number = height() / _imageWidth;
    int _differenceX =  -_imageWidth + (width()/2 % 5);
    int _differenceY =  -_imageWidth + ((height()) % (number));

    QPainter painter(this);

    _viewOffsetX = _playerX * _imageWidth - width() / 2;
    _viewOffsetY = _playerY * _imageWidth - height() / 2;

    // Iterate through the entire area of the widget
    for (int x = _differenceX; x <= width() + _differenceX; x += _imageWidth) {
        for (int y = _differenceY; y <= height() + _differenceY; y += _imageWidth) {
            // Convert screen coordinates to labyrinth coordinates
            int labyrinthX = _playerX + (x - width()/2) / _imageWidth;
            int labyrinthY = _playerY + (y - height()/2) / _imageWidth;

            // Check if the labyrinth coordinates fall within the labyrinth bounds

            if (labyrinthX >= 0 && labyrinthX < _labyrinthWidth && labyrinthY >= 0 && labyrinthY < _labyrinthHeight) {
                // Draw elements of the labyrinth
                if (_labyrinth[labyrinthX][labyrinthY] == 'm') {
                    painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
                } else if (_labyrinth[labyrinthX][labyrinthY] == 'l') {
                    painter.drawImage(x, y, _lockerImage.scaled(_imageWidth, _imageWidth));
                } else if (_labyrinth[labyrinthX][labyrinthY] == 'd') {
                    painter.drawImage(x, y, _doorImage.scaled(_imageWidth, _imageWidth));
                }
            } else {
                // Draw the wall texture for areas outside the labyrinth
                painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
            }
        }
    }

    // Draw the player
    painter.drawImage(width() / 2 , height() / 2 , _playerImage.scaled(_imageWidth, _imageWidth));
}
