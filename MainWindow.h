#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QImageReader>
#include <QWidget>
#include <QTimer>

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
        bool _key;
        bool _coin;
        bool _food;
        bool _checkmachine;
        bool _checklocker;
        bool _shake;
        bool _speed;

        int _vies;
        int _sizeBar;

    public:
        void addMap(char m, int x, int y);
        void emptyMap();
        void afficherMap();
        void setPlayerPosition(int x, int y);

        // Items
        void setFlash(bool etat);
        void setKey(bool etat);
        void setCoin(bool etat);
        void setFood(bool etat);

        // Indications
        void setMachine(bool etat);
        void setLocker(bool etat);
        void changerVies(int changement);
        void resetVies();
        void setShake(bool etat);
        void changerSizeBar();
        void setSpeed(bool etat);

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
    QImage _shadowKeyImage;
    QImage _flashImage;
    QImage _shadowFlashImage;
    QImage _coinImage;
    QImage _shadowCoinImage;
    QImage _foodImage;
    QImage _shadowFoodImage;
    QImage _machineImage;
    QImage _floorImage;
    QImage _shakeImage;
    QImage _coeurImage;

    int _playerX, _playerY;
    bool _hidePlayer;
};
