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
    ref array<ref KRJ_KeyCardCargoConfig> cargo;

    void KRJ_KeyCardRewardConfig()
    {
        attachments = new array<ref KRJ_KeyCardRewardConfig>;
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

    protected void AddAttachments(EntityAI parent, ref array<ref KRJ_KeyCardRewardConfig> attachments)
    {
        if (!parent || !attachments)
            return;

        foreach (ref KRJ_KeyCardRewardConfig attachment : attachments)
        {
            if (!attachment || attachment.className == "")
                continue;

            EntityAI attachmentObject = parent.GetInventory().CreateAttachment(attachment.className);
            if (attachmentObject)
                AddAttachments(attachmentObject, attachment.attachments);
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

        AddAttachments(rewardObject, reward.attachments);
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

modded class Land_KlimaX_T1Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddTierLoot(crate, "Land_KlimaX_T1Door");
    }
}

modded class Land_KlimaX_T2Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddTierLoot(crate, "Land_KlimaX_T2Door");
    }
}

modded class Land_KlimaX_T3Door
{
    override void AddLoot(EntityAI crate)
    {
        KRJ_KeyCardRewardManager.GetInstance().AddTierLoot(crate, "Land_KlimaX_T3Door");
    }
}
