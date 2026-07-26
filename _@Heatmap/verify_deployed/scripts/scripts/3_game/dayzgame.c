#ifdef SERVER
modded class DayZGame
{
    static float HEATMAP_TICK_TIME = 2.0 * 60;
    static float HEATMAP_TICK_TIME_VEHICLE = 30.0;

    override void GlobalsInit()
    {
        super.GlobalsInit();

        int ticktime = GetGame().ServerConfigGetInt( "heatmapTickTime" );
        if ( ticktime != 0 )
        {
            HEATMAP_TICK_TIME = ticktime;
        }
		ticktime = GetGame().ServerConfigGetInt( "heatmapTickTimeVehicle" );
        if ( ticktime != 0 )
        {
            HEATMAP_TICK_TIME_VEHICLE = ticktime;
        }
    }
}
#endif