#include "OFPManager.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtDebug>

// TODO: constants
static const QString BASE_URL = "https://search.swurl.xyz/";

OFPManager::OFPManager(QObject *parent)
    : QObject{parent}
    , m_manager(new QNetworkAccessManager(this))
{}

void OFPManager::process(const QByteArray &data, const QNetworkRequest &request)
{
    QByteArray newData = data;
    newData.removeLast();

    if (newData == "[]" || newData.isEmpty() || !newData.isValidUtf8()) {
        goto err;
    }

    {
        QJsonParseError e;
        QJsonDocument doc = QJsonDocument::fromJson(newData, &e);

        if (e.error != QJsonParseError::NoError) {
            qDebug() << "Json parse error" << e.errorString();
            goto err;
        }

        QJsonArray array = doc.array();

        QList<FoodItem> items{};

        for (QJsonValueRef ref : array) {
            QJsonObject obj = ref.toObject();
            FoodItem item(obj);
            items.append(item);
        }

        emit searchComplete(items);
    }

    return;

err:
    if (numTries > 5) {
        qCritical() << "Search failed, too many attempts";
        emit searchFailed("Too many attempts");
    } else {
        qWarning() << "Search gave bad data, retrying. Data:" << newData;
        numTries++;

        // a little hacky but idc
        // should probably extract to a method
        QNetworkReply *reply = m_manager->get(request);
        connect(reply, &QNetworkReply::readyRead, this, [this, reply, request] {
            process(reply->readAll(), request);
        });

        return;
    }

};

void OFPManager::search(const QString &query, const SearchOptions &options)
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
    numTries = 0;

    connect(reply, &QNetworkReply::readyRead, this, [this, reply, req] {
        process(reply->readAll(), req);
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [reply, this](QNetworkReply::NetworkError e) {
        qCritical() << e;
        auto metaEnum = qt_getEnumMetaObject(e);
        const char *name = qt_getEnumName(e);

        // TODO: more comprehensive
        emit searchFailed(QString(name));
    });

    connect(this, &OFPManager::cancelAll, reply, &QNetworkReply::abort);
}
