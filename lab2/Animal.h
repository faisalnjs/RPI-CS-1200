#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>

// Class for the animal
class Animal {
 public:
  std::string name = "Animal";     // Animal name
  int weight = 0;                  // Animal weight
  bool canSurviveOnLand = false;   // If the animal can survive on land
  bool canSurviveInWater = false;  // If the animal can survive in water
  bool canEatMeat = false;         // If the animal can eat meat
  bool canEatPlants = false;       // If the animal can eat plants
  Animal(const std::string& animalName) {
    name = animalName;
  }

  bool isOmnivore() {
    return canEatMeat && canEatPlants;
  }

  bool isAmphibious() {
    return canSurviveOnLand && canSurviveInWater;
  }
};

#endif