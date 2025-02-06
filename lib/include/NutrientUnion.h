#ifndef NUTRIENTUNION_H
#define NUTRIENTUNION_H

#include <QString>
#include <QObject>
#include <QQmlEngine>

typedef struct NutrientUnion
{
    Q_GADGET

    Q_PROPERTY(double fat MEMBER fat)
    Q_PROPERTY(double satFat MEMBER satFat)
    Q_PROPERTY(double monoFat MEMBER monoFat)
    Q_PROPERTY(double polyFat MEMBER polyFat)
    Q_PROPERTY(double transFat MEMBER transFat)

    Q_PROPERTY(double carbs MEMBER carbs)
    Q_PROPERTY(double fiber MEMBER fiber)
    Q_PROPERTY(double sugar MEMBER sugar)
    Q_PROPERTY(double addedSugar MEMBER addedSugar)

    Q_PROPERTY(double protein MEMBER protein)
    Q_PROPERTY(double cholesterol MEMBER cholesterol)
    Q_PROPERTY(double calcium MEMBER calcium)
    Q_PROPERTY(double iron MEMBER iron)
    Q_PROPERTY(double sodium MEMBER sodium)
    Q_PROPERTY(double potassium MEMBER potassium)
    Q_PROPERTY(double vitaminA MEMBER vitaminA)
    Q_PROPERTY(double vitaminC MEMBER vitaminC)
    Q_PROPERTY(double vitaminD MEMBER vitaminD)

    Q_PROPERTY(double calories READ calories)
    QML_VALUE_TYPE(nutrientUnion)

public:
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
    struct NutrientUnion operator*=(const double multiplier);
    struct NutrientUnion operator/=(const double multiplier);
    double calories() const;

    QString toString() const;

    Q_INVOKABLE NutrientUnion add(const NutrientUnion &other);
} NutrientUnion;

NutrientUnion operator+(const NutrientUnion &a, const NutrientUnion &b);
NutrientUnion operator*(const NutrientUnion &n, const double &multiplier);
NutrientUnion operator/(const NutrientUnion &n, const double &multiplier);

Q_DECLARE_METATYPE(NutrientUnion)

#endif // NUTRIENTUNION_H
