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
        bool _key;
        bool _coin;
        bool _food;
        bool _checkmachine;
        bool _checklocker;

        int _vies;

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
        void setMachine(bool etat);
        void setLocker(bool etat);
        void changerVies(int changement);
        void resetVies();

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
    QImage _shake;
    QImage _coeur;

    int _playerX, _playerY;
    bool _hidePlayer;
};
