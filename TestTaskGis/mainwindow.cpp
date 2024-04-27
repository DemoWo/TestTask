#include "mainwindow.h"

MainWindow::MainWindow( QObject *parent ) : QObject( parent )
{
}

MainWindow::~MainWindow()
{
}

// Инициализация
void MainWindow::Init()
{
    Load = new QObject;
    Load->moveToThread( &LoadFile );
    connect( &LoadFile, &QThread::finished, Load, &QObject::deleteLater );
    connect( this, static_cast<void( MainWindow::* )( const QString & )>( &MainWindow::signalLoadFile ), static_cast< MainWindow * >( Load ), [this]( const QString &pathFile )
            {
                this->MainWindow::ReadFile( pathFile );
            } );

    Processing = new QObject;
    Processing->moveToThread( &ProcessingFile );
    connect( &ProcessingFile, &QThread::finished, Processing, &QObject::deleteLater );
    connect( this, static_cast<void( MainWindow::* )( const QString & )>( &MainWindow::signalProcessingLoadFile), static_cast< MainWindow* >( Processing ), [this]( const QString & word )
            {
                this->MainWindow::ProcessingReadFile( word );
            } );
    connect( this, static_cast<void( MainWindow::* )()>( &MainWindow::signalUpdateLoad ), this, [this]()
            {

                this->MainWindow::UpdateLoad();
            } );
}

// Обновление прогресса загрузки
void MainWindow::UpdateLoad()
{
    emit progressLoadChanged();
}

// Модель отображения топ 15 слов
QVariantList MainWindow::modeWord()
{
    QVariantList result;
    QVariantMap list;
    if( List2.isEmpty() ) {
        for( int i = 0; i < 15; i++) {
            List2.append( ListElementMode{} );
        }
    }
    if( List2.length() > 0 ) {
        for( int i = 0; i < List2.length(); i++) {
            list["row"] = List2.at( i ).row;
            list["word"] = List2.at( i ).word;
            list["countMode"] = List2.at( i ).countMode;
            result << list;
        }
    }
    return result;
}

// Прогресс загрузки
double MainWindow::progressLoad()
{
    return loadFile;
}

// Записываем путь к выбранному файлу
void MainWindow::setPathFile( QString path )
{
    nameFile = path.remove( 0, 8 );
    ActiveStart = false;
    ActivePause = false;
    ActiveCancel = false;
    emit pathFileChanged();
    emit startActiveChanged();
    emit pauseActiveChanged();
    emit cancelActiveChanged();
}

// Передаем путь к загружаемому файлу
QString MainWindow::pathFile()
{
    return nameFile;
}

// Передаем флаг активности кнопки Старт
bool MainWindow::startActive()
{
    return ActiveStart;
}

// Обработка нажатия на кнопку Старт
void MainWindow::setStartActive( const bool active )
{
    if( ActivePause ) {
        ActiveStart = active;
        ActivePause = false;
        emit startActiveChanged();
        emit pauseActiveChanged();
        return;
    }

    ActiveStart = active;
    ActivePause = false;
    ActiveCancel = false;

    if( nameFile.length() > 0 ) {
        LoadFile.start();
        ProcessingFile.start();
        emit signalLoadFile( nameFile );
    }

    emit startActiveChanged();
    emit pauseActiveChanged();
    emit cancelActiveChanged();
}

// Передаем флаг активности кнопки Пауза
bool MainWindow::pauseActive()
{
    return ActivePause;
}

// Обработка нажатия на кнопку Пауза
void MainWindow::setPauseActive( const bool active )
{
    ActivePause = active;
    ActiveStart = false;
    ActiveCancel = false;
    emit startActiveChanged();
    emit pauseActiveChanged();
    emit cancelActiveChanged();
}

// Передаем флаг активности кнопки Отмена
bool MainWindow::cancelActive()
{
    return ActiveCancel;
}

// Обработка нажатия на кнопку Отмена
void MainWindow::setCancelActive( const bool active )
{
    ActiveCancel = active;
    ActiveStart = false;
    ActivePause = false;
    loadFile = 0.0;
    emit progressLoadChanged();
    emit startActiveChanged();
    emit pauseActiveChanged();
    emit cancelActiveChanged();
}

// Чтение файла
void MainWindow::ReadFile( const QString &pathFile )
{
    QFile file( nameFile );
    if( file.open(QIODevice::ReadOnly) ) {
        QString list = file.readAll();
        QStringList in = list.split( ' ' );
        count = 1.0 / in.count();
        for( int i = 0; i < in.length(); i++ ) {
            QString word = in.at( i );
            QString bufWord;
            QThread::msleep( 50 );
            for( auto j : word ) {
                if( ( ( j >= 'A' && j <= 'Z' || j >= 'a' && j <= 'z' || j >= L'А'  && j <=  L'Я' || j >= L'а' && j <=  L'я' ) || j == '-' ) && j != '\n'  ) {
                    bufWord += j;
                }
            }
            if( bufWord.length() > 0 ) {
                emit signalProcessingLoadFile( bufWord );
            }
        }
        file.close();
    }
}

// Процесс обработки слов
void MainWindow::ProcessingReadFile( const QString &word )
{
    listWord[word]++;
    QMap<QString, int>::iterator iter = listWord.begin();
    for(;iter != listWord.end(); ++iter) {
        ListElementMode list;
        list.row = "1";
        list.word = iter.key();
        list.countMode = QString::number( iter.value() );
        AddVector( list );
    }
    if( loadFile < 1.0 - count ) {
        loadFile += count;
    } else {
        loadFile = 0.1;
    }
}

// Обновление графика и прогресса загрузки по таймеру
void MainWindow::timerUpdate()
{
    emit signalUpdateLoad();
    emit modeWordChanged();
}

// Добавление данных ввектор для последующего отображения
void MainWindow::AddVector( ListElementMode list )
{
    bool check = false;
    for( int i = 0; i < List.size(); i++ ) {
        if( list.word == List.at( i ).word ) {
            List[i].countMode = list.countMode;
            check = true;
            break;
        }
    }
    for( int j = 0; j < List.size(); j++ ) {
        for( int i = 0; i < List.size() - 1; i++ ) {
            if( List.at( i ).countMode > List.at( i + 1 ).countMode ) {
                auto tmp = List.at( i );
                List[ i ] = List[ i + 1 ];
                List[ i + 1 ] = tmp;
            }
        }
    }
    if( !check ) {
        List.append( list );
    }
    for( int i = 0; i < List2.size(); i++ ) {
        for( int k = 0; k < List.size(); k++ ) {
            if( i > 0 ? List2.at( i - 1 ).countMode > List.at( k ).countMode : List2.at( i ).countMode < List.at( k ).countMode ) {
                List2[ i ] = List[ k ];
            }
        }
    }
}
