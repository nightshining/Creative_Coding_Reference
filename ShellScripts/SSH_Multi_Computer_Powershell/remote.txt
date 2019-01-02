workflow Open-Players
{
    $addresses = 109..111 | %{ “172.16.1.$_" } #does a for each loop through these tips
    foreach -Parallel ($address in $addresses) {
      InlineScript {
        $address = $using:address
        $ping = new-object System.Net.NetworkInformation.Ping
        $res = $ping.send($address)
        if($res.Status -eq "Success") {
            $user = "stuff"
            $password = "tru3l0v3"
            $cmd = "C:/Jenkins/workspace/FL_Forma_Master/Changelist/WindowsNoEditor/Forma.exe"
            $domain = [System.Net.Dns]::GetHostByAddress($address).hostname.split('.')[0]
            C:\Jenkins\PSTools\PsExec.exe -accepteula -u $domain\$user -p $password \\$address -i -d $cmd
        }
      }
    }
    #This next line opens up Forma on this computer locally
    Start-Process “C:/Jenkins/workspace/FL_Forma_Master/Changelist/WindowsNoEditor/Forma.exe"
    echo “Process Complete”
}
 
workflow Close-Players
{
    $addresses = 109..111 | %{ "172.16.1.$_" }
    foreach -Parallel ($address in $addresses) {
      InlineScript {
        $address = $using:address
        $ping = new-object System.Net.NetworkInformation.Ping
        $res = $ping.send($address)
        if($res.Status -eq "Success") {
            $cmd = “Forma.exe"
            try {
                C:\Jenkins\PSTools\pskill -accepteula \\$address $cmd
            } catch {
                write-warning "$address not accepting pskill"
                continue
            }
        }
      }
    }
    #This next line opens up Forma on this computer locally
    Stop-Process -processname Forma.exe
    echo “Process Complete”
}