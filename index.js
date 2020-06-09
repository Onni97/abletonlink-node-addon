//For a more detailed description of the class and methods visit https://github.com/Onni97/abletonlink-node-addon#readme


const AbletonLinkAddon = require("bindings")("AbletonLinkAddon");



class AbletonLink{
    
    /**
     * Creates an instance of the addon and save it locally (and private)
     */
    constructor() {
        this._link = new AbletonLinkAddon.webAudioLink(120);
        //default values
        //tempo = 120
        //quantum = 4
        //useAppThreadFunctions = false
    }
    
    
    
    /**
     * Says if Link syncronization is enabled
     * @returns {boolean} true if Link syncronization is enabled, false otherwise
     */
    isEnabled() {
        return this._link.isEnabled();
    }
    
    
    
    /**
     * Enables Link syncronization
     */
    enable() {
        this._link.enable();
    }
    
    
    
    /**
     * Disables Link syncronization
     */
    disable() {
        this._link.disable();
    }
    
    
    
    /**
     * Says if start/stop sync is enabled
     * @returns {boolean}  true if start/stop sync is enabled, false otherwise
     */
    isStartStopSyncEnabled() {
        return this._link.isStartStopSyncEnabled();
    }
    
    
    
    /**
     * Enables start/stop sync
     */
    enableStartStopSync() {
        this._link.enableStartStopSync();
    }
    
    
    
    /**
     * Disables start/stop sync
     */
    disableStartStopSync() {
        this._link.disableStartStopSync();
    }
    
    
    
    /**
     * Says the number of other peers connected (doesn't count the caller)
     * @returns {number} The number of peers
     */
    getNumPeers() {
        return this._link.getNumPeers();
    }
    
    
    
    /**
     * Sets the callback to be executed when the number of peer changes
     * @param {function} numPeerCallback The callback to be executed, takes the new number of peers as number parameter
     */
    setNumPeersCallback(numPeerCallback) {
        if(typeof(numPeerCallback) !== "function") {
            throw "Parameter must be a function!";
        }
        this._link.setNumPeersCallback(numPeerCallback);
    }
    
    
    
    /**
     * Removes the callback to be executed when the number of peer changes
     */
    removeNumPeersCallback() {
        this._link.setNumPeersCallback(function() {});
    }
    
    
    
    /**
     * Sets the callback to be executed when the tempo changes
     * @param {function} tempoCallback The callback to be executed, takes the new tempo as number parameter
     */
    setTempoCallback(tempoCallback) {
        if(typeof(tempoCallback) !== "function") {
            throw "Parameter must be a function!";
        }
        this._link.setTempoCallback(tempoCallback);
    }
    
    
    
    /**
     * Removes the callback to be executed when the tempo changes
     */
    removeTempoCallback() {
        this._link.setTempoCallback(function() {});
    }
    
    
    
    /**
     * Sets the callback to be executed when the start/stop sync changes
     * @param {function} startStopCallback The callback to be executed, takes the new start/stop state as boolean paramenter
     */
    setStartStopCallback(startStopCallback) {
        if(typeof(startStopCallback) !== "function") {
            throw "Parameter must be a function!";
        }
        this._link.setStartStopCallback(startStopCallback);
    }
    
    
    
    /**
     * Removes the callback to be executed when the start/stop sync changes
     */
    removeStartStopCallback() {
        this._link.setStartStopCallback(function() {});
    }
    
    
    
    /**
     * Returns the current tempo(bpm)
     * @param   {boolean} [cleanResult=false] If returns clean data
     * @returns {number} The tempo
     */
    getTempo(cleanResult = false) {
        if(typeof(cleanResult) !== "boolean") {
            throw "Parameter must be a boolean!";
        }
        if(cleanResult) {
            return Math.round(this._link.getTempo()*100)/100;
        } else {
            return this._link.getTempo();
        }
    }
    
    
    
    /**
     * Returns the current tempo(bpm)
     * @param {number} tempo The new tempo
     */
    setTempo(tempo) {
        if(typeof(tempo) !== "number") {
            throw "Parameter must be a number!";
        }
        this._link.setTempo(tempo);
    }
    
    
    
    /**
     * Returns the quantum
     * @returns {number} The quantum
     */
    getQuantum() {
        return this._link.getQuantum();
    }
    
    
    
    /**
     * Sets the quantum
     * @param {number} quantum The new quantum
     */
    setQuantum(quantum) {
        if(typeof(quantum) !== "number") {
            throw "Parameter must be a number!";
        }
        this._link.setQuantum(Math.round(quantum));
    }
    
    
    
    /**
     * Returns the current beat
     * @param   {boolean} [cleanResult = false] If returns clean data
     * @returns {number} The beat
     */
    getBeat(cleanResult = false) {
        if(typeof(cleanResult) !== "boolean") {
            throw "Parameter must be a boolean!";
        }
        if(cleanResult) {
            return Math.floor(this._link.getBeat());
        } else {
            return this._link.getBeat();
        }
    }
    
    
    
    /**
     * Set the new beat in sync with the session
     * @param {number} beat The new beat
     */
    requestBeat(beat) {
        if(typeof(beat) !== "number") {
            throw "Parameter must be a number!";
        }
        this._link.requestBeat(beat);
    }
    
    
    
    /**
     * Set the new beat instantly, not in sync with the session
     * @param {number} beat The new beat
     */
    forceBeat(beat) {
        if(typeof(beat) !== "number") {
            throw "Parameter must be a number!";
        }
        this._link.forceBeat(beat);
    }
    
    
    
    /**
     * Returns the phase
     * @param   {boolean} [cleanResult = false] If returns clean data
     * @returns {number} The phase
     */
    getPhase(cleanResult = false) {
        if(typeof(cleanResult) !== "boolean") {
            throw "Parameter must be a boolean!";
        }
        if(cleanResult) {
            return Math.floor(this._link.getPhase());
        } else {
            return this._link.getPhase();
        }
    }
    
    
    
    /**
     * Says if the session is playing
     * @returns {boolean} True if session is playing, false otherwise
     */
    isPlaying() {
        return this._link.isPlaying();
    }
    
    
    
    /**
     * Makes the session play
     */
    play() {
        this._link.play();
    }
    
    
    
    /**
     * Makes the session stop
     */
    stop() {
        this._link.stop();
    }
    
    
    
    /**
     * Says if this is in audio thread mode
     * @returns {boolean} True if this is in audio thread mode, false if is in app thread mode
     */
    isAudioThread() {
        return this._link.isAudioThread();
    }
    
    
    
    /**
     * Sets App thread mode
     */
    setAppThread() {
        this._link.setAppThread();
    }
    
    
    
    /**
     * Sets Audio thread mode
     */
    setAudioThread() {
        this._link.setAudioThread();
    }
}

module.exports = AbletonLink;