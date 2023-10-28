#include <iostream>
#include <vector>
#include <string>

class Objet {
public:
    int positionX;
    int positionY;

    Objet() : positionX(0), positionY(0) {}

    Objet(int posX, int posY) : positionX(posX), positionY(posY) {}

    virtual void deplacer(int newX, int newY) = 0;
    virtual void afficher() = 0;
};

class Tableau;

class Robot : public Objet {
public:
    int batterie;

    Robot(int posX, int posY) : Objet(posX, posY), batterie(100) {}

    void deplacer(int newX, int newY) override {
        int distanceX = std::abs(newX - positionX);
        int distanceY = std::abs(newY - positionY);

        if (distanceX == 1 && distanceY == 0 || distanceX == 0 && distanceY == 1) {
            if (batterie > 0) {
                positionX = newX;
                positionY = newY;
                batterie--;
            } else {
                std::cout << "Batterie épuisée, le robot ne peut pas se déplacer\n";
            }
        } else {
            std::cout << "Déplacement impossible\n";
        }
    }

    virtual void afficher() {
        std::cout << "R \t";
    }
};

class Arbre : public Objet {
public:
    std::string statut;

    Arbre(int posX, int posY, std::string statut) : Objet(posX, posY), statut(statut) {}

    void deplacer(int newX, int newY) override {
        // Les arbres ne peuvent pas être déplacés
    }

    void afficher() override {
        if (statut == "pouce")
            std::cout << "a \t";
        else if (statut == "grand")
            std::cout << "A \t";
    }
};

class RobotPlanteur : public Robot {
public:
    RobotPlanteur(int posX, int posY) : Robot(posX, posY) {}

    void planterArbrePouce(Tableau &tableau);

    void afficher() override {
        std::cout << "RP \t";
    }
};

class RobotArroseur : public Robot {
public:
    RobotArroseur(int posX, int posY) : Robot(posX, posY) {}

    void arroserArbre(Arbre &arbre) {
        arbre.statut = "grand";
        std::cout << "Le robot arrose l'arbre\n\n";
    }

    void afficher() override {
        std::cout << "RA \t";
    }
};

class Tableau {
private:
    static const int numRows = 5;
    static const int numCols = 5;
    std::vector<std::vector<Objet*>> tableau;

    bool isValidPosition(int posX, int posY) const {
        return posX >= 0 && posX < numRows && posY >= 0 && posY < numCols;
    }

public:
    Tableau() {
        tableau.resize(numRows, std::vector<Objet*>(numCols, nullptr));
    }

    void afficherTableau() {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (tableau[i][j] != nullptr) {
                    tableau[i][j]->afficher();
                } else {
                    std::cout << "- \t"; // Case vide
                }
            }
            std::cout << std::endl;
        }
    }

    int getNumCols() const {
        return numCols;
    }

    void placerObjet(Objet* objet, int posX, int posY) {
        if (isValidPosition(posX, posY)) {
            tableau[posX][posY] = objet;
            objet->positionX = posX;
            objet->positionY = posY;
        }
    }

    void deplacerObjet(Objet* objet, int newX, int newY) {
        if (objet != nullptr && isValidPosition(newX, newY)) {
            int distanceX = std::abs(newX - objet->positionX);
            int distanceY = std::abs(newY - objet->positionY);

            if (distanceX == 1 && distanceY == 0 || distanceX == 0 && distanceY == 1) {
                Robot* robot = dynamic_cast<Robot*>(objet);
                if (robot) {
                    if (robot->batterie > 0) {
                        tableau[objet->positionX][objet->positionY] = nullptr;
                        tableau[newX][newY] = objet;
                        objet->positionX = newX;
                        objet->positionY = newY;
                        robot->batterie--;
                        std::cout << "Batterie : " << robot->batterie << std::endl;
                    } else {
                        std::cout << "Batterie épuisée, le robot ne peut pas se déplacer\n";
                    }
                } else {
                    tableau[objet->positionX][objet->positionY] = nullptr;
                    tableau[newX][newY] = objet;
                    objet->positionX = newX;
                    objet->positionY = newY;
                }
            } else {
                std::cout << "Déplacement impossible\n";
            }
        }
    }
};

void RobotPlanteur::planterArbrePouce(Tableau &tableau) {
    int newX = positionX+1;
    int newY = positionY ;

    if (newY >= tableau.getNumCols()) {
        std::cout << "Impossible de planter en bas, il n'y a plus de place.\n";
        return;
    }

    Arbre *arbrePouce = new Arbre(newX, newY, "pouce");

    tableau.placerObjet(arbrePouce, newX, newY);
    std::cout << "Robot Planteur plante un arbre 'pouce' en bas.\n";
}

int main() {
    Tableau tableau;

    Robot robotB(1, 2);
    Arbre arbreC(3, 4, "grand");
    Arbre arbreF(1, 1, "pouce");
    RobotPlanteur robotP(0, 0);
    RobotArroseur robotR(2, 1);

    tableau.placerObjet(&arbreF, 1, 1);
    tableau.placerObjet(&robotP, 0, 0);
    tableau.placerObjet(&robotR, 1, 2);
    tableau.placerObjet(&arbreC, 3, 4);

    tableau.afficherTableau();
    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotR, 1, 3);
    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotR, 2, 3);
    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotR, 1, 3);
    tableau.afficherTableau();
    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotR, 1, 2);
    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    robotR.arroserArbre(arbreF);

    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotP, 1, 0);
    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotP, 2, 0);
    tableau.afficherTableau();

    std::cout << "\n________________________________________________________________________________________\n\n";
    tableau.deplacerObjet(&robotP, 3, 0);
    tableau.afficherTableau();
     std::cout << "\n________________________________________________________________________________________\n\n";
     robotP.planterArbrePouce(tableau);
     
    
    tableau.afficherTableau();
    return 0;
}
