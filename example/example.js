const readlineSync = require('readline-sync');

const AbletonLink = require("../index.js");
link = new AbletonLink();


while(true) {
    var selection = readlineSync.question("\nWhat to do? ( isEnabled | enable | disable | isStartStopSyncEnabled | enableStartStopSync | disableStartStopSync | getNumPeers | getTempo | getTempoClean | setTempo | getQuantum | setQuantum | getBeat | getBeatClean | requestBeat | forceBeat | getPhase | getPhaseClean | isPlaying | play | stop | isAudioThread | setAppThread | setAudioThread )\n>");
    
    
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
        case "getTempo":
            console.log(link.getTempo());
            break;
        case "getTempoClean":
            console.log(link.getTempo(true));
            break;
        case "setTempo":
            var tempo = readlineSync.question("Tempo: ");
            link.setTempo(parseFloat(tempo));
            break;
        case "getQuantum":
            console.log(link.getQuantum());
            break;
        case "setQuantum":
            var quantum = readlineSync.question("Quantum: ");
            link.setQuantum(parseInt(quantum));
            break;
        case "getBeat":
            console.log(link.getBeat());
            break;
        case "getBeatClean":
            console.log(link.getBeat(true));
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
        case "getPhaseClean":
            console.log(link.getPhase(true));
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
        default:
            console.log("Command not found")
    }
    console.log("\n");
}









