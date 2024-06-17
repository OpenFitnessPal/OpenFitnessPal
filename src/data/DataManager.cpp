#include "data/DataManager.h"
#include "data/CacheManager.h"

#include "items/Exercise.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <QMessageBox>
#include <QDirIterator>

QDir DataManager::dataDir{};

void DataManager::init()
{
    dataDir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    bool ok = dataDir.mkpath("journal");

    if (!ok) {
        QMessageBox::critical(nullptr, "mkpath failed", "Failed to make data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        std::exit(127);
    }
}

DataManager::DataError DataManager::removeFood(int meal, QDate date, const FoodItem &item)
{
    QString dateString = date.toString("MM-dd-yyyy");
    QDir dir(dataDir);
    dir.cd("journal");

    bool ok = dir.cd(dateString);

    if (!ok) {
        // QMessageBox::critical(nullptr, "mkdir failed", "Failed to make today's data directory. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return NoOp;
    }

    dir.cd("meals");
    dir.cd(QString::number(meal));

    QFile file(dir.absoluteFilePath(item.id()));
    return file.remove() ? Success : Failure;
}

DataManager::DataError DataManager::saveFood(int meal, QDate date, const FoodItem &item, const ServingSize &size, const double units)
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
    for (int i = 1; i < 6; ++i) {
        dir.mkpath("meals/" + QString::number(i));
    }

    dir.cd("meals");
    dir.cd(QString::number(meal));

    QFile file(dir.absoluteFilePath(item.id()));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::critical(nullptr, "Write failed", "Failed to save food data for today. Check permissions on your local data directory.", QMessageBox::StandardButton::Ok);
        return Failure;
    }

    QByteArray data = QString(QString::number(units)
                              + "\n" + QString::number(size.baseMultiplier())
                              + "\n" + size.unit()).toUtf8();

    file.write(data);
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
    dir.cd(QString::number(meal));

    QDirIterator iter(dir);

    while (iter.hasNext()) {
        QFile f = iter.next();
        if (f.fileName().endsWith(".") || f.fileName().endsWith("..")) continue;

        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QString id = f.fileName().split('/').last();

        QString data = f.readAll();
        QStringList list = data.split('\n');

        if (list.empty() || list.length() != 3) {
            continue;
        }

        QStringList unit = list.at(2).split(' ');

        double defaultValue = unit.at(0).toInt();
        QString unitString = unit.last(unit.length() - 1).join(' ');

        FoodItem item = CacheManager::itemById(id);

        ServingSize size = ServingSize(list.at(1).toDouble(), unitString, defaultValue);
        double units = list.at(0).toDouble();

        FoodServing serving(item, size, units);
        servings.append(serving);

        f.close();
    }

    return servings;
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
