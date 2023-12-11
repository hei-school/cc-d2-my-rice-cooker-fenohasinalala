<?php

class Validator
{
    public static function validateNumericInput($input)
    {
        while (!is_numeric($input) || $input < 0) {
            echo "Veuillez entrer un nombre valide (non négatif): ";
            $input = readline();
            if ($input === false) {
                exit("\nOpération annulée.\n");
            }
        }
        return $input;
    }
}

class Ingredient
{
    public $name;
    public $unit;
    public $quantity;

    public function __construct($name, $unit, $quantity)
    {
        $this->name = $name;
        $this->unit = $unit;
        $this->quantity = $quantity;
    }
}

class Recipe
{
    public function prepare()
    {
        echo "Le plat est prêt!\n";
    }
}

class RiceCookerApp
{
    private $temperature;
    private $duration;
    private $recipe;

    public function run()
    {
        while (true) {
            $this->showMainMenu();
            $choice = $this->getUserChoice();

            switch ($choice) {
                case 1:
                    $this->prepareRecipe();
                    break;
                case 2:
                    $this->prepareManual();
                    break;
                default:
                    exit("Opération annulée.\n");
            }
        }
    }

    private function showMainMenu()
    {
        echo "Choisissez votre action:\n";
        echo "1-> Recette existante\n";
        echo "2-> Manuelle\n";
    }

    private function getUserChoice()
    {
        return Validator::validateNumericInput(readline());
    }

    private function prepareRecipe()
    {
        $this->showRecipeMenu();
        $recipeChoice = $this->getUserChoice();

        switch ($recipeChoice) {
            case 1:
                $this->recipe = new Recipe();
                break;
            case 2:
                $this->recipe = new Recipe(); // Ajouter la logique pour la recette d'oeufs
                break;
            default:
                exit("Opération annulée.\n");
        }

        $this->addIngredients();
    }

    private function showRecipeMenu()
    {
        echo "Choisissez votre recette:\n";
        echo "1-> Riz\n";
        echo "2-> Oeuf\n";
        echo "3-> Annuler\n";
    }

    private function prepareManual()
    {
        echo "Définir la température en degré:\n";
        $this->temperature = Validator::validateNumericInput(readline());

        echo "Définir la durée de traitement en minute:\n";
        $this->duration = Validator::validateNumericInput(readline());

        $this->addIngredients();
    }

    private function addIngredients()
    {
        $ingredients = [];
        echo "Choisissez si vous acceptez de commencer l'ajout d'ingrédients:\n";
        echo "1-> Ouvrir le rice-cooker et ajouter des ingrédients\n";
        echo "2-> Annuler\n";

        $addChoice = $this->getUserChoice();
        while ($addChoice == 1) {
            switch ($addChoice) {
                case 1:
                    $ingredient = $this->addIngredient();
                    $ingredients[] = $ingredient;
                    break;
                case 2:
                    $this->finishPreparation($ingredients);
                    break;
                default:
                    exit("Opération annulée.\n");
            }
            echo "Choisir si accepte de continuer l'ajout d'ingrédient:\n";
            echo "1-> Ajouter un autre ingrédient\n";
            echo "2-> Fermer le rice-cooker et démarrer la préparation\n";
            echo "3-> Annuler\n";
            $addChoice = $this->getUserChoice();
        }
        switch ($addChoice) {
            case 2:
                $this->finishPreparation($ingredients);
                break;
            default:
                exit("Opération annulée.\n");
        }
    }

    private function addIngredient()
    {
        echo "Nom de l'ingrédient: ";
        $name = readline();

        echo "Définir l'unité: ";
        $unit = readline();

        echo "Définir la quantité: ";
        $quantity = Validator::validateNumericInput(readline());

        return new Ingredient($name, $unit, $quantity);
    }

    private function finishPreparation($ingredients)
    {
        echo "Le plat est prêt!\n";
        echo "Liste des ingrédients utilisés:\n";
        foreach ($ingredients as $ingredient) {
            echo "{$ingredient->name}: {$ingredient->quantity} {$ingredient->unit}\n";
        }

        echo "Température: " . ($this->temperature ?? "Automatique") . " degrés\n";
        echo "Durée: " . ($this->duration ?? "Automatique") . " minutes\n";

        // Réinitialiser les variables pour annuler les opérations
        $this->temperature = null;
        $this->duration = null;
        $this->recipe = null;
    }
}

$app = new RiceCookerApp();
$app->run();
?>
