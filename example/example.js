var readlineSync = require('readline-sync');


//const AbletonLinkAddon = require('bindings')("AbletonLinkAddon");
//var link = new AbletonLinkAddon.MyLink();

const AbletonLink = require("../index.js");
link = new AbletonLink();






while(true) {
    var selection = readlineSync.question("What to do? ( isEnabled | enable | disable | isStartStopSyncEnabled | enableStartStopSync | disableStartStopSync | getNumPeers | setNumPeersCallback | setTempoCallback | setStartStopCallback | getTempo | setTempo | getQuantum | setQuantum | getBeat | requestBeat | forceBeat | getPhase | isPlaying | play | stop | isAudioThread | setAppThread | setAudioThread )\n>");
    
    
    switch(selection) {
        case "isEnabled":
            console.log(link.isEnabled());
            break;
        case "enable":
            link.enable();
            break;
        case "disable":
            link.disable();
            break;
        case "isStartStopSyncEnabled":
            console.log(link.isStartStopSyncEnabled());
            break;
        case "enableStartStopSync":
            link.enableStartStopSync();
            break;
        case "disableStartStopSync":
            link.disableStartStopSync();
            break;
        case "getNumPeers":
            console.log(link.getNumPeers());
            break;
        case "setNumPeersCallback":
            console.log("TODO");
            break;
        case "setTempoCallback":
            console.log("TODO");
            break;
        case "setStartStopCallback":
            console.log("TODO");
            break;
        case "getTempo":
            console.log(link.getTempo());
            break;
        case "setTempo":
            var tempo = readlineSync.question("Tempo: ");
            link.setTempo(parseFloat(tempo));
            break;
        case "getQuantum":
            console.log(link.getQuantum());
            break;
        case "setQuantum":
            var tempo = readlineSync.question("Quantum: ");
            link.setQuantum(parseInt(quantum));
            break;
        case "getBeat":
            console.log(link.getBeat());
            break;
        case "requestBeat":
            var beat = readlineSync.question("Beat: ");
            link.requestBeat(parseInt(beat));
            break;
        case "forceBeat":
            var beat = readlineSync.question("Beat: ");
            link.requestBeat(parseInt(beat));
            break;
        case "getPhase":
            console.log(link.getPhase());
            break;
        case "isPlaying":
            console.log(link.isPlaying());
            break;
        case "play":
            link.play();
            break;
        case "stop":
            link.stop();
            break;
        case "isAudioThread":
            console.log(link.isAudioThread());
            break;
        case "setAppThread":
            link.setAppThread();
            break;
        case "setAudioThread":
            link.setAudioThread();
            break;
    }
    console.log("\n\n\n");
}









