# Quake-Live-Rcon

<b><u>Download Latest Release</b></u>: https://github.com/BarelyMiSSeD/Quake-Live-Rcon/releases

<b>Visual C++ Redistributable 2015</b> is required for this application. Most people should already have what is needed to run this application, so try running it first. If it won't run download and install Visual C++ here: https://www.microsoft.com/en-us/download/details.aspx?id=52685

This is my attempt at making an easy to use Remote Console Program for Quake Live.
QuakeLiveRcon_x64_\*.\*.\*.\*.zip is for Windows 64 bit systems.
QuakeLiveRcon_x86_\*.\*.\*.\*.zip is for Windows 32 bit systems.


Download the desired QuakeLiveRcon_x\*\*_\*.\*.\*.\*.zip and put the 2 files into the same folder.
I put mine in my Quake Live baseq3 and made a shortcut on my desktop.

The QuakeLiveRcon.exe is the file I made, the libzmq.dll is the communications protocol 0mq
that Quake Live Servers use. It can be found at: http://www.zeromq.org
The Newtonsoft.Json.dll file is for parsing some information from the server, the file can be downloaded at: https://www.newtonsoft.com/json

When you run the program you will have to add servers to it. Click on 'Edit Servers'
and enter your servers. When servers are save a file named QuakeLiveServers.ini will be 
created in the folder housing the QuakeLiveRcon.exe.

<b>Edit Server fields explained:</b>
- Connect to Server on Program Start: It will connect to all the servers that this is checked on start-up.
- IP Address: The ip address of the server
- Port: The RCON port of the server (not the game port)
- Name: Whatever you want to call the server in this program (It will be displayed on the main screen when the server's tab is selected)
- RCON Password: The rcon password set in the server config file.
- Log RCON info to file: This will save the output you see on the screen to a log file. The logs are stored in the 'QuakeLiveRconLogs'
sub folder from the location of the executable. The file names start with the server IP_PORT. If a lot of logging is done, when the file reaches 5MB in size, the current file will be renamed by appending a _1, _2, _3, etc..., to the end of the file name and starting a new file. If loging is enabled, when exiting the program it may take a few seconds because the information not written to the file yet needs to be processed.

After saving all the servers you want saved, close the 'Edit Servers' window and you will see the servers
are now available to select in the main window. Select a server and click connect.

Once it has registered with the server you are free to send commands to the server.
Enter the commands on the command entry line and hit enter to send.
The Up/Down arrows will scroll through the last 10 commands sent so they can be resent without having to type them again.
This will be different for each server tab.

<b>Settings:</b> (Settings here will apply to all servers)
Clicking the Settings button will bring up the settings window. This window shows the current version of the program and has a link to the Github website where the file is avaiable.<br>

-<b><u>The 'send status Command on Connect to each server' option</u></b> will send a status command automatically when sucessful server registration is completed.<br>
-<b><u>The Enable 'Connect to Game Server' option</u></b> will allow you to connect to game servers that have an active RCON connection.<br>
-<b><u>The 'Keep Computer from entering any sleep mode' option</u></b> will keep the computer in a state that will allow it to continue to communicate with servers. This option will still allow the monitor to go into any screensaver mode that is set. Once all server tabs are closed or the program is exited settings will be returned to normal.<br>
-<b><u>There are 6 configurable command buttons</u></b> avaiable for use. Each button must be activated to be used. The 'Button Label' field is what you will see on the button when clicking on it. The 'Button Comand' field is the command that will be sent to the server. (Note: The format and spelling of the command is NOT checked before sending. Make sure you enter the command exactly as the server requires.) (To send MINQLX bot commands preface the command normally sent on the server with a 'qlx' for example: '!elos' would be 'qlx !elos')<br>
-<b><u>The 'Disable Auto Scroll' option</u></b> will stop the scrolling of the server output window. This is to allow the reading of the window while still connected to the server. This option can be disabled and re-enabled while connected to servers.<br>
-<b><u>The Maximum Amount of Lines allowed option</u></b> will set the server output windows maximum lines. When this line amount is reached the [b][u]amount of lines to remove</u></b> setting will be used to trim the earlier messages before continuing to print messages to the window. This will continue to happen each time the maximun lines setting is reached.<br>
-<b><u>The 'Quake Live Colors' settings page</u></b> is where the colors used in the server output window to represent the color coding in Quake Live can be set. This will allow the configuring of the colors to individual preferences.<br>
-<b><u>The 'Enable Logging' option</u></b> is on by default. It will allow the disabling of all server logging from a single setting. This setting must be enabled to allow individual server logging.<br>
-<b><u>The Enable stripping color codes from Log File</u></b> will strip the Quake style color codes from the logged information. The color codes are left in the log file if not enabled. <br>

<br><br>

The server output will display the special characters you see used by players in the server and will display color when Quake Style color coding is sent by the server.

The program will connect to up-to 20 servers at the same time.

I hope this works well for everyone. I will post new versions here as I make them.

Let me know of any bugs or feature requests.
