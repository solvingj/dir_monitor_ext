#include "dir_monitor_ext/dir_monitor_ext.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <functional>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace dme = dir_monitor_ext;
namespace bfs = boost::filesystem;

int main(int argc, char * argv[])
{
  ba::io_service io_service;
  std::cout << "Starting... \n";
  std::string name("test_file.txt");
  bfs::path file(name);
  bfs::save_string_file(file, "starting content\n");
  
  dme::file_change_action fca([](bs::error_code ec, ba::dir_monitor_event dme)
  {
    std::cout << dme.path.filename().string() << " was changed and matched condition" << std::endl;
  });

  dme::file_trigger ft(bfs::absolute(file).string(), fca);

  dme::file_monitor fm(ft, io_service);

  fm.start();

  std::thread ios_thread([&]
  {
    io_service.run();
  });

  std::cout << "File Monitored: " << ft.absolute_file_path << std::endl;
  std::cout << "Available Commands: modify_file_contents, quit" << std::endl;

  std::string input;
  while (getline(std::cin, input) && input != "quit")
  {
    if (input == "modify_file_contents")
    {
      std::cout << "Changing File" << std::endl;
      std::ifstream input(ft.absolute_file_path);
      std::ofstream output(ft.absolute_file_path, std::ofstream::out | std::ofstream::app);
      output << input.rdbuf() << std::endl << "new content" << std::endl;
    }
    else
    {
      std::cout << "Unrecognized command: " << input << std::endl;
    }
  };

  io_service.stop();
  ios_thread.join();

  return 0;
}