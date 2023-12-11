import kotlin.system.exitProcess

// Définition de la classe Recette
data class Recette(val nom: String, val temperature: Int, val duree: Int)

// Définition de la classe Ingredient
data class Ingredient(val nom: String, val unite: String, val quantite: Int)

// Classe principale de l'application
class RiceCookerApp {
    private var temperatureAuto = 0
    private var dureeAuto = 0
    private var ingredients: MutableList<Ingredient> = mutableListOf()

    fun start() {
        while (true) {
            println("Choisissez votre action:")
            println("1-> Recette existante")
            println("2-> Manuelle")
            println("3-> Quitter")

            when (readLine()?.toIntOrNull()) {
                1 -> recetteExistante()
                2 -> manuelle()
                3 -> exitProcess(0)
                else -> println("Choix invalide, veuillez réessayer.")
            }
        }
    }

    private fun recetteExistante() {
        println("Choisissez votre recette:")
        println("1-> Riz")
        println("2-> Oeuf")
        println("3-> Annuler")

        when (readLine()?.toIntOrNull()) {
            1 -> preparerRecette(Recette("Riz", temperatureAuto, dureeAuto))
            2 -> preparerRecette(Recette("Oeuf", temperatureAuto, dureeAuto))
            3 -> return
            else -> println("Choix invalide, veuillez réessayer.")
        }
    }

    private fun manuelle() {
        println("Définir la température en degrés:")
        val temperature = demanderNombrePositif()

        println("Définir la durée de traitement en minutes:")
        val duree = demanderNombrePositif()

        preparerRecette(Recette("Manuelle", temperature, duree))
    }

    private fun preparerRecette(recette: Recette) {
        temperatureAuto = recette.temperature
        dureeAuto = recette.duree
        ingredients.clear()

        ajoutIngredient()
    }

    private fun ajoutIngredient() {
        val ajoutIngredientMenu = """
            Choisissez votre action:
            1-> Ouvrir le rice-cooker et ajouter des ingrédients
            2-> Annuler
        """.trimIndent()

        println(ajoutIngredientMenu)

        when (readLine()?.toIntOrNull()) {
            1 -> ajoutIngredientManuel()
            2 -> return
            else -> println("Choix invalide, veuillez réessayer.")
        }
    }

    private fun ajoutIngredientManuel() {
        while (true) {
            val ingredient = Ingredient(
                demanderString("Nom de l'ingrédient:"),
                demanderString("Unité de mesure:"),
                demanderNombrePositif()
            )

            ingredients.add(ingredient)

            println("""
                Choisissez votre action:
                1-> Ajouter un autre ingrédient
                2-> Fermer le rice-cooker et démarrer la préparation
                3-> Annuler
            """.trimIndent())

            when (readLine()?.toIntOrNull()) {
                1 -> continue
                2 -> {
                    afficherResultat()
                    return
                }
                3 -> {
                    annulerPreparation()
                    return
                }
                else -> println("Choix invalide, veuillez réessayer.")
            }
        }
    }

    private fun afficherResultat() {
        println("Le plat est prêt!")
        println("Ingrédients utilisés:")
        ingredients.forEach { println("${it.nom}: ${it.quantite} ${it.unite}") }
        println("Température: $temperatureAuto °C")
        println("Durée: $dureeAuto minutes")
        annulerPreparation()
    }

    private fun annulerPreparation() {
        temperatureAuto = 0
        dureeAuto = 0
        ingredients.clear()
        println("Annulation de la préparation. Retour au menu principal.")
    }

    private fun demanderNombrePositif(): Int {
        var nombre: Int
        do {
            print("Veuillez entrer un nombre positif: ")
            nombre = readLine()?.toIntOrNull() ?: -1
        } while (nombre < 0)

        return nombre
    }

    private fun demanderString(message: String): String {
        print("$message ")
        return readLine() ?: ""
    }
}

fun main() {
    val riceCookerApp = RiceCookerApp()
    riceCookerApp.start()
}
