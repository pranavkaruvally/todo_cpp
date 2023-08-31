#include <iostream>
#include <fstream>
#include <mariadb/conncpp.hpp>

class Todo
{
  private:
    std::shared_ptr<sql::Connection> conn;

  public:
    Todo(std::shared_ptr<sql::Connection> connection)
    {
      this->conn = connection;
    }

    void insertTask(std::string taskString)
    {
      try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tasks (item) VALUES (?)"));
        stmnt->setString(1, taskString);
        stmnt->executeQuery();
      }
      catch(sql::SQLException& e) {
        std::cerr << "Error inserting task: " << e.what() << '\n';
      }
    }

    void showEntireTasks()
    {
      try {
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM tasks");
        int count = 1;
        while (res->next()) {
          std::cout << count++ << ") " << res->getString(2) << '\n';
        }
      } catch(sql::SQLException& e) {
        std::cerr << "Error retrieving task: " << e.what() << '\n';
      }
    }

    void show()
    {
      try {
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM tasks LIMIT 1");
        res->next(); // Current position is before first row
        std::cout << res->getString(2) << '\n';
      } catch(sql::SQLException& e) {
        std::cerr << "Error retrieving task: " << e.what() << '\n';
      }
    }

    void push(std::string newItem)
    {
      insertTask(newItem);
    }

    void pop(int position=1)
    {
      try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("DELETE FROM tasks WHERE item_no = (SELECT MIN(item_no) FROM tasks)"));
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error deleting task: " << e.what() << '\n';
      }
    }

    void clear()
    {
      try{
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("DELETE FROM tasks;"));
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error clearing tasks: " << e.what() << '\n';
      }
    }

    void insert(int position, std::string newItem)
    {}

    void insertFrom(std::string FILENAME)
    {
      std::string newline;
      std::fstream newFile(FILENAME);
      std::vector<std::string> newFileStrings;

      while (newFile) {
          getline(newFile, newline);
          newFileStrings.push_back(newline);
      }
      newFile.close();
      newFileStrings.pop_back();

      for (std::string task: newFileStrings) {
          this->push(task);
      }
    }

    void swapTask(int pos1, int pos2)
    {}
};
