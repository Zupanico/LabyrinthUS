/*Fichier: ComArduino.cpp
Description : Fichier d'en-tête de la classe ComArduino
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "ComArduino.h"

ComArduino::ComArduino() : arduino(), com("COM3"), raw_msg(""), j_msg_send(), j_msg_rcv(), led_state(1)
{
    _time = ((double) clock()) / CLOCKS_PER_SEC;
    connexion();
}

ComArduino::~ComArduino()
{
    delete arduino;
}

void ComArduino::connexion()
{
    arduino = new SerialPort(com.c_str(), BAUD); // Créer un objet SerialPort

    if(!arduino->isConnected())
    {
        cerr << "Impossible de se connecter au port "<< string(com) <<". Fermeture du programme!" <<endl;
    }
    else
    {
        cout << "Connexion au port " << string(com) << " reussie." << endl;
    }
}

bool ComArduino::isConnected()
{
    return arduino->isConnected();
}


bool ComArduino::SendToSerial(SerialPort *arduino, json j_msg)
{
    // Return 0 if error
    string msg = j_msg.dump(); // Convertir l'objet JSON en string
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length()); // Ecrire les données sur le port série
    return ret;
}

// Dans ComArduino.cpp
bool ComArduino::RcvFromSerial(SerialPort *arduino, string &msg)
{
    if (!arduino->isConnected())
    {
        std::cerr << "La connexion avec l'Arduino est perdue." << std::endl;
        return false;
    }

    char char_buffer[MSG_MAX_SIZE];
    int buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE - 1); // Lire les données du port série

    if (buffer_size > 0)
    {
        char_buffer[buffer_size] = '\0'; // Assurez-vous que le buffer est terminé correctement
        msg = string(char_buffer);
        return true;
    }
    else
    {
        // Gestion des cas où aucun byte n'est lu
        return false;
    }
}

void ComArduino::setMessages()
{
    if ((((double) clock()) / CLOCKS_PER_SEC) - _time >= 0.225)
    {
        j_msg_send["led"] = led_state;

        if(!SendToSerial(arduino, j_msg_send))
        {
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }

        // Reception message Arduino
        j_msg_rcv.clear(); // effacer le message precedent

        if(!RcvFromSerial(arduino, raw_msg))
        {
            cerr << "Erreur lors de la reception du message. " << endl;
        }

        _time = ((double) clock()) / CLOCKS_PER_SEC;
    }
}

bool ComArduino::lireboutonDroite()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    bool boutonRight = false;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            boutonRight = j_msg_rcv["right"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return boutonRight;
}

bool ComArduino::lireboutonGauche()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    bool boutonLeft = false;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            boutonLeft = j_msg_rcv["left"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return boutonLeft;
}

bool ComArduino::lireboutonHaut()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    bool boutonUp = false;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            boutonUp = j_msg_rcv["up"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return boutonUp;
}

bool ComArduino::lireboutonBas()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    bool boutonDown = false;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            boutonDown = j_msg_rcv["down"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return boutonDown;
}

bool ComArduino::lireboutonjoystick()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    bool boutonJoystick = false;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            boutonJoystick = j_msg_rcv["joystick"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return boutonJoystick;
}

tuple<double, double, double> ComArduino::lireAccelerometre()
{
    setMessages(); // Assurez-vous que cette méthode lit les données du port série

    double accelerationX = 0.0, accelerationY = 0.0, accelerationZ = 0.0;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            accelerationX = j_msg_rcv["aX"];
            accelerationY = j_msg_rcv["aY"];
            accelerationZ = j_msg_rcv["aZ"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return make_tuple(accelerationX, accelerationY, accelerationZ);
}

tuple<double, double> ComArduino::lireJoystick()
{
    setMessages(); // Lire les données du port série

    double joystickX = 0.0, joystickY = 0.0;
    if (raw_msg.size() > 0)
    {
        try
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            joystickX = j_msg_rcv["jX"];
            joystickY = j_msg_rcv["jY"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return make_tuple(joystickX, joystickY);
}
