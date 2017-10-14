#ifndef FILE_TRIGGER_HPP_
#define FILE_TRIGGER_HPP_

#include "dir_monitor_ext/typedefs.hpp"
#include <functional>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace dir_monitor_ext
{
  namespace bfs = boost::filesystem;
  class file_trigger
  {
  public:
    std::string absolute_file_path;
    file_change_action action;
    condition_for_action condition;

    file_trigger(
      std::string absolute_file_path,
      file_change_action action,
      condition_for_action condition) :
      absolute_file_path(absolute_file_path), action(action), condition(condition) {}

    file_trigger( 
      std::string absolute_file_path,
      file_change_action action) :
      file_trigger(absolute_file_path, action, default_name_condition(absolute_file_path)) {}

    condition_for_action default_name_condition(std::string & absolute_file_path)
    {
      return [absolute_file_path](error_code ec, dir_monitor_event dme)
      {
        return (bfs::absolute(dme.path).string() == absolute_file_path);
      };
    }
  };
}

#endif
