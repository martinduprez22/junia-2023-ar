#include <iostream>
#include <string>

class Objet {
public:
    int num;
    int positionX;
    int positionY;
    std::string equipe;
    

    Objet() : num(-1), positionX(0), positionY(0),equipe("") {} // -1 =libre -2 obstacle 1 robot
    Objet(int num, int posX, int posY,std::string eq)
        : num(num), positionX(posX), positionY(posY),equipe(eq) {}

    void deplacer(int newX, int newY) {
        positionX = newX;
        positionY = newY;
    }

    void afficher() {
    std::cout << "Robot \t" << equipe << "\t";
}

};

class Tableau {
public:
    int ligne;
    int colonne;
    Objet *tableau; // Utilisez le type Robot pour le tableau

    Tableau(int lignes, int colonnes) : ligne(lignes), colonne(colonnes) {
        tableau = new Objet[lignes * colonnes]; // Initialisez le tableau avec des objets Robot
        for (int i = 0; i < ligne; i++) {
            for (int j = 0; j < colonne; j++) {
                tableau[i * colonne + j] = Objet(); //initialise à libre
            }
        }
    }

     Objet getObjet(int i, int j) {
        return tableau[i * colonne + j];
    }

    void afficher() {
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
             if(tableau[i * colonne + j].num==-2){
             std::cout << "arbre  \t"; 
            }
            else if(tableau[i * colonne + j].num==-1){
             std::cout << "libre  \t"; 
            }
            else {
            tableau[i * colonne + j].afficher();
            }
            std::cout << "§"; // Utilisez le caractère § comme séparateur
        }
        std::cout << std::endl;
    }
}
    void changerCellule(int num, int i, int j,std::string eq) {

            if(tableau[i * colonne + j].num == -2){

                std::cout << "\nimpossible de se déplacer \n"; 
    }
            else {
            tableau[i * colonne + j] = Objet(num, i, j, eq); // Changez la cellule en créant un nouveau Robot
            }
        }

   void deplacerRobot(Objet o, std::string d) {
    int newX = o.positionX;
    int newY = o.positionY;

    // Vérifier si l'objet est un robot
    if (o.num != 1) {
        std::cout << "Impossible de déplacer l'objet, ce n'est pas un robot." << std::endl;
        return;
    }

    if (d == "nord") {
        newX--;
    } else if (d == "sud") {
        newX++;
    } else if (d == "est") {
        newY++;
    } else if (d == "ouest") {
        newY--;
    } else {
        std::cout << "Direction invalide. Utilisez 'nord', 'sud', 'est' ou 'ouest'." << std::endl;
        return;
    }

    if (newX >= 0 && newX < ligne && newY >= 0 && newY < colonne) {
        if (tableau[newX * colonne + newY].num == -2) {
            std::cout << "Impossible de se déplacer sur un arbre." << std::endl;
        } else if (tableau[newX * colonne + newY].num == -1) {
            tableau[o.positionX * colonne + o.positionY] = Objet(-1, o.positionX, o.positionY, ""); // Libère la cellule actuelle
            tableau[newX * colonne + newY] = o; // Déplace le robot
            o.deplacer(newX, newY);
        } else if (tableau[newX * colonne + newY].num == 1) {
            std::cout << "La case de destination est occupée par un autre robot." << std::endl;
        }
    } else {
        std::cout << "Déplacement impossible. La nouvelle position est en dehors des limites du tableau." << std::endl;
    }
}


    ~Tableau() {
        delete[] tableau;
    }
};

int main() {
    Tableau environnement(3, 4);

    environnement.changerCellule(1,1, 2,"A" );//on place 3 robot
    environnement.changerCellule(1,2, 2,"B" );
    environnement.changerCellule(1,0, 2,"A");

    // Affiche le tableau initial
    environnement.afficher();
    environnement.changerCellule(-1,0, 2,"");//libre
    environnement.changerCellule(-2,0, 0,"");//arbre
     environnement.changerCellule(-1,0, 0,"");//libre
    
   
    std::cout << "\n______________________________________________________________________\n \n";
   
    environnement.afficher();
    environnement.deplacerRobot(environnement.getObjet(1,2),"sud");//on déplace le robot sur un robot
    environnement.deplacerRobot(environnement.getObjet(1,2),"est");//on déplace le robot

     std::cout << "\n______________________________________________________________________\nDeplacemnt Robot A à gauche \n";
   
    environnement.afficher();
   environnement.deplacerRobot(environnement.getObjet(1,2),"est");//on déplace du vide(impossible) 
   std::cout << environnement.getObjet(1, 3).num << std::endl;


    return 0;
}
