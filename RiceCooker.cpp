#include <iostream>
#include <limits>
#include <vector>
#include <string>

class Ingredient {
public:
    std::string name;
    std::string unit;
    double quantity;

    Ingredient(const std::string& n, const std::string& u, double q)
        : name(n), unit(u), quantity(q) {}
};

class RiceCooker {
private:
    double temperature;
    int duration;
    std::vector<Ingredient> ingredients;

public:
    RiceCooker() : temperature(0.0), duration(0) {}

    void setTemperature(double temp) {
        temperature = temp;
    }

    void setDuration(int dur) {
        duration = dur;
    }

    void addIngredient(const std::string& name, const std::string& unit, double quantity) {
        ingredients.emplace_back(name, unit, quantity);
    }

    void displayResult() {
        std::cout << "Le plat est prêt !\n";
        std::cout << "Ingrédients utilisés :\n";
        for (const auto& ingredient : ingredients) {
            std::cout << "- " << ingredient.quantity << " " << ingredient.unit << " de " << ingredient.name << "\n";
        }
        std::cout << "Température : " << temperature << " degrés\n";
        std::cout << "Durée : " << duration << " minutes\n";
    }

    void reset() {
        temperature = 0.0;
        duration = 0;
        ingredients.clear();
    }
};

class Validator {
public:
    static double getValidDouble() {
        double value;
        while (true) {
            std::cin >> value;
            if (std::cin.fail() || value < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Veuillez entrer un nombre valide et non négatif : ";
            } else {
                break;
            }
        }
        return value;
    }

    static int getValidInt() {
        int value;
        while (true) {
            std::cin >> value;
            if (std::cin.fail() || value < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Veuillez entrer un nombre entier valide et non négatif : ";
            } else {
                break;
            }
        }
        return value;
    }
};

int main() {
    RiceCooker riceCooker;
    int choice;

    do {
        std::cout << "Choisir votre action:\n";
        std::cout << "1-> Recette existante\n";
        std::cout << "2-> Manuelle\n";
        std::cout << "3-> Annuler\n";
        choice = Validator::getValidInt();

        switch (choice) {
            case 1: {
                std::cout << "Choisir votre action:\n";
                std::cout << "1-> Riz\n";
                std::cout << "2-> Oeuf\n";
                std::cout << "3-> Annuler\n";
                int recipeChoice = Validator::getValidInt();

                if (recipeChoice == 1) {
                    // Riz
                    riceCooker.setTemperature(100.0);
                    riceCooker.setDuration(20);
                } else if (recipeChoice == 2) {
                    // Oeuf
                    riceCooker.setTemperature(70.0);
                    riceCooker.setDuration(10);
                }
                break;
            }
            case 2: {
                std::cout << "Définir température en degrés : ";
                double temp = Validator::getValidDouble();
                riceCooker.setTemperature(temp);

                std::cout << "Définir la durée de traitement en minutes : ";
                int dur = Validator::getValidInt();
                riceCooker.setDuration(dur);
                break;
            }
            case 3:
                std::cout << "Annulation de toutes les opérations.\n";
                break;
            default:
                std::cout << "Choix invalide. Veuillez réessayer.\n";
        }

        if (choice != 3) {
            // Ajout d'ingrédients
            int addIngredientChoice;
            std::cout << "Choisir si accepte de commencer l'ajout d'ingrédient:\n";
            std::cout << "1-> Ouvrir le rice-cooker et ajouter des ingrédients\n";
            std::cout << "2-> Annuler\n";
            addIngredientChoice = Validator::getValidInt();

            do {
                if (addIngredientChoice == 1) {
                    // Ajout d'ingrédient
                    std::string name, unit;
                    double quantity;

                    std::cout << "Nom de l'ingrédient : ";
                    std::cin >> name;

                    std::cout << "Définir l'unité : ";
                    std::cin >> unit;

                    std::cout << "Définir la quantité : ";
                    quantity = Validator::getValidDouble();

                    riceCooker.addIngredient(name, unit, quantity);

                    std::cout << "Choisir si accepte de continuer l'ajout d'ingrédient:\n";
                    std::cout << "1-> Ajouter un autre ingrédient\n";
                    std::cout << "2-> Fermer le rice-cooker et démarrer la préparation\n";
                    std::cout << "3-> Annuler\n";
                    addIngredientChoice = Validator::getValidInt();
                }
            } while (addIngredientChoice == 1);

            if (addIngredientChoice == 2) {
                riceCooker.displayResult();
                riceCooker.reset();
            }
        }
    } while (choice != 3);

    return 0;
}
