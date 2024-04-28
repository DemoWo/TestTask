# TestTask

// Инициализация
void MainWindow::Init();

// Обновление прогресса загрузки
void MainWindow::UpdateLoad();

// Модель отображения топ 15 слов
QVariantList MainWindow::modeWord();

// Прогресс загрузки
double MainWindow::progressLoad();

// Записываем путь к выбранному файлу
void MainWindow::setPathFile( QString path );

// Передаем путь к загружаемому файлу
QString MainWindow::pathFile();

// Передаем флаг активности кнопки Старт
bool MainWindow::startActive()

// Обработка нажатия на кнопку Старт
void MainWindow::setStartActive( const bool active );

// Передаем флаг активности кнопки Пауза
bool MainWindow::pauseActive();

// Обработка нажатия на кнопку Пауза
void MainWindow::setPauseActive( const bool active );

// Передаем флаг активности кнопки Отмена
bool MainWindow::cancelActive();

// Обработка нажатия на кнопку Отмена
void MainWindow::setCancelActive( const bool active );

// Чтение файла
void MainWindow::ReadFile( const QString &pathFile );

// Процесс обработки слов
void MainWindow::ProcessingReadFile( const QString &word );

// Обновление графика и прогресса загрузки по таймеру
void MainWindow::timerUpdate();

// Добавление данных ввектор для последующего отображения
void MainWindow::AddVector( ListElementMode list );
