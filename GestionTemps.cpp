/*
 * File:   GestionTemps.cpp
 * Author: dbrochard
 *
 * Created on 27 mars 2024, 15:01
 */
 
#include "GestionTemps.h"

GestionTemps::GestionTemps()
{
    majDate();
}

GestionTemps::~GestionTemps()
{
}

// Fonction pour obtenir l'heure actuelle
std::tm GestionTemps::obtenirHeureActuelle()
{
  std::chrono::time_point<std::chrono::system_clock> maintenant = std::chrono::system_clock::now();
  std::time_t tempsActuel = std::chrono::system_clock::to_time_t(maintenant);
  std::tm tmMaintenant = *localtime(&tempsActuel);
  return tmMaintenant;
}

void GestionTemps::majDate()
{
    // Obtention du temps actuel
    auto tempsMaintenant = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::tm *tempsLocal = std::localtime(&tempsMaintenant);

    // Mise à jour des champs de la structure Temps
    temps.annee = std::to_string(tempsLocal->tm_year + 1900);
    if (tempsLocal->tm_year + 1900 < 1000)
        temps.annee = "0" + temps.annee;
    temps.mois = std::to_string(tempsLocal->tm_mon + 1);
    if (tempsLocal->tm_mon < 10)
        temps.mois = "0" + temps.mois;
    temps.jour = std::to_string(tempsLocal->tm_mday);
    if (tempsLocal->tm_mday < 10)
        temps.jour = "0" + temps.jour;
    temps.heure = std::to_string(tempsLocal->tm_hour);
    if (tempsLocal->tm_hour < 10)
        temps.heure = "0" + temps.heure;
    temps.minute = std::to_string(tempsLocal->tm_min);
    if (tempsLocal->tm_min < 10)
        temps.minute = "0" + temps.minute;
    temps.seconde = std::to_string(tempsLocal->tm_sec);
    if (tempsLocal->tm_sec < 10)
        temps.seconde = "0" + temps.seconde;

    // Calculer le temps avant la prochaine sauvegarde en utilisant le modulo
    tempsAvantProchaineSauvegarde = 10 - (tempsLocal->tm_sec % 10);

    // Calculer le temps avant le prochain envoie de trame LoRa en utilisant le modulo
    if (tempsLocal->tm_min % 2 == 0) {
        if (tempsLocal->tm_sec < 30) {
            tempsAvantProchainEnvoiLoRa = 30 - (tempsLocal->tm_sec % 30);
        }
        else if (tempsLocal->tm_sec > 30 && tempsLocal->tm_sec < 60) {
            tempsAvantProchainEnvoiLoRa = 120 - (tempsLocal->tm_sec % 30);
        }
    }
    else {
        if (tempsLocal->tm_sec < 30) {
            tempsAvantProchainEnvoiLoRa = 90 - (tempsLocal->tm_sec % 30);
        }
        else if (tempsLocal->tm_sec > 30 && tempsLocal->tm_sec < 60) {
            tempsAvantProchainEnvoiLoRa = 60 - (tempsLocal->tm_sec % 30);
        } 
        else {
            tempsAvantProchainEnvoiLoRa = 60;
        }
    }

    //std::cout << temps.annee << "-" << temps.mois << "-" << temps.jour << " " << temps.heure << ":" << temps.minute << ":" << temps.seconde << " - mise à jour de la date" << std::endl;
}

int GestionTemps::getTempsAvantProchaineSauvegarde() const
{
    return tempsAvantProchaineSauvegarde;
}

int GestionTemps::getTempsAvantProchainEnvoiLoRa() const
{
    return tempsAvantProchainEnvoiLoRa;
}

std::string GestionTemps::getDateFormatee() const
{
    return getDateAnnee() + "-" + getDateMois() + "-" + getDateJour() + " " + getDateHeure() + ":" + getDateMinute() + ":" + getDateSeconde();
}

// Fonctions pour obtenir les différentes parties de la date
std::string GestionTemps::getDateAnnee() const
{
    return temps.annee;
}

std::string GestionTemps::getDateMois() const
{
    return temps.mois;
}

std::string GestionTemps::getDateJour() const
{
    return temps.jour;
}

std::string GestionTemps::getDateHeure() const
{
    return temps.heure;
}

std::string GestionTemps::getDateMinute() const
{
    return temps.minute;
}

std::string GestionTemps::getDateSeconde() const
{
    return temps.seconde;
}
