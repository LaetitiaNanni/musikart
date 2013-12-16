#pragma once
#include <iostream>

#include <vector>
#include "common.hpp"


//bool DoTheImportThing(const std::string& pFile);
/* /!\ Le chemin à mettre est celui entre l'exécutable (généralement dans le dossier build)
et le fichier 3D.
Prend en entrée un string (chemin vers le fichier 3D)
Importe le fichier et crée un aiScene qui contient toutes les meshs de l'objet 3D à modéliser
Retourne true si l'import a marché, false sinon.
*/


std::vector<glimac::ShapeVertex> DoTheImportThing(const std::string& sFilePath);