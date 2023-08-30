#include <iostream>
#include <mariadb/conncpp.hpp>

class Todo
{
  public:

    void insertTask(std::unique_ptr<sql::Connection> &conn, std::string taskString) {
      try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO tasks VALUES (?)"));
        stmnt->setString(1, taskString);
        stmnt->executeQuery();
      }
      catch(sql::SQLException& e) {
        std::cerr << "Error inserting task: " << e.what() << '\n';
      }
    }
};

int main() {
  Todo todoc;
  std::string mytask = "Water the plants";

  sql::Driver* driver = sql::mariadb::get_driver_instance();
  sql::SQLString url("jdbc:mariadb://localhost:3306/todoc");
  sql::Properties properties({{"user", "pranav"}, {"password", "navaneeth"}});
  std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

  todoc.insertTask(conn, mytask);
  return 0;
}
