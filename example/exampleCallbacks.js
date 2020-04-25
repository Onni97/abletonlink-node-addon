const AbletonLink = require("../index.js");
link = new AbletonLink();

link.setTempoCallback((newTempo) => {
    console.log("Tempo changed: " + newTempo);
});

link.setNumPeersCallback((newNumPeers) =>{
    console.log("Number of peers changed: " + newNumPeers);
});

link.enableStartStopSync();

link.setStartStopCallback((newStartStopState) => {
    if (newStartStopState) {
        console.log("Start/stop state changed: Play");
    } else {
        console.log("Start/stop state changed: Stop");
    }
});

setInterval(function(){}, 10);