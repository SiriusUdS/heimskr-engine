# heimskr-engine

### Requirements
- Doxygen (https://www.doxygen.nl/download.html)
- Premake5 if you plan to change the premake5.lua file for regenerating the solution
- Visual Studio 2022

### Solution setup
1. Clone the repository.
2. Execute the `setup.bat` script in the **setup** folder.
3. Open the **heimskr-engine.sln** solution in Visual Studio 2022.
4. Build then run.

### Documentation
For the code documentation, you have 2 choices at the moment:
1. Build the solution in Visual Studio then open the `index.html` file in the **doc/html** folder from the project root folder.
2. Open a terminal inside dthe root folder of the project, then run `doxygen Doxyfile`. The documentation will be in the **doc/html** folder from the project root folder.
