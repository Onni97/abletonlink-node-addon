const AbletonLinkAddon = require('bindings')("AbletonLinkAddon");

class AbletonLink{
    
    /**
     * Create istance of the addon
     */
    constructor() {
        this._link = new AbletonLinkAddon.MyLink(120);
    }
    
    /**
     * Return true if Link is enabled, false otherwise
     * @returns {boolean} true if Link is enabled
     */
    isEnabled() {
        return this._link.isEnabled;
    }
}