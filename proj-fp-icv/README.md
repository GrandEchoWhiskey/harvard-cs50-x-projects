# My Interactive CV

#### This project was created for the [CS50x](https://github.com/GrandEchoWhiskey/harvard-cs50-x-projects/blob/main/README.md) course, as the Final Project. 

#### Video Demo: https://youtu.be/MXsBOsn7h5k
### Description:

- #### `My Interactive CV` is a program which changes the way of recruitment to a job.

- #### It comes with cobined `.icvx` files. That combine .pdf, and .avi files.

- #### Easy to handle but, for this time only for `Windows` with `x64` architecture support.

- #### Just create a `.icvx` file in the creator and send it to someone, who also uses this aplication. He can easily read your `CV` while watching and hearing your motivation message.
    >_Say NO to motivation letters!_
#
### Installation files:

- #### `install.exe` 🡢 this verison requires administrator permissions to access the instalation process. It installs the program in program files by default, but there it needs admin rights to work properly.
    > If you don't want to click every time run by administrator, just change the install dir to something a normal user can access. _eg. C:\\users\\%USER%\\Desktop_. This is because the `settings.json` file is stored in the install dir.

- #### `portable.zip` 🡢 can be unpacked and used portable. The best way if you don't have administrator permissions. Or just want to have the program on a portable device.
#
### Source files:

#### from `MyCV.zip`

- #### `MyCV.pro` 🡢 qmake file to install and build the program. This file also imports important `dll` libraries.

- #### `main.cpp` 🡢 main C++ file which only creates a `MainWindow` object, and shows it.

- #### `mainwindow` :

    - #### `.ui` 🡢 graphical layout and style file for `MainWindow` class.

    - #### `.h` 🡢 header file that predefines methods, and properties of `MainWindow` class.

    - #### `.cpp` 🡢 methods from `MainWindow` class.

- #### `settingswindow` :

    - #### `.ui` 🡢 graphical layout and style file for `SettingsWindow` class.

    - #### `.h` 🡢 header file that predefines methods, and properties of `SettingsWindow` class.

    - #### `.cpp` 🡢 methods from `SettingsWindow` class.

- #### `filetype` :

    - #### `.h` 🡢 header file that predefines methods, and properties of `FileType` class.

    - #### `.cpp` 🡢 methods from `FileType` class.

- #### `settings` :

    - #### `.h` 🡢 header file that predefines methods, and properties of `Settings` class.

    - #### `.cpp` 🡢 methods from `Settings` class.

    - #### `.json` 🡢 stores all user inputs for next session.

- #### `videoplayer` :

    - #### `.h` 🡢 header file that predefines methods, and properties of `VideoPlayer` class.

    - #### `.cpp` 🡢 methods from `VideoPlayer` class.

- #### `graphics.qrc` 🡢 stores all resources from the program in a directory called graphics, and handles the access.
#
### Classes:

- #### `MainWindow` 🡢 Main class in which all other classes meet.

    ```C++

    public:
        explicit MainWindow(QWidget *parrent = nullptr)
        ~MainWindow()

    signals:
        void path_changed();

    public slots:
        void video_status_changed(Status s);
        void refresh();

    private slots:
        void on_browse_clicked();
        void on_files_itemDoubleClicked(QListWidgetItem *item);
        void on_settings_clicked();
        void on_accept_btn_clicked();
        void on_reject_btn_clicked();
        void open_next();
        void on_volume_sliderMoved(int position);
        void on_vol_btn_clicked();

    private:
        void connectVideo();
        void setupSettings();
        void movefile(QString key);

    private:
        Ui::MainWindow *ui;
        VideoPlayer *video;
        FileType *file;
        SettingsWindow *w;
        Settings settings;

        struct {
            bool is_set;
            QString path;
            QString filename;
        } activeItem;

        struct {
            bool muted;
            int last_volume;
        } volume;

    ```

- #### `SettingsWindow` 🡢 Is run by MainWindow. On this window happens all of the changing user settings like where to store accepted or rejected `.icvx` files.

    ```C++

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

    ```

- #### Settings 🡢 simply connected hash table from `settings.json` file.

    ```C++

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

    ```

- #### FileType 🡢 handles the `.icvx` files to work as a .pdf and .avi file.

    ```C++

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

    ```

- #### VideoPlayer 🡢 This class handles the videoplayer object. Also contains a enum for the status.

    ```C++

    enum Status{
        unloaded,
        loaded,

        playing,
        stopped,
        paused
    };

    ```

    ```C++
    public:
        explicit VideoPlayer(QWidget *parent = nullptr, QWidget *destination = nullptr);
        ~VideoPlayer();

    public slots:
        void setSrc(QString src);
        void unload();

        void play();
        void stop();
        void pause();
        void playpause();

        void changeProgress(int x);
        void setVolume(int x);
        void setBar(int x);

    signals:
        void statusChanged(Status s);

    public:
        Status status() {return this->m_status;}
        void setProgress(QSlider *progress);

    private:
        Status m_status;
        QSlider *progress;
        QMediaPlayer *mp;
        QVideoWidget *vw;

    ```
#
### Skills I've learned:

- #### Threading and connections of signals and slots in QT

    ```C++
    object.connect(object1, signal1, object2, slot2);
    ```
    it works as a event listener. When object1 `emit`s a signal, then object2 runs a method defined as a public or private slot. It works only with `Q_OBJECT`.

    ```C++
    connect(this, &ClassName::signal_name, other_object, &OtherClass::slot_name);
    ```

    This works also just fine, because it's no longer object.connect(), but this->connect(). It can be used only in a child class of QObject.

- #### Little bit about byte arrays

    ```C++
    int index = data.lastIndexOf("RIFF");
    ```
    AVI files always start with this bytes. I tried earlier to make a separator to connect 2 files in one, but as we can see here, there never was a need to do that. So .avi should always start with RIFF then comes the lenght of the video data, and then who would guess? AVI.
    ```
    RIFF v12%@#shg6@#%m AVI 🡢 avi header
    ```
    PDF files are more readable:
    ```
    %PDF-1.4
    %Óëéá
    1 0 obj
    <</Creator (Mozilla/5.0 \(Windows NT 10.0; Win64; x64\) AppleWebKit/537.36 \(KHTML, like Gecko\) Chrome/92.0.4515.131 Safari/537.36 OPR/78.0.4093.186)
    /CreationDate (D:20210922225416+00'00')
    ...
    'ŰżŞüÇŮĎ°Ťq^`çŢ•Ě§­=#vŇŐ{ÓÓŢŘa...
    ```
    here the header starts with %PDF, and next are all the properties. At the end is the actual byte array.

- #### ActiveX Dynamic-Link Library

    In MyICV I've used a Adobe PDF Reader ActiveX library. So everything that would happen in the actual PDF reader, you can now just do in MyICV. To get it working i just needed 2 lines of code.
    ```C++
    ui->pdfview->setControl("Adobe PDF Reader");
    ui->pdfview->dynamicCall("LoadFile(QString)", QDir::tempPath().append("/icvx_text.tmp"));
    ```

- #### Working with signal-slot loops

    ```C++
    connect(this, &Foo::bar, other, &Bar::foo);
    connect(other, &Bar::after_foo, this, &Foo::before_bar);

    void Foo::before_bar(){ emit bar(); }
    void Bar::foo(){ emit after_foo(); }
    ```
    This code would surely create a infinite loop. But the below?
    <br>QAbstractSlider example:
    ```C++
    on_foo_valueChanged(int value){
        ui->foo->setValue(value);
    }
    ```
    This also don't works, because of the way QAbstractSlider is connected, and how the object is emiting value changes. I had to make sure this will not happen. And accidentally made 2 such loops; for the video progress slider, and the volume slider.
    <br>I mean disconnecting the object is also a workaround for this loops. But QAbstractSlider for example comes with slider_moved, and value_changed signals. The first one takes just the user input, the second takes all value changes. So:
    ```C++
    on_foo_sliderMoved(int position){
        ui->foo->setValue(position);
    }
    ```
    Works! `setValue` is the same as setting the `int position`, but the signal is emited just once by QAbstractSlider, because user didn't moved the slider a second time. While moving signals are emited, but when the program changes the value, nothing will happen.
    <br>That's how I made the slider moved by user, and changed by program. So that the user can see where at the video he currently is, but still be able to move to another point.

- #### Templates
    From _settings.h_:
    ```C++
    QHash<QString, QString> table;
    ```
    the QHash is made by a template that takes 2 inputs here \< QString, QString \>, but it could be any other class. The template is compiling when constructing an object. So editors sometime have problems to show possible issues in the code. So how to make a template class?
    ```C++
    template <typedef T, typedef U>
    class MyClass{

    public:
        U process(T t_object){...}

    private:
        T variable;
    };

    MyClass<int, bool> object;
    ```

#

### How the app works:

1. #### First when the program is started it shows you a gui interface.
2. #### In the interface the program has some event listeners, so when you click something it will show some changes.
3. #### When you have choosen your directory you want to work on, the program will automaticly change 3 pairs in the settings.json file.
4. #### If you doubleclick the file of your choice, the program will create 2 files in the temporary direction of your system. Both will be deleted when you change the file, close the program or shut down your PC.

    - #### icvx_text.tmp - holds only the pdf from the icvx file.
    - #### icvx_video.tmp - holds just the avi file from icvx.

5. #### Play/Pause, Stop, and volume button works like in any other videoplayer. If you want to mute, just click the button with the speaker.
6. #### Changing the video position is also like in any other video player. Just move the slider to set the place you want. When not moving it moves automaticly with the video progress.

#
### How to work with this program:

1. #### First of all run the MyCV.exe file.
2. #### It shows you a window called `"My Interactive Curriculum Vitae"`. You have a whole gui to work on. Video, and Pdf aren't loaded yet.
3. #### Change the input to some direction where `.icvx` files already exist.
4. #### Pick a file from the list right on the window, `double click` it.
5. #### If window, and pdf already shown, just `Accept` or `Reject`, and the program will load the next file automaticly.
6. #### To change the file manually just go back to step `4`.

The video player gives you the freedom to change volume, position, start, stop and pause. So don't change your PC's volume. It can even mute it totally. :)

Just want to make a `.icvx` file?
1. #### Complete above steps `1` and `2`.
2. #### Click the gear icon.
3. #### Another window may open in which you get 2 input fields at the bottom.
4. #### Just find your files with the select buttons.
5. #### Click create, and choose a output directory.

If you got low on storage it is recomended to check the delete rejected checkbox in settings window. It will automaticly remove the files you reject on main window.

Also consider to change your output directories, to something static like ..user/documents/acceptedCV, or a LAN path. Because _in active_ will always change if you change the path on the main window.

#
### Worked with:
- #### C++
- #### JSON
- #### QT DLLs
    - #### core
    - #### gui
    - #### widgets
    - #### multimedia
    - #### multimediawidgets
    - #### axcontainer
- #### XML
- #### NSIS

#
### Plans for the future:
#### It's not like the app is not done, but there will always be something to improve. In the time I'm writing this readme file i just got so much ideas that could make the program much more usable, or easier to watch at.

- #### Creating own pdf reader.
- #### Add dark theme.
- #### Adding a conversion API. Support `.mp4` files.
- #### Remake the file picking system. It should have a option to get all files from subdirs.
- #### Opening settings or direction dialog, will pause the video, and after close, it will resume.
- #### Graphical changes.
- #### Add option to change screen resolution. Now is set to fixed.
- #### Get rid of some repetition, for example in the VideoPlayer class. Like muting or getting the player state enum.

#

[shield1_img]: https://img.shields.io/github/commit-activity/m/GrandEchoWhiskey/my-icv?style=flat-square
[shield1_link]: #
