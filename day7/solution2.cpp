#include <algorithm>

import input7;
import std;
import module7;

using namespace day7;

int main() {
    try{
  std::shared_ptr<directory> current_directory = std::make_shared<directory>();
  current_directory->name = "/";

  const auto root_directory = current_directory;

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
      current_directory = current_directory->parent.lock();
      std::cout << "Changed to Parent Directory : " << current_directory->name
                << '\n';

      const auto &contents = current_directory->contents;
      std::size_t sum{
          std::accumulate(contents.begin(), contents.end(), std::size_t{},
                          [](std::size_t previous_sum, const auto &dir) {
                            return previous_sum + dir->size;
                          })};

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

  std::stringstream inputstringstream{std::string{inputdata}};

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

  auto rootdircollection = root_directory->contents;

  std::size_t current_stored =
      std::accumulate(std::begin(rootdircollection),
                      std::end(rootdircollection), std::size_t{});

  std::cout << "\nTotal Available Space => " << disk_limit << '\n';

  std::cout << "Current Stored => " << current_stored << '\n';

  const auto target_space_removal{30000000};

  std::cout << "Desired Space Removal => " << target_space_removal << '\n';

  const std::size_t target =
      target_space_removal - (disk_limit - current_stored);

  std::cout << "Target Reduction => " << target << '\n';

  std::size_t smallest_dir_to_remove{target_space_removal};

  for (const auto &dir : directories) {
    auto dirsize = dir->size;
    if (dirsize >= target) {
      smallest_dir_to_remove = std::min(dirsize, smallest_dir_to_remove);
    }
  }

  std::cout << "Smallest dir size => " << smallest_dir_to_remove << '\n';
}
catch(std::exception &e){
    std::cerr<<std::format("Exception : {}\n", e.what());
}
}
