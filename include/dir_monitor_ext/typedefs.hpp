#ifndef TYPEDEFS_HPP_
#define TYPEDEFS_HPP_

#include <functional>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>

namespace dir_monitor_ext
{
  using error_code = boost::system::error_code;
  using dir_monitor_event = boost::asio::dir_monitor_event;
  using condition_for_action = std::function<bool(error_code, dir_monitor_event)>;
  using file_change_action = std::function<void(error_code, dir_monitor_event)>;
}

#endif