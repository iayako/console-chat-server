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


int main() {
    try {
        Database db("test.db");
//        db.executeDbConfig("database/database.cfg");
        db.addUser("Vanya", "Pupkin");
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
