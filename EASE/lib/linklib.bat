:: Use these batch commands to create symbolic links to EAS-E library files
:: Paths in this batch file should be edited to match your installation folders
:: All EAS-E applications need the following two links
mklink easlib.h C:\EASE\lib\easlib.h
mklink easlib.cpp C:\EASE\lib\easlib.cpp
:: Applications that use EAS-E SET capability need these two
mklink easeSets.h C:\EASE\lib\easeSets.h
mklink easeSets.cpp C:\EASE\lib\easeSets.cpp
:: Applications that use persistence need these two
mklink comlib.h C:\EASE\lib\comlib
mklink comlib.cpp C:\EASE\lib\comlib.cpp
