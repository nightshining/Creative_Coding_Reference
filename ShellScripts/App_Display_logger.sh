#Set this on a launchd/cronjob to run every few minutes
#!/bin/bash

#check if application is running and log it in the file - will just log a 'grep' if app is not running
ps aux | grep 'MadMapper' >> /Users/user/Dropbox/FL_Support/RalphLauren/AppProcessLog.txt

#check available resolutions to see if displays are acting properly
system_profiler SPDisplaysDataType | grep Resolution >> /Users/user/Dropbox/FL_Support/user/AppProcessLog.txt

system_profiler SPDisplaysDataType | grep Online >> /Users/user/Dropbox/FL_Support/user/AppProcessLog.txt

