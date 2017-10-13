#include <iostream>
#include <boost/asio.hpp>
#include <dir_monitor/dir_monitor.hpp>
#include <dir_monitor_ext/dir_monitor_ext.hpp>
	
int main() 
{
	std::string file = "fakefile.txt"; 
  boost::asio::io_service io_service;
	//test hangs if i uncomment the below line. needs fix. 
	dir_monitor_ext::dir_manager wdm(file, io_service);

  return 0;
}