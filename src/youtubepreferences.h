#ifndef YOUTUBEPREFERENCES_H
#define YOUTUBEPREFERENCES_H

#include <QDialog>
#include <QWidget>
#include <QString>


namespace Ui {
    class YoutubePreferences;
}

class YoutubePreferences : public QDialog
{
    Q_OBJECT

private:
    Ui::YoutubePreferences *ui;

    static bool loadedConfiguration;
    static QString youtubeKey;
    static int quality;
    static bool playVideo;
    static int saveMusic;
    static QString saveLocation;

    void accept();

public:
    explicit YoutubePreferences(QWidget *parent = 0);
    ~YoutubePreferences();

    static void readConfiguration(bool forceReload = false);
    // Getters
    static QString getYoutubeKey();
    static int getQuality();
    static bool getPlayVideo();
    static int getSaveMusic();
    static QString getSaveLocation();


private slots:
    void on_comboSaveMusic_currentIndexChanged(int index);
    void on_buttonSaveLocation_clicked();
};

#endif // YOUTUBEPREFERENCES_H
