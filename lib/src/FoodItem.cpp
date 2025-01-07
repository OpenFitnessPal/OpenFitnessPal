#include "FoodItem.h"

#include <QJsonArray>
#include <QJsonDocument>

QString FoodItem::brand() const
{
    return m_brand;
}

QString FoodItem::name() const
{
    return m_name;
}

QString FoodItem::prettyName() const
{
    return m_brand + " " + m_name;
}

QString FoodItem::siteName() const
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    static QRegExp regex("[^a-z0-9\\-]");
    static QRegExp multiSpace("[-]{2,4}");
#else
    static QRegularExpression regex("[^a-z0-9\\-]");
    static QRegularExpression multiSpace("[-]{2,4}");
#endif
    return m_name.toLower().replace(" ", "-").replace(regex, "").replace(multiSpace, "-") + "-" + (m_id);
}

NutrientUnion FoodItem::nutrients() const
{
    return m_nutrients;
}

QList<ServingSize> FoodItem::servingSizes() const
{
    return m_servingSizes;
}

ServingSize FoodItem::defaultServing() const
{
    return m_defaultServing;
}

int FoodItem::defaultServingIdx() const
{
    return m_servingSizes.indexOf(m_defaultServing);
}

void FoodItem::addServingSize(const ServingSize &size)
{
    m_servingSizes.append(size);
}

QString FoodItem::id() const
{
    return m_id;
}

bool operator==(const FoodItem &a, const FoodItem &b)
{
    return a.id() == b.id();
}

bool operator!=(const FoodItem &a, const FoodItem &b) {
    return a.id() != b.id();
}

void FoodItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
}

void FoodItem::setBrand(const QString &newBrand)
{
    if (m_brand == newBrand)
        return;
    m_brand = newBrand;
}

void FoodItem::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
}

void FoodItem::setNutrients(const NutrientUnion &newNutrients)
{
    m_nutrients = newNutrients;
}

FoodItem::FoodItem(const QJsonObject &obj) {
    m_brand = obj.value("brand").toString("Generic");
    m_name = obj.value("name").toString("Unknown");

    m_id = obj.value("id").toVariant().toString();

    auto getValue = [obj](const QString &field) -> double {
        return obj.value(field).toDouble();
    };

    NutrientUnion n;

    n.fat = getValue("fat");
    n.satFat = getValue("sat");
    n.monoFat = getValue("mono");
    n.polyFat = getValue("poly");
    n.transFat = getValue("trans");

    n.carbs = getValue("carbs");
    n.fiber = getValue("fiber");
    n.sugar = getValue("sugar");
    n.addedSugar = getValue("added_sugars");

    n.protein = getValue("protein");
    n.cholesterol = getValue("cholesterol");

    n.calcium = getValue("calcium");
    n.iron = getValue("iron");
    n.sodium = getValue("sodium");
    n.potassium = getValue("potassium");

    n.vitaminA = getValue("vitaminA");
    n.vitaminC = getValue("vitaminC");
    n.vitaminD = getValue("vitaminD");

    m_nutrients = n;

    // Serving Sizes
    QJsonArray servings = obj.value("servings").toArray();

    QList<double> multipliers;

    for (QJsonValueRef ref : servings) {
        QJsonObject obj = ref.toObject();

        double mult = obj.value("mult").toDouble();
        QString unit = obj.value("unit").toString("g");
        double value = obj.value("value").toDouble();

        multipliers.append(mult);

        ServingSize size(mult, unit, value);

        m_servingSizes.append(size);
    }

    int idx = 0;
    if (multipliers.contains(1.0)) idx = multipliers.indexOf(1.0);
    else {
        double nearest = std::numeric_limits<double>::lowest();
        int i = 0;
        for (const double mult : multipliers) {
            if (std::abs(mult - 1.0) < std::abs(nearest - 1.0)) {
                nearest = mult;
                idx = i;
            }

            ++i;
        }
    }
    m_defaultServing = m_servingSizes.at(idx);
}

QJsonObject FoodItem::toJson() const
{
    QJsonObject obj{};

    obj.insert("brand", m_brand);
    obj.insert("name", m_name);
    obj.insert("id", m_id);

    auto setValue = [&obj](const QString &field, double value) mutable {
        obj.insert(field, value);
    };

    setValue("fat", m_nutrients.fat);
    setValue("sat", m_nutrients.satFat);
    setValue("mono", m_nutrients.monoFat);
    setValue("poly", m_nutrients.polyFat);
    setValue("trans", m_nutrients.transFat);

    setValue("carbs", m_nutrients.carbs);
    setValue("fiber", m_nutrients.fiber);
    setValue("sugar", m_nutrients.sugar);
    setValue("added_sugars", m_nutrients.addedSugar);

    setValue("protein", m_nutrients.protein);
    setValue("cholesterol", m_nutrients.cholesterol);

    setValue("calcium", m_nutrients.calcium);
    setValue("iron", m_nutrients.iron);
    setValue("sodium", m_nutrients.sodium);
    setValue("potassium", m_nutrients.potassium);

    setValue("vitaminA", m_nutrients.vitaminA);
    setValue("vitaminC", m_nutrients.vitaminC);
    setValue("vitaminD", m_nutrients.vitaminD);

    // Serving Sizes
    QJsonArray servings{};

    for (const ServingSize &size : m_servingSizes) {
        QJsonObject serving{};

        serving.insert("mult", size.baseMultiplier());
        serving.insert("unit", size.baseUnit());
        serving.insert("value", size.defaultValue());

        servings.append(serving);
    }

    obj.insert("servings", servings);

    return obj;
}

bool operator==(const FoodServing &a, const FoodServing &b) {
    return a.item == b.item
           && a.sizeIdx == b.sizeIdx
           && a.units == b.units;
}

NutrientUnion FoodServing::nutrients() const
{
    double mult = size().baseMultiplier() * units;

    return item.nutrients() * mult;
}

ServingSize FoodServing::size() const
{
    return item.servingSizes().at(sizeIdx);
}

QJsonObject FoodServing::toJson() const
{
    QJsonObject obj;

    obj.insert("item", item.toJson());
    obj.insert("size", size().toJson());
    obj.insert("units", units);

    return obj;
}

FoodServing FoodServing::fromJson(const QJsonObject &obj)
{
    FoodItem item = FoodItem(obj.value("item").toObject());
    ServingSize size = ServingSize::fromJson(obj.value("size").toObject());
    int sizeIdx = item.servingSizes().indexOf(size);
    double units = obj.value("units").toDouble();

    return FoodServing{item, sizeIdx, units};
}

bool FoodItem::isRecipe() const
{
    return m_isRecipe;
}

void FoodItem::setIsRecipe(bool newIsRecipe)
{
    m_isRecipe = newIsRecipe;
}
