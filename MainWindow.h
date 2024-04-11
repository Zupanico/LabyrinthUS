#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QFontDatabase>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <QSoundEffect>
#include <vector>   
#include <QCoreApplication>
#include <QMenuBar>
#include <QMenu>

class Authentification;
class LoadGame;
class Info;
class Play;
class game;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    void MenuPrincipale();
    void MenuPause();
    void Cas1(int i);
    void Cas2(int i);
    void MenuAuthentification();
    void MenuLoadGame();
    void MenuInfo();
    void MenuQuitPlay();
    void Continuer();
    void Redemarrer();
    void RetourMenuPrincipale();
    void Settings();
    void Game();

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void playClickSound(int menu_index);

private:
    std::vector<QPushButton*> listButton;
    QPushButton* iconButton;
    QPushButton* iconButton1;
    QPushButton* iconButton2;
    QWidget* centralWidget;
    QFont font;
    QSoundEffect SonClick;

    Authentification* authentificationWindow = nullptr;
    LoadGame* LoadGameWindow = nullptr;
    Info* infoWinow = nullptr;
    Play* play = nullptr;
};

#endif // MAINWINDOW_H  