#include <fstream>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp> // 使用第三方库来处理json文件，你可以在[这里](https://www.programiz.com/cpp-programming/object-class)找到它

#include "jsonstore.h"

using json = nlohmann::json;

namespace command {
std::string Store::Load(std::string &&key) {
  if (data.contains(key)) {
    std::string res = data[key]["value"];
    return res;
  } else {
    return "";
  }
}

vector<string> Store::LoadByLabel(string &&label) {
  vector<string> labels;
  for (auto &item : data.items()) {
    std::string key = item.key();
    if (item.value().contains("label") &&
        item.value()["label"].contains(label)) {
      labels.push_back(key);
    }
  }
  return labels;
}

// 给指定key添加一个label，如果成功则返回true，否则返回false
bool Store::AddLabel(string &&key, string &&label) {
  if (data.contains(key)) { // 检查key是否存在于json数据中
    if (!data[key].contains("label")) {
      data[key]["label"] = nlohmann::json::object();
    }
    data[key]["label"][label] = true;
    return Dump();
  } else {
    cout << "没有找到key: " << key << endl;
    return false;
  }
}

// 删除指定key的一个label，如果成功则返回true，否则返回false
bool Store::DelLabel(string &&key, string &&label) {
  if (data.contains(key) && data[key].contains("label") &&
      data[key]["label"].contains(label)) {
    return Dump();
  }
  return true;
}

// 保存指定key和value到json文件中，如果成功则返回true，否则返回false
bool Store::Save(string &&key, string &&value) {
  data[key]["value"] = value; // 将value存储到key对应的value中
  return Dump();
}

} // namespace command
