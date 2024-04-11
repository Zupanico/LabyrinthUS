#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QSoundEffect>
#include <QImageReader>

class MainWindow;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget* parent = nullptr);
    void MenuJeu();
    ~Window();

protected:
    void paintEvent(QPaintEvent* event) override;
    bool _flashlight;

public:
    void addMap(char m, int x, int y);
    void emptyMap();
    void afficherMap();
    void setPlayerPosition(int x, int y);
    void setFlash(bool etat);

private slots:
    void playClickSound();

private:
    int _viewOffsetX, _viewOffsetY;
    char** _labyrinth;
    int _labyrinthWidth, _labyrinthHeight;
    int _playerX, _playerY;
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

    QWidget* centralWidget;
    QPushButton* pauseButton;
    QSoundEffect SonClick;
    MainWindow* mainWindow;
};
#endif
