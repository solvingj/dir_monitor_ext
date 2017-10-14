#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <dir_monitor_ext/dir_monitor_ext.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
namespace dme = dir_monitor_ext;

int main() 
{
  dme::file_change_action fca([](bs::error_code ec, ba::dir_monitor_event dme)
  {
    std::cout << dme.path.filename().string() << " was changed and matched condition" << std::endl;
  });

  return 0;
}