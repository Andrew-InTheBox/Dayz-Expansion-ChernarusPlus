modded class PluginKeyCardSystemServer
{
    override bool StaticItemsSpawn()
    {
        super.StaticItemsSpawn();

        // Always spawn just the structures a configured door actually needs:
        // the building shell it sits in/on, and any door-specific side panels.
        // No decorative/filler objects (logs, roadblocks, extra plates, etc.)
        // regardless of disableMapEditsPreset - those add clutter with nothing
        // to do with the door setups in config.json.
        SpawnRoomStructures();
        SpawnDoorPanels();

        return true;
    }

    private void SpawnRoomStructures()
    {
        SpawnObject( "Land_Mil_Barracks2", "2488.370117 194.725006 5075.779785", "-32.998474 0.000000 0.000000" );
        SpawnObject( "Land_Barn_Brick1", "6039.250000 272.399994 10398.000000", "31.999216 0.076935 -0.118628" );
        SpawnObject( "Land_Mil_AircraftShelter", "1768.829956 450.200012 14024.000000", "83.991737 0.000000 -0.000000" );
        SpawnObject( "Land_Mil_Barracks1", "2835.449951 272.670013 9748.820313", "54.001255 2.998346 -0.175660" );
        SpawnObject( "Land_Workshop2", "9845.169922 284.500000 8709.179688", "173.998520 0.230806 0.744274" );
        SpawnObject( "Land_Shed_M1", "7816.589844 141.199997 12410.299805", "1.000209 0.000000 -0.000000" );
        SpawnObject( "Land_Shed_M3", "7622.680176 215.992996 5202.419922", "90.261948 1.528395 -0.685703" );
    }

    // Per-door decorative panels, driven entirely by each location's optional
    // "panels" array in config.json. Add/remove/move a door's panels there -
    // no source change or rebuild needed. A location with no "panels" array
    // (like the "odd one out" door built into an existing vanilla building)
    // simply gets none.
    private void SpawnDoorPanels()
    {
        foreach ( ref SecurityDoorLocationConfig locationConfig : m_config.locations )
        {
            ref array< ref SecurityDoorPanelConfig > panels = locationConfig.GetPanels();
            if ( !panels )
                continue;

            foreach ( ref SecurityDoorPanelConfig panel : panels )
                SpawnObject( panel.className, panel.position, panel.orientation );
        }
    }

    private void SpawnObject(string objType, vector objPos, vector objOrientation)
    {
        Object m_Building = Object.Cast(GetGame().CreateObject(objType, objPos));
        if (m_Building == null) return;
        m_Building.SetAffectPathgraph(true, false);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, m_Building);
        m_Building.SetPosition(objPos);
        m_Building.SetOrientation(objOrientation);
    }


}
