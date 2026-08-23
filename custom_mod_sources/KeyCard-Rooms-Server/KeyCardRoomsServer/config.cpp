class CfgPatches
{
    class KRJ_KeyCardRoomsServer
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"KeyCardSystemServerConfig"};
    };
};

class CfgMods
{
    class KRJ_KeyCardRoomsServer
    {
        name = "KRJ KeyCard Rooms Server";
        type = "mod";
        dependencies[] = {"World"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"KRJ_KeyCardRoomsServer/4_World"};
            };
        };
    };
};
