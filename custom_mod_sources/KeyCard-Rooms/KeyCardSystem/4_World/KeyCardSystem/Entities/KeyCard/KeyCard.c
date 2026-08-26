class KeyCard_ParentBase : ItemBase {
    int GetKeyCardTier() {
        return 0;
    }

    bool CanAuthorizeDoor( KeyCard_Door_Base door ) {
        if (!door)
            return false;

        return GetKeyCardTier() == door.GetKeyCardTier();
    }
};

class RedemptionKeyCard_01 : KeyCard_ParentBase {
    override int GetKeyCardTier() {
        return 1;
    }
};
class RedemptionKeyCard_02 : KeyCard_ParentBase {
    override int GetKeyCardTier() {
        return 2;
    }
};
class RedemptionKeyCard_03 : KeyCard_ParentBase {
    override int GetKeyCardTier() {
        return 3;
    }
};
