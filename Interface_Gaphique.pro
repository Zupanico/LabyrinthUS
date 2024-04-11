# Modèle pour une application Qt
TEMPLATE = vcapp

# Nom de l'exécutable de sortie
TARGET = Interface_Graphique

# Répertoires d'inclusion des fichiers d'en-tête
INCLUDEPATH += \
    . \
    ./include \
    ./include/serial

# Modules Qt requis par l'application
QT += \
    core \
    gui \
    multimedia \
    multimediawidgets \
    widgets

# Fichiers d'en-tête utilisés dans le projet
HEADERS += \
    MainWindow.h \
    Authentification.h \
    LoadGame.h \
    Info.h \
    Play.h \
    ComArduino.h \
    fenetre.h \
    game.h \
    Inventaire.h \
    Item.h \
    map.h \
    monster.h \
    personnage.h \
    Window.h \
    ./include/json.hpp \
    ./include/serial/SerialPort.hpp

# Fichiers source utilisés dans le projet
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Authentification.cpp \
    LoadGame.cpp \
    Info.cpp \
    Play.cpp \
    ComArduino.cpp \
    fenetre.cpp \
    game.cpp \
    Inventaire.cpp \
    Item.cpp \
    map.cpp \
    monster.cpp \
    personnage.cpp \
    Window.cpp \
    ./include/serial/SerialPort.cpp

# Fichiers de ressources utilisés dans le projet
RESOURCES += \
    ressources.qrc

