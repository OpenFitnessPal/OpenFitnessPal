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

DataManager::DataError DataManager::removeFood(int meal, QDate date, const FoodServing &food)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.cd(dateString + "/meals");

    if (!ok) {
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
        // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    dir.cd(dateString);

    dir.mkpath("meals");

    dir.cd("meals");

    QFile file(dir.absoluteFilePath(QString::number(meal) + ".json"));

    return addJsonObject(file, food.toJson());
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
        // QMessageBox::critical(nullptr, "Write failed", "Failed to save some recipe data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
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

DataManager::DataError DataManager::removeExercise(const Exercise &exercise, const QDate &date)
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

    ok = dir.mkpath("exercises");

    if (!ok) {
        // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    dir.cd("exercises");

    QFile file(dir.absoluteFilePath(exercise.name()));
    return file.remove() ? Success : Failure;
}

DataManager::DataError DataManager::saveExercise(const Exercise &ex, QDate date)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.mkpath(dateString);

    if (!ok) {
        return Failure;
    }

    dir.cd(dateString);

    ok = dir.mkpath("exercises");

    if (!ok) {
        return Failure;
    }

    dir.cd("exercises");

    QFile file(dir.absoluteFilePath(ex.name()));

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return Failure;
    }

    QStringList data;

    for (ExerciseSet &set : ex.sets()) {
        QStringList csv;
        csv << QString::number(set.weight()) << QString::number(set.reps());

        data << csv.join(',');
    }

    data << "";

    file.write(data.join('\n').toUtf8());
    file.close();

    return Success;
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

    ok = dir.mkpath("exercises");

    if (!ok) {
        return Failure;
    }

    dir.cd("exercises");

    QDirIterator iter(dir, QDirIterator::IteratorFlag::Subdirectories);

    while (iter.hasNext()) {
        QFile f = iter.next();
        f.remove();
    }

    for (const Exercise & ex : exercises) {
        QFile file(dir.absoluteFilePath(ex.name()));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return Failure;
        }

        QStringList data;

        for (ExerciseSet &set : ex.sets()) {
            QStringList csv;
            csv << QString::number(set.weight()) << QString::number(set.reps());

            data << csv.join(',');
        }

        data << "";

        file.write(data.join('\n').toUtf8());
        file.close();
    }

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

    if (!dir.cd("exercises")) {
        return exercises;
    }

    dir.cd("exercises");

    QDirIterator iter(dir, QDirIterator::IteratorFlag::Subdirectories);

    while (iter.hasNext()) {
        QFile f = iter.next();
        QString fileName = f.fileName();
        QString baseName = fileName.split('/').last();
        if (baseName.startsWith('.')) continue;

        Exercise ex;

        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QString data = f.readAll();
        QStringList lines = data.split('\n');

        QList<ExerciseSet> sets;

        for (const QString &line : lines) {
            if (line == "") continue;

            QStringList csv = line.split(',');

            if (csv.size() < 2) {
                continue;
            }

            ExerciseSet set;

            set.setWeight(csv.at(0).toInt());
            set.setReps(csv.at(1).toInt());

            sets.append(set);
        }

        ex.setSets(sets);
        ex.setName(baseName);

        f.close();

        exercises.append(ex);
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

    QFile f(dataDir.absoluteFilePath("recipes.json"));
    f.rename(newPath + "/recipes.json");

    dataDir.setPath(newPath);

    return Success;
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
        // QMessageBox::critical(nullptr, "Write failed", "Failed to write some data. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray toWrite = QJsonDocument(array).toJson();

    file.write(toWrite);

    file.close();

    return Success;
}
