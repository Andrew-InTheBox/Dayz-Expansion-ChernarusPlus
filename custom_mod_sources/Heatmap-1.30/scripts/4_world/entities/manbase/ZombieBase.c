#ifdef SERVER
modded class ZombieBase extends DayZInfected
{
    protected float m_HeatmapTime = float.MAX;
	protected ref array<vector> m_WayPoints = new array<vector>;

    override void EEKilled( Object killer )
    {
        super.EEKilled( killer );


            Print("ZombieBase::EEKilled" + GetWaypoint());
            m_WayPoints.Insert( GetWaypoint() );
            HeatmapData.CURRENT_HEATMAP.m_ZombiePoints.Insert( GetWaypoint() );
        
    }

    vector GetWaypoint()
    {
        vector waypoint = GetPosition();

        waypoint[1] = GetGame().GetTime() / 1000;

        return waypoint;
    }
}
#endif