#ifndef NUTRIENTUNION_H
#define NUTRIENTUNION_H

typedef struct NutrientUnion
{
    double fat = 0;
    double satFat = 0;
    double monoFat = 0;
    double polyFat = 0;
    double transFat = 0;

    double carbs = 0;
    double fiber = 0;
    double sugar = 0;
    double addedSugar = 0;

    double protein = 0;
    double cholesterol = 0;
    double calcium = 0;
    double iron = 0;
    double sodium = 0;
    double potassium = 0;
    double vitaminA = 0;
    double vitaminC = 0;
    double vitaminD = 0;

    struct NutrientUnion operator+=(const struct NutrientUnion &other);
    double calories() const;

} NutrientUnion;

NutrientUnion operator+(const NutrientUnion &a, const NutrientUnion &b);

#endif // NUTRIENTUNION_H
