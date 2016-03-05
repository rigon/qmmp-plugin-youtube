#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <qmmp/qmmp.h>

#include "youtubepreferences.h"
#include "ui_youtubepreferences.h"

#include <iostream>


bool YoutubePreferences::loadedConfiguration = false;
QString YoutubePreferences::youtubeKey = QString();
int YoutubePreferences::quality = 0;
bool YoutubePreferences::playVideo = false;
int YoutubePreferences::saveMusic = 0;
QString YoutubePreferences::saveLocation = QString();


YoutubePreferences::YoutubePreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YoutubePreferences)
{
    ui->setupUi(this);

    // Read configuration and apply it
    YoutubePreferences::readConfiguration();
    ui->textYoutubeKey->setText(YoutubePreferences::youtubeKey);
    ui->comboQuality->setCurrentIndex(YoutubePreferences::quality);
    ui->checkPlayVideo->setChecked(YoutubePreferences::playVideo);
    ui->comboSaveMusic->setCurrentIndex(YoutubePreferences::saveMusic);
    ui->textSaveLocation->setText(YoutubePreferences::saveLocation);
    // Update Save
    this->on_comboSaveMusic_currentIndexChanged(YoutubePreferences::saveMusic);
}

YoutubePreferences::~YoutubePreferences() {
    delete ui;
}

void YoutubePreferences::on_comboSaveMusic_currentIndexChanged(int index)
{
    bool state = !(index == 0);
    ui->labelSaveLocation->setEnabled(state);
    ui->textSaveLocation->setEnabled(state);
    ui->buttonSaveLocation->setEnabled(state);
}

void YoutubePreferences::on_buttonSaveLocation_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        ui->textSaveLocation->text(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(dir.length() > 0)    // If is not Cancel
        ui->textSaveLocation->setText(dir);
}


void YoutubePreferences::accept()
{
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    settings.beginGroup("Youtube");
    settings.setValue("youtube_key", ui->textYoutubeKey->text());
    settings.setValue("quality", ui->comboQuality->currentIndex());
    settings.setValue("play_video", ui->checkPlayVideo->isChecked());
    settings.setValue("save_music", ui->comboSaveMusic->currentIndex());
    settings.setValue("save_location", ui->textSaveLocation->text());
    settings.endGroup();

    this->close();
}


void YoutubePreferences::readConfiguration(bool forceReload)
{
    if(YoutubePreferences::loadedConfiguration && !forceReload)
        return;
    YoutubePreferences::loadedConfiguration = true;

    // Default music location
    QString defaultMusicLocation = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);

    // Read configuration
    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    settings.beginGroup("Youtube");
    YoutubePreferences::youtubeKey = settings.value("youtube_key", "").toString();
    YoutubePreferences::quality = settings.value("quality", 0).toInt();
    YoutubePreferences::playVideo = settings.value("play_video", false).toBool();
    YoutubePreferences::saveMusic = settings.value("save_music", 0).toInt();
    YoutubePreferences::saveLocation = settings.value("save_location", defaultMusicLocation).toString();
    settings.endGroup();
}



/* *******************
 * Getters
 * ******************/

QString YoutubePreferences::getYoutubeKey()
{
    YoutubePreferences::readConfiguration();
    return YoutubePreferences::youtubeKey;
}

int YoutubePreferences::getQuality()
{
    YoutubePreferences::readConfiguration();
    return YoutubePreferences::quality;
}

bool YoutubePreferences::getPlayVideo()
{
    YoutubePreferences::readConfiguration();
    return YoutubePreferences::playVideo;
}

int YoutubePreferences::getSaveMusic()
{
    YoutubePreferences::readConfiguration();
    return YoutubePreferences::saveMusic;
}

QString YoutubePreferences::getSaveLocation()
{
    YoutubePreferences::readConfiguration();
    return YoutubePreferences::saveLocation;
}

