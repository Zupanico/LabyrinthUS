#ifndef	LOADGAME_H
#define LOADGAME_H

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

class MainWindow;// Déclaration anticipée pour éviter la dépendance circulaire.

using namespace std;

class LoadGame : public QMainWindow
{
	Q_OBJECT

public:

	explicit LoadGame(QWidget* parent = nullptr);
	void MenuLoadGame();

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void playClickSound();

private:
	QWidget* centralWidget;
	QSoundEffect SonClick;
	MainWindow* mainWindow = nullptr;
	QPushButton* boutonDemarrer;
	QPushButton* boutonPrecedent;
};
#endif
