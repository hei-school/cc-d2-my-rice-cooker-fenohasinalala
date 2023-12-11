package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Ingredient représente un ingrédient avec son nom, unité et quantité.
type Ingredient struct {
	Name     string
	Unit     string
	Quantity float64
}

// Cooker représente le rice-cooker avec ses propriétés.
type Cooker struct {
	Temperature float64
	Duration    int
	Ingredients []Ingredient
}

// Validator est une fonction qui valide une saisie utilisateur.
type Validator func(string) (float64, error)

// ValidateNumber valide si la saisie est un nombre positif.
func ValidateNumber(input string) (float64, error) {
	value, err := strconv.ParseFloat(input, 64)
	if err != nil || value < 0 {
		return 0, fmt.Errorf("Veuillez entrer un nombre positif")
	}
	return value, nil
}

// ShowMenu affiche le menu principal.
func ShowMenu() {
	fmt.Println("Choisissez votre action:")
	fmt.Println("1-> Recette existante")
	fmt.Println("2-> Manuelle")
}

// ShowRecipeMenu affiche le menu des recettes existantes.
func ShowRecipeMenu() {
	fmt.Println("Choisissez votre recette:")
	fmt.Println("1-> Riz")
	fmt.Println("2-> Oeuf")
	fmt.Println("3-> Annuler")
}

// ShowIngredientMenu affiche le menu d'ajout d'ingrédient.
func ShowIngredientMenu() {
	fmt.Println("Choisissez votre action:")
	fmt.Println("1-> Ajouter d'autres ingrédients")
	fmt.Println("2-> Fermer le rice-cooker et démarrer la préparation")
	fmt.Println("3-> Annuler")
}

// AddIngredient permet à l'utilisateur d'ajouter un ingrédient.
func AddIngredient(scanner *bufio.Scanner) (Ingredient, error) {
	fmt.Print("Nom de l'ingrédient: ")
	name := scanner.Text()

	fmt.Print("Unité: ")
	unit := scanner.Text()

	fmt.Print("Quantité: ")
	quantityInput := scanner.Text()
	quantity, err := ValidateNumber(quantityInput)
	if err != nil {
		return Ingredient{}, err
	}

	return Ingredient{Name: name, Unit: unit, Quantity: quantity}, nil
}

// StartCooking démarre la préparation et affiche les détails.
func StartCooking(cooker Cooker) {
	fmt.Println("Le plat est prêt!")
	fmt.Println("Ingrédients utilisés:")
	for _, ingredient := range cooker.Ingredients {
		fmt.Printf("- %s: %.2f %s\n", ingredient.Name, ingredient.Quantity, ingredient.Unit)
	}

	fmt.Printf("Température: %.2f °C\n", cooker.Temperature)
	fmt.Printf("Durée: %d minutes\n", cooker.Duration)
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var cooker Cooker

	for {
		ShowMenu()
		scanner.Scan()
		menuChoice := scanner.Text()

		switch menuChoice {
		case "1":
			ShowRecipeMenu()
			scanner.Scan()
			recipeChoice := scanner.Text()
			switch recipeChoice {
			case "1", "2":
				cooker = Cooker{Temperature: 100, Duration: 15, Ingredients: []Ingredient{}}
				fmt.Println("Opération d'ajout d'aliment commencera automatiquement.")
			case "3":
				fmt.Println("Annulation de l'opération en cours.")
				continue
			default:
				fmt.Println("Choix invalide.")
				continue
			}
		case "2":
			fmt.Print("Définir la température en degré: ")
			scanner.Scan()
			temperatureInput := scanner.Text()
			temperature, err := ValidateNumber(temperatureInput)
			if err != nil {
				fmt.Println(err)
				continue
			}
			cooker.Temperature = temperature

			fmt.Print("Définir la durée de traitement en minute: ")
			scanner.Scan()
			durationInput := scanner.Text()
			duration, err := strconv.Atoi(durationInput)
			if err != nil || duration < 0 {
				fmt.Println("Veuillez entrer une durée valide en minutes.")
				continue
			}
			cooker.Duration = duration
		default:
			fmt.Println("Choix invalide.")
			continue
		}

		for {
			ShowIngredientMenu()
			scanner.Scan()
			ingredientChoice := scanner.Text()

			switch ingredientChoice {
			case "1":
				ingredient, err := AddIngredient(scanner)
				if err != nil {
					fmt.Println(err)
					continue
				}
				cooker.Ingredients = append(cooker.Ingredients, ingredient)
			case "2":
				StartCooking(cooker)
				// Annulation de toutes les opérations
				cooker = Cooker{}
				break
			case "3":
				fmt.Println("Annulation de l'opération en cours.")
				cooker = Cooker{}
				break
			default:
				fmt.Println("Choix invalide.")
			}
		}
	}
}
