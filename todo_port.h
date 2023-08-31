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
      std::cout << "Showing entire tasks\n";
      try {
        std::unique_ptr<sql::Statement> stmnt((*conn)->createStatement());
        sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM tasks");

        while (res->next()) {
          std::cout << res->getInt(1) << ") " << res->getString(2) << '\n';
        }
      }
      catch(sql::SQLException& e) {
        std::cerr << "Error retrieving task: " << e.what() << '\n';
      }
    }
};
