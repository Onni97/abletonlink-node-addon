var express = require('express');
var app = express();
const http = require('http').Server(app);
const AbletonLinkAddon = require('bindings')("AbletonLinkAddon");
var link = new AbletonLinkAddon.MyLink(120);

link.enableStartStopSync();
console.log(link.isPlaying());

link.setTempoCallback((tempo) => {
    console.log("Tempo changed: " + tempo);
});

link.setNumPeersCallback((numPeers) => {
    console.log("Num Peers changed: " + numPeers);
});

link.setStartStopCallback((isPlaying) => {
    if(isPlaying)
        console.log("Play");
    else
        console.log("Stop");
});


//start server
http.listen(3000, function(){
    console.log('\n');
    console.log('listening on port ' + 3000);
});
