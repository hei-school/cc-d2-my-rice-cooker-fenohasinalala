#include <iostream>
#include <limits>
#include <string>
#include <vector>

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

    void SetTemperature(double temp) {
        temperature = temp;
    }

    void SetDuration(int dur) {
        duration = dur;
    }

    void AddIngredient(const std::string& name, const std::string& unit, double quantity) {
        ingredients.emplace_back(name, unit, quantity);
    }

    void DisplayResult() const {
        std::cout << "Le plat est prêt !\n";
        std::cout << "Ingrédients utilisés :\n";
        for (const auto& ingredient : ingredients) {
            std::cout << "- " << ingredient.quantity << " " << ingredient.unit << " de " << ingredient.name << "\n";
        }
        std::cout << "Température : " << temperature << " degrés\n";
        std::cout << "Durée : " << duration << " minutes\n";
    }

    void Reset() {
        temperature = 0.0;
        duration = 0;
        ingredients.clear();
    }
};

class Validator {
public:
    static double GetValidDouble() {
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

    static int GetValidInt() {
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
        choice = Validator::GetValidInt();

        switch (choice) {
            case 1: {
                std::cout << "Choisir votre action:\n";
                std::cout << "1-> Riz\n";
                std::cout << "2-> Oeuf\n";
                std::cout << "3-> Annuler\n";
                int recipeChoice = Validator::GetValidInt();

                if (recipeChoice == 1) {
                    // Riz
                    riceCooker.SetTemperature(100.0);
                    riceCooker.SetDuration(20);
                } else if (recipeChoice == 2) {
                    // Oeuf
                    riceCooker.SetTemperature(70.0);
                    riceCooker.SetDuration(10);
                }
                break;
            }
            case 2: {
                std::cout << "Définir température en degrés : ";
                double temp = Validator::GetValidDouble();
                riceCooker.SetTemperature(temp);

                std::cout << "Définir la durée de traitement en minutes : ";
                int dur = Validator::GetValidInt();
                riceCooker.SetDuration(dur);
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
            addIngredientChoice = Validator::GetValidInt();

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
                    quantity = Validator::GetValidDouble();

                    riceCooker.AddIngredient(name, unit, quantity);

                    std::cout << "Choisir si accepte de continuer l'ajout d'ingrédient:\n";
                    std::cout << "1-> Ajouter un autre ingrédient\n";
                    std::cout << "2-> Fermer le rice-cooker et démarrer la préparation\n";
                    std::cout << "3-> Annuler\n";
                    addIngredientChoice = Validator::GetValidInt();
                }
            } while (addIngredientChoice == 1);

            if (addIngredientChoice == 2) {
                riceCooker.DisplayResult();
                riceCooker.Reset();
            }
        }
    } while (choice != 3);

    return 0;
}
