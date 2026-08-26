class KeyCard_Door_Base : Building 
{
    protected int m_KeyCardTier;

    void KeyCard_Door_Base()
    {
        m_KeyCardTier = GetDefaultKeyCardTier();
        RegisterNetSyncVariableInt("m_KeyCardTier", 1, 3);
    }

    protected int GetDefaultKeyCardTier()
    {
        string doorType = GetType();
        if (doorType == "Land_KlimaX_T2Door")
            return 2;
        if (doorType == "Land_KlimaX_T3Door")
            return 3;

        return 1;
    }

    void SetKeyCardTier(int tier)
    {
        if (tier < 1 || tier > 3)
            tier = GetDefaultKeyCardTier();

        m_KeyCardTier = tier;
        SetSynchDirty();
    }

    int GetKeyCardTier()
    {
        if (m_KeyCardTier < 1 || m_KeyCardTier > 3)
            return GetDefaultKeyCardTier();

        return m_KeyCardTier;
    }

    void Open( int index );
    void InitiateClose( int index );
    void Close( int index );
};

class Land_KlimaX_T1Door : KeyCard_Door_Base {};
class Land_KlimaX_T2Door : KeyCard_Door_Base {};
class Land_KlimaX_T3Door : KeyCard_Door_Base {};
