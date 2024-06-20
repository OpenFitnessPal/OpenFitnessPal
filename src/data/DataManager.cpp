#include "data/DataManager.h"
#include "data/CacheManager.h"

#include "items/Exercise.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonArray>

#include <QMessageBox>
#include <QDirIterator>
#include <qjsondocument.h>

QDir DataManager::dataDir{};

void DataManager::init()
{
    dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    bool ok = dataDir.mkpath("journal");

    if (!ok) {
        QMessageBox::critical(nullptr, "mkpath failed", "Failed to make data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }

    ok = dataDir.mkpath("person");

    if (!ok) {
        QMessageBox::critical(nullptr, "mkpath failed", "Failed to make data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }

}

DataManager::DataError DataManager::removeFood(int meal, QDate date, const FoodServing &food)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.cd(dateString + "/meals");

    if (!ok) {
        // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return NoOp;
    }

    QFile file(dir.absoluteFilePath(QString::number(meal) + ".json"));
    if (!file.open(QIODevice::ReadOnly)) {
        return NoOp;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    QJsonObject obj = food.toJson();

    for (int i = 0; i < array.size(); ++i) {
        if (array.at(i).toObject() == obj) {
            array.removeAt(i);
            break;
        }
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save some meal data for today. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    file.write(toWrite);

    file.close();

    return Success;
}

DataManager::DataError DataManager::saveFood(int meal, QDate date, const FoodServing &food)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.mkpath(dateString);

    if (!ok) {
        QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    dir.cd(dateString);

    dir.mkpath("meals");

    dir.cd("meals");

    QFile file(dir.absoluteFilePath(QString::number(meal) + ".json"));

    return addJsonObject(file, food.toJson());
}

QList<FoodServing> DataManager::loadFoods(int meal, QDate date)
{
    QList<FoodServing> servings{};
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir.absolutePath());
    dir.cd("journal");

    if (!dir.cd(dateString)) {
        return servings;
    }

    dir.cd(dateString);

    dir.cd("meals");
    QFile f(dir.absoluteFilePath(QString::number(meal) + ".json"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return servings;
    }

    QByteArray data = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        servings.append(FoodServing::fromJson(obj));
    }

    f.close();

    return servings;
}

DataManager::DataError DataManager::removeRecipe(const Recipe &recipe)
{
    QFile file(dataDir.absoluteFilePath("recipes.json"));
    if (!file.open(QIODevice::ReadOnly)) {
        return NoOp;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    QJsonObject obj = recipe.toJson();

    for (int i = 0; i < array.size(); ++i) {
        if (array.at(i).toObject() == obj) {
            array.removeAt(i);
            break;
        }
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save some recipe data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    file.write(toWrite);

    file.close();

    return Success;
}

DataManager::DataError DataManager::saveRecipe(const Recipe &recipe)
{
    QFile file(dataDir.absoluteFilePath("recipes.json"));

    return addJsonObject(file, recipe.toJson());
}

QList<Recipe> DataManager::loadRecipes()
{
    QList<Recipe> recipes;

    QFile f(dataDir.absoluteFilePath("recipes.json"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return recipes;
    }

    QByteArray data = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        recipes.append(Recipe::fromJson(obj));
    }

    f.close();

    return recipes;
}

DataManager::DataError DataManager::saveExercises(QList<Exercise *> exercises, QDate date)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.mkpath(dateString);

    if (!ok) {
        QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    dir.cd(dateString);

    QFile file(dir.absoluteFilePath("exercises"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save exercise data for today. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QStringList data;

    for (Exercise *ex : exercises) {
        data << ex->name();

        for (ExerciseSet *set : ex->sets()) {
            QStringList csv;
            csv << QString::number(set->weight()) << QString::number(set->reps()) << set->time().toString();

            data << csv.join(',');
        }

        data << "";
    }

    file.write(data.join('\n').toUtf8());
    file.close();

    return Success;
}

QList<Exercise *> DataManager::loadExercises(QWidget *parent, QDate date)
{
    QList<Exercise *> exercises{};
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir.absolutePath());
    dir.cd("journal");

    if (!dir.cd(dateString)) {
        return exercises;
    }

    dir.cd(dateString);

    QFile file(dir.absoluteFilePath("exercises"));
    if (!file.open(QIODevice::ReadOnly)) {
        return exercises;
    }

    QString data = file.readAll();

    QStringList textExercises = data.split("\n\n");

    for (const QString &ex : textExercises) {
        QStringList lines = ex.split('\n');
        Exercise *exercise = new Exercise(parent);
        exercise->setName(lines.first());

        lines.pop_front();

        QList<ExerciseSet *> sets;
        for (const QString &line : lines) {
            if (line == "") continue;

            QStringList csv = line.split(',');

            if (csv.size() != 3) {
                continue;
            }

            ExerciseSet *set = new ExerciseSet(exercise);

            set->setWeight(csv.at(0).toInt());
            set->setReps(csv.at(1).toInt());
            set->setTime(QTime::fromString(csv.at(2)));

            sets.append(set);
        }

        exercise->setSets(sets);
        exercises.append(exercise);
    }

    file.close();

    return exercises;
}

DataManager::DataError DataManager::saveInfo(QString field, QVariant data)
{
    QDir dir(dataDir);
    dir.cd("person");

    QStringList split = field.split('/');
    QString fileName = split.last();
    split.pop_back();
    QString fileDir = split.join('/');

    if (!split.empty()) {
        bool ok = dir.mkpath(fileDir);

        if (!ok) {
            QMessageBox::critical(nullptr, "mkdir failed", "Failed to make personal info directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
            return Failure;
        }

        dir.cd(fileDir);
    }

    QFile file(dir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save personal info. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    file.write(data.toByteArray());
    file.close();

    return Success;
}

QVariantMap DataManager::loadInfo()
{
    QVariantMap map{};
    QDir dir(dataDir);
    dir.cd("person");

    QDirIterator iter(dir, QDirIterator::IteratorFlag::Subdirectories);

    while (iter.hasNext()) {
        QFile f = iter.next();
        QString fileName = f.fileName();
        QString baseName = fileName.split('/').last();
        if (baseName.startsWith('.')) continue;

        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QVariant var = f.readAll();

        map.insert(baseName, var);
        f.close();
    }

    return map;

}

QVariant DataManager::getInfo(const QString &field)
{
    QVariant value{};
    QDir dir(dataDir);
    dir.cd("person");

    QFile f(dir.absoluteFilePath(field));
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return value;
    }

    value = f.readAll();

    f.close();

    return value;

}

DataManager::DataError DataManager::addJsonObject(QFile &file, const QJsonObject &obj)
{
    QJsonArray array;

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        array = doc.array();

        file.close();
    }

    array.append(obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to write some data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;
}
