/*
Fichier: son.h
Description: Fichier d'en-tête de la classe Son
Date: 2024-04-11
*/
#ifndef SON_H
#define SON_H

#include <QTimer>
#include <QApplication>
#include <QSoundEffect>

class son : public QObject {
    Q_OBJECT
    protected:
        // Sons
        QSoundEffect *_sonClick1;
        QSoundEffect *_sonCollect1;
        QSoundEffect *_sonDoorClose1;
        QSoundEffect *_sonDoorClose2;
        QSoundEffect *_sonDoorOpen1;
        QSoundEffect *_sonDropKey1;
        QSoundEffect *_sonEating1;
        QSoundEffect *_sonBreathing1;
        QSoundEffect *_sonHeartbeat1;
        QSoundEffect *_sonLockerClose1;
        QSoundEffect *_sonLockerOpen1;
        QSoundEffect *_sonVendingMachine1;
        QSoundEffect *_sonWalk1;
        QSoundEffect *_sonWalk2;

    public:
        explicit son(QObject *parent = nullptr);
        ~son();

        // Sons
        void newSons();
        void loadSons();
        void setVolume();

        // Play
        void playClick1()           { _sonClick1->play(); }
        void playCollect1()         { _sonCollect1->play();}
        void playDoorClose1()       { _sonDoorClose1->play();}
        void playDoorClose2()       { _sonDoorClose2->play();}
        void playDoorOpen1()        { _sonDoorOpen1->play();}
        void playDropKey1()         { _sonDropKey1->play();}
        void playEating1()          { _sonEating1->play();}
        void playBreathing1()       { _sonBreathing1->play();}
        void playHeartbeat1()       { _sonHeartbeat1->play();}
        void playLockerClose1()     { _sonLockerClose1->play();}
        void playLockerOpen1()      { _sonLockerOpen1->play();}
        void playVendingMachine1()  { _sonVendingMachine1->play();}
        void playWalk1()            { _sonWalk1->play();}
        void playWalk2()            { _sonWalk2->play();}
};

#endif
