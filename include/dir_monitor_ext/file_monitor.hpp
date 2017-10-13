#ifndef FILE_MONITOR_HPP_
#define FILE_MONITOR_HPP_

#include "dir_monitor_ext/typedefs.hpp"
#include <functional>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace dir_monitor_ext
{
  class file_monitor
  {
  public:
    std::string filename;
    file_change_action action;
    condition_for_action condition;

    file_monitor(
      std::string filename,
      file_change_action action,
      condition_for_action condition) :
      filename(filename), action(action), condition(condition) {}

    file_monitor(
      std::string filename,
      file_change_action action) :
      file_monitor(filename, action, default_name_condition(filename)) {}

    condition_for_action default_name_condition(std::string & filename)
    {
      return [filename](error_code ec, dir_monitor_event dme)
      {
        return (dme.path.filename().string() == filename);
      };
    }
  };
}

#endif
