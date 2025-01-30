#ifndef CHAT_DATABASE_H
#define CHAT_DATABASE_H

#include <string>
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <stdexcept>

//класс для
class Database {
public:
    explicit Database(const char *filename);
    ~Database();

    void executeDbConfig(const char *filename);
    void addUser(const char *name, const char *password);

private:
    void addChat();
    std::string readSqlFromFile(const std::string &filename);
    sqlite3 *db_ = nullptr;
    const char *db_file_name_;
};

#endif // CHAT_DATABASE_H
