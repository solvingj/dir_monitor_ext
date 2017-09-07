#ifndef WIN_DIR_MANAGER_HPP_
#define WIN_DIR_MANAGER_HPP_

#include "dir_monitor_ext/typedefs.hpp"
#include "dir_monitor_ext/win_file_monitor.hpp"
#include <set>
#include <iostream>
#include <algorithm>
#include <stdbool.h>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace dir_monitor_ext
{

  class win_dir_manager
  {
  public:
    boost::asio::dir_monitor dm;
    std::string directory;
    std::map<std::string, win_file_monitor> file_monitors;
    bool stopped = false;

    win_dir_manager(const std::string directory, boost::asio::io_service & io_service) :
      dm(io_service), directory(directory)
    {
      dm.add_directory(directory);
    }


    void add_file_monitor(win_file_monitor fm)
    {
      file_monitors.insert_or_assign(fm.filename, fm);
    }

    void remove_file_monitor(win_file_monitor fm)
    {
      file_monitors.erase(fm.filename);
    }

    void start()
    {
      dm.async_monitor([this](const error_code & ec, const dir_monitor_event & dme)
      {
        handler(ec, dme);
      });
    }

    void stop()
    {
      stopped = true;
    }

    void handler(const error_code & ec, const dir_monitor_event & dme)
    {
      if (!stopped) { start(); }; // restart immediately to effecitvely always be monitoring unless stopped
      for (auto fm : file_monitors)
      {
        if (fm.second.condition(ec, dme))
        {
          fm.second.action(ec, dme);
        }
        else
        {
          std::cout << dme.path.filename().string() << " was changed but matched no condition" << std::endl;
        }
      };
    }
  };
}

#endif
