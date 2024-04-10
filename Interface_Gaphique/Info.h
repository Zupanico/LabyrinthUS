#ifndef INFO_H
#define INFO_H

#include <QMainWindow>
#include <QPushButton>
#include <QPaintEvent>
#include <QStyleOption>
#include <QFontDatabase>
#include <QGroupbox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QSoundEffect>

#include "MainWindow.h"

class MainWindow;

using namespace std;

class Info : public QMainWindow
{
	Q_OBJECT

public:

	explicit Info(QWidget* parent = nullptr);
	void MenuInfo();

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void playClickSound();

private:
	QWidget* centralWidget;
	QSoundEffect SonClick;
	MainWindow* mainWindow = nullptr;
};
#endif