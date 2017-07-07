# Quake-Live-Rcon

This is my attempt at making an easy to use Remote Console Program for Quake Live.
It is for Windows 64 bit systems.

Download the QuakeLiveRcon.zip and put the 2 files into the same folder.
I put mine in my Quake Live baseq3 and made a shortcut on my desktop.

The QuakeLiveRcon.exe is the file I made, the libzmq.dll is the communications protocol 0mq
that Quake Live Servers use. It can be found at: http://www.zeromq.org

When you run the program you will have to add servers to it. Click on 'Edit Servers'
and enter your servers. When servers are save a file named QuakeLiveServers.ini will be 
created in the folder housing the QuakeLiveRcon.exe.

Edit Server fields explained:
- Connect to Server on Program Start: It will connect to all the servers that this is checked on start-up.
- IP Address: The ip address of the server
- Port: The RCON port of the server (not the game port)
- Name: Whatever you want to call the server in this program (It will be displayed on the main screen when the server's tab is selected)
- RCON Password: The rcon password set in the server config file.

After saving all the servers you want saved, close the 'Edit Servers' window and you will see the servers
are now available to select in the main window. Select a server and click connect.

Once it has registered with the server you are free to send commands to the server.
Enter the commands on the command entry line and hit enter to send.
The Up/Down arrows will scroll through the last 10 commands sent so they can be resent without having to type them again.
This will be different for each server tab.

The program will connect to up-to 20 servers at the same time. I wouldn't connect to that many at once though. My machine uses about 12% processor for each active server connection. I am going to see if I can get the CPU usage down, hopefully I will be able to, btu I am still pretty new to this programming thing. :-)

I have plans to add a logging feature for teh servers so you will be able to log info from the servers you would like to.

I have also had a request to add buttons that you will be able to set rcon commands to so the saved commands 
will be sent with just a button click.

I hope this works well for everyone. I will post new versions here as I make them.

Let me know of any bugs or feature requests.
