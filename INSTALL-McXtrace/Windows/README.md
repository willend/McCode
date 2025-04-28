# Installation of McXtrace 3.5.27 on Windows 64 bit systems

* Please either of:
  1. **Recommended:**
    * Install [Visual Studio including c/c++ support](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170#download-and-install-the-tools) (Any version of Visual Studio itself should do. Please install at minumum "Desktop development with c++" selecting VS2019 build tools. You can also use newer VS2022 build tools, but VS2019 must be present also.
	* Use the [mcxtrace-conda](mcxtrace-conda.bat) batch script to install the latest mcxtrace from `conda-forge` 
  2. **Legacy:**
    * install the legacy-style MinGW based [McXtrace 3.5.27 metapackage](https://download.mcxtrace.org/mcxtrace-3.5.27/Windows/McXtrace-Metapackage-3.5.27-win64.exe) - now includes MCPL. Option 2 is also functional on `arm64` processors.
  3. **WSL:**
    * Use the directions available in [WSL](WSL/README.md) to install the "Windows subsystem for Linux" and run the Linux Debian binaries there.  Option 3 is also functional on `arm64` processors.
 
If you are `conda-forge` knowledgable already, you may also simply install a new environment as explained in [conda-forge](../conda/README.md)

## Internet access required:
* If you are behind a proxy server, please use the commands
	```bash
		set HTTP_PROXY=http://your_proxy_ip:port
	```
	```bash
		set HTTPS_PROXY=https://your_proxy_ip:port
	```
in a cmd.exe shell and start the McXtrace installer from there	

## In case of issues
Please report any trouble with the repository to [mcxtrace-users](mailto:mcxtrace-users@mcxtrace.org)

