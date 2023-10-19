#include "string"
#include <iostream>
#include <utility>

#include "cli/CLI.hpp"

#include "jsonstore.h"

struct Alias {
  std::string name;
  std::string value;
};

int main(int argc, char **argv) {
  std::cout << "here" << std::endl;
  CLI::App app{"A command snippet"};
  app.set_help_flag("-h", "Print help message");

  std::string storepath = STOREPATH;
  app.add_option("-s", storepath, "store path");

  // command alias
  auto alias_cmd =
      app.add_subcommand("alias", "Accept two strings as alias and value");

  Alias alias;

  alias_cmd->add_option("name", alias.name, "The name of the alias")
      ->required();
  alias_cmd->add_option("value", alias.value, "The value of the alias")
      ->required();

  // command get
  auto get_cmd = app.add_subcommand(
      "get", "Accept one string as alias and print its value");

  std::string name;

  get_cmd->add_option("name", name, "The name of the alias")->required();

  bool label = false;
  get_cmd->add_flag("-l", label, "Print log information");

  CLI11_PARSE(app, argc, argv);

  command::Store store(std::move(storepath));

  if (alias_cmd->parsed()) {
    store.Save(std::move(alias.name), std::move(alias.value));
  } else if (get_cmd->parsed()) {
    if (label) {
      for (auto item : store.LoadByLabel(std::move(name))) {
        std::cout << item << std::endl;
      }
    } else {
      std::cout << store.Load(std::move(name)) << std::endl;
    }
  }

  return 0;
}
