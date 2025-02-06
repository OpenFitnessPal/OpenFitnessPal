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

NutrientUnion NutrientUnion::operator*=(const double multiplier)
{
    this->calcium *= multiplier;
    this->carbs *= multiplier;
    this->fat *= multiplier;
    this->satFat *= multiplier;
    this->monoFat *= multiplier;
    this->polyFat *= multiplier;
    this->transFat *= multiplier;
    this->fiber *= multiplier;
    this->sugar *= multiplier;
    this->addedSugar *= multiplier;
    this->protein *= multiplier;
    this->cholesterol *= multiplier;
    this->iron *= multiplier;
    this->sodium *= multiplier;
    this->potassium *= multiplier;
    this->vitaminA *= multiplier;
    this->vitaminC *= multiplier;
    this->vitaminD *= multiplier;

    return *this;
}

NutrientUnion NutrientUnion::operator/=(const double multiplier)
{
    this->calcium /= multiplier;
    this->carbs /= multiplier;
    this->fat /= multiplier;
    this->satFat /= multiplier;
    this->monoFat /= multiplier;
    this->polyFat /= multiplier;
    this->transFat /= multiplier;
    this->fiber /= multiplier;
    this->sugar /= multiplier;
    this->addedSugar /= multiplier;
    this->protein /= multiplier;
    this->cholesterol /= multiplier;
    this->iron /= multiplier;
    this->sodium /= multiplier;
    this->potassium /= multiplier;
    this->vitaminA /= multiplier;
    this->vitaminC /= multiplier;
    this->vitaminD /= multiplier;

    return *this;
}

double NutrientUnion::calories() const
{
    return fat * 9 + (carbs - fiber) * 4 + protein * 4;
}

QString NutrientUnion::toString() const
{
    return QString("NutrientUnion(%1 kcal, %2 fat, %3 carbs, %4 protein)").arg(calories()).arg(fat).arg(carbs).arg(protein);
}

NutrientUnion NutrientUnion::add(const NutrientUnion &other)
{
    return *this + other;
}

NutrientUnion operator+(const NutrientUnion &a, const NutrientUnion &b)
{
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

NutrientUnion operator*(const NutrientUnion &a, const double &multiplier) {
    NutrientUnion n = a;

    n.calcium *= multiplier;
    n.carbs *= multiplier;
    n.fat *= multiplier;
    n.satFat *= multiplier;
    n.monoFat *= multiplier;
    n.polyFat *= multiplier;
    n.transFat *= multiplier;
    n.fiber *= multiplier;
    n.sugar *= multiplier;
    n.addedSugar *= multiplier;
    n.protein *= multiplier;
    n.cholesterol *= multiplier;
    n.iron *= multiplier;
    n.sodium *= multiplier;
    n.potassium *= multiplier;
    n.vitaminA *= multiplier;
    n.vitaminC *= multiplier;
    n.vitaminD *= multiplier;

    return n;
}


NutrientUnion operator/(const NutrientUnion &a, const double &multiplier)
{
    NutrientUnion n = a;

    n.calcium /= multiplier;
    n.carbs /= multiplier;
    n.fat /= multiplier;
    n.satFat /= multiplier;
    n.monoFat /= multiplier;
    n.polyFat /= multiplier;
    n.transFat /= multiplier;
    n.fiber /= multiplier;
    n.sugar /= multiplier;
    n.addedSugar /= multiplier;
    n.protein /= multiplier;
    n.cholesterol /= multiplier;
    n.iron /= multiplier;
    n.sodium /= multiplier;
    n.potassium /= multiplier;
    n.vitaminA /= multiplier;
    n.vitaminC /= multiplier;
    n.vitaminD /= multiplier;

    return n;
}

