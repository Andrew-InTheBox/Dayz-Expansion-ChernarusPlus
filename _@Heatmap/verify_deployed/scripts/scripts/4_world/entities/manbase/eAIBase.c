#ifdef SERVER
modded class eAIBase
{
    protected float m_HeatmapTime = float.MAX;
    protected ref array<vector> m_AIWayPoints;

    override void OnSelectPlayer()
    {
        super.OnSelectPlayer();

        if ( GetGame().IsDedicatedServer() )
        {
            m_AIWayPoints = new array<vector>;

            HeatmapData.CURRENT_HEATMAP.m_AIWayPoints.Insert( m_AIWayPoints );
        }
    }

    override void OnScheduledTick( float deltaTime )
    {
        super.OnScheduledTick( deltaTime );

        if( !m_AIWayPoints || !IsPlayerSelected() || !IsAlive() )
        {
            return;
        }

        m_HeatmapTime += deltaTime;
        if ( ( m_HeatmapTime >= g_Game.HEATMAP_TICK_TIME_VEHICLE && IsInVehicle() ) ||  m_HeatmapTime >= g_Game.HEATMAP_TICK_TIME )
        {
            m_AIWayPoints.Insert( GetWaypoint() );

            m_HeatmapTime = 0.0;
        }
    }

    override void EEKilled( Object killer )
    {
        super.EEKilled( killer );

        if ( m_AIWayPoints )
        {
            m_AIWayPoints.Insert( GetWaypoint() );
            HeatmapData.CURRENT_HEATMAP.m_AIDeathPoints.Insert( GetWaypoint() );
        }
    }

    override vector GetWaypoint()
    {
        vector waypoint = GetPosition();

        waypoint[1] = GetGame().GetTime() / 1000;

        return waypoint;
    }
}
#endif