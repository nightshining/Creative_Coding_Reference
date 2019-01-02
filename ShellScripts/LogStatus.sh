#!/bin/bash
echo "================================" >> /Users/myUserName/Desktop/StatusLogs/TimelineLog1.txt
date >> /Users/myUserName/Desktop/StatusLogs/TimelineLog1.txt
ps aux | grep '%CPU' >> /Users/myUserName/Desktop/StatusLogs/TimelineLog1.txt
ps aux | grep 'myProgramTimeline' >> /Users/myUserName/Desktop/StatusLogs/TimelineLog1.txt
ps aux | grep 'Curator' >> /Users/myUserName/Desktop/StatusLogs/TimelineLog1.txt
#echo "================================" >> /Users/myUserName/Desktop/StatusLogs/SerialLog1.txt
#date >> /Users/myUserName/Desktop/StatusLogs/SerialLog1.txt
#ls /dev/tty.* | grep 'tty.usbmodem12341' >> /Users/myUserName/Desktop/StatusLogs/SerialLog1.txt
echo "================================" >> /Users/myUserName/Desktop/StatusLogs/DisplayTimelineLog1.txt
date >> /Users/myUserName/Desktop/StatusLogs/DisplayTimelineLog1.txt
system_profiler SPDisplaysDataType | grep 1920 >> /Users/myUserName/Desktop/StatusLogs//DisplayTimelineLog1.txt
echo "================================" >> /Users/myUserName/Desktop/StatusLogs/CuratorSizeLog1.txt
date >> /Users/myUserName/Desktop/StatusLogs/CuratorSizeLog1.txt
du -sh /Users/myUserName/Library/Application\ Support/myProgram\ Curator/* >> /Users/myUserName/Desktop/StatusLogs//CuratorSizeLog1.txt
