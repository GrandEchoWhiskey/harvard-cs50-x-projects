#ifndef FILETYPE_H
#define FILETYPE_H

#include <QFile>
#include <QString>
#include <QUrl>


/*
    This class is responsible for creating and reading a *.icvx file.
    It's nothing other than a *.pdf, and *.avi file combined.
    On loading this class creates two files in temp directory (or any of choice)
*/


class FileType{

public:

    FileType();

    ~FileType();


    bool load(QString input, QString out_cv, QString out_vid);

    bool create(QString in_cv, QString in_vid, QString output);

    bool loaded() {return this->m_loaded;}


    QFile *pdf() {return m_loaded ? this->out_cv : nullptr;}

    QFile *video() {return m_loaded ? this->out_vid : nullptr;}


private:

    bool m_loaded;


    QFile *out_cv;

    QFile *out_vid;


};

#endif // FILETYPE_H
