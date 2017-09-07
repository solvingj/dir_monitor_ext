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

  dme::win_dir_manager wdm(bfs::absolute(file).parent_path().string(), io_service);
  
  dme::file_change_action fca([](bs::error_code ec, ba::dir_monitor_event dme)
  {
    std::cout << dme.path.filename().string() << " was changed and matched condition" << std::endl;
  });

  dme::win_file_monitor fm(name, fca);

  wdm.add_file_monitor(fm);

  wdm.start();

  std::thread ios_thread([&]
  {
    io_service.run();
  });

  std::string input;
  std::cout << "Directory Monitored: " << wdm.directory << std::endl;
  std::cout << "File Monitored: " << bfs::absolute(bfs::path(wdm.file_monitors.begin()->first)) << std::endl;
  std::cout << "Available Commands: change_file, quit" << std::endl;

  while (getline(std::cin, input) && input != "quit")
  {
    if (input == "change_file")
    {
      std::cout << "Changing File" << std::endl;
      std::ifstream input(name);
      std::ofstream output(name, std::ofstream::out | std::ofstream::app);
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