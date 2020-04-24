# Ableton Link node addon
Ableton Link native addon for Node


## Tested Env
##### OS TESTED: 
* Ubuntu 18.04 running on WSL on Windows 10
* Windows 10

##### NODE VERSIONS TESTED:
* 13.13.0


## Requisites
To run this project you need the **G++** compiler (4.8 or above)  and **Python** (v2.7, v3.5, v3.6, v3.7, or v3.8)

##### Linux
Run this command to install requisites
```
sudo apt-get install g++ python
```

##### Windows
You need the windows-buil-tools that containt boot G++ and Python
```
npm install windows-buil-tools
```


## Dependencies
* [Ableton Link](https://github.com/ableton/link)
* [node-addon-api](https://github.com/nodejs/node-addon-api)
* [bindings](https://github.com/TooTallNate/node-bindings)


## Install (not disponible yet on npm)
The package is also avaiable in npm, so you can simply execute
```
npm install abletonlink-node-addon
```
or add the dependency to your ```package.json```

The ```install``` script will install the dependencies and also compile the AbletonLink source code for the current enviroment


## Usage
This module exposes a class that interracts with the native code of Ableton Link.
```js
const AbletonLinkAddon = require("ableton-link-addon");
var link = new AbletonLinkAddon.AbletonLink();
```

Every single instance rapresents a partecipant in the session


### Constructor
The constructor initialises the addon and sets the default values:
* the session is enabled
* quantum = 4
* tempo = 120 (if the session isn't already started)
* the object will use the application thread functions
* the beat starts from 0
* the start/stop syncronization in disabled
* the start/stop state is stopped

### Methods 1
These methods don't depend on the application/audio thread setting.

They have thread-safety and realtime-safety properties:
When a method is marked thread-safe, it means it is safe to call from multiple threads concurrently. 
When a method is marked realtime-safe, it means that it does not block and is appropriate for use in 
the thread that performs audio IO.


##### - isEnabled
thread-safe :heavy_check_mark: | realtime-safe :heavy_check_mark: 
```js
isEnabled() : boolean
```
Says if Link syncronization is enabled

```@returns``` true if Link syncronization is enabled, false otherwise


##### - enable
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
enable()
```
Enables Link syncronization


##### - disable
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
disable()
```
Disables Link syncronization


##### - isStartStopSyncEnabled
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
isStartStopSyncEnabled() : boolean
```
Says if start/stop sync is enabled

```@returns``` true if start/stop sync is enabled, false otherwise


##### - enableStartStopSync
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
enableStartStopSync()
```
Enables start/stop sync


##### - disableStartStopSync
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
disableStartStopSync()
```
Disables start/stop sync


##### - getNumPeers
thread-safe :heavy_check_mark: | realtime-safe :heavy_check_mark:
```js
getNumPeers() : Number
```
Says the number of peers connected (doesn't count who calls the method)

```@returns``` The number of peers


##### - setNumPeersCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setNumPeersCallback(numPeersCallback)
```
Sets the callback to be executed when the number of peer changes

```@numPeersCallback``` The callback to be executed, takes the new number of peers as Number parameter


##### - removeNumPeersCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeNumPeersCallback()
```
Removes the callback to be executed when the number of peer changes


##### - setTempoCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setTempoCallback(tempoCallback)
```
Sets the callback to be executed when the tempo changes

```@tempoCallback``` The callback to be executed, takes the new tempo as Number parameter


##### - removeTempoCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeTempoCallback()
```
Removes the callback to be executed when the tempo changes


##### - setStartStopCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setStartStopCallback(startStopCallback)
```
Sets the callback to be executed when the start/stop sync changes

```startStopCallback``` The callback to be executed, takes the new start/stop state as boolean paramenter


##### - removeStartStopCallback
thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeStartStopCallback()
```
Removes the callback to be executed when the start/stop sync changes


### Methods 2
These methods depend on the application/audio thread setting.

In general, modifying the session state should be done in the audio thread for the most 
accurate timing results. The ability to modify the session state from application threads should 
only be used in cases where an application's audio thread is not actively running or if it 
doesn't generate audio at all. Modifying the Link session state from both the audio thread and 
an application thread concurrently is not advised and will potentially lead to unexpected behavior.


##### - getTempo



##### - setTempo


##### - getQuantum


##### - setQuantum


##### - getBeat


##### - requestBeat


##### - forceBeat


##### - getPhase


##### - isPlaying


##### - play


##### - stop


##### - isAudioThread


##### - setAppThread


##### - setAudioThread