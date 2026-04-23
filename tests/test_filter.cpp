#include <gtest/gtest.h>
#include "DataFilter.hpp"

// Test de base pour vérifier que la moyenne mobile est mathématiquement correcte
TEST(MovingAverageFilterTest, BasicFiltering) {
    // Création d'un filtre avec une fenêtre de 3 valeurs
    MovingAverageFilter filter(3);

    // Étape 1 : Le tableau est [10, 0, 0] -> Somme = 10 -> Moyenne = 10 / 3 = 3
    EXPECT_EQ(filter.process(10), 3);

    // Étape 2 : Le tableau est [10, 20, 0] -> Somme = 30 -> Moyenne = 30 / 3 = 10
    EXPECT_EQ(filter.process(20), 10);

    // Étape 3 : Le tableau est [10, 20, 30] -> Somme = 60 -> Moyenne = 60 / 3 = 20
    EXPECT_EQ(filter.process(30), 20);

    // Étape 4 : Le tableau remplace la plus vieille valeur [40, 20, 30] -> Somme = 90 -> Moyenne = 30
    EXPECT_EQ(filter.process(40), 30);
}

// Test pour vérifier le comportement avec des valeurs négatives (ex: températures sous zéro)
TEST(MovingAverageFilterTest, NegativeValues) {
    MovingAverageFilter filter(2);
    
    EXPECT_EQ(filter.process(-10), -5);
    EXPECT_EQ(filter.process(-20), -15);
}