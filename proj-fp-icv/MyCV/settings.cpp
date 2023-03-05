#include "settings.h"

//! Construct & Destruct

Settings::Settings(QString file_name, QString file_path){

    path = QDir(file_path).absolutePath().append("/").append(file_name);

    this->file = new QFile(path);

    if(!this->load()) this->create();

}

Settings::~Settings(){

    delete file;

}


//! Private

// Load from json file
bool Settings::load(){

    if(!file->open(QIODevice::ReadOnly)) return false;

    QJsonDocument loadJson(QJsonDocument::fromJson(file->readAll()));

    QJsonObject obj = loadJson.object();

    foreach(QString key, obj.keys()){
        this->table[key] = obj.value(key).toString();
    }

    file->close();

    return true;

}

// Save current hashtable to settings file
void Settings::save(){
    if(!file->open(QIODevice::WriteOnly)) return;

    QJsonObject obj;

    foreach(QString key, this->table.keys()){
        obj[key] = QJsonValue(this->table.value(key));
    }

    QJsonDocument saveJson(obj);

    file->write(saveJson.toJson());

    file->close();

    return;
}

// Create a new settings file
void Settings::create(){

    if(!file->open(QIODevice::WriteOnly)) return;

    file->close();

    return;

}


//! Public

// Get key list
QStringList Settings::getKeys(){

    this->load();

    return this->table.keys();

}

// Does the key exist?
bool Settings::keyExist(QString key){

    this->load();

    foreach(QString k, this->table.keys()){
        if(key == k)
            return true;
    }

    return false;

}

// Get value given by a key
QString Settings::value(QString key){

    this->load();

    return this->table.value(key);

}

// Set value for a key
void Settings::setValue(QString key, QString value){

    this->load();

    this->table[key] = value;

    this->save();

}

// Delete key with value
void Settings::delKey(QString key){

    this->load();

    this->table.remove(key);

    this->save();

}
