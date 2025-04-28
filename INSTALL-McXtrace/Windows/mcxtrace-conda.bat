@mkdir %USERPROFILE%\AppData\Roaming\micromamba
@cd %USERPROFILE%\AppData\Roaming\micromamba
@echo Downloading latest micromamba
@set URL=https://github.com/mamba-org/micromamba-releases/releases/latest/download/micromamba-win-64
@curl -L -o micromamba.exe %URL%
@echo Requesting init of micromamba on the shell
.\micromamba.exe shell init --shell cmd.exe
.\micromamba.exe shell hook -s cmd.exe
.\micromamba config append channels conda-forge
.\micromamba config set channel_priority strict
.\micromamba.exe create -n mcxtrace mcxtrace -y

echo start %USERPROFILE%\AppData\Roaming\mamba\condabin\micromamba activate mcxtrace > %USERPROFILE%\Desktop\mcxtrace-shell-conda.bat
