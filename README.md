# CandCPP-Learning
My C and C++ learning memo and corresponding setting, 
such as visual studio code setting both on windows and ubuntu


There are two config sets of visual studio code for window and ubuntu,
.vscode_window and .vscode_ubuntu, you can create a soft link to the
corresponding right config on according OS, for example on Ubuntu:
--> ln -s .vscode_ubuntu .vscode

And there are some common vscode setting, such as kebindings.json,
define some shortcut for cmake, build, run tasks defined in tasks.json
You need to copy it into corresponding dir of vscode according OS,
For the details, you can refer to the vscode keybinding reference:
https://code.visualstudio.com/docs/getstarted/keybindings


The initial version is experience of some basic feature about C and C++,
Providing the CmakeLists for using Cmake as the Make control tools,
And use MinGW64(install by msys2) on windows, gcc make on ubuntu,
Hence there are two different CmakeLists file for each OS, 
In practice, you need create a soft link to the right CmakeLists.


Integrate google-test and google-mock as the testing framework,
To use gtest and gmock need to compile gtest from its source,
and copy the related header files and generated libs into
include directory and lib directory in related OS,
you can refer the CmakeLists file for details
