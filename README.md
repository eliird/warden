# WARDEN: Lightweight Environment Manager For Python

# Motivation

Automate the environment creation for python using `venv` library similar to the conda but with no additional overheads.
Warden can be used to:
    - create an environment 
    - install and uninstall packages to that environment
    - run python scripts from that environment.

# Installation

## Linux
    ```
    git clone https://github.com/eliird/warden
    ./build.sh
    ./install.sh
    ```

## Windows
Easy Method:
    Place the `warden.exe` file in a cloned folder which is include in the environment path variable.

Building From Source:
    - Clone the directory `git clone https://github.com/eliird/warden`
    
    - You need a terminal which can run cmake like `Developer Powershell for Vscode`.
    - Navigate to the cloned folder in the terminal.
    - Run the build.bat file.
    - This will generate a `warden.exe` file in the cloned folder.
    - Place the executable in a folder that is in environment path variable or add it to the environment path.
    - You can also place it in the project directory and use it from there to maintain the environment.



# Usage

## setup

Creates a new environment in the directory the command is run from.
You can also give this environment a name.
If there is a `requirements.txt` available, it automatically installs all the listed packages in the environment.

```

> warden setup

> warden setup env_name

```

## install

This command can be used to install additional packages to the environment.

```
warden install numpy==1.21

warden install matplotlib

```

## update

This command can be used to upgrade the pip to the latest version

```

warden update


```

## uninstall

This command can be used to uninstall packages from the environment



```

warden uninstall numpy

```


## run

This command executes the python script with the setup environment

```

warden run main.py

```

This can be executed from the directory where environment was created