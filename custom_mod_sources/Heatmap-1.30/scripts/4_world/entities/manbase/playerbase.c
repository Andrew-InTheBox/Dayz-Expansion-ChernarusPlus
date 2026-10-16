#ifdef SERVER
modded class PlayerBase
{
    protected float m_HeatmapTime = float.MAX;
    protected ref array<vector> m_WayPoints;

    override void OnSelectPlayer()
    {
        super.OnSelectPlayer();

        if ( GetGame().IsDedicatedServer() )
        {
            m_WayPoints = new array<vector>;

            HeatmapData.CURRENT_HEATMAP.m_WayPoints.Insert( m_WayPoints );
        }
    }

    override void OnScheduledTick( float deltaTime )
    {
        super.OnScheduledTick( deltaTime );

        if( !m_WayPoints || !IsPlayerSelected() || !IsAlive() )
        {
            return;
        }

        m_HeatmapTime += deltaTime;
        if ( ( m_HeatmapTime >= g_Game.HEATMAP_TICK_TIME_VEHICLE && IsInVehicle() ) ||  m_HeatmapTime >= g_Game.HEATMAP_TICK_TIME )
        {
            m_WayPoints.Insert( GetWaypoint() );

            m_HeatmapTime = 0.0;
        }
    }

    override void EEKilled( Object killer )
    {
        super.EEKilled( killer );

        if ( m_WayPoints )
        {
            m_WayPoints.Insert( GetWaypoint() );
            HeatmapData.CURRENT_HEATMAP.m_DeathPoints.Insert( GetWaypoint() );
        }
    }

    vector GetWaypoint()
    {
        vector waypoint = GetPosition();

        waypoint[1] = GetGame().GetTime() / 1000;

        return waypoint;
    }
}
#endif