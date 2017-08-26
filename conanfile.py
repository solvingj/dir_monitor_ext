from conans import ConanFile

class DirMonitorCMakeConan(ConanFile):
    name = "dir_monitor_ext"
    version = "0.0.1"
    description = "Extensions to the dir_monitor library"
    author = "Solvingj"
    generators = "cmake"
    url = "https://github.com/bincrafters/dir_monitor_ext"
    exports_sources = "include/*"
    requires = "jsonformoderncpp/2.1.1@vthiery/stable", \
        "dir_monitor/1.0.0@bincrafters/testing", \
        "Boost/1.62.0@lasote/stable", \
        #"Boost/1.64.0@conan/stable", \

    def package(self):
        self.copy(pattern="*", dst="include", src="include")

    def package_id(self):
        self.info.header_only()

