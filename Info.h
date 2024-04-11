#ifndef INFO_H
#define INFO_H

#include <QMainWindow>
#include <QPushButton>
#include <QPaintEvent>
#include <QFontDatabase>
#include <QGroupbox>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QWidget>
#include <QSoundEffect>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

class MainWindow;

class Info : public QMainWindow
{
    Q_OBJECT

public:
    explicit Info(QWidget* parent = nullptr);
    void MenuInfo();
    void saveData();

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void playClickSound();

private:
    QWidget* centralWidget;
    QSoundEffect SonClick;
    MainWindow* mainWindow;
    QPushButton* boutonPrecedent;
    QTextEdit* textEdit;
};

#endif
