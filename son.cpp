#include "son.h"

son::son(QObject *parent) : QObject(parent)
{
    _sonClick1           = new QSoundEffect(this);          
    _sonCollect1         = new QSoundEffect(this);        
    _sonDoorClose1       = new QSoundEffect(this);      
    _sonDoorClose2       = new QSoundEffect(this);      
    _sonDoorOpen1        = new QSoundEffect(this);       
    _sonDropKey1         = new QSoundEffect(this);        
    _sonEating1          = new QSoundEffect(this);         
    _sonBreathing1       = new QSoundEffect(this);      
    _sonHeartbeat1       = new QSoundEffect(this);      
    _sonLockerClose1     = new QSoundEffect(this);    
    _sonLockerOpen1      = new QSoundEffect(this);     
    _sonVendingMachine1  = new QSoundEffect(this); 
    _sonWalk1            = new QSoundEffect(this);           
    _sonWalk2            = new QSoundEffect(this);    

    _sonClick1->          setSource(QUrl::fromLocalFile("./sounds/click1.wav"));
    _sonCollect1->        setSource(QUrl::fromLocalFile("./sounds/collect1.wav"));
    _sonDoorClose1->      setSource(QUrl::fromLocalFile("./sounds/door_close1.wav"));
    _sonDoorClose2->      setSource(QUrl::fromLocalFile("./sounds/door_close2.wav"));
    _sonDoorOpen1->       setSource(QUrl::fromLocalFile("./sounds/door_pen1.wav"));
    _sonDropKey1->        setSource(QUrl::fromLocalFile("./sounds/drop_key1.wav"));
    _sonEating1->         setSource(QUrl::fromLocalFile("./sounds/eating1.wav"));
    _sonBreathing1->      setSource(QUrl::fromLocalFile("./sounds/breathing1.wav"));
    _sonHeartbeat1->      setSource(QUrl::fromLocalFile("./sounds/heartbeat1.wav"));
    _sonLockerClose1->    setSource(QUrl::fromLocalFile("./sounds/locker_close1.wav"));
    _sonLockerOpen1->     setSource(QUrl::fromLocalFile("./sounds/locker_open1.wav"));
    _sonVendingMachine1-> setSource(QUrl::fromLocalFile("./sounds/vending_machine1.wav"));
    _sonWalk1->           setSource(QUrl::fromLocalFile("./sounds/walk1.wav"));
    _sonWalk2->           setSource(QUrl::fromLocalFile("./sounds/walk2.wav"));

    _sonClick1->          setVolume(0.90);
    _sonCollect1->        setVolume(0.90);
    _sonDoorClose1->      setVolume(0.90);
    _sonDoorClose2->      setVolume(0.90);
    _sonDoorOpen1->       setVolume(0.90);
    _sonDropKey1->        setVolume(0.90);
    _sonEating1->         setVolume(0.90);
    _sonBreathing1->      setVolume(0.90);
    _sonHeartbeat1->      setVolume(0.90);
    _sonLockerClose1->    setVolume(0.90);
    _sonLockerOpen1->     setVolume(0.90);
    _sonVendingMachine1-> setVolume(0.90);
    _sonWalk1->           setVolume(0.90);
    _sonWalk2->           setVolume(0.90);
}

son::~son()
{
    delete _sonClick1;
    delete _sonCollect1;
    delete _sonDoorClose1;
    delete _sonDoorClose2;
    delete _sonDoorOpen1;
    delete _sonDropKey1;
    delete _sonEating1;
    delete _sonBreathing1;
    delete _sonHeartbeat1;
    delete _sonLockerClose1;
    delete _sonLockerOpen1;
    delete _sonVendingMachine1;
    delete _sonWalk1;
    delete _sonWalk2;
}


void son::newSons()
{
    _sonClick1           = new QSoundEffect(this);          
    _sonCollect1         = new QSoundEffect(this);        
    _sonDoorClose1       = new QSoundEffect(this);      
    _sonDoorClose2       = new QSoundEffect(this);      
    _sonDoorOpen1        = new QSoundEffect(this);       
    _sonDropKey1         = new QSoundEffect(this);        
    _sonEating1          = new QSoundEffect(this);         
    _sonBreathing1       = new QSoundEffect(this);      
    _sonHeartbeat1       = new QSoundEffect(this);      
    _sonLockerClose1     = new QSoundEffect(this);    
    _sonLockerOpen1      = new QSoundEffect(this);     
    _sonVendingMachine1  = new QSoundEffect(this); 
    _sonWalk1            = new QSoundEffect(this);           
    _sonWalk2            = new QSoundEffect(this);           
}

void son::loadSons()
{
    _sonClick1->          setSource(QUrl::fromLocalFile(":/sounds/click1.wav"));
    _sonCollect1->        setSource(QUrl::fromLocalFile(":/sounds/collect1.wav"));
    _sonDoorClose1->      setSource(QUrl::fromLocalFile(":/sounds/door_close1.wav"));
    _sonDoorClose2->      setSource(QUrl::fromLocalFile(":/sounds/door_close2.wav"));
    _sonDoorOpen1->       setSource(QUrl::fromLocalFile(":/sounds/door_pen1.wav"));
    _sonDropKey1->        setSource(QUrl::fromLocalFile(":/sounds/drop_key1.wav"));
    _sonEating1->         setSource(QUrl::fromLocalFile(":/sounds/eating1.wav"));
    _sonBreathing1->      setSource(QUrl::fromLocalFile(":/sounds/breathing1.wav"));
    _sonHeartbeat1->      setSource(QUrl::fromLocalFile(":/sounds/heartbeat1.wav"));
    _sonLockerClose1->    setSource(QUrl::fromLocalFile(":/sounds/locker_close1.wav"));
    _sonLockerOpen1->     setSource(QUrl::fromLocalFile(":/sounds/locker_open1.wav"));
    _sonVendingMachine1-> setSource(QUrl::fromLocalFile(":/sounds/vending_machine1.wav"));
    _sonWalk1->           setSource(QUrl::fromLocalFile(":/sounds/walk1.wav"));
    _sonWalk2->           setSource(QUrl::fromLocalFile(":/sounds/walk2.wav"));
}

void son::setVolume()
{
    _sonClick1->          setVolume(0.90);
    _sonCollect1->        setVolume(0.90);
    _sonDoorClose1->      setVolume(0.90);
    _sonDoorClose2->      setVolume(0.90);
    _sonDoorOpen1->       setVolume(0.90);
    _sonDropKey1->        setVolume(0.90);
    _sonEating1->         setVolume(0.90);
    _sonBreathing1->      setVolume(0.90);
    _sonHeartbeat1->      setVolume(0.90);
    _sonLockerClose1->    setVolume(0.90);
    _sonLockerOpen1->     setVolume(0.90);
    _sonVendingMachine1-> setVolume(0.90);
    _sonWalk1->           setVolume(0.90);
    _sonWalk2->           setVolume(0.90);
}