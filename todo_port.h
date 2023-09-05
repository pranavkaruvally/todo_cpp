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

    void push(std::string taskString)
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
        sql::ResultSet *res = stmnt->executeQuery("SELECT item FROM tasks ORDER BY item_no, tstamp DESC");
        int count = 1;
        while (res->next()) {
          std::cout << count++ << ") " << res->getString(1) << '\n';
        }
      } catch(sql::SQLException& e) {
        std::cerr << "Error retrieving task: " << e.what() << '\n';
      }
    }

    void show()
    {
      try {
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        sql::ResultSet *res = stmnt->executeQuery("SELECT item FROM tasks ORDER BY item_no, tstamp DESC LIMIT 1");
        res->next(); // Current position is before first row
        std::cout << res->getString(1) << '\n';
      } catch(sql::SQLException& e) {
        std::cerr << "Error retrieving task: " << e.what() << '\n';
      }
    }

    void pop(int position=1)
    {
      try {
        std::string query = "DELETE FROM tasks WHERE (item_no, tstamp) = (SELECT item_no, tstamp FROM tasks ORDER BY item_no, tstamp DESC LIMIT ?, 1);";
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement(query));
        stmnt->setInt(1, position-1);
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error deleting task: " << e.what() << '\n';
      }
    }

    void clear()
    {
      try{
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("TRUNCATE tasks;"));
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error clearing tasks: " << e.what() << '\n';
      }
    }

    void insert(int position, std::string newItem)
    {
      try{
        std::unique_ptr<sql::Statement> positionStatement(conn->createStatement());
        std::string limitArgs = std::to_string(position-1) + ", 1;";
        sql::ResultSet *res = positionStatement->executeQuery("SELECT item_no FROM tasks ORDER BY item_no, tstamp DESC LIMIT " + limitArgs);
        res->next();
        int newPosition = res->getInt(1);

        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tasks(item_no, item) VALUES (?, ?)"));
        stmnt->setInt(1, newPosition);
        stmnt->setString(2, newItem);
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error inserting task: " << e.what() << '\n';
      }
    }

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
