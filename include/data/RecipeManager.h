#ifndef RECIPEMANAGER_H
#define RECIPEMANAGER_H

#include <QDir>
#include <QObject>
#include <Recipe.h>
#include <QQmlEngine>

class RecipeManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    QString m_file;

    QList<Recipe> m_recipes;
public:
    RecipeManager(QObject *parent = nullptr);

    Q_INVOKABLE bool save(const QList<Recipe> &recipes);
    Q_INVOKABLE QList<Recipe> load();
    Q_INVOKABLE QList<Recipe> search(const QString &query);
};

#endif // RECIPEMANAGER_H
