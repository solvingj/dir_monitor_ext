#ifndef FILE_MONITOR_HPP_
#define FILE_MONITOR_HPP_

#include "dir_monitor_ext/typedefs.hpp"
#include "dir_monitor_ext/file_trigger.hpp"
#include <set>
#include <iostream>
#include <algorithm>
#include <stdbool.h>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace dir_monitor_ext
{
  namespace bfs = boost::filesystem;
  class file_monitor
  {
  public:
    boost::asio::dir_monitor dm;
    file_trigger ft;
    bool stopped = false;

    file_monitor(const file_trigger file_trigger, boost::asio::io_service & io_service) :
      ft(file_trigger), dm(io_service)
    {
      dm.add_directory(bfs::path(file_trigger.absolute_file_path).parent_path().string());
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
      if (ft.condition(ec, dme))
      {
        ft.action(ec, dme);
      }
      else
      {
        //TODO: Replace with logging
        std::cout << dme.path.filename().string() << " was changed but did not match condition" << std::endl;
      }
    }
  };
}

#endif
