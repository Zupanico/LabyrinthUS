#ifndef	AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPaintEvent>
#include <QStyleOption>
#include <QFontDatabase>
#include <QGroupbox.h>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QWidget>
#include <QSoundEffect>

#include "MainWindow.h"

class MainWindow;// Déclaration anticipée pour éviter la dépendance circulaire.

using namespace std;

class Authentification : public QMainWindow
{
	Q_OBJECT

public:

	explicit Authentification(QWidget* parent = nullptr);
	void MenuAuthentification();

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void updateDemarrerButtonState();
	void playClickSound();

private:
	QWidget* centralWidget;
	QLabel* LabelAuthentification;
	MainWindow* mainWindow = nullptr;
	QLineEdit* EditNomJoueur;
	QPushButton* boutonDemarrer;
	QPushButton* boutonPrecedent;
	QSoundEffect SonClick;

};
#endif