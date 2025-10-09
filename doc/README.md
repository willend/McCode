## This is the documentation directory of McStas

It contains the User and Component Manuals.
Additionally, the `mcdoc` tool may be used with the syntax:

```
usage: mcdoc [-h] [--install] [--dir DIR] [--manual] [--comps] [--web] [--verbose] [searchterm]

Generates html docpages from mccode instrument and component files. A docpage is generated for every instrument and component file, and an overview page is written and browsed. Default option Read installed docpage. Specify a directory to add local
results, and a search term for filtered or specific file results.

positional arguments:
  searchterm         search filter or .instr/.comp file

options:
  -h, --help         show this help message and exit
  --install, -i      generate installation master doc page
  --dir DIR, -d DIR  add search results from this directory
  --manual, -m       open the system manual
  --comps, -c        open the component manual
  --web, -w          open the mcstas website
  --verbose, -v      prints a parsing log during execution
```
For instance, to access the McStas web site, type:

  `mcdoc --web`

To access the McStas User Manual, type

  `mcdoc --manual`

To browse the component library, type

  `mcdoc`

Finally, to display the help for a single component, type for instance

  `mcdoc Guide.comp`

Via the `mcrun --edit-user-config` hook you may configure which BROWSER is used by e.g. mcdoc. 
(A reasonable default has been provided for your platform.)

The list of available McStas Tools is:
* `mcstas` - Main instrument compiler
* `mcrun` - Instrument maker and execution utility
* `mcgui` - Graphical User Interface instrument builder
* `mcdoc` - Component library documentation generator/viewer
* `mcplot` - Simulation result viewer
* `mcdisplay` - Instrument geometry viewer
* `mcresplot` - Instrument resolution function viewer

When used with the `-h` flag, all tools display a specific help.

Please also consult our wiki found at
https://github.com/mccode-dev/McCode/wiki

