#ifndef FOODITEM_H
#define FOODITEM_H

#include <QJsonObject>
#include <QQmlEngine>

#include "NutrientUnion.h"
#include "ServingSize.h"

class FoodItem
{
    Q_GADGET

    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(QString brand READ brand WRITE setBrand FINAL)
    Q_PROPERTY(QString id READ id WRITE setId FINAL)
    Q_PROPERTY(NutrientUnion nutrients READ nutrients WRITE setNutrients FINAL)
    Q_PROPERTY(QList<ServingSize> servingSizes READ servingSizes FINAL)
    Q_PROPERTY(bool isRecipe READ isRecipe WRITE setIsRecipe FINAL)

    QML_VALUE_TYPE(foodItem)
private:
    QString m_brand;
    QString m_name;

    QString m_id;

    NutrientUnion m_nutrients;

    QList<ServingSize> m_servingSizes{};
    ServingSize m_defaultServing;

    bool m_isRecipe;

public:
    /**
     * @brief FoodItem Construct a food-item from a search JSON.
     * @param obj The JSON object found from a search.
     */
    FoodItem(const QJsonObject &obj);

    FoodItem() = default;

    QJsonObject toJson() const;

    QString brand() const;
    void setBrand(const QString &newBrand);

    QString name() const;
    void setName(const QString &newName);

    QString prettyName() const;
    QString siteName() const;

    NutrientUnion nutrients() const;
    void setNutrients(const NutrientUnion &newNutrients);

    QList<ServingSize> servingSizes() const;
    ServingSize defaultServing() const;
    int defaultServingIdx() const;
    void addServingSize(const ServingSize &size);

    QString id() const;
    void setId(const QString &newId);

    bool isRecipe() const;
    void setIsRecipe(bool newIsRecipe);
};

bool operator==(const FoodItem &a, const FoodItem &b);
bool operator!=(const FoodItem &a, const FoodItem &b);

Q_DECLARE_METATYPE(FoodItem);

typedef struct FoodServing {
    Q_GADGET

    Q_PROPERTY(double units MEMBER units FINAL)
    Q_PROPERTY(int sizeIdx MEMBER sizeIdx FINAL)
    Q_PROPERTY(ServingSize size READ size FINAL)
    Q_PROPERTY(FoodItem item MEMBER item FINAL)

    QML_VALUE_TYPE(food)

public:
    FoodItem item;
    int sizeIdx;
    double units;

    ServingSize size() const;

    QJsonObject toJson() const;
    static struct FoodServing fromJson(const QJsonObject &obj);
    NutrientUnion nutrients() const;
} FoodServing;

bool operator==(const FoodServing &a, const FoodServing &b);

Q_DECLARE_METATYPE(FoodServing);

#endif // FOODITEM_H
