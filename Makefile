# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Пути к библиотекам (замени если нужно)
MSYS = C:/msys64/mingw64

# Параметры компиляции для Boost и SQLite
BOOST_LIBS = -L$(MSYS)/lib -lboost_system -lboost_thread -lpthread
SQLITE_LIBS = -L$(MSYS)/lib -lsqlite3
INCLUDE_DIRS = -I$(BOOST_DIR)/include -I$(SQLITE_DIR)/include

# Бинарные файлы
SERVER_BIN = server/chat_server.exe
CLIENT_BIN = client/chat_client.exe
DATABASE_BIN = database/database.exe

# Папка для объектных файлов
OBJ_DIR = build

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Компиляция серверных исходников
$(OBJ_DIR)/server.o: server/server.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ #$(INCLUDE_DIRS) подключение заголовочных файлов библиотек

# Компиляция клиентских исходников
$(OBJ_DIR)/client.o: client/client.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ #$(INCLUDE_DIRS) подключение заголовочных файлов библиотек

# Компиляция исходников базы данных
$(OBJ_DIR)/database.o: database/database.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ #$(INCLUDE_DIRS) подключение заголовочных файлов библиотек

# Сборка сервера
$(SERVER_BIN): $(OBJ_DIR)/server.o $(OBJ_DIR)/database.o
	$(CXX) $(CXXFLAGS) -o $@ $^ #$(BOOST_LIBS) $(SQLITE_LIBS)

# Сборка клиента
$(CLIENT_BIN): $(OBJ_DIR)/client.o $(OBJ_DIR)/database.o
	$(CXX) $(CXXFLAGS) -o $@ $^ #$(BOOST_LIBS) $(SQLITE_LIBS)

# Сборка бд
$(DATABASE_BIN): $(OBJ_DIR)/database.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SQLITE_LIBS) -DUNICODE -D_UNICODE

# Запуск сервера
run-server:
	./server/chat_server

# Запуск клиента
run-client:
	./client/chat_client

# Запуск бд
run-database:
	./database/database

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(SERVER_BIN) $(CLIENT_BIN) database/database.exe test.db

# Сборка всего проекта
all: $(OBJ_DIR) $(DATABASE_BIN) run-database
