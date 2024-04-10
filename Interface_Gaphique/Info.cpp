#include "Info.h"

Info::Info(QWidget* parent) :QMainWindow(parent)
{
    MenuInfo();
}

void Info::paintEvent(QPaintEvent* event)
{
    // Ajout d'image en arriere plan
    QPainter painter(this);
    QPixmap background(":/images/imgInterface.jpg");

    if (background.isNull())
    {
        qDebug() << "L'image n'a pas pu �tre charg�e ! V�rifiez le chemin.";
    }
    else
    {
        painter.drawPixmap(rect(), background);
    }
}

void Info::MenuInfo()
{
    // Supprime tous les enfants de ce widget
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    centralWidget = new QWidget(this);

    // Configuration des groupes Info Label
    QGroupBox* InfoGroupBox = new QGroupBox(tr(""), this);
    InfoGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QHBoxLayout* InfoLayout = new QHBoxLayout(InfoGroupBox);
    QLabel* LabelLaodGameInfo = new QLabel(tr("INFORMATIONS"), InfoGroupBox);

    LabelLaodGameInfo->setAlignment(Qt::AlignCenter);
    LabelLaodGameInfo->setStyleSheet("QLabel { color: red; }");

    InfoLayout->addWidget(LabelLaodGameInfo);
    InfoGroupBox->setLayout(InfoLayout);

    // Chargement et application des polices Sur Informations
    QFont font1;
    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId1 != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId1).at(0);
        font1 = QFont(fontFamily, 50, QFont::Bold);
    }
    else {
        qDebug() << "�chec du chargement de la police BadBoys.";
        font1 = QFont("Arial", 50, QFont::Bold);
    }
    LabelLaodGameInfo->setFont(font1);

    // Chargement et application des polices sur tous le restes
    QFont font;
    int fontId = QFontDatabase::addApplicationFont(":/fonts/BadBoys.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        font = QFont(fontFamily, 40, QFont::Bold);
    }
    else {
        qDebug() << "�chec du chargement de la police BadBoys.";
        font = QFont("Arial", 40, QFont::Bold);
    }

    // Groupe pour le bouton "Pr�c�dant"
    QGroupBox* precedentGroupBox = new QGroupBox(this);
    precedentGroupBox->setStyleSheet("QGroupBox { border: 0; }"); // Masquer les contours

    QVBoxLayout* precedentLayout = new QVBoxLayout(precedentGroupBox);
    QPushButton* boutonPrecedent = new QPushButton(tr("Precedant"), precedentGroupBox);

    boutonPrecedent->setStyleSheet("QPushButton { color: green; background-color: transparent; border: none; }"
        "QPushButton:pressed { color: yellow; background-color: transparent; }");
    boutonPrecedent->setEnabled(true);
    boutonPrecedent->setFixedSize(230, 100);
    precedentLayout->addWidget(boutonPrecedent);
    precedentGroupBox->setLayout(precedentLayout);
    boutonPrecedent->setFont(font); // Applique police au bouton "Pr�c�dant"
    boutonPrecedent->setProperty("role", "precedent");

    // Layout principal
    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    for (size_t i = 0; i < 10; i++)
    {
        mainLayout->setRowStretch(i, 1);
        mainLayout->setColumnStretch(i, 1);
    }

    mainLayout->addWidget(InfoGroupBox, 0, 4, Qt::AlignTop | Qt::AlignCenter);

    mainLayout->addWidget(precedentGroupBox, 10, 0, Qt::AlignBottom | Qt::AlignLeft);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connexions
    connect(boutonPrecedent, &QPushButton::clicked, this, &Info::playClickSound);

    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
}

void Info::playClickSound()
{
    // D�terminer le bouton cliqu�
    QObject* obj = sender();
    QPushButton* button = qobject_cast<QPushButton*>(obj);

    if (button != nullptr)
    {
        SonClick.setSource(QUrl::fromLocalFile("clickSound.wav"));
        SonClick.setLoopCount(1);
        SonClick.setVolume(1.0f);
        SonClick.play();

        // v�rifier l'identit� du bouton en utilisant sa propri�t�
        QString role = button->property("role").toString();

        if (role == "demarrer")
        {
            // Faire quelque chose pour le bouton "D�marrer" Comme lancement du jeu
        }
        else if (role == "precedent")
        {
            if (mainWindow == nullptr)
            {
                mainWindow = new MainWindow(this);
                mainWindow->show();
                mainWindow->MenuPrincipale();
            }
            else
            {
                mainWindow->show();
                mainWindow->MenuPrincipale();
            }
            this->hide(); // Cachez la fen�tre d'authentification actuelle
        }
    }
}