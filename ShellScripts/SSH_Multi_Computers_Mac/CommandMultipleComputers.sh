#!/bin/sh
IP[0]=192.168.1.1 # Computer 1
IP[1]=192.168.1.2 # Computer 2
IP[2]=192.168.1.3 # Computer 3
~/Desktop/ShellScripts/sshsudo -u myUsername ${IP[0]},${IP[1]},${IP[2]} open ./Desktop/SomeFileToTest.app

# - brew install https://raw.githubusercontent.com/kadwanev/bigboybrew/master/Library/Formula/sshpass.rb
# - ~/Desktop/ShellScripts/sshsudo
# - chmod +x ~/Desktop/ShellScripts/sshsudo
# - cd ~/Desktop/ShellScripts/ 
# - touch myAppRunner 
# - chmod u+x myAppRunner 


