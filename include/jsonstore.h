#ifndef STORE_H
#define STORE_H

#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using namespace std;

using json = nlohmann::json;

#define STOREPATH "~/.command.json"

namespace command {

class Store {
private:
  std::string jsonFile;
  std::mutex mutex_;
  json data; // 用于存储json数据的变量

public:
  Store(std::string &&p = STOREPATH) : jsonFile(p) {
    ifstream f(jsonFile);
    if (f.is_open()) {
      f >> data; // 将json数据存储到data变量中
      f.close();
    } else {
      fstream file;
      file.open(jsonFile, ios::out);
      file.close();

      data = nlohmann::json::object();
      // 将空的json对象写入文件中
      ofstream f(jsonFile);
      if (f.is_open()) {
        f << data;
        f.close();
      } else {
        cout << "无法打开文件" << endl;
      }
    }
  }
  bool Dump() {
    ofstream file(jsonFile);
    if (file.is_open()) {
      file << data; // 将更新后的json数据写入文件中
      file.close();
      return true;
    } else {
      cout << "无法打开文件" << endl;
      return false;
    }
  }
  std::string Load(std::string &&key);
  std::vector<std::string> LoadByLabel(std::string &&label);
  bool Save(std::string &&key, std::string &&value);
  bool AddLabel(std::string &&key, std::string &&label);
  bool DelLabel(std::string &&key, std::string &&label);
};

} // namespace command

#endif