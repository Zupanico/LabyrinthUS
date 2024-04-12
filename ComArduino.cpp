/*Fichier: ComArduino.cpp
Description : Fichier d'en-tête de la classe ComArduino
Date : 2024-02-22
Auteur : Bakayoko Kanvali*/

#include "ComArduino.h"

// Constructeur de la classe ComArduino
ComArduino::ComArduino() : arduino(), com("COM5"), raw_msg(""), j_msg_send(), j_msg_rcv(), led_state(1), _time(0.0), distance_Monstre_Joueur(0.0)
{
    _time = ((double)clock()) / CLOCKS_PER_SEC;
    connexion();
}

// Destructeur de la classe ComArduino
ComArduino::~ComArduino()
{
    delete arduino;
}

// Méthode de connexion à l'Arduino
void ComArduino::connexion()
{
    arduino = new SerialPort(com.c_str(), BAUD); // Créer un objet SerialPort

    if (!arduino->isConnected())
    {
        cerr << "Impossible de se connecter au port " << string(com) << ". Fermeture du programme!" << endl;
    }
    else
    {
        cout << "Connexion au port " << string(com) << " reussie." << endl;
    }

}

void ComArduino::disconnect()
{
    arduino->closeSerial();
}

bool ComArduino::isConnected()
{
    return arduino->isConnected();
}

// Méthode pour envoyer des données à l'Arduino
bool ComArduino::SendToSerial(SerialPort* arduino, json j_msg)
{
    // Return 0 if error
    string msg = j_msg.dump(); // Convertir l'objet JSON en string
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length()); // Ecrire les données sur le port série
    return ret;
}

// Méthode pour recevoir des données de l'Arduino
bool ComArduino::RcvFromSerial(SerialPort* arduino, string& msg)
{
    if (!arduino->isConnected()) // Vérifier si la connexion avec l'Arduino est perdue
    {
        std::cerr << "La connexion avec l'Arduino est perdue." << std::endl;
        return false;
    }

    char char_buffer[MSG_MAX_SIZE]; // Créer un buffer pour stocker les données
    int buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE - 1); // Lire les données du port série

    if (buffer_size > 0)
    {
        char_buffer[buffer_size] = '\0'; // Assurez-vous que le buffer est terminé correctement
        msg = string(char_buffer); // Convertir le buffer en string
        return true;
    }
    else
    {
        // Gestion des cas où aucun byte n'est lu
        return false;
    }
}

// Méthode pour recevoir des données de l'Arduino
void ComArduino::setMessages()
{
    if ((((double)clock()) / CLOCKS_PER_SEC) - _time >= 0.06)
    {
        j_msg_send["led"] = led_state;
        j_msg_send["distance"] = distance_Monstre_Joueur;
        j_msg_send["nbVies"] = nbVies;

        if (!SendToSerial(arduino, j_msg_send))
        {
            cerr << "Erreur lors de l'envoie du message. " << endl;
        }

        // Reception message Arduino
        j_msg_rcv.clear(); // effacer le message precedent

        if (!RcvFromSerial(arduino, raw_msg))
        {
            cerr << "Erreur lors de la reception du message. " << endl;
        }

        _time = ((double)clock()) / CLOCKS_PER_SEC;
    }
}

void ComArduino::setMessagesDistance(float distance)
{
    distance_Monstre_Joueur = distance;
}

void ComArduino::setMessagesVies(int _vies)
{
    nbVies = _vies;
}

// Méthode pour lire l'état du bouton droit
bool ComArduino::lireboutonDroite()
{
    bool boutonRight = false;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

// Méthode pour lire l'état du bouton gauche
bool ComArduino::lireboutonGauche()
{
    bool boutonLeft = false;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

// Méthode pour lire l'état du bouton haut
bool ComArduino::lireboutonHaut()
{
    bool boutonUp = false;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

// Méthode pour lire l'état du bouton bas
bool ComArduino::lireboutonBas()
{
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

// Méthode pour lire l'état du bouton joystick
bool ComArduino::lireboutonjoystick()
{
    bool boutonJoystick = false;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

// Méthode pour lire les valeurs de l'accéléromètre
tuple<double, double, double> ComArduino::lireAccelerometre()
{
    double accelerationX = 0.0, accelerationY = 0.0, accelerationZ = 0.0;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

// Méthode pour lire les valeurs du joystick
tuple<double, double> ComArduino::lireJoystick()
{
    double joystickX = 0.0, joystickY = 0.0;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
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

int ComArduino::lirerand()
{
    int rand = 0;
    if (raw_msg.size() > 0)
    {
        // Convertir les données brutes en objet JSON
        try // Gérer les erreurs de parsing JSON
        {
            json j_msg_rcv = json::parse(raw_msg); // Convertir les données brutes en objet JSON
            rand = j_msg_rcv["r"];
        }
        catch (json::parse_error& e) // Gérer les erreurs de parsing JSON
        {
            cerr << "Erreur de parsing JSON: " << e.what() << '\n';
        }
    }
    return rand;
}

//nbVies
