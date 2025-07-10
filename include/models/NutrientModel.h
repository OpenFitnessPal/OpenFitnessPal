#ifndef NUTRIENTMODEL_H
#define NUTRIENTMODEL_H

#include <QAbstractItemModel>

typedef struct Nutrient {
    QString name;
    QString dataName;
    int defaultValue;
    QString suffix = "g";
} Nutrient;

class NutrientModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NMRoleTypes {
        NAME = Qt::UserRole + 1,
        DATA,
        DEFAULT,
        SUFFIX
    };

    explicit NutrientModel(const bool macros = true, const bool micros = true, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Nutrient> m_data;
};

#endif // NUTRIENTMODEL_H
