# Install chocolatey
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
refreshenv

# Install oh-my-posh dependency
Install-Module -Name posh-git -RequiredVersion 0.7.1
refreshenv

# Install dev environment for C, C++, Java8, JavaLatest, Node, Python and other languages with VS Code
choco install -y git.install --params "/GitAndUnixToolsOnPath" googlechrome mingw ojdkbuild8 ojdkbuild vscode nvm postgresql --params "/Password:" --params-global winrar revo-uninstaller python
