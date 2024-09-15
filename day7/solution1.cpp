import input7;
import std;
import module7;

using namespace day7;

const auto add_dir_size = [](const std::size_t &sum,
                             const std::shared_ptr<directory> &dir) {
  return sum + dir->size;
};


int main() {
  std::shared_ptr<directory> current_directory = std::make_shared<directory>();
  current_directory->name = "/";

  std::vector<std::shared_ptr<directory>> directories;
  directories.push_back(current_directory);

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

      for (const auto &dir : current_directory->contents) {
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

  auto lines = std::string_view{inputdata} | std::views::split(line_delimiter);

  for (const auto &line : lines) {
    std::string linestring{line.begin(), line.end()};

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

  const auto limit{100000U};
  auto less_directories = [](const auto &directory) {
    return directory->size <= limit;
  };

  auto viewdirectories = directories | std::views::filter(less_directories);

  const auto sum =
      std::accumulate(viewdirectories.begin(), viewdirectories.end(),
                      std::size_t{}, add_dir_size);

  std::cout << "Sum of dirs => " << sum << '\n';

  const auto totalvalue = std::accumulate(std::begin(directories),
                                    std::end(directories), std::size_t{}, add_dir_size);

  std::cout << "Total Storage Sum => " << totalvalue << '\n';
}
