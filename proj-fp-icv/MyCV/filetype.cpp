#include "filetype.h"

FileType::FileType(){

    this->out_cv = nullptr;
    this->out_vid = nullptr;

}

FileType::~FileType(){

    // Delete text temp file if still exist
    if(this->out_cv != nullptr){
        this->out_cv->remove();
        delete out_cv;
    }

    // Delete video temp file if still exist
    if(this->out_vid != nullptr){
        this->out_vid->remove();
        delete out_vid;
    }

}

bool FileType::load(QString input, QString out_cv, QString out_vid){

    // Open input file. Return on error
    QFile in(input);
    if(!in.open(QIODevice::ReadOnly)) return false;
    this->m_loaded = true;

    // Free previous memory before allocating more
    if(this->out_cv != nullptr) delete this->out_cv;
    if(this->out_vid != nullptr) delete this->out_vid;

    this->out_cv = new QFile(out_cv);
    this->out_vid = new QFile(out_vid);

    // Read all input data
    QByteArray data = in.readAll();

    in.close();

    // Find the start of AVI file special bytes
    int index = data.lastIndexOf("RIFF");

    // Split data into two files
    QByteArray cv;
    QByteArray vid;

    for(int i=0; i<index; i++){
        cv.append(data[i]);
    }

    for(int i=index; i<data.length(); i++){
        vid.append(data[i]);
    }

    // Write the data
    this->out_cv->open(QIODevice::WriteOnly);
    this->out_cv->write(cv);
    this->out_cv->close();

    this->out_vid->open(QIODevice::WriteOnly);
    this->out_vid->write(vid);
    this->out_vid->close();

    return true;

}

bool FileType::create(QString in_cv, QString in_vid, QString output){

    // Get files
    QFile cv(in_cv);
    QFile vid(in_vid);

    // Continue if both files open
    if(!cv.open(QIODevice::ReadOnly)) return false;
    if(!vid.open(QIODevice::ReadOnly)){
        cv.close();
        return false;
    }

    // Create output data array
    QByteArray data = cv.readAll() + vid.readAll();

    // Close files
    cv.close();
    vid.close();

    // Create output file and open
    QFile out(output);

    out.open(QIODevice::WriteOnly);

    // Put the created data into the new file
    out.write(data);

    out.close();

    return true;

}
