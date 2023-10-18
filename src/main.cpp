#include "string"
#include <iostream>

#include "cli/CLI.hpp"

struct Alias {
  std::string name;
  std::string value;
};

// 定义一个函数，用于打印别名和值
void print_alias(const Alias &a) {
  std::cout << "Alias: " << a.name << "\n";
  std::cout << "Value: " << a.value << "\n";
}

int main(int argc, char **argv) {
  CLI::App app{"A command snippet"};

  app.set_help_flag("-h", "Print help message");

  auto alias_cmd =
      app.add_subcommand("alias", "Accept two strings as alias and value");

  Alias alias;

  // 在alias子命令中添加两个位置参数，分别绑定到Alias对象的name和value属性
  alias_cmd->add_option("name", alias.name, "The name of the alias")
      ->required();
  alias_cmd->add_option("value", alias.value, "The value of the alias")
      ->required();

  auto get_cmd = app.add_subcommand(
      "get", "Accept one string as alias and print its value");

  std::string name;

  get_cmd->add_option("name", name, "The name of the alias")->required();

  bool log = false;
  get_cmd->add_flag("-l", log, "Print log information");

  CLI11_PARSE(app, argc, argv);

  if (alias_cmd->parsed()) {
    print_alias(alias);
    if (log) {
      std::cout << "Log: alias command executed\n";
    }
  } else if (get_cmd->parsed()) {
    if (name == "foo") {
      std::cout << "Value: bar\n";
    } else {
      std::cout << "Alias not found\n";
    }
    if (log) {
      std::cout << "Log: get command executed\n";
    }
  }

  return 0;
}
