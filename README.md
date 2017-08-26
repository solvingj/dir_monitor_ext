# Proposed option for windows files

This repo contains two additional class/abstractions for dir_monitor.  In theory, they could be re-formed into the existing lib differently. I'm just testing the strategy in a POC project of my own, so will continue to update it if I find time to improve it. 

# Summary
Windows wants to monitor directories, people usually want to monitor one or more files (not always, but usually). 

# file_monitor
This class has with four relevant members: 

```c++
      std::string filename;
      file_change_action action;
      condition_for_action condition;
```

## Explanation
Create at one instance of `file_monitor` for each unique combination of a filename to be monitored, plus unique condition to trigger on and the action to take.  I.E. You could create one instance for file "xyz" for file changes, and another instance one for if/when the file is deleted or renamed.  The `condition` and `action` are each just a `std::function` which return `bool` and `void` respectively.  They both take the parameters `dir_monitor` provides to it's handler: `error_code` and `dir_monitor_event`, and have the `filename` variable captured from the `file_monitor` scope.  You can omit the condition parameter, and the default is to triggering on all changes which match the filename (expected to be the most common case).  

# win_dir_monitor
This class has three relevant members: 
```c++
      boost::asio::dir_monitor dm;
      std::string directory;
      std::map<std::string, file_monitor> file_monitors;
```
## Explanation
This class manages a single `dir_monitor` instance with many `file_monitors`.  Create at one instance of `win_dir_monitor` for each directory which has files you want to monitor.  After creation, use the `add_file_monitor` method to populate `file_monitors` for each file you wanted to monitor.  All the members of file_monitors get called (and passed the `error_code` and `dir_monitor_event` every time a change is detected in the directory.  Each `action` is called if the corresponding `condition` returns true.  

There are methods to add/remove `file_monitor` instances, and start and stop the monitor.  Currently, the `dir_monitor` stops it's `async_monitor` every time an event is triggered.  The most common expected case is to monitor a target indefinitely.  To this end, the `start` method is called immediately upon each event, "restarting" the monitor. 

## Summary
The example shows a fairly specific implementation to solve specific goals, but it's believed to be a very common set of goals.  The hope is that the small abstractions used are simple and generic enough to be approachable, flexible and adaptable for anyone who just wants to monitor a file for changes. 

## TODO
Everything, it's a barely working POC. 