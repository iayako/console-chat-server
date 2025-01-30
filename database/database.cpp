#include "database.h"

Database::Database(const char *filename) : db_file_name_(filename) {
    if (sqlite3_open(filename, &db_) != SQLITE_OK) {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db_) << std::endl;
        throw std::runtime_error("Failed to open DB");
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
        std::cout << "The database is closed: " << db_file_name_ << std::endl;
    }
}

std::string Database::readSqlFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void Database::executeDbConfig(const char *filename) {
    std::string sql = readSqlFromFile(filename);
    if (sql.empty()) {
        std::cerr << "Error: SQL script is empty" << std::endl;
        return;
    }

    char *error_message = nullptr;
    if (sqlite3_exec(db_, sql.c_str(), 0, 0, &error_message) != SQLITE_OK) {
        std::cerr << "SQL execution error: " << error_message << std::endl;
        sqlite3_free(error_message);
    } else {
        std::cout << "Tables created successfully!" << std::endl;
    }
}

void Database::addUser(const char *name, const char *password) {
    const char *sql = "INSERT INTO USERS (username, password) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL preparation error: " << sqlite3_errmsg(db_) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error executing request: " << sqlite3_errmsg(db_) << std::endl;
    } else {
        std::cout << "User added!" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Database::addMessage(const int sender_id, const int receiver_id, const int chat_id, const char *message) {
    const char *sql = "INSERT INTO MESSAGES (sender_id, receiver_id, chat_id, message) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL preparation error: " << sqlite3_errmsg(db_) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, sender_id);
    sqlite3_bind_int(stmt, 2, receiver_id);
    sqlite3_bind_int(stmt, 3, chat_id);
    sqlite3_bind_text(stmt, 4, message, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error executing request: " << sqlite3_errmsg(db_) << std::endl;
    } else {
        std::cout << "Message sended!" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Database::addChat(const char *name) {
    const char *sql = "INSERT INTO CHATS (name) VALUES (?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL preparation error: " << sqlite3_errmsg(db_) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error executing request: " << sqlite3_errmsg(db_) << std::endl;
    } else {
        std::cout << "Chat created!" << std::endl;
    }

    sqlite3_finalize(stmt);
}

void Database::addChatMember(const int chat_id, const int user_id) {
    const char *sql = "INSERT INTO CHAT_MEMBERS (chat_id, user_id) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL preparation error: " << sqlite3_errmsg(db_) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, chat_id);
    sqlite3_bind_int(stmt, 2, user_id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error executing request: " << sqlite3_errmsg(db_) << std::endl;
    } else {
        std::cout << "Chat member added!" << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    try {
        Database db("test.db");
//        db.executeDbConfig("database/database.cfg");
//        db.addUser("Vanya", "Pupkin");
//        db.addUser("Polya", "Ivanova");
//        db.addMessage(1, 2, 1, "hi");
//        db.addChat("Vanya-Polya");
//        db.addChatMember(1, 1);
//        db.addChatMember(1, 2);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
