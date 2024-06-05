/*
 * File:   GestionTemps.h
 * Author: dbrochard
 *
 * Created on 27 mars 2024, 15:01
 */

#ifndef GestionTemps_H
#define GestionTemps_H

#include <iomanip>
#include <ctime>
#include <chrono>
#include <iostream>

// Structure pour stocker le temps
struct Temps
{
    std::string annee{};
    std::string mois{};
    std::string jour{};
    std::string heure{};
    std::string minute{};
    std::string seconde{};
};


class GestionTemps
{

public:
    GestionTemps(); // Constructeur
    ~GestionTemps(); // Destructeur

    std::tm obtenirHeureActuelle(); // Méthode pour obtenir l'heure actuelle
    void majDate(); // Méthode pour mettre à jour la date
    std::string getDateFormatee() const;

    // Fonctions pour obtenir les différentes parties de la date
    std::string getDateAnnee() const;
    std::string getDateMois() const;
    std::string getDateJour() const;
    std::string getDateHeure() const;
    std::string getDateMinute() const;
    std::string getDateSeconde() const;

    int getTempsAvantProchaineSauvegarde() const;
    int getTempsAvantProchainEnvoiLoRa() const;

private:
    Temps temps; // Variable pour stocker le temps
    int tempsAvantProchaineSauvegarde;
    int tempsAvantProchainEnvoiLoRa;
};

#endif /* GestionTemps_H */
