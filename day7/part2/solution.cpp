#include "input7.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ranges>
#include <sstream>
#include <vector>

struct file {
  std::string name{};
  std::size_t size{};
};

struct directory : public file {
  std::shared_ptr<directory> parent{};
  std::vector<std::shared_ptr<file>> contents{};

  };

std::size_t operator+(const std::size_t & value1, const std::shared_ptr<directory>& other){
    return value1 + other->size;
  }


int main() {
  std::shared_ptr<directory> current_directory = std::make_shared<directory>();
  current_directory->name = "/";

  std::vector<std::shared_ptr<directory>> directories;

  auto add_directory = [&current_directory,
                        &directories](const std::string &name) {
    auto new_directory = std::make_shared<directory>();
    new_directory->name = name;
    new_directory->parent = current_directory;
    current_directory->contents.push_back(new_directory);
    directories.push_back(new_directory);
    std::cout << " Create New Directory : " << new_directory->name
              << " | in : " << current_directory->name << '\n';
  };

  auto add_file = [&current_directory](const std::string &filename,
                                       const std::size_t filesize) {
    auto new_file = std::make_shared<file>();
    new_file->name = filename;
    new_file->size = filesize;
    current_directory->contents.push_back(new_file);
    current_directory->size += filesize;

    std::cout << "Created New File : " << new_file->name
              << "  | in : " << current_directory->name
              << " | With Size : " << filesize << '\n';
  };

  auto change_directory = [&](const std::string &destination) {
    if (destination == "..") {
      current_directory = current_directory->parent;
      std::cout << "Changed to Parent Directory : " << current_directory->name
                << '\n';
      std::size_t sum{0};
      for (auto &dir : current_directory->contents) {
        sum += dir->size;
      }

      if (current_directory->size != sum) {
        current_directory->size = sum;
        std::cout << "\tUpdated directory size to : " << current_directory->size
                  << '\n';
      }

    } else {

      for (auto &dir : current_directory->contents) {
        if (dir->name == destination) {
          auto cast_directory = std::static_pointer_cast<directory>(dir);

          if (cast_directory) {
            std::cout << "Changed to directory : " << cast_directory->name
                      << '\n';
            current_directory = cast_directory;
            break;
          }
        }
      }
    }
  };

  std::stringstream inputstringstream{inputdata};

  while (!inputstringstream.eof()) {
    std::string linestring{};
    std::getline(inputstringstream, linestring);

    if (linestring.length() > 0) {
      std::istringstream linestream{linestring};

      std::cout << linestring << '\n';

      std::string first{};
      linestream >> first;

      if (first == "$") {
        std::string command{};
        linestream >> command;

        if (command == "cd") {
          std::string destination{};
          linestream >> destination;
          change_directory(destination);
          continue;
        }

        if (command == "ls") {
          continue;
        }
      }

      if (first == "dir") {
        std::string directory_name{};
        linestream >> directory_name;
        add_directory(directory_name);
        continue;
      }

      auto file_size = stoul(first);

      std::string file_name{};
      linestream >> file_name;

      add_file(file_name, file_size);
    }
  }

  const std::size_t disk_limit{70000000};

  std::size_t current_stored = std::accumulate(std::begin(directories), std::end(directories), 0U);

  std::size_t sum{0};

  for(auto & dir : directories){
      sum += dir->size;
  }

  std::cout << "Sum of dirs => " << sum << '\n';
  
  const std::size_t target = current_stored - disk_limit;

  std::cout << "Target Reduction => " << target <<'\n';
}
