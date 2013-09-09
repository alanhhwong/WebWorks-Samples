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

#include "screenshot_js.hpp"

ScreenshotJS::ScreenshotJS(const string& id) : m_id(id) {
	m_pScreenshotController = new webworks::ScreenshotNDK(this);
}

ScreenshotJS::~ScreenshotJS() {
	if (m_pScreenshotController)
		delete m_pScreenshotController;
}

/**
 * This method returns the list of objects implemented by this native
 * extension.
 */
char* onGetObjList() {
    static char name[] = "ScreenshotJS";
    return name;
}

/**
 * This method is used by JNext to instantiate the Memory object when
 * an object is created on the JavaScript server side.
 */
JSExt* onCreateObject(const string& className, const string& id) {
    if (className == "ScreenshotJS") {
        return new ScreenshotJS(id);
    }

    return NULL;
}

/**
 * Method used by JNext to determine if the object can be deleted.
 */
bool ScreenshotJS::CanDelete() {
    return true;
}

/**
 * It will be called from JNext JavaScript side with passed string.
 * This method implements the interface for the JavaScript to native binding
 * for invoking native code. This method is triggered when JNext.invoke is
 * called on the JavaScript side with this native objects id.
 */
string ScreenshotJS::InvokeMethod(const string& command){
    // Determine which function should be executed
	size_t index = command.find_first_of(" ");
	string strCommand = command.substr(0, index);

	if (strCommand == "captureDisplay") {
		return m_pScreenshotController->captureDisplay();
	} else if (strCommand == "captureDisplayWithPath") {
		//called with specific path as argument
		string params = command.substr(index + 1, command.length());
		size_t indexPath = params.find_first_of(" ");
		string path = params.substr(0, indexPath);

		return m_pScreenshotController->captureDisplay(path);

	} else {
		return "Unsupported Method";
	}
}

void ScreenshotJS::NotifyEvent(const string& event) {
	string eventString = m_id + " ";
	eventString.append(event);
	SendPluginEvent(eventString.c_str(), m_pContext);
}
