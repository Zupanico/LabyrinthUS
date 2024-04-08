#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    labyrinthWidth = 30;
    labyrinthHeight = 30;
    labyrinth = new char*[labyrinthWidth];
    for (int i = 0; i < labyrinthWidth; i++)
    {
        labyrinth[i] = new char[labyrinthHeight];
    }
    for (int i = 0; i < labyrinthWidth; i++)
    {
        for (int j = 0; j < labyrinthHeight; j++)
        {
            labyrinth[i][j] = ' ';
        }
    }

    wallImage.load(":/images/wall_image.png");
    imageWidth = width()/labyrinthWidth;

    viewOffsetX = 0;
    viewOffsetY = 0;

}

// Add a method to add a wall to the labyrinth
void MainWindow::addMap(char m, int x, int y) {
    // Update your data model to include the new wall at position (x, y)
    if (x >= 0 && x < labyrinthWidth && y >= 0 && y < labyrinthHeight)
    {
        labyrinth[x][y] = m;
    }
     // Assuming labyrinth is a 2D array indicating whether a cell contains a wall
}

void MainWindow::afficherMap()
{
    // Update the view to reflect the changes in the labyrinth
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this);

    // Iterate through the labyrinth and draw walls
    for (int x = 0; x < labyrinthWidth; ++x) {
        for (int y = 0; y < labyrinthHeight; ++y) {
            if (labyrinth[x][y] == 'm') { // Check if there's a wall at this position
                int screenX = x * imageWidth - viewOffsetX;
                int screenY = y * imageWidth - viewOffsetY;
                
                // Draw the wall at the calculated screen coordinates
                painter.drawImage(screenX, screenY, wallImage.scaled(imageWidth, imageWidth));
            }
        }
    }
}
    