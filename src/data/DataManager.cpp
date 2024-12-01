#include "data/DataManager.h"

#include "items/Exercise.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QJsonArray>

#include <QDirIterator>
#include <qjsondocument.h>

QDir DataManager::dataDir{};

void DataManager::init()
{
    QString dir;

    QDir settingsDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    QFile f(settingsDir.absoluteFilePath("dataDir"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    } else {
        dir = f.readAll().trimmed();
        f.close();
    }

    dataDir = dir;

    bool ok = dataDir.mkpath("journal");

    if (!ok) {
        qCritical() << "Failed to create journal directory, exiting.";
        std::exit(127);
    }

    ok = dataDir.mkpath("person");

    if (!ok) {
        qCritical() << "Failed to create goal directory, exiting.";
        std::exit(127);
    }

}

DataManager::DataError DataManager::truncateSaveFoods(int meal, QDate date, const QList<FoodServing> &foods)
{
    QString dateString = date.toString("MM-dd-yyyy");

    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.mkpath(dateString);

    if (!ok) {
        // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    dir.cd(dateString);

    dir.mkpath("meals");

    dir.cd("meals");

    QFile file(dir.absoluteFilePath(QString::number(meal) + ".json"));

    QJsonArray array;

    for (const FoodServing &s : foods) {
        array.append(s.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // QMessageBox::critical(nullptr, "Write failed", "Failed to write some data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;
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

DataManager::DataError DataManager::truncateSaveRecipes(const QList<Recipe> &recipes)
{
    QFile file(dataDir.absoluteFilePath("recipes.json"));

    QJsonArray array;

    for (const Recipe &r : recipes) {
        array.append(r.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;

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

QList<Recipe> DataManager::searchRecipes(const QString &query)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QRegExp regex(".*" + query + ".*", Qt::CaseInsensitive);
#else
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);
#endif

    QList<Recipe> recipes;
    for (const Recipe &recipe : loadRecipes()) {
        if (recipe.name().contains(regex)) {
            recipes.append(recipe);
        }
    }

    return recipes;
}

DataManager::DataError DataManager::truncateSaveRoutines(const QList<ExerciseRoutine> &routines)
{
    QFile file(dataDir.absoluteFilePath("routines.json"));

    QJsonArray array;

    for (const ExerciseRoutine &r : routines) {
        array.append(r.toJson());
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;
}

QList<ExerciseRoutine> DataManager::loadRoutines()
{
    QList<ExerciseRoutine> routines;

    QFile f(dataDir.absoluteFilePath("routines.json"));

    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return routines;
    }

    QByteArray data = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();

    for (QJsonValueRef ref : array) {
        QJsonObject obj = ref.toObject();
        routines.append(ExerciseRoutine::fromJson(obj));
    }

    f.close();

    return routines;
}

QList<ExerciseRoutine> DataManager::searchRoutines(const QString &query)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QRegExp regex(".*" + query + ".*", Qt::CaseInsensitive);
#else
    QRegularExpression regex(".*" + query + ".*", QRegularExpression::PatternOption::CaseInsensitiveOption);
#endif

    QList<ExerciseRoutine> routines;
    for (const ExerciseRoutine &routine : loadRoutines()) {
        if (routine.name().contains(regex)) {
            routines.append(routine);
        }
    }

    return routines;
}

DataManager::DataError DataManager::truncateSaveExercises(const QList<Exercise> &exercises, QDate date)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.mkpath(dateString);

    if (!ok) {
        return Failure;
    }

    dir.cd(dateString);

    QFile file(dir.absoluteFilePath("exercises.json"));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return Failure;
    }

    QJsonArray arr;

    for (const Exercise & ex : exercises) {
        arr.append(ex.toJson());
    }

    file.write(QJsonDocument(arr).toJson());

    return Success;

}

QList<Exercise> DataManager::loadExercises(QDate date)
{
    QList<Exercise> exercises{};
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir.absolutePath());
    dir.cd("journal");

    if (!dir.cd(dateString)) {
        return exercises;
    }

    dir.cd(dateString);

    QFile file(dir.absoluteFilePath("exercises.json"));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return exercises;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonArray arr = QJsonDocument::fromJson(data).array();

    for (const QJsonValueRef ref : arr) {
        exercises.append(Exercise::fromJson(ref.toObject()));
    }

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
            // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make personal info directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
            return Failure;
        }

        dir.cd(fileDir);
    }

    QFile file(dir.absoluteFilePath(fileName));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // QMessageBox::critical(nullptr, "Write failed", "Failed to save personal info. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
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

QVariant DataManager::getInfo(const QString &field, const QVariant &defaultValue)
{
    QVariant value = defaultValue;
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

DataManager::DataError DataManager::mv(const QString &newPath)
{
    QDir journal(dataDir);

    journal.cd("journal");

    QDirIterator jIter(journal, QDirIterator::Subdirectories);

    QDir newDir(newPath);
    newDir.mkpath("journal");
    newDir.mkpath("person");

    while (jIter.hasNext()) {
        QFile f = jIter.next();
        QString name = journal.relativeFilePath(f.fileName());

        f.rename(newPath + "/journal/" + name);
    }

    QDir person(dataDir);
    person.cd("person");

    QDirIterator pIter(person, QDirIterator::Subdirectories);

    while (pIter.hasNext()) {
        QFile f = pIter.next();
        QString name = person.relativeFilePath(f.fileName());

        f.rename(newPath + "/person/" + name);
    }

    QFile recipes(dataDir.absoluteFilePath("recipes.json"));
    recipes.rename(newPath + "/recipes.json");

    QFile routines(dataDir.absoluteFilePath("routines.json"));
    routines.rename(newPath + "/routines.json");

    DataManager::newPath(newPath);

    return Success;
}

void DataManager::newPath(const QString &newPath)
{
    dataDir.setPath(newPath);
}
