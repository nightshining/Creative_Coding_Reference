 
 #!/bin/sh 
 if [ $(ps ax | grep -v grep | grep "twitterTimeline.app" | wc -l) -eq 0 ] 
    then
        echo "twitterTimeline not running yet. opening..."
        open /Users/myUserName/Documents/of_v0.8.4_osx_release/apps/myAppName/TT_Combined/bin/twitterTimeline.app
    else
        echo "twitterTimeline already running - will not open duplicate"
    fi