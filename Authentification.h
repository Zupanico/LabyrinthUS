#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSoundEffect>
#include <QTimer>
#include <QGridLayout>
#include <QGroupBox>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class MainWindow;
class game;

class Authentification : public QMainWindow
{
    Q_OBJECT

public:
    explicit Authentification(QWidget* parent = nullptr);
    void startGame();
    void restartGame();
    void continueGame();
protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void updateDemarrerButtonState();
    void playClickSound();

private:
    void MenuAuthentification();
    

    QWidget* centralWidget;
    QLabel* LabelAuthentification;
    MainWindow* mainWindow;
    QLineEdit* EditNomJoueur;
    QPushButton* boutonDemarrer;
    QPushButton* boutonPrecedent;
    QSoundEffect SonClick;
    QLabel* iconLabel;
    game* g;
};

#endif // AUTHENTIFICATION_H
