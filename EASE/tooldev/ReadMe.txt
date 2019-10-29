Note:

Renaming Visual Studio projects is somewhat complicated; therefore:

EAS0002 is the Visual Studio development project for EASEdevelop
 - it is MFC application with no EAS-E source code components

ExpTran is the development project for EASEtranslate
 - it is almost entirely EAS-E source code from toolsrc\NEWTRAN
 - it has an MFC dialog for choice of project to translate 

ConsoleApplication1 is the project for the persistence server
 - it has EAS-E components for allocating file storage 
 - the EAS-E source is the ESERVER project in toolsrc

When these projects are built the executables are copied to tools and renamed