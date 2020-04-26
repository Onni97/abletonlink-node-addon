# Ableton Link node addon
Ableton Link native addon for Node.

Realized using node-addon-api (supported by Node) and always the latest version of Ableton Link.


## Tested Env
### OS tested: 
* Ubuntu 18.04 running on WSL on Windows 10
* Windows 10

### Node versions tested:
* 13.13.0
* 12.0.0
* 10.16.0
* All versions < 10.16.0 **doesn't** work


## Requisites
To run this project you need the **G++** compiler (4.8 or above), **Python** (v2.7, v3.5, v3.6, v3.7, or v3.8) and **Node** (10.16.0 or above)

### Linux
Run this command to install requisites:
```
sudo apt-get install g++ python
```

### Windows
You need the windows-buil-tools that containt boot G++ and Python, to install run:
```
npm install -g windows-buil-tools
```


## Dependencies
* [Ableton Link](https://github.com/ableton/link)
* [node-addon-api](https://github.com/nodejs/node-addon-api)
* [bindings](https://github.com/TooTallNate/node-bindings)


## Install
The installation will download all the dependencies and also compile the AbletonLink source code for the current enviroment.

During the installation the program you will see all the logs of the compilation. The logs depends on your compiler and version.

### GitHub
Run the script:
```
git clone --recursive https://github.com/Onni97/abletonlink-node-addon
cd abletonlink-node-addon
npm install
```
**Important:** --recursive is required to download the submodules

### npm
The package is also avaiable in npm, so you can simply execute:
```
npm install abletonlink-addon
```
or add the dependency to your ```package.json```


### Example
To run the included example you need [readline-sync](https://github.com/anseki/readline-sync). Install it with:
```
npm install readline-sync
```


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

### Methods - 1
These methods don't depend on the application/audio thread setting.

They have thread-safety and realtime-safety properties:
When a method is marked thread-safe, it means it is safe to call from multiple threads concurrently. 
When a method is marked realtime-safe, it means that it does not block and is appropriate for use in 
the thread that performs audio IO.


**- isEnabled**

Says if Link syncronization is enabled

thread-safe :heavy_check_mark: | realtime-safe :heavy_check_mark: 
```js
isEnabled() : boolean
```
```@returns``` true if Link syncronization is enabled, false otherwise


**- enable**

Enables Link syncronization

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
enable()
```


**- disable**

Disables Link syncronization

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
disable()
```


**- isStartStopSyncEnabled**

Says if start/stop sync is enabled

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
isStartStopSyncEnabled() : boolean
```
```@returns``` true if start/stop sync is enabled, false otherwise


**- enableStartStopSync**

Enables start/stop sync

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
enableStartStopSync()
```


**- disableStartStopSync**

Disables start/stop sync

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
disableStartStopSync()
```


**- getNumPeers**

Says the number of peers connected (doesn't count who calls the method)

thread-safe :heavy_check_mark: | realtime-safe :heavy_check_mark:
```js
getNumPeers() : number
```
```@returns``` The number of peers


**- setNumPeersCallback**

Sets the callback to be executed when the number of peer changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setNumPeersCallback(numPeersCallback : function)
```
```@numPeersCallback``` The callback to be executed, takes the new number of peers as number parameter


**- removeNumPeersCallback**

Removes the callback to be executed when the number of peer changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeNumPeersCallback()
```


**- setTempoCallback**

Sets the callback to be executed when the tempo changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setTempoCallback(tempoCallback : function)
```
```@tempoCallback``` The callback to be executed, takes the new tempo as number parameter


**- removeTempoCallback**

Removes the callback to be executed when the tempo changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeTempoCallback()
```


**- setStartStopCallback**

Sets the callback to be executed when the start/stop sync changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
setStartStopCallback(startStopCallback : function)
```

```startStopCallback``` The callback to be executed, takes the new start/stop state as boolean paramenter


**- removeStartStopCallback**

Removes the callback to be executed when the start/stop sync changes

thread-safe :heavy_check_mark: | realtime-safe :x:
```js
removeStartStopCallback()
```


### Methods - 2
These methods depend on the application/audio thread setting.

In general, modifying the session state should be done in the audio thread for the most 
accurate timing results. The ability to modify the session state from application threads should 
only be used in cases where an application's audio thread is not actively running or if it 
doesn't generate audio at all. Modifying the Link session state from both the audio thread and 
an application thread concurrently is not advised and will potentially lead to unexpected behavior.


**- getTempo**

Returns the current tempo(bpm)
```js
getTempo(cleanResult = false) : number
```
```@cleanResult``` If the data must be rounded to 2 decimals before return (false by default)

```@return``` The tempo


**- setTempo**

Returns the current tempo(bpm)
```js
setTempo(tempo)
```
```@tempo``` The new tempo


**- getQuantum**

Returns the quantum
```js
getQuantum() : number
```
```@return``` The quantum


**- setQuantum**

Sets the quantum
```js
setQuantum(quantum: number)
```
```quantum``` The new quantum


**- getBeat**

Returns the current beat
```js
getBeat(cleanResult = false) : number
```
```@cleanResult``` If the data must be rounded before return (false by default)

```@return``` The beat


**- requestBeat**

Set the new beat in sync with the session
```js
requestBeat(beat: number)
```
```@beat``` The new beat


**- forceBeat**

Set the new beat instantly, not in sync with the session
```js
forceBeat(beat: number)
```
```@beat``` The new beat


**- getPhase**

Returns the phase
```js
getPhase(cleanResult = false) : number
```
```@cleanResult``` If the data must be rounded before return (false by default)

```@return``` The phase


**- isPlaying**

Says if the session is playing
```js
isPlaying() : boolean
```
```@return``` True if session is playing, false otherwise


**- play**

Makes the session play
```js
play()
```


**- stop**

Makes the session stop
```js
stop()
```


**- isAudioThread**

Says if this is in audio thread mode
```js
isAudioThread() : boolean
```
```@return``` True if this is in audio thread mode, false if is in app thread mode


**- setAppThread**

Sets App thread mode
```js
setAppThread()
```


**- setAudioThread**

Sets Audio thread mode
```js
setAudioThread()
```


## Examples
To see another usage example you can go [here](https://github.com/Onni97/AbletonLinkOnNodeServer).


## License
MIT


## Issues
Please open new issues on  the [GitHub dedicated page](https://github.com/Onni97/abletonlink-node-addon/issues).


## Author
Me, [Alessandro Oniarti](https://github.com/Onni97)