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

#include "screenshot_ndk.hpp"
#include "screenshot_js.hpp"

namespace webworks {

ScreenshotNDK::ScreenshotNDK(ScreenshotJS *parent) {
	m_pParent = parent;
}

ScreenshotNDK::~ScreenshotNDK() {
}

string ScreenshotNDK::captureDisplay() {
	bb::system::Screenshot screenshot;
	string result = screenshot.captureDisplay().toStdString();

	if (result.empty()) {
		bb::system::ScreenshotError::Type error = screenshot.error();
		//send failure event
		switch (error) {
			case bb::system::ScreenshotError::InternalError:
				result = "An unrecoverable internal error occurred.";
				break;
			case bb::system::ScreenshotError::PermissionDenied:
				result = "Insufficient permissions to perform the operation (access_shared and use_camera_desktop required).";
				break;
			case bb::system::ScreenshotError::BadFilePath:
				result = "The screenshot could not be written to the supplied location.";
				break;
			case bb::system::ScreenshotError::UnsupportedFileType:
				result = "The image format specified is not supported.";
				break;
			case bb::system::ScreenshotError::UserDeclined:
				result = "The user prevented the screenshot from being captured.";
				break;
			default:
				break;
		}
		string event = "community.screenshot.error";
		m_pParent->NotifyEvent(event + " " + result);
		return "false";
	}
	else {
		string event = "community.screenshot.success";
		m_pParent->NotifyEvent(event + " " + result);
		return "true";
	}
}

string ScreenshotNDK::captureDisplay(string path) {
	bb::system::Screenshot screenshot;
	QUrl filePath(QString::fromStdString(path));
	string result = screenshot.captureDisplay(filePath).toStdString();

	if (result.empty()) {
		bb::system::ScreenshotError::Type error = screenshot.error();
		//send failure event
		switch (error) {
			case bb::system::ScreenshotError::InternalError:
				result = "An unrecoverable internal error occurred.";
				break;
			case bb::system::ScreenshotError::PermissionDenied:
				result = "Insufficient permissions to perform the operation (access_shared and use_camera_desktop required).";
				break;
			case bb::system::ScreenshotError::BadFilePath:
				result = "The screenshot could not be written to the supplied location.";
				break;
			case bb::system::ScreenshotError::UnsupportedFileType:
				result = "The image format specified is not supported.";
				break;
			case bb::system::ScreenshotError::UserDeclined:
				result = "The user prevented the screenshot from being captured.";
				break;
			default:
				break;
		}
		string event = "community.screenshot.error";
		m_pParent->NotifyEvent(event + " " + result);
		return "false";
	}
	else {
		string event = "community.screenshot.success";
		m_pParent->NotifyEvent(event + " " + result);
		return "true";
	}
}

} //namespace webworks
