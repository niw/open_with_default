Open with Default
=================
A tiny extension for Google Chrome on Mac OS X which adds "Open with Default" to context menu of links.
We can open the link wifh Safari or Firefox from Chrome.

This extension use native code to run external application like Safari or Firefox from Chrome.
The native code are running as NPAPI plugin like Flash Player in background page.
See <http://code.google.com/chrome/extensions/trunk/npapi.html> for more details.

This extension might be good example how to implement native plugin for Google Chrome extension on Mac OS X.
Enjoy!

How to Build and Test
---------------------
Open `OpenWithDefault.xcodeproj` with Xcode then build.
Enable developer mode on Extensions page on Chrome, then load unpacked extension from `Extension` folder.

Build .crx File
---------------
Select "Packaging" target then build it, you'll get OpenWithDefault.crx in project folder.

Run Chrome
----------
This extension uses context menu API which is only enabled in DevChannel.
You need to use Chrome from [DevChannel](http://www.chromium.org/getting-involved/dev-channel).

On XCode, add Google Chrome as a custom executable then use "Build and Run" for debug this extension on "OpenWithDefault" Target, or just select "Google Chrome" Target and build it. You can run Chrome with experimental api.

Open URL with Default Application
---------------------------------
Use Launch Service to open URL with the default application which user select for opening URL.
See [Launch Service Reference](http://developer.apple.com/mac/library/documentation/Carbon/Reference/LaunchServicesReference/Reference/reference.html).

Security Risk
-------------
Use this extension AT YOUR OWN RISK, WE MAKE NO WARRANTY.
