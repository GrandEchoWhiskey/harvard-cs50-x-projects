#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QHash>
#include <QDir>


/*
    This class takes care of saving, and restoring data in, or from a json file.
    It's used almost like a normal hashtable, but every change is stored in a file.
*/


class Settings{

public:

    Settings(QString file_name="settings.json", QString file_path = ".");

    ~Settings();


    QStringList getKeys();

    bool keyExist(QString key);

    void delKey(QString key);

    QString value(QString key);

    void setValue(QString key, QString value);


private:

    QHash<QString, QString> table;

    QString path;

    QFile *file;


    void create();

    bool load();

    void save();


};

#endif // SETTINGS_H
