#include <QMainWindow>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
    explicit MainWindow(QWidget *parent = nullptr);
        // Initialize your game state, player position, labyrinth, etc.

    protected:
        void paintEvent(QPaintEvent *event) override;

    public:
        void addMap(char m, int x, int y);
        void afficherMap();

private:
    // Define your variables and methods here
    int viewOffsetX, viewOffsetY;
    char** labyrinth;
    int labyrinthWidth, labyrinthHeight;
    QImage wallImage;
    int imageWidth;
};
