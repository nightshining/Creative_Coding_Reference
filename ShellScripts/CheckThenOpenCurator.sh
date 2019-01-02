 
 #!/bin/sh 
 if [ $(ps ax | grep -v grep | grep "myAppName.app" | wc -l) -eq 0 ]
    then
        echo "myAppName not running yet. opening..."
        open /Applications/TwitterCuratorTool/TwitterCurator17.app
    else
        echo "myAppName already running - will not open duplicate"
    fi