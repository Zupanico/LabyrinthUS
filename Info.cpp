#include "Info.h"
#include "MainWindow.h"

Info::Info(QWidget* parent) : QMainWindow(parent)
{
    mainWindow = qobject_cast<MainWindow*>(parent);
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
    qDeleteAll(this->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    centralWidget = new QWidget(this);

    // Layout principal
    QGridLayout* mainLayout = new QGridLayout(centralWidget);

    textEdit = new QTextEdit;
    textEdit->setFixedSize(1000, 400);
    textEdit->setReadOnly(true);

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

    // Cr�ation du QPushButton pour afficher l'ic�ne Pr�c�dent
    boutonPrecedent = new QPushButton(this);
    QPixmap originalPrevIcon(":/images/retour.png"); // Chemin de l'ic�ne pr�c�dente
    QPixmap resizedPrevIcon = originalPrevIcon.scaled(QSize(60, 60), Qt::KeepAspectRatio); // Redimensionner l'ic�ne
    boutonPrecedent->setIcon(QIcon(resizedPrevIcon));
    boutonPrecedent->setIconSize(resizedPrevIcon.size());
    boutonPrecedent->setFixedSize(resizedPrevIcon.size()); // Taille fixe pour s'adapter � l'ic�ne
    boutonPrecedent->setFlat(true); // Rendre le bouton sans bordure
    boutonPrecedent->setProperty("role", "precedent");

    // Ajouter l'ic�ne Pr�c�dent dans le grid layout
    connect(boutonPrecedent, &QPushButton::clicked, this, &Info::playClickSound);

    for (size_t i = 0; i < 10; i++)
    {
        mainLayout->setRowStretch(i, 1);
        mainLayout->setColumnStretch(i, 1);
    }

    mainLayout->addWidget(textEdit, 5, 2, 1, 6, Qt::AlignCenter);
    mainLayout->addWidget(InfoGroupBox, 0, 4, Qt::AlignTop | Qt::AlignCenter);

    mainLayout->addWidget(boutonPrecedent, 9, 0, 1, 1, Qt::AlignLeft | Qt::AlignBottom); // Pr�c�dent en bas � gauche

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connexions
    connect(boutonPrecedent, &QPushButton::clicked, this, &Info::playClickSound);

    setFixedSize(1525, 785);
    setWindowTitle(tr("LABYRINTHUS GROUPE P6 : : PROJET DE FIN DE SESSION S2 -->> BAKAYOKO KANVALI"));
    
    saveData();
}

void Info::saveData()
{
    // Chemin du fichier de sauvegarde
    QString filePath = "./Interface_Graphique/Informations.txt";

    // Ouvrir le fichier en mode �criture (cr�er s'il n'existe pas)
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier pour l'�criture.";
        return;
    }

    // Cr�er un flux de texte pour �crire dans le fichier
    QTextStream out(&file);

    // �crire les donn�es dans le fichier
    out << "Informations importantes\n";
    out << "Ligne 1 : Donn�es importantes\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    out << "Ligne 2 : Autres informations\n";
    // Ajoutez autant de lignes que n�cessaire

    // Fermer le fichier apr�s avoir �crit les donn�es
    file.close();

    qDebug() << "Donn�es enregistr�es avec succ�s dans le fichier.";

    // Afficher le contenu du fichier dans le QTextEdit
    if (!textEdit->toPlainText().isEmpty())
    {
        textEdit->clear(); // Efface le contenu pr�c�dent
    }

    // Lire le contenu du fichier et l'afficher dans textEdit
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString fileContent = in.readAll();
        textEdit->setText(fileContent);

        // Fermer le fichier apr�s lecture
        file.close();
    }
    else
    {
        qDebug() << "Impossible d'ouvrir le fichier pour la lecture.";
    }
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

        if (role == "precedent")
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


