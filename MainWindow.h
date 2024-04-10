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

    public:
        void addMap(char m, int x, int y);
        void emptyMap();
        void afficherMap();
        void setPlayerPosition(int x, int y);

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
    int _playerX, _playerY;
};