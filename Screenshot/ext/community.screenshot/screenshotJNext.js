/*
* Copyright 2013 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

////////////////////////////////////////////////////////////////////
// JavaScript wrapper for JNEXT plugin
///////////////////////////////////////////////////////////////////
var screenshot,
    _event = require("../../lib/event");

JNEXT.Screenshot = function ()
{   
    var _self = this, hasInstance = false;
    _self._id = "";

    _self.getId = function () {
        return _self._id;
    };

    _self.init = function () {
        if (!JNEXT.require("libScreenshotExt")) {
            return false;
        }
        
        _self._id = JNEXT.createObject("libScreenshotExt.ScreenshotJS");
        
        if (_self._id === "") {
            return false;
        }

        JNEXT.registerEvents(_self);
    };

    _self.getInstance = function() {
    	if (!hasInstance) {
    		hasInstance = true;
    		_self.init();
    	}
    	return _self;
    }

    // *****************
    // Methods
    // *****************

    _self.captureDisplay = function () {
        return JNEXT.invoke(_self._id, "captureDisplay");   
    };

    _self.captureDisplayWithPath = function (args) {
        return JNEXT.invoke(_self._id, "captureDisplayWithPath" + args);
    };

    _self.onEvent = function (strData) {
        var strEventId = strData.substr(0, strData.indexOf(" ")).trim();
        var arg = strData.substr(strData.indexOf(" ")).trim();

        // Trigger the event handler of specific Push events
        if (strEventId === "community.screenshot.success") {
            _event.trigger("community.screenshot.success", arg);
        }
        if (strEventId === "community.screenshot.error") {
            _event.trigger("community.screenshot.error", arg);
        }
    };
    
    // *****************
    // End of Methods
    // *****************
};

screenshot = new JNEXT.Screenshot();

module.exports = {
	screenshot: screenshot
}