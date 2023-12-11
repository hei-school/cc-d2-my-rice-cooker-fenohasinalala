import kotlin.system.exitProcess

fun main() {
    val riceCooker = RiceCooker()

    while (true) {
        println("Choisir votre action:")
        println("1-> recette existante")
        println("2-> Manuelle")
        println("3-> Quitter")

        when (readLine()?.toIntOrNull()) {
            1 -> riceCooker.preparerRecetteExistante()
            2 -> riceCooker.preparerManuelle()
            3 -> {
                println("Merci d'avoir utilisé le simulateur de rice-cooker. Au revoir!")
                exitProcess(0)
            }
            else -> println("Choix invalide. Veuillez entrer 1, 2, ou 3.")
        }
    }
}

class RiceCooker {
    fun preparerRecetteExistante() {
        println("Choisir votre recette existante:")
        println("1-> riz")
        println("2-> oeuf")
        println("3-> annuler")

        when (readLine()?.toIntOrNull()) {
            1 -> ajouterIngredients("riz")
            2 -> ajouterIngredients("oeuf")
            3 -> return
            else -> println("Choix invalide. Veuillez entrer 1, 2, ou 3.")
        }
    }

    fun preparerManuelle() {
        var temperature: Int
        var duree: Int

        println("Définir température en degrés:")
        temperature = readInt()

        println("Définir la durée de traitement en minutes:")
        duree = readInt()

        ajouterIngredients("manuel", temperature, duree)
    }

    private fun ajouterIngredients(type: String, temperature: Int = 0, duree: Int = 0) {
        val ingredients = mutableListOf<Ingredient>()

        println("Commencer l'ajout d'ingrédients:")
        while (true) {
            println("1-> Ouvrir le rice-cooker et ajouter des ingrédients")
            println("2-> Annuler")

            when (readLine()?.toIntOrNull()) {
                1 -> {
                    val nom = readString("Nom de l'ingrédient:")
                    val unite = readString("Définir l'unité:")
                    val quantite = readInt("Définir la quantité:")

                    ingredients.add(Ingredient(nom, unite, quantite))

                    println("1-> Ajouter un autre ingrédient")
                    println("2-> Fermer le rice-cooker et démarrer la préparation")
                    println("3-> Annuler")

                    when (readLine()?.toIntOrNull()) {
                        1 -> continue
                        2 -> {
                            afficherResultat(type, temperature, duree, ingredients)
                            return
                        }
                        3 -> {
                            println("Opération annulée. Retour au menu principal.")
                            return
                        }
                        else -> println("Choix invalide. Veuillez entrer 1, 2, ou 3.")
                    }
                }
                2 -> {
                    println("Opération annulée. Retour au menu principal.")
                    return
                }
                else -> println("Choix invalide. Veuillez entrer 1 ou 2.")
            }
        }
    }

    private fun afficherResultat(type: String, temperature: Int, duree: Int, ingredients: List<Ingredient>) {
        println("Le plat est prêt!")
        println("Type: $type")
        println("Température: $temperature degrés")
        println("Durée: $duree minutes")
        println("Ingrédients:")
        ingredients.forEach { println("${it.nom}: ${it.quantite} ${it.unite}") }

        // Réinitialiser les opérations
        println("Retour au menu principal. Toutes les opérations annulées.")
    }

    private fun readString(prompt: String): String {
        while (true) {
            print("$prompt ")
            val input = readLine()
            if (!input.isNullOrBlank()) {
                return input
            }
            println("Veuillez entrer une valeur non vide.")
        }
    }

    private fun readInt(prompt: String): Int {
        while (true) {
            print("$prompt ")
            val input = readLine()
            val value = input?.toIntOrNull()
            if (value != null && value >= 0) {
                return value
            }
            println("Veuillez entrer un nombre entier positif.")
        }
    }
}

data class Ingredient(val nom: String, val unite: String, val quantite: Int)
