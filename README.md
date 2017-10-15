# Summary
dir_monitor wants to monitor directories, people usually want to monitor one or more files (not always, but usually).  This library adds two additional abstractions, and it's style is somewhat "functional" in that most of the functionality is achieved by passing functions as object, not mutating state, etc. 

# typedefs
```c++
    using condition_for_action = std::function<bool(error_code, dir_monitor_event)>;
    using file_change_action = std::function<void(error_code, dir_monitor_event)>;
```

# file_trigger
```c++
      std::string filename;
      file_change_action action;
      condition_for_action condition;
```

# file_monitor
This class has three relevant members: 
```c++
    boost::asio::dir_monitor dm;
    file_trigger ft;
    bool stopped;
```

## Explanation
Create at one instance of `file_trigger` for each unique combination of a filename to be monitored, plus unique condition to trigger on and the action to take.  I.E. You could create one instance for file "xyz" for file changes, and another instance one for if/when the file is deleted or renamed.  The `condition` and `action` are each just a `std::function` which return `bool` and `void` respectively.  Both functions take the parameters: `error_code` and `dir_monitor_event`.   You can omit the condition parameter, and the default is to trigger on all changes which match the filename (expected to be the most common case).  

Create one instance of `file_monitor` for each `file_trigger`, which handles ingesting the events from the `dir_monitor` and applying the `file_trigger`.  

There are methods for starting and stopping each `file_monitor`.  Currently, the `dir_monitor` stops it's `async_monitor` every time an event is triggered.  The most common expected case is to monitor a target indefinitely.  So, at the end of the method that processes every event that comes from `dir_monitor`, the `stopped` boolean is checked.  If it is `false` (the default) then the `start` method is called as the last step before the function is returned.  This causes the monitor to continue running indefinitely until a user calls the `.stop()` method.  

## Summary
The example shows a fairly specific implementation to solve specific goals, but it's believed to be a very common set of goals.  The hope is that the small abstractions used are simple and generic enough to be approachable, flexible and adaptable for anyone who just wants to monitor a file for changes. 

## TODO
Everything, it's a barely working POC. 