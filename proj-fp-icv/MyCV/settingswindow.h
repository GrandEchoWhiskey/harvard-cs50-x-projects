#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "filetype.h"
#include "settings.h"


/*
    Settings window see settingswindow.ui for layout
*/


namespace Ui{ class SettingsWindow; }

class SettingsWindow : public QMainWindow{

    Q_OBJECT

public:

    explicit SettingsWindow(QWidget *parent = nullptr);

    ~SettingsWindow();

signals:

    void file_added();

public slots:

    void refresh();

private slots:

    void on_accept_btn_clicked();

    void on_reject_btn_clicked();

    void on_pdf_btn_clicked();

    void on_avi_btn_clicked();

    void on_inActive_stateChanged(int arg1);

    void on_deleteRejected_stateChanged(int arg1);

    void on_create_clicked();

private:

    void change_mode();

    Ui::SettingsWindow *ui;

    Settings settings;

    FileType *file;

};

#endif // SETTINGSWINDOW_H
