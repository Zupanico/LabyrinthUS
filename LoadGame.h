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
#include <QVector>
#include <QFile>

class MainWindow;

// Définition de la structure Joueur
struct Joueur {
	QString nom;
	int niveau;
	// Ajoutez d'autres membres si nécessaire

	// Surcharge de l'opérateur < pour permettre le tri
	bool operator<(const Joueur& other) const {
		// Comparaison basée sur le niveau
		return niveau < other.niveau;
	}
};

class LoadGame : public QMainWindow
{
	Q_OBJECT

public:

	explicit LoadGame(QWidget* parent);
	void MenuLoadGame();
	void afficherTop5(const QString& nomJoueur);
	void setNomJoueur(const QString& nom);

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void playClickSound();

private:
	QWidget* centralWidget;
	QSoundEffect SonClick;
	MainWindow* mainWindow;
	QPushButton* boutonDemarrer;
	QPushButton* boutonPrecedent;
	QString nomJoueur; // Ajout du membre nomJoueur
	QVector<Joueur> joueurs; // Ajout du conteneur joueurs
};
#endif
