const AbletonLinkAddon = require('bindings')("AbletonLinkAddon");

var link = new AbletonLinkAddon.MyLink(120);

console.log(link.tempo());