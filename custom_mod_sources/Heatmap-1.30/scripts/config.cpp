////////////////////////////////////////////////////////////////////
//DeRap: scripts\config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Wed Oct 01 21:38:39 2025 : 'file' last modified on Wed Oct 01 19:26:05 2025
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Heatmap
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts"};
	};
};
class CfgMods
{
	class Heatmap
	{
		name = "Heatmap";
		dir = "Heatmap/scripts";
		credits = "";
		author = "affenb3rt";
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"Heatmap/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"Heatmap/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"Heatmap/scripts/5_Mission"};
			};
		};
	};
};
