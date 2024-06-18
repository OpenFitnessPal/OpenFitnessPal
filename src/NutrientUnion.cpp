#include "NutrientUnion.h"



NutrientUnion NutrientUnion::operator+=(const NutrientUnion &other)
{
    this->calcium += other.calcium;
    this->carbs += other.carbs;
    this->fat += other.fat;
    this->satFat += other.satFat;
    this->monoFat += other.monoFat;
    this->polyFat += other.polyFat;
    this->transFat += other.transFat;
    this->fiber += other.fiber;
    this->sugar += other.sugar;
    this->addedSugar += other.addedSugar;
    this->protein += other.protein;
    this->cholesterol += other.cholesterol;
    this->iron += other.iron;
    this->sodium += other.sodium;
    this->potassium += other.potassium;
    this->vitaminA += other.vitaminA;
    this->vitaminC += other.vitaminC;
    this->vitaminD += other.vitaminD;

    return *this;
}

double NutrientUnion::calories() const
{
    return fat * 9 + (carbs - fiber) * 4 + protein * 4;
}

NutrientUnion operator+(const NutrientUnion &a, const NutrientUnion &b) {
    NutrientUnion n;

    n.calcium = a.calcium + b.calcium;
    n.carbs = a.carbs + b.carbs;
    n.fat = a.fat + b.fat;
    n.satFat = a.satFat + b.satFat;
    n.monoFat = a.monoFat + b.monoFat;
    n.polyFat = a.polyFat + b.polyFat;
    n.transFat = a.transFat + b.transFat;
    n.fiber = a.fiber + b.fiber;
    n.sugar = a.sugar + b.sugar;
    n.addedSugar = a.addedSugar + b.addedSugar;
    n.protein = a.protein + b.protein;
    n.cholesterol = a.cholesterol + b.cholesterol;
    n.iron = a.iron + b.iron;
    n.sodium = a.sodium + b.sodium;
    n.potassium = a.potassium + b.potassium;
    n.vitaminA = a.vitaminA + b.vitaminA;
    n.vitaminC = a.vitaminC + b.vitaminC;
    n.vitaminD = a.vitaminD + b.vitaminD;

    return n;
}
