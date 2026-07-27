Overall project description

This project is a DayZ server setup.  Configuration files tend to be in /config or /mpmissions/Expansion.chernarusplus.   We are using the core components of a mod called DayZ Expansion which has a set of docs pages at and under this url:  https://github.com/salutesh/DayZ-Expansion-Scripts/wiki

AI aka bot patrols are configured in the file AIPatrolSettings.json located at mpmissions\Expansion.chernarusplus\expansion\settings\AIPatrolSettings.json

The loadouts the patrols wear are located in a folder here and are all json files:  config\ExpansionMod\Loadouts

Many of the xml and json config files are 3000 lines or more, so we shouldn't try to read the whole things into context, but instead try to find relevant sections, or write python scripts to help us work and analyze their contents.

Important: when running python scripts, use the venv here:  C:\Users\andre\venv-dirs\venv-utils.  If needed we can pip install additional libraries into it.