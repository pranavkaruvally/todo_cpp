#include <iostream>
#include <mariadb/conncpp.hpp>

class Todo
{
  private:
    std::unique_ptr<sql::Connection> *conn;

  public:
    Todo(std::unique_ptr<sql::Connection> &conn)
    {
      this->conn = &conn;
    }

    void insertTask(std::string taskString)
    {
      try {
        std::unique_ptr<sql::PreparedStatement> stmnt((*conn)->prepareStatement("INSERT INTO tasks (item) VALUES (?)"));
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
        std::unique_ptr<sql::Statement> stmnt((*conn)->createStatement());
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
        std::unique_ptr<sql::Statement> stmnt((*conn)->createStatement());
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
        std::unique_ptr<sql::PreparedStatement> stmnt((*conn)->prepareStatement("DELETE FROM tasks WHERE item_no = (SELECT MIN(item_no) FROM tasks)"));
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error deleting task: " << e.what() << '\n';
      }
    }

    void clear()
    {
      try{
        std::unique_ptr<sql::PreparedStatement> stmnt((*conn)->prepareStatement("DELETE FROM tasks;"));
        stmnt->executeQuery();
      } catch(sql::SQLException &e) {
        std::cerr << "Error clearing tasks: " << e.what() << '\n';
      }
    }

    void insert(int position, std::string newItem)
    {}

    void insertFrom(std::string FILENAME)
    {}

    void swapTask(int pos1, int pos2)
    {}
};
