#include "database.h"

Database::Database(QObject *parent) : QObject(parent) { }

Database::~Database()
{
    // при закрытии программы и уничтожении
    // этого класса закрываем базу  данных
    closeDataBase();
}

// Подключение к БД
void Database::connectToDataBase(QString dbName)
{
    // Сохраняем путь и имя базы
    DataBaseName = dbName;
    // Проверка на существование базы
    if(!QFile(dbName).exists()){ // если база данных не существует - создаём новую
        this->restoreDataBase();
    } else { // иначе открываем существующую
        this->openDataBase();
    }
}

// Функция для восстановления базы
bool Database::restoreDataBase()
{
    if(this->openDataBase()){ // Если БД открыта
        if(!this->createDeviceTable()){ // если таблица в базе данных не была создана после вызова createDeviceTable()
            return false;
        } else {
            return true;
        }
    } else { // если бд не была открыта
        return false;
    }
    return false; // в любом другом случае возвращаем false
}

// Функция для открытия БД
bool Database::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DataBaseName);
    if(db.open()){ // если таблица успешно открыта - сообщаем об этом
        return true;
    } else {
        return false; // иначе сообщаем, что нам не удалось ее открыть
    }
}

// Функция для закрытия базы
void Database::closeDataBase()
{
    db.close();
}

// Функция для создания таблиц в базе данных
bool Database::createDeviceTable()
{
    // Создание таблиц через SQL запрос
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE_SOURCE " ("
                        K                       " INTEGER       NOT NULL UNIQUE PRIMARY KEY CHECK (N <= 99),"
                        CONDITION               " INTEGER (3)   NOT NULL CHECK (Condition <= 3),"
                        NUMBER                  " INTEGER       NOT NULL,"
                        AK                      " DOUBLE        NOT NULL,"
                        BK                      " DOUBLE (360)  NOT NULL CHECK (Bk <= 360),"
                        START_TIME              " TIME          NOT NULL,"
                        REPEAT_DURATION         " INTEGER       NOT NULL,"
                        MAX_REPEAT_COUNT        " INTEGER (99)  NOT NULL CHECK (Maxr <= 99),"
                        F_MESSAGE_SENT          " TEXT          NOT NULL,"
                        BROKEN_TIME             " INTEGER       NOT NULL,"
                        MAX_SEARCH_TIME         " INTEGER       NOT NULL,"
                        MAX_SYNC_PROBABILITY    " STRING        NOT NULL,"
                        MAX_WAIT_TIME           " INTEGER       NOT NULL,"
                        F_SYNC_LOST             " TEXT          NOT NULL"
                    " );") || !query.exec("CREATE TABLE " TABLE_RECEIVER " ("
                        NUM                     " INTEGER       NOT NULL UNIQUE PRIMARY KEY CHECK (N <= 99),"
                        SEQUENCE                " INTEGER       NOT NULL,"
                        N0                      " INTEGER       NOT NULL"
                    ");")) {
        return false; // возвращаем false если таблица не создана
    } else {
        return true; // если создана возвращаем true
    }
    return false; // в любом другом случае возвращаем false
}




