#include "models/NutrientModel.h"

NutrientModel::NutrientModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_nutrients.append(Nutrient{"Carbs", "carbs", "g"});
    m_nutrients.append(Nutrient{"Fiber", "fiber", "g"});
    m_nutrients.append(Nutrient{"Sugar", "sugar", "g"});

    m_nutrients.append(Nutrient{"Fat", "fat", "g"});
    m_nutrients.append(Nutrient{"Saturated Fat", "sat", "g"});
    m_nutrients.append(Nutrient{"Monounsaturated Fat", "mono", "g"});
    m_nutrients.append(Nutrient{"Polyunsaturated Fat", "poly", "g"});
    m_nutrients.append(Nutrient{"Trans Fat", "trans", "g"});

    m_nutrients.append(Nutrient{"Protein", "protein", "g"});

    m_nutrients.append(Nutrient{"Cholesterol", "cholesterol", "mg"});

    m_nutrients.append(Nutrient{"Sodium", "sodium", "mg"});
    m_nutrients.append(Nutrient{"Potassium", "potassium", "mg"});

    m_nutrients.append(Nutrient{"Calcium", "calcium", "%"});
    m_nutrients.append(Nutrient{"Iron", "iron", "%"});

    m_nutrients.append(Nutrient{"Vitamin A", "vitaminA", "%"});
    m_nutrients.append(Nutrient{"Vitamin C", "vitaminC", "%"});
    m_nutrients.append(Nutrient{"Vitamin D", "vitaminD", "%"});
}

// TODO: Implement this in GoalsPage
// will need to have a calculator for macros & submacros

QDate NutrientModel::date() const
{
    return m_date;
}

void NutrientModel::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
}

int NutrientModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int NutrientModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant NutrientModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    Nutrient nutrient = m_data[index.row()];

    QString name = nutrient.name;
    QString displayName = nutrient.displayName;
    QString suffix = nutrient.suffix;

    if (role == NMRoleTypes::NAME) {
        return name;
    } else if (role == NMRoleTypes::DNAME) {
        return displayName;
    } else if (role == NMRoleTypes::SUFFIX) {
        return suffix;
    } else if (role == NMRoleTypes::GOAL) {
        return m_goals.get(name);
    } else if (role == NMRoleTypes::VALUE) {
        // this is kinda cancer
        NutrientUnion n = m_nutrition.getDailyNutrients(m_date);

        auto prop = n.staticMetaObject.property(n.staticMetaObject.indexOfProperty(name.toStdString().c_str()));

        return prop.readOnGadget(&n);
    } else if (role == NMRoleTypes::FILTER) {
        return m_settings.get("avoid_" + name);
    } else if (role == NMRoleTypes::ID) {
        return index.row();
    }

    return QVariant();
}

void NutrientModel::add(const Nutrient &n)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_data.append(n);

    endInsertRows();
}


void NutrientModel::add(QString name, QString displayName, QString suffix)
{
    add(Nutrient{displayName, name, suffix});
}

void NutrientModel::loadData()
{
    clear();

    for (const Nutrient &n : m_nutrients) {
        add(n);
    }
}

void NutrientModel::loadFilterData()
{
    clear();

    for (const Nutrient &n : m_nutrients) {
        if (m_settings.get("avoid_" + n.name).isValid()) {
            add(n);
        }
    }
}

void NutrientModel::loadUnfilteredData()
{
    clear();

    for (const Nutrient &n : m_nutrients) {
        if (!m_settings.get("avoid_" + n.name).isValid()) {
            add(n);
        }
    }

}

bool NutrientModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count == 0) return false;

    beginRemoveRows(parent, row, row + count - 1);
    m_data.remove(row, count);
    endRemoveRows();

    return true;
}

void NutrientModel::remove(QString name)
{
    int i = 0;
    for (const Nutrient &n : m_data) {
        if (n.name == name) {
            removeRow(i);
        }
        ++i;
    }
}

void NutrientModel::clear()
{
    removeRows(0, m_data.count());
}

bool NutrientModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    Nutrient nutrient = m_data[index.row()];

    QString name = nutrient.name;

    if (role == NMRoleTypes::GOAL) {
        m_goals.set(name, value);
    } else if (role == NMRoleTypes::FILTER) {
        m_settings.set("avoid_" + name, value);
    } else {
        return false;
    }

    return true;
}

Qt::ItemFlags NutrientModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> NutrientModel::roleNames() const
{
    QHash<int,QByteArray> rez;
    rez[NAME] = "name";
    rez[DNAME] = "displayName";
    rez[SUFFIX] = "suffix";
    rez[GOAL] = "goal";
    rez[VALUE] = "value";
    rez[FILTER] = "filter";
    rez[ID] = "ntID";
    return rez;
}
