#include "Window.h"
#include "MainWindow.h"

Window::Window(QWidget *parent) : QMainWindow(parent) 
{
    mainWindow = qobject_cast<MainWindow*>(parent);
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
    reader.setFileName("floor.png");
    _floorImage = reader.read();

    _viewOffsetX = 0;
    _viewOffsetY = 0;

    // Création du layout principal de la fenêtre
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // Création du grid layout pour l'icône et les boutons
    QGridLayout* gridLayout = new QGridLayout();

    // Création du QPushButton pour afficher l'icône Menu bar
    pauseButton = new QPushButton(this);
    QPixmap originalIcon(":/images/pause-button.png");
    QPixmap resizedIcon = originalIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'icône
    pauseButton->setIcon(QIcon(resizedIcon));
    pauseButton->setIconSize(resizedIcon.size());
    pauseButton->setFixedSize(resizedIcon.size()); // Taille fixe pour s'adapter à l'icône
    pauseButton->setFlat(true); // Rendre le bouton sans bordure
    pauseButton->setProperty("role", "pause");

     // Ajouter l'icône dans le grid layout
    gridLayout->addWidget(pauseButton, 0, 0, Qt::AlignTop | Qt::AlignLeft); // Utiliser pour placer l'icône en haut à gauche
    
    // Ajouter le grid layout au layout principal
    mainLayout->addLayout(gridLayout);

    // Affichage de la des boutons
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout); // Affecter le layout principal à la fenêtre
    setCentralWidget(centralWidget);
    
    connect(pauseButton, &QPushButton::clicked, this, &Window::playClickSound);

    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}

void Window::playClickSound()
{
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
        SonClick.setLoopCount(1);
        SonClick.setVolume(1.0f);
        SonClick.play();

        QString role = button->property("role").toString();

        if (role == "pause")
        {
            if (mainWindow == nullptr)
            {
                mainWindow = new MainWindow(this);
            }
            mainWindow->show();
            mainWindow->MenuPause();
            this->hide();
        }
    }
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

void Window::paintEvent(QPaintEvent* event) 
{
    QMainWindow::paintEvent(event);

    int _imageWidth = width() / 18;

    QPainter painter(this);

    painter.drawImage(0, 0, _floorImage.scaled(width(), height()));

    _viewOffsetX = _playerX * _imageWidth - width() / 2;
    _viewOffsetY = _playerY * _imageWidth - height() / 2;

    // Iterate through the entire area of the widget
    int i1 = _viewOffsetX / _imageWidth - 1;
    int j1 = _viewOffsetY / _imageWidth - 1;
    int i2 = (width() + _viewOffsetX) / _imageWidth + 1;
    int j2 = (height() + _viewOffsetY) / _imageWidth + 1;
    for (int i = i1; i < i2; i++)
    {
        for (int j = j1; j < j2; j++)
        {
            // Convert screen coordinates to labyrinth coordinates
            int x = i * _imageWidth - _viewOffsetX;
            int y = j * _imageWidth - _viewOffsetY;
            if (i >= 0 && i < _labyrinthWidth && j >= 0 && j < _labyrinthHeight)
            {
                // Draw elements of the labyrinth
                if (_labyrinth[i][j] == 'w') {
                    painter.drawImage(x, y, _wallImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'l') {
                    painter.drawImage(x, y, _lockerImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'd') {
                    painter.drawImage(x, y, _doorImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'k') {
                    painter.drawImage(x, y, _keyImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'c') {
                    painter.drawImage(x, y, _coinImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'f') {
                    painter.drawImage(x, y, _flashImage.scaled(_imageWidth, _imageWidth));
                }
                else if (_labyrinth[i][j] == 'm') {
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
    painter.drawImage(width() / 2, height() / 2, _playerImage.scaled(_imageWidth, _imageWidth));

    // Calculate the center position of the circle
    int centerX = (width() + _imageWidth) / 2;
    int centerY = (height() + _imageWidth) / 2; // Adjust the vertical position as needed

    // Calculate the radius of the circle
    int radius = qMax(width(), height()) / 2;

    if (_flashlight == false)
    {
        radius *= 1.5;

        QRadialGradient gradient(centerX, centerY, radius / 2, centerX, centerY);
        gradient.setColorAt(0, Qt::transparent);
        gradient.setColorAt(1, Qt::black); // Set the inside color to black

        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::black, radius));

        painter.drawEllipse(centerX - 2 * radius, centerY - 2 * radius, 4 * radius, 4 * radius);

        painter.setPen(Qt::NoPen); // No border

        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    }
    else if (_flashlight == true)
    {
        radius *= 2.2;

        QRadialGradient gradient(centerX, centerY, radius / 2, centerX, centerY);
        gradient.setColorAt(0, Qt::transparent);
        gradient.setColorAt(1, Qt::black); // Set the inside color to black

        painter.setBrush(gradient);
        painter.setPen(QPen(Qt::black, radius));

        painter.drawEllipse(centerX - 2 * radius, centerY - 2 * radius, 4 * radius, 4 * radius);

        painter.setPen(Qt::NoPen); // No border

        painter.drawEllipse(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    }
}

void Window::setFlash(bool etat)
{
    _flashlight = etat;
}
