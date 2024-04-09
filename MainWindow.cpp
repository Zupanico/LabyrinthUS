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
    _imageWidth = 20;

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

    QPainter painter(this);

    // Iterate through the labyrinth and draw walls
    for (int x = 0; x < _labyrinthWidth; ++x) {
        for (int y = 0; y < _labyrinthHeight; ++y) {
            if (_labyrinth[x][y] == 'm') { // Check if there's a wall at this position
                int screenX = x * _imageWidth - _viewOffsetX;
                int screenY = y * _imageWidth - _viewOffsetY;
                
                // Draw the wall at the calculated screen coordinates
                painter.drawImage(screenX, screenY, _wallImage.scaled(_imageWidth, _imageWidth));
            }
        }
    }
}
    