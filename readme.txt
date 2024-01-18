MK2
===========================


Before compiling
===========================
Do `git submodule init` and
`git submodule update` to 
fetch the gnu-efi module.
Not doing this would result
in the project being unbuiltable.

How to compile
===========================
Open a Visual Studio Cross Tools x64 command prompt and 
change to the directory where you cloned.
Then executed `tools\startbldenv.cmd`.
This will close the VS Cross Tools command prompt and open
a new one. Type bld to compile and clr to clean.
When it is compiled, type run to run it in qemu.