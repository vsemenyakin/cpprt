###--- Overview ---

Console is small testing tool, that may be used for observe registered class hierarchies and for testing objects creation by class name (objects are stores in testing array).


###--- Console commands ---

You may use next commands with console:


**help**
Command, that print overview of all console possible commands

**print ({-c}) ({class-name})**
If no arguments provided - print all created objects.
With -c flag (optionaly) this command may be used for printing registered classes. If just flag provided, all class hierarhies will be printed.
If class name provided with {class-name} argument after -c flag - printing just this class children hierarhy.

**create {class-name} {object-name}**
Creates object with name {object-name} and type {class-name}, that stores in testing array.

**delete {object-name}**
Removes an object with provided name
