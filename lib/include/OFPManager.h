#ifndef OFPMANAGER_H
#define OFPMANAGER_H

#include <QObject>
#include <QList>
#include <QNetworkAccessManager>

#include "FoodItem.h"

typedef struct SearchOptions {
    QMap<QString, double> avoid{};
    int results = 0;
    bool generics = false;
} SearchOptions;

class OFPManager : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *m_manager;

public:
    explicit OFPManager(QObject *parent = nullptr);

public slots:
    void search(const QString &query, const SearchOptions &options = SearchOptions{}) const;

signals:
    void searchComplete(const QList<FoodItem> results) const;
    void cancelAll() const;
};

#endif // OFPMANAGER_H
