#ifndef PLAY_H
#define PLAY_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupbox>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStyleOption>
#include <QFontDatabase>
#include <QPainter>
#include <QDebug>
#include <QWidget>
#include <QSoundEffect>

#include "MainWindow.h"

class MainWindow;

using namespace std;

class Play : public QMainWindow
{
    Q_OBJECT

public:
    explicit Play(QWidget* parent = nullptr);
    void MenuPlay();


protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void playClickSound();

private:
    QWidget* centralWidget;
    QFont font;
    QSoundEffect SonClick;

    QMediaPlayer* LectureVideo;
    QVideoWidget* videoWidget;
    QAudioOutput* audioOutput;
    MainWindow* mainWindow = nullptr;
};


#endif // PLAY_