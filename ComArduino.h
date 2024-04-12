/*Fichier: ComArduino.h
Description : Fichier d'en-tête de la classe ComArduino
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#ifndef COMARDUINO_H
#define COMARDUINO_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <tuple>
#include <string>
#include "include/serial/SerialPort.hpp"
#include "include/json.hpp"
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
using json = nlohmann::json;

#define BAUD 115200
#define MSG_MAX_SIZE 1024

class ComArduino
{
private:
    int led_state;

    float distance_Monstre_Joueur;
    int nbVies;
    float _time;

    SerialPort* arduino;
    string com;
    string raw_msg;
    json j_msg_send, j_msg_rcv;

public:
    ComArduino();
    ~ComArduino();

    void connexion();
    bool isConnected();
    void disconnect();
    void setMessages();
    void setMessagesDistance(float distance);
    void setMessagesVies(int vies);

    bool SendToSerial(SerialPort* arduino, json j_msg);
    bool RcvFromSerial(SerialPort* arduino, string& msg);

    bool lireboutonDroite();
    bool lireboutonGauche();
    bool lireboutonHaut();
    bool lireboutonBas();
    bool lireboutonjoystick();
    int lirerand();

    tuple<double, double, double> lireAccelerometre();
    tuple<double, double> lireJoystick();
};

#endif
