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
    void addMessage(const int sender_id, const int receiver_id, const int chat_id, const char *message);
    void addChat(const char *name);
    void addChatMember(const int chat_id, const int user_id);

private:
    std::string readSqlFromFile(const std::string &filename);
    sqlite3 *db_ = nullptr;
    const char *db_file_name_;
};

#endif // CHAT_DATABASE_H
