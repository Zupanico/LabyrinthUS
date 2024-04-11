#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QImageReader>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
        // Initialize your game state, player position, labyrinth, etc.

    protected:
        void paintEvent(QPaintEvent *event) override;
        bool _flashlight;

    public:
        void addMap(char m, int x, int y);
        void emptyMap();
        void afficherMap();
        void setPlayerPosition(int x, int y);
        void setFlash(bool etat);

private:
    // Define your variables and methods here
    int _viewOffsetX, _viewOffsetY;
    char** _labyrinth;
    int _labyrinthWidth, _labyrinthHeight;
    QImage _wallImage;
    QImage _lockerImage;
    QImage _playerImage;
    QImage _monsterImage;
    QImage _doorImage;
    QImage _keyImage;
    QImage _flashImage;
    QImage _coinImage;
    QImage _foodImage;
    QImage _machineImage;
    QImage _cerclevision1;
    QImage _cerclevision2;
    QImage _floorImage;

    int _playerX, _playerY;
};
