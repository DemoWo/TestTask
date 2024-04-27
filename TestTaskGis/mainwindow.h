#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QVariant>
#include <QFile>
#include <QThread>
#include <QVector>

class MainWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY( double progressLoad READ progressLoad NOTIFY progressLoadChanged )
    Q_PROPERTY( QString pathFile READ pathFile NOTIFY pathFileChanged )
    Q_PROPERTY( bool startActive READ startActive NOTIFY startActiveChanged )
    Q_PROPERTY( bool pauseActive READ pauseActive NOTIFY pauseActiveChanged )
    Q_PROPERTY( bool cancelActive READ cancelActive NOTIFY cancelActiveChanged )
    Q_PROPERTY( QVariantList modeWord READ modeWord NOTIFY modeWordChanged )

public:
    explicit MainWindow ( QObject *parent = nullptr );
    ~MainWindow();

    double progressLoad();
    QString pathFile();
    bool startActive();
    bool pauseActive();
    bool cancelActive();
    QVariantList modeWord();
    void Init();
    void UpdateLoad();
    void ReadFile( const QString & );
    void ProcessingReadFile( const QString & );
    Q_INVOKABLE void timerUpdate();
    Q_INVOKABLE void setPathFile( QString );
    Q_INVOKABLE void setStartActive( const bool );
    Q_INVOKABLE void setPauseActive( const bool );
    Q_INVOKABLE void setCancelActive( const bool );

private:
    double loadFile = 0.0;
    double count = 0.0;
    QString nameFile;
    bool ActiveStart = false;
    bool ActivePause = false;
    bool ActiveCancel = false;
    QObject * Load;
    QObject * Processing;
    QThread LoadFile;
    QThread ProcessingFile;
    QMap<QString, int> listWord;
    struct ListElementMode
    {
        QString row;
        QString word;
        QString countMode;
    };
    QVector <ListElementMode> List;
    QVector <ListElementMode> List2;

public:
    void AddVector( ListElementMode );

private slots:

signals:
    void progressLoadChanged();
    void pathFileChanged();
    void startActiveChanged();
    void pauseActiveChanged();
    void cancelActiveChanged();
    void signalLoadFile( const QString & );
    void signalProcessingLoadFile( const QString & );
    void signalUpdateLoad();
    void modeWordChanged();

};

#endif // MAINWINDOW_H
