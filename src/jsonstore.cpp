#include <fstream>
#include <iostream>
#include <vector>

#include <nlohmann/json.hpp> // 使用第三方库来处理json文件，你可以在[这里](https://www.programiz.com/cpp-programming/object-class)找到它

#include "jsonstore.h"

using json = nlohmann::json;

namespace command {
std::string Store::Load(std::string &&key) {
  if (data.contains(key)) {
    return data[key]["value"].dump();
  } else {
    return "";
  }
}

vector<string> Store::LoadByKey(string &&key) {
  vector<string> labels;
  if (data.contains(key)) { // 检查key是否存在于json数据中
    for (auto &item : data[key].items()) { // 遍历key对应的value中的所有项
      if (item.key() != "value") { // 如果项的键不是"value"，则认为它是一个label
        labels.push_back(item.key()); // 将label添加到向量中
      }
    }
  } else {
    cout << "没有找到key: " << key << endl;
  }
  return labels;
}

// 保存指定key和value到json文件中，如果成功则返回true，否则返回false
bool Store::Save(string &&key, string &&value) {
  data[key]["value"] = value; // 将value存储到key对应的value中
  return Dump();
}

// 给指定key添加一个label，如果成功则返回true，否则返回false
bool Store::AddLabel(string &&key, string &&label) {
  if (data.contains(key)) { // 检查key是否存在于json数据中
    data[key][label] = true; // 将label存储到key对应的value中，并赋值为true
    return Dump();
  } else {
    cout << "没有找到key: " << key << endl;
    return false;
  }
}

// 删除指定key的一个label，如果成功则返回true，否则返回false
bool Store::DelLabel(string &&key, string &&label) {
  if (data.contains(key)) {          // 检查key是否存在于json数据中
    if (data[key].contains(label)) { // 检查label是否存在于key对应的value中
      data[key].erase(label);        // 删除label
      return Dump();
    } else {
      cout << "没有找到label: " << label << endl;
      return false;
    }
  } else {
    cout << "没有找到key: " << key << endl;
    return false;
  }
}
} // namespace command
