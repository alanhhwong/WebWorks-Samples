Screenshot
==================

This BlackBerry 10 WebWorks extension allows the application to capture a screenshot of the device, optionally passing the desired path and image format (png or jpg).

**Requirements**

BlackBerry 10.2 or later

**Tested On**

BlackBerry 10 Dev Alpha B running 10.2.0.1445

**Author**

[Alan Wong](https://github.com/alawong)

## Building and Testing the Sample

1. Deploy the extension into your BB10 WebWorks SDK by copying the __community.screenshot__ folder from the ext folder to the Framework/ext folder in your WebWorks SDK

2. Package the sample in the sample\_application folder. You can do this with Ripple or the WebWorks packager command: 
	__bbwp__ sample\_application -g _signingpassword_

3. Load it on your phone using Ripple or _blackberry-deploy_ command found in the dependencies/tools folder of your WebWorks SDK.

4. When the application runs, you will have two buttons for capturing a screenshot with and without save path.

## Including the feature in your application
Whenever you use the below feature id in any of your WebWorks applications this extension will be loaded for use.

```xml
<feature id="community.screenshot" required="true" version="1.0.0.0" />
```

## The Extension API
The Prevent Sleep Extension provides the following API:

```javascript
//onSuccess and onError are predefined callback functions
var result = community.screenshot.captureDisplay(onSuccess, onError);

var path = "file:///accounts/1000/shared/camera/custompath.jpg"
var result = community.screenshot.captureDisplayWithPath(path, onSuccess, onError);
```

## Building the extension from source

Copy the extension folder to a location on your computer to start working with it.

### Momentics NDK setup

1. Open the Momentics IDE. Navigate to the workbench and from the program menu
select File -> Import and choose "Existing Projects into Workspace".
2. Choose "Select root directory: " and browse to the NDK_project directory where you copied the extension. Select the PreventSleep project in the Projects list and uncheck "Copy projects into workspace". Click Finish.
3. Follow these next steps to build the extension to be sure the setup is working.

#### How to build your native Extension</a>

1. Right click your project and select the Clean Project option.
2. Right click your project again and select Build Configurations -> Build Selected... .
3. A window will appear that shows all the available build configurations
for the project. Select Device-Release and Simulator-Debug and click ok.
4. You should see the shared libraries generated in the folders for each Build Configuration that you selected.
5. Copy the .so file(s) to the device and simulator folders under the ext/community.preventsleep directory. Or you can use the Ant build script to do so.

### Copying the Extension to the SDK</a>

1. Under the ext folder in this project should be the community.preventsleep folder with the following file structure underneath it:

![Screenshot](files.png)

2. The device and simulator folders should contain the libScreenshotExt.so files built by the NDK.3. 
3. Copy the community.screenshot folder into your WebWorks SDK, placing it in the Framework/ext directory.


### Using the Extension in an Application</a>

With the extension copied into your WebWorks SDK as explained above, you can use it in your applications by referencing it as a feature in your config.xml file. 

```xml
<feature id="community.screenshot" />
```

All the methods in the extension will be prefixed by that feature id, so a method called setPreventSleep() supplied in the community.preventsleep extension will be called in JavaScript like so:

```javascript
community.screenshot.captureDisplay(onSuccessCallback, onFailureCallback);
community.screenshot.captureDisplay(path, onSuccessCallback, onFailureCallback);
```

### Modifying the Extension

See the examples in the [Template Extension](https://github.com/blackberry/WebWorks-Community-APIs/blob/master/BB10/Template) for how to add additional features to this extension

#### Rebuild 
When making changes, rebuild regularly so you don't make a really hard to find typo.

Follow the steps above to:
1. [Build the native portion](#how-to-build-your-native-extension),
2. [Copy the extension to your SDK](#copying-the-extension-to-the-sdk), and
3. [Use the extension in your test app](#using-the-extension-in-an-application).


**To contribute code to this repository you must be [signed up as an official contributor](http://blackberry.github.com/howToContribute.html).**

## Disclaimer

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.