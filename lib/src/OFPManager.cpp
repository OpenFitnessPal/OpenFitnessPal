#include "OFPManager.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>

// TODO: constants
static const QString BASE_URL = "https://search.swurl.xyz/";

OFPManager::OFPManager(QObject *parent)
    : QObject{parent}
    , m_manager(new QNetworkAccessManager(this))
{}

void OFPManager::search(const QString &query, const SearchOptions &options) const
{
    QString newQuery = query;
    newQuery.replace(' ', '+');

    QNetworkRequest req;
    QString url(BASE_URL + newQuery + "?");

    bool first = true;
    if (options.generics) {
        first = false;
        url += "generics";
    }

    if (options.results != 0) {
        url += (first ? "" : "&");
        url += "results=" + QString::number(options.results);
        first = false;
    }

    if (!options.avoid.empty()) {
        QMapIterator iter(options.avoid);

        while (iter.hasNext()) {
            iter.next();
            url += (first ? "" : "&");
            url += iter.key() + "=" + QString::number(iter.value());
            first = false;
        }
    }

    qDebug() << url;
    req.setUrl(QUrl(url));

    QNetworkReply *reply = m_manager->get(req);
    connect(reply, &QNetworkReply::readyRead, this, [reply, this] {
        QByteArray data = reply->readAll();

        data.removeLast();

        QJsonParseError e;
        QJsonDocument doc = QJsonDocument::fromJson(data, &e);

        QJsonArray array = doc.array();

        QList<FoodItem> items{};

        for (QJsonValueRef ref : array) {
            QJsonObject obj = ref.toObject();
            FoodItem item(obj);
            items.append(item);
        }

        emit searchComplete(items);
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [reply, this](QNetworkReply::NetworkError e) {
        qDebug() << e;
    });

    connect(this, &OFPManager::cancelAll, reply, &QNetworkReply::abort);
}
