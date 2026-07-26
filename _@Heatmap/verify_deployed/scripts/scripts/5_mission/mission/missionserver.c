#ifdef SERVER
modded class MissionServer
{
    static const string HEATMAP_PROFILE_FOLDER = "$profile:Heatmap";
    protected float m_AutosaveTimer = 0;
    static const float AUTOSAVE_INTERVAL = 120; // 2 minutes in seconds
    protected string m_SessionFileName = "";

    override void OnInit()
    {
        super.OnInit();

        if (!FileExist(HEATMAP_PROFILE_FOLDER))
        {
            MakeDirectory(HEATMAP_PROFILE_FOLDER);
        }

        // Create session filename on startup
        int year, month, day, hour, minute, second;
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);
        second = GetGame().GetTime() % 60;

        m_SessionFileName = HEATMAP_PROFILE_FOLDER + "/session_" + year + "-" + month + "-" + day + "_" + hour + "-" + minute + "-" + second + "_Heatmap.json";
        Print("[Heatmap] Initialized - Session file: " + m_SessionFileName);
        Print("[Heatmap] Autosaving every " + AUTOSAVE_INTERVAL + " seconds");
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        m_AutosaveTimer += timeslice;
        if (m_AutosaveTimer >= AUTOSAVE_INTERVAL)
        {
            m_AutosaveTimer = 0;
            SaveHeatmapData();
            Print("[Heatmap] Auto-saved heatmap data");
        }
    }

    override void OnMissionFinish()
    {
        super.OnMissionFinish();
        Print("[Heatmap] Saving heatmap data...");
        SaveHeatmapData();
        Print("[Heatmap] Data saved successfully to: " + m_SessionFileName);
    }

    private void SaveHeatmapData()
    {
        if (m_SessionFileName != "")
        {
            JsonFileLoader<HeatmapData>.JsonSaveFile(m_SessionFileName, HeatmapData.CURRENT_HEATMAP);
        }
    }
}
#endif