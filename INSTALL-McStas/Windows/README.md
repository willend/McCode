# Installation of McStas 3.5.27 on Windows 64 bit systems

* Please either of **IMPORTANT: active internet connection required during installation** 
  * Use the [mcstas-conda](mcstas-conda.bat) batch script to install
    the latest mcstas from `conda-forge` (**recommended**). You need
    to manually install [c/c++ support in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170#download-and-install-the-tools)
  * install the legacy MinGW based [McStas 3.5.27 metapackage](https://download.mcstas.org/mcstas-3.5.27/Windows/McStas-Metapackage-3.5.27-win64.exe)
 
* An alternative to installing this cross-compiled verison is to follow the instructions
posted under [WSL](WSL/README.md) to install the "Windows subsystem for Linux" and run the Debian binaries there
* Or manually install from [conda-forge](../conda/README.md)

## Internet access required:
* If you are behind a proxy server, please use the commands
	```bash
		set HTTP_PROXY=http://your_proxy_ip:port
	```
	```bash
		set HTTPS_PROXY=https://your_proxy_ip:port
	```
in a cmd.exe shell and start the McStas installer from there	

## In case of issues
Please report any trouble with the repository to [mcstas-users](mailto:mcstas-users@mcstas.org)

