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
    reader.setFileName("shadow_key.png");
    _shadowKeyImage = reader.read();
    reader.setFileName("dollar.png");
    _coinImage = reader.read();
    reader.setFileName("shadow_coin.png");
    _shadowCoinImage = reader.read();
    reader.setFileName("torch.png");
    _flashImage = reader.read();
    reader.setFileName("shadow_torch.png");
    _shadowFlashImage = reader.read();
    reader.setFileName("chocolate.png");
    _foodImage = reader.read();
    reader.setFileName("shadow_chocolate.png");
    _shadowFoodImage = reader.read();
    reader.setFileName("vending-machine.png");
    _machineImage = reader.read();
    reader.setFileName("floor.png");
    _floorImage = reader.read();

    _viewOffsetX = 0;
    _viewOffsetY = 0;
    _hidePlayer = false;
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
    if (x >= 0 && x < _labyrinthWidth && y >= 0 && y < _labyrinthHeight)
    {
        _playerX = x;
        _playerY = y;
        _hidePlayer = false;
    }
    else
    {
        _hidePlayer = true;
    }
        
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

    int _imageWidth = width() / 18;

    QPainter painter(this);

    painter.drawImage(0, 0, _floorImage.scaled(width(), height()));

    _viewOffsetX = _playerX * _imageWidth - width() / 2;
    _viewOffsetY = _playerY * _imageWidth - height() / 2;

    // Iterate through the entire area of the widget
    int i1 = _viewOffsetX / _imageWidth -1;
    int j1 = _viewOffsetY / _imageWidth -1;
    int i2 = (width() + _viewOffsetX) / _imageWidth +1;
    int j2 = (height() + _viewOffsetY) / _imageWidth +1;
    for (int i = i1; i < i2; i++)
    {
        for (int j = j1; j < j2; j++)
        {
            // Convert screen coordinates to labyrinth coordinates
            int x = i * _imageWidth - _viewOffsetX;
            int y = j* _imageWidth - _viewOffsetY;
            if (i >= 0 && i < _labyrinthWidth && j >= 0 && j < _labyrinthHeight)
            {
                // Draw elements of the labyrinth
                if (_labyrinth[i][j] == 'w') {
                    painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
                } else if (_labyrinth[i][j] == 'l') {
                    painter.drawImage(x, y, _lockerImage.scaled(_imageWidth, _imageWidth));
                } else if (_labyrinth[i][j] == 'd') {
                    painter.drawImage(x, y, _doorImage.scaled(_imageWidth, _imageWidth));
                } else if (_labyrinth[i][j] == 'k') {
                    painter.drawImage(x, y, _keyImage.scaled(_imageWidth/2, _imageWidth/2));
                } else if (_labyrinth[i][j] == 'c') {
                    painter.drawImage(x, y, _coinImage.scaled(_imageWidth/2, _imageWidth/2));
                } else if (_labyrinth[i][j] == 'f') {
                    painter.drawImage(x, y, _flashImage.scaled(_imageWidth/2, _imageWidth/2));
                } else if (_labyrinth[i][j] == 'm') {
                    painter.drawImage(x, y, _machineImage.scaled(_imageWidth, _imageWidth));
                }
            }
            else
            {
                // Draw the boundaries of the labyrinth
                painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
            }
                
        }
    }
    // Draw the player
    if (!_hidePlayer) painter.drawImage(width() / 2, height() / 2, _playerImage.scaled(_imageWidth, _imageWidth));


    // Calculate the center position of the circle
    int centerX = (width() + _imageWidth) / 2;
    int centerY = (height() + _imageWidth) / 2; // Adjust the vertical position as needed

    // Calculate the radius of the circle
    int radius = qMax(width(), height())/2;

    // Cercle de vision
    if (_flashlight == false)
    {
        radius *= 1.5;

        QRadialGradient gradient(centerX, centerY, radius/2, centerX, centerY);
        gradient.setColorAt(0, Qt::transparent);
        gradient.setColorAt(1, Qt::black); // Set the inside color to black

        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::black, radius)); 

        painter.drawEllipse(centerX - 2*radius, centerY - 2*radius, 4 * radius, 4 * radius);

        painter.setPen(Qt::NoPen); // No border

        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    }
    else if (_flashlight == true)
    {
        radius *= 2.2;

        QRadialGradient gradient(centerX, centerY, radius/2, centerX, centerY);
        gradient.setColorAt(0, Qt::transparent);
        gradient.setColorAt(1, Qt::black); // Set the inside color to black

        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::black, radius)); 

        painter.drawEllipse(centerX - 2*radius, centerY - 2*radius, 4 * radius, 4 * radius);

        painter.setPen(Qt::NoPen); // No border

        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    }

    // Inventaire
    painter.setPen(QPen(Qt::darkGray, width()*0.002));

    painter.drawRect(width()*0.41, height()*0.07, width()*0.035, width()*0.035);
    painter.drawRect(width()*0.47, height()*0.07, width()*0.035, width()*0.035);
    painter.drawRect(width()*0.53, height()*0.07, width()*0.035, width()*0.035);
    painter.drawRect(width()*0.59, height()*0.07, width()*0.035, width()*0.035);
    
    if (_key == true)
    {
        painter.drawImage(width()*0.415, height()*0.08, _keyImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    else if (_key == false)
    {
        painter.drawImage(width()*0.415, height()*0.08, _shadowKeyImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    if (_flashlight == true)
    {
        painter.drawImage(width()*0.475, height()*0.08, _flashImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    else if (_flashlight == false)
    {
        painter.drawImage(width()*0.475, height()*0.08, _shadowFlashImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    if (_coin == true)
    {
        painter.drawImage(width()*0.535, height()*0.08, _coinImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    else if (_coin == false)
    {
        painter.drawImage(width()*0.535, height()*0.08, _shadowCoinImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    if (_food == true)
    {
        painter.drawImage(width()*0.595, height()*0.08, _foodImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
    else if (_food == false)
    {
        painter.drawImage(width()*0.595, height()*0.08, _shadowFoodImage.scaled(_imageWidth/2.2, _imageWidth/2.2));
    }
}

void MainWindow::setFlash(bool etat)
{
    _flashlight = etat;
}

void MainWindow::setKey(bool etat)
{
    _key = etat;
}

void MainWindow::setCoin(bool etat)
{
    _coin = etat;
}

void MainWindow::setFood(bool etat)
{
    _food = etat;
}