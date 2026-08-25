class KRJ_KeyCardCargoConfig
{
    string className;
    int count;
}

class KRJ_KeyCardRewardConfig
{
    string className;
    float chance;
    ref array<ref KRJ_KeyCardRewardConfig> attachments;
    float randomAttachmentChance;
    ref array<ref KRJ_KeyCardRewardConfig> randomAttachments;
    ref array<ref KRJ_KeyCardCargoConfig> containerCargo;
    ref array<ref KRJ_KeyCardCargoConfig> cargo;

    void KRJ_KeyCardRewardConfig()
    {
        attachments = new array<ref KRJ_KeyCardRewardConfig>;
        randomAttachmentChance = 0;
        randomAttachments = new array<ref KRJ_KeyCardRewardConfig>;
        containerCargo = new array<ref KRJ_KeyCardCargoConfig>;
        cargo = new array<ref KRJ_KeyCardCargoConfig>;
    }
}

class KRJ_KeyCardTierConfig
{
    string doorClassName;
    int randomRewardCount;
    ref array<ref KRJ_KeyCardRewardConfig> randomRewards;
    ref array<ref KRJ_KeyCardRewardConfig> fixedRewards;

    void KRJ_KeyCardTierConfig()
    {
        randomRewardCount = 1;
        randomRewards = new array<ref KRJ_KeyCardRewardConfig>;
        fixedRewards = new array<ref KRJ_KeyCardRewardConfig>;
    }
}

class KRJ_KeyCardRewardsConfig
{
    int version;
    ref array<ref KRJ_KeyCardTierConfig> tiers;

    void KRJ_KeyCardRewardsConfig()
    {
        version = 1;
        tiers = new array<ref KRJ_KeyCardTierConfig>;
    }
}

modded class SecurityDoorLocationConfig
{
    // Optional logical reward tier, independent of the physical door class.
    // Supported values are T1, T2, and T3. Empty preserves vendor behavior.
    string rewardTier;

    string KRJ_GetRewardTier()
    {
        return rewardTier;
    }
}

class KRJ_KeyCardRewardManager
{
    protected static ref KRJ_KeyCardRewardManager s_Instance;
    protected static const string CONFIG_DIR = "$profile:KeyCardRoomsCompanion";
    protected static const string CONFIG_FILE = CONFIG_DIR + "/rewards.json";
    protected ref KRJ_KeyCardRewardsConfig m_Config;

    static KRJ_KeyCardRewardManager GetInstance()
    {
        if (!s_Instance)
            s_Instance = new KRJ_KeyCardRewardManager();

        return s_Instance;
    }

    void KRJ_KeyCardRewardManager()
    {
        LoadConfig();
    }

    protected void LoadConfig()
    {
        m_Config = new KRJ_KeyCardRewardsConfig();

        if (!FileExist(CONFIG_DIR))
            MakeDirectory(CONFIG_DIR);

        if (FileExist(CONFIG_FILE))
        {
            JsonFileLoader<ref KRJ_KeyCardRewardsConfig>.JsonLoadFile(CONFIG_FILE, m_Config);
        }
        else
        {
            JsonFileLoader<ref KRJ_KeyCardRewardsConfig>.JsonSaveFile(CONFIG_FILE, m_Config);
            Print("[KRJ KeyCard Rooms] Created empty reward config: " + CONFIG_FILE);
        }
    }

    protected ref KRJ_KeyCardTierConfig FindTier(string doorClassName)
    {
        if (!m_Config || !m_Config.tiers)
            return NULL;

        foreach (ref KRJ_KeyCardTierConfig tier : m_Config.tiers)
        {
            if (tier && tier.doorClassName == doorClassName)
                return tier;
        }

        return NULL;
    }

    protected string NormalizeRewardTier(string rewardTier, string fallbackDoorClass)
    {
        if (rewardTier == "T1")
            return "Land_KlimaX_T1Door";
        if (rewardTier == "T2")
            return "Land_KlimaX_T2Door";
        if (rewardTier == "T3")
            return "Land_KlimaX_T3Door";

        return fallbackDoorClass;
    }

    protected string FindDoorRewardTier(KeyCard_Door_Base door)
    {
        if (!door)
            return "";

        string fallbackDoorClass = door.GetType();
        PluginKeyCardSystemServer plugin = PluginKeyCardSystemServer.Cast(GetPlugin(PluginKeyCardSystemServer));
        if (!plugin || !plugin.m_config || !plugin.m_config.locations)
            return fallbackDoorClass;

        vector doorPosition = door.GetPosition();
        foreach (ref SecurityDoorLocationConfig locationConfig : plugin.m_config.locations)
        {
            if (!locationConfig)
                continue;

            if (vector.Distance(locationConfig.GetPosition(), doorPosition) <= 0.1)
                return NormalizeRewardTier(locationConfig.KRJ_GetRewardTier(), fallbackDoorClass);
        }

        return fallbackDoorClass;
    }

    protected void AddCargo(EntityAI crate, ref array<ref KRJ_KeyCardCargoConfig> cargo)
    {
        if (!cargo)
            return;

        foreach (ref KRJ_KeyCardCargoConfig cargoItem : cargo)
        {
            if (!cargoItem || cargoItem.className == "")
                continue;

            int itemCount = cargoItem.count;
            if (itemCount < 1)
                itemCount = 1;

            for (int itemIndex = 0; itemIndex < itemCount; itemIndex++)
                crate.GetInventory().CreateInInventory(cargoItem.className);
        }
    }

    protected void AddAttachment(EntityAI parent, EntityAI fallbackCrate, ref KRJ_KeyCardRewardConfig attachment)
    {
        if (!parent || !attachment || attachment.className == "")
            return;

        EntityAI attachmentObject;
        ItemBase parentItem;

        // Expansion's wrapper handles weapon magazines specially: it creates
        // them in InventorySlots.MAGAZINE, restores the correct weapon FSM
        // state, chambers a round, and synchronizes the weapon.
        if (Class.CastTo(parentItem, parent))
            attachmentObject = parentItem.ExpansionCreateAttachment(attachment.className);
        else
            attachmentObject = parent.GetInventory().CreateAttachment(attachment.className);
        if (attachmentObject)
        {
            AddAttachments(attachmentObject, fallbackCrate, attachment.attachments);
            AddRandomAttachment(attachmentObject, fallbackCrate, attachment);
        }
        else
        {
            Print("[KRJ KeyCard Rooms] Could not attach " + attachment.className + " to " + parent.GetType() + "; spawning it loose in the reward crate");
            if (fallbackCrate)
                fallbackCrate.GetInventory().CreateInInventory(attachment.className);
        }
    }

    protected void AddAttachments(EntityAI parent, EntityAI fallbackCrate, ref array<ref KRJ_KeyCardRewardConfig> attachments)
    {
        if (!parent || !attachments)
            return;

        foreach (ref KRJ_KeyCardRewardConfig attachment : attachments)
            AddAttachment(parent, fallbackCrate, attachment);
    }

    protected void AddRandomAttachment(EntityAI parent, EntityAI fallbackCrate, ref KRJ_KeyCardRewardConfig reward)
    {
        if (!parent || !reward || !reward.randomAttachments || reward.randomAttachments.Count() == 0)
            return;

        float groupChance = reward.randomAttachmentChance;
        if (groupChance <= 0 || Math.RandomFloat01() > groupChance)
            return;

        float totalChance = 0;
        foreach (ref KRJ_KeyCardRewardConfig candidateForTotal : reward.randomAttachments)
        {
            if (candidateForTotal && candidateForTotal.className != "" && candidateForTotal.chance > 0)
                totalChance += candidateForTotal.chance;
        }

        if (totalChance <= 0)
            return;

        float selectedChance = Math.RandomFloat(0, totalChance);
        float chanceCounter = 0;
        foreach (ref KRJ_KeyCardRewardConfig candidate : reward.randomAttachments)
        {
            if (!candidate || candidate.className == "" || candidate.chance <= 0)
                continue;

            chanceCounter += candidate.chance;
            if (selectedChance <= chanceCounter)
            {
                AddAttachment(parent, fallbackCrate, candidate);
                return;
            }
        }
    }

    protected void SpawnReward(EntityAI crate, ref KRJ_KeyCardRewardConfig reward)
    {
        if (!reward || reward.className == "")
            return;

        EntityAI rewardObject = crate.GetInventory().CreateInInventory(reward.className);
        if (!rewardObject)
        {
            Print("[KRJ KeyCard Rooms] Could not spawn reward " + reward.className);
            return;
        }

        AddAttachments(rewardObject, crate, reward.attachments);
        AddRandomAttachment(rewardObject, crate, reward);
        AddCargo(rewardObject, reward.containerCargo);
        AddCargo(crate, reward.cargo);
    }

    protected void AddFixedRewards(EntityAI crate, ref array<ref KRJ_KeyCardRewardConfig> rewards)
    {
        if (!rewards)
            return;

        foreach (ref KRJ_KeyCardRewardConfig reward : rewards)
            SpawnReward(crate, reward);
    }

    protected void AddRandomRewards(EntityAI crate, ref array<ref KRJ_KeyCardRewardConfig> rewards, int rewardCount)
    {
        if (!rewards || rewards.Count() == 0 || rewardCount < 1)
            return;

        ref array<ref KRJ_KeyCardRewardConfig> availableRewards = new array<ref KRJ_KeyCardRewardConfig>;
        foreach (ref KRJ_KeyCardRewardConfig availableReward : rewards)
        {
            if (availableReward && availableReward.chance > 0)
                availableRewards.Insert(availableReward);
        }

        int rolls = rewardCount;
        if (rolls > availableRewards.Count())
            rolls = availableRewards.Count();

        for (int rollIndex = 0; rollIndex < rolls; rollIndex++)
        {
            float totalChance = 0;
            foreach (ref KRJ_KeyCardRewardConfig rewardForTotal : availableRewards)
                totalChance += rewardForTotal.chance;

            if (totalChance <= 0)
                return;

            float selectedChance = Math.RandomFloat(0, totalChance);
            float chanceCounter = 0;
            for (int rewardIndex = 0; rewardIndex < availableRewards.Count(); rewardIndex++)
            {
                ref KRJ_KeyCardRewardConfig reward = availableRewards[rewardIndex];
                chanceCounter += reward.chance;
                if (selectedChance <= chanceCounter)
                {
                    SpawnReward(crate, reward);
                    availableRewards.Remove(rewardIndex);
                    break;
                }
            }
        }
    }

    void AddTierLoot(EntityAI crate, string doorClassName)
    {
        ref KRJ_KeyCardTierConfig tier = FindTier(doorClassName);
        if (!tier)
        {
            Print("[KRJ KeyCard Rooms] No reward tier configured for " + doorClassName);
            return;
        }

        AddFixedRewards(crate, tier.fixedRewards);
        int randomRewardCount = tier.randomRewardCount;
        if (randomRewardCount < 1)
            randomRewardCount = 1;

        AddRandomRewards(crate, tier.randomRewards, randomRewardCount);
    }

    void AddDoorLoot(EntityAI crate, KeyCard_Door_Base door)
    {
        AddTierLoot(crate, FindDoorRewardTier(door));
    }
}

modded class KeyCard_Door_Base
{
    override void Open(int index)
    {
        OpenDoor(index);
        m_persistanceData.SetIsOpen(index, true);
        SetTimeTillAutoClose(index, m_persistanceData.GetAutoCloseTime() * 1000);
        SpawnRewards();
    }

    override void InitiateClose(int index)
    {
        float delay = m_persistanceData.GetCloseDelay();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Close, delay * 1000, false, index);
        m_IsClosing = true;
    }
}

modded class PluginKeyCardSystemServer
{
    override void StaticItemsSpawn()
    {
        super.StaticItemsSpawn();

        // The vendor preset references obsolete vbldr aircraft-door classes.
        // Fill both sides of the T3 hangar entrance with current BuilderItems tin walls.
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1746.386371 450.300011 14015.495815", "83.003548 0 0");
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1746.386371 452.300011 14015.495815", "83.003548 0 0");
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1746.386371 454.300011 14015.495815", "83.003548 0 0");
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1745.143659 450.300012 14027.404575", "83.003494 0 0");
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1745.143659 452.300012 14027.404575", "83.003494 0 0");
        KRJ_SpawnStaticObject("bldr_wall_tin_5", "1745.143659 454.300012 14027.404575", "83.003494 0 0");
    }

    protected void KRJ_SpawnStaticObject(string className, vector position, vector orientation)
    {
        Object object = GetGame().CreateObject(className, position);
        if (!object)
        {
            Print("[KRJ KeyCard Rooms] Could not spawn static filler " + className + " at " + position);
            return;
        }

        object.SetAffectPathgraph(true, false);
        object.SetPosition(position);
        object.SetOrientation(orientation);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, object);
    }
}

modded class Land_KlimaX_T1Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddDoorLoot(crate, this);
    }
}

modded class Land_KlimaX_T2Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddDoorLoot(crate, this);
    }
}

modded class Land_KlimaX_T3Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddDoorLoot(crate, this);
    }
}
