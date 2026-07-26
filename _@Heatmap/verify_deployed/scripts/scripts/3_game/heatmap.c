#ifdef SERVER
class HeatmapData
{
    static ref HeatmapData CURRENT_HEATMAP = new HeatmapData();

    ref array<ref array<vector>> m_WayPoints = new array<ref array<vector>>;
    ref array<ref array<vector>> m_AIWayPoints = new array<ref array<vector>>;
    ref array<vector> m_DeathPoints = new array<vector>;
    ref array<vector> m_ZombiePoints = new array<vector>;
    ref array<vector> m_AIDeathPoints = new array<vector>;

    private void HeatmapData()
    {
    }
}
#endif