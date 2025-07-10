#include "models/NutrientModel.h"

NutrientModel::NutrientModel(const bool macros, const bool micros, QObject *parent)
    : QAbstractListModel(parent)
{
    if (macros) {
        m_data.append(Nutrient{"Carbs", "carbs", 35});
        m_data.append(Nutrient{"Fat", "fat", 35});
        m_data.append(Nutrient{"Protein", "protein", 30});
    }

    if (micros) {
        m_data.append(Nutrient{"Saturated Fat", "satFat", 50});
        m_data.append(Nutrient{"Monounsaturated Fat", "monoFat", 50});
        m_data.append(Nutrient{"Polyunsaturated Fat", "polyFat", 0});
        m_data.append(Nutrient{"Trans Fat", "transFat", 0});

        m_data.append(Nutrient{"Cholesterol", "cholesterol", 600, "mg"});
        m_data.append(Nutrient{"Sodium", "sodium", 6000, "mg"});
        m_data.append(Nutrient{"Potassium", "potassium", 4000, "mg"});

        m_data.append(Nutrient{"Fiber", "fiber", 20});
        m_data.append(Nutrient{"Sugar", "sugar", 100});

        m_data.append(Nutrient{"Vitamin A", "vitaminA", 100, "% DV"});
        m_data.append(Nutrient{"Vitamin C", "vitaminC", 100, "% DV"});
        m_data.append(Nutrient{"Calcium", "calcium", 100, "% DV"});
        m_data.append(Nutrient{"Iron", "iron", 100, "% DV"});
    }
}

int NutrientModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant NutrientModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Nutrient n = m_data.at(index.row());
    switch (role) {
    case NAME:
        return n.name;
    case DATA:
        return n.dataName;
    case DEFAULT:
        return n.defaultValue;
    case SUFFIX:
        return n.suffix;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NutrientModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[DATA] = "data";
    rez[DEFAULT] = "defaultValue";
    rez[SUFFIX] = "suffix";
    return rez;

}
