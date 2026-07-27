class Expansion_Vehicles_GoToVehicle_State_0: eAIState_GoToVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GoToVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GoToVehicle_State_0";
		m_Name = "GoToVehicle";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		m_Entity = fsm.entity;
		m_Seat = fsm.seat;
		super.OnEntry(Event, null);
		unit.OverrideMovementDirection(false, 0);
		unit.OverrideMovementSpeed(false, 0);
	}
}
class Expansion_Vehicles_GetInVehicle_State_0: eAIState_GetInVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetInVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetInVehicle_State_0";
		m_Name = "GetInVehicle";
	}
}
class Expansion_Vehicles_GetOutVehicle_State_0: eAIState_GetOutVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetOutVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetOutVehicle_State_0";
		m_Name = "GetOutVehicle";
	}
}
class Expansion_Vehicles_OpenVehicleDoor_State_0: eAIState_OpenVehicleDoor {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor_State_0";
		m_Name = "OpenVehicleDoor";
	}
}
class Expansion_Vehicles_CloseVehicleDoor_State_0: eAIState_CloseVehicleDoor {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_CloseVehicleDoor_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_CloseVehicleDoor_State_0";
		m_Name = "CloseVehicleDoor";
	}
}
class Expansion_Vehicles_Sitting_State_0: eAIState {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_Sitting_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_Sitting_State_0";
		m_Name = "Sitting";
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		return EXIT;
	}
}
class Expansion_Vehicles_GoToVehicle_OpenVehicleDoor_Transition_0: eAITransition {
	private Expansion_Vehicles_GoToVehicle_State_0 src;
	private Expansion_Vehicles_OpenVehicleDoor_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GoToVehicle_OpenVehicleDoor_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GoToVehicle_OpenVehicleDoor_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_GoToVehicle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
	}
	override int Guard() {
		if (vector.DistanceSq(unit.GetPosition(), src.m_Position) > 1.0) return FAIL;
		if (!src.m_Transport.IsAreaAtDoorFree(src.m_Seat)) return FAIL;
		if (src.m_Transport.CrewMember(src.m_Seat) || (src.m_Vehicle.IsSeatReservedByOther(src.m_Seat, unit))) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_GoToVehicle_GoToVehicle_Transition_0: eAITransition {
	private Expansion_Vehicles_GoToVehicle_State_0 src;
	private Expansion_Vehicles_GoToVehicle_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GoToVehicle_GoToVehicle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GoToVehicle_GoToVehicle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_GoToVehicle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_GoToVehicle_State_0"));
	}
	override int Guard() {
		//auto group = unit.GetGroup();
		//if (!group) return FAIL;
		//
		//auto leader = group.GetFormationLeader();
		//if (leader && leader != unit)
		//{
			//	if (!leader.IsInTransport()) return FAIL;
		//}
		if (vector.DistanceSq(unit.GetPosition(), src.m_Position) < 1.0) return FAIL;
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_OpenVehicleDoor_GetInVehicle_Transition_0: eAITransition {
	private Expansion_Vehicles_OpenVehicleDoor_State_0 src;
	private Expansion_Vehicles_GetInVehicle_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor_GetInVehicle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor_GetInVehicle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_GetInVehicle_State_0"));
	}
	override int Guard() {
		if (vector.DistanceSq(unit.GetPosition(), src.m_Position) > 1.0) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		if (!src.m_Transport.CrewCanGetThrough(src.m_Seat) || !src.m_Transport.IsAreaAtDoorFree(src.m_Seat)) return FAIL;
		if (src.m_Transport.CrewMember(src.m_Seat) || (src.m_Vehicle.IsSeatReservedByOther(src.m_Seat, unit))) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_GetInVehicle_CloseVehicleDoor_Transition_0: eAITransition {
	private Expansion_Vehicles_GetInVehicle_State_0 src;
	private Expansion_Vehicles_CloseVehicleDoor_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetInVehicle_CloseVehicleDoor_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetInVehicle_CloseVehicleDoor_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_GetInVehicle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_CloseVehicleDoor_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_Sitting_OpenVehicleDoor_Transition_0: eAITransition {
	private Expansion_Vehicles_Sitting_State_0 src;
	private Expansion_Vehicles_OpenVehicleDoor_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_Sitting_OpenVehicleDoor_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_Sitting_OpenVehicleDoor_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_Sitting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
	}
	override int Guard() {
		if (unit.IsUnconscious()) return FAIL;
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		auto leader = group.GetFormationLeader();
		if (leader && leader != unit)
		{
			if (group.GetFormationState() != eAIGroupFormationState.IN || leader.GetParent() == unit.GetParent())
			return FAIL;
		}
		if (!dst.m_Transport.IsAreaAtDoorFree(dst.m_Seat)) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_OpenVehicleDoor_GetOutVehicle_Transition_0: eAITransition {
	private Expansion_Vehicles_OpenVehicleDoor_State_0 src;
	private Expansion_Vehicles_GetOutVehicle_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor_GetOutVehicle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor_GetOutVehicle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_GetOutVehicle_State_0"));
	}
	override int Guard() {
		if (unit.IsUnconscious()) return FAIL;
		if (!unit.IsInTransport()) return FAIL;
		if (!src.m_Transport.CrewCanGetThrough(src.m_Seat) || !src.m_Transport.IsAreaAtDoorFree(src.m_Seat)) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_GetOutVehicle_CloseVehicleDoor_Transition_0: eAITransition {
	private Expansion_Vehicles_GetOutVehicle_State_0 src;
	private Expansion_Vehicles_CloseVehicleDoor_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetOutVehicle_CloseVehicleDoor_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetOutVehicle_CloseVehicleDoor_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_GetOutVehicle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_CloseVehicleDoor_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_CloseVehicleDoor_Sitting_Transition_0: eAITransition {
	private Expansion_Vehicles_CloseVehicleDoor_State_0 src;
	private Expansion_Vehicles_Sitting_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_CloseVehicleDoor_Sitting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_CloseVehicleDoor_Sitting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_CloseVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_Sitting_State_0"));
	}
	override int Guard() {
		if (!unit.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_Sitting_Sitting_Transition_0: eAITransition {
	private Expansion_Vehicles_Sitting_State_0 src;
	private Expansion_Vehicles_Sitting_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_Sitting_Sitting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_Sitting_Sitting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_Sitting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_Sitting_State_0"));
	}
	override int Guard() {
		if (!unit.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_OpenVehicleDoor_Sitting_Transition_0: eAITransition {
	private Expansion_Vehicles_OpenVehicleDoor_State_0 src;
	private Expansion_Vehicles_Sitting_State_0 dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor_Sitting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor_Sitting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Vehicles_Sitting_State_0"));
	}
	override int Guard() {
		if (!unit.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_CloseVehicleDoor__Transition_0: eAITransition {
	private Expansion_Vehicles_CloseVehicleDoor_State_0 src;
	private ExpansionState dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_CloseVehicleDoor__Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_CloseVehicleDoor__Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_CloseVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("ExpansionState"));
	}
	override int Guard() {
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_OpenVehicleDoor__Transition_0: eAITransition {
	private Expansion_Vehicles_OpenVehicleDoor_State_0 src;
	private ExpansionState dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor__Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor__Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_OpenVehicleDoor_State_0"));
		Class.CastTo(dst, _fsm.GetState("ExpansionState"));
	}
	override int Guard() {
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_GoToVehicle__Transition_0: eAITransition {
	private Expansion_Vehicles_GoToVehicle_State_0 src;
	private ExpansionState dst;
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GoToVehicle__Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GoToVehicle__Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Vehicles_GoToVehicle_State_0"));
		Class.CastTo(dst, _fsm.GetState("ExpansionState"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Vehicles_FSM_0: eAIFSM {
	EntityAI entity;
	int seat;
	void Expansion_Vehicles_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
		m_Name = "Vehicles";
		m_DefaultState = "Expansion_Vehicles_GoToVehicle_State_0";
		Setup();
	}
	void Setup() {
		AddState(new Expansion_Vehicles_GoToVehicle_State_0(this));
		AddState(new Expansion_Vehicles_GetInVehicle_State_0(this));
		AddState(new Expansion_Vehicles_GetOutVehicle_State_0(this));
		AddState(new Expansion_Vehicles_OpenVehicleDoor_State_0(this));
		AddState(new Expansion_Vehicles_CloseVehicleDoor_State_0(this));
		AddState(new Expansion_Vehicles_Sitting_State_0(this));
		AddTransition(new Expansion_Vehicles_GoToVehicle_OpenVehicleDoor_Transition_0(this));
		AddTransition(new Expansion_Vehicles_GoToVehicle_GoToVehicle_Transition_0(this));
		AddTransition(new Expansion_Vehicles_OpenVehicleDoor_GetInVehicle_Transition_0(this));
		AddTransition(new Expansion_Vehicles_GetInVehicle_CloseVehicleDoor_Transition_0(this));
		AddTransition(new Expansion_Vehicles_Sitting_OpenVehicleDoor_Transition_0(this));
		AddTransition(new Expansion_Vehicles_OpenVehicleDoor_GetOutVehicle_Transition_0(this));
		AddTransition(new Expansion_Vehicles_GetOutVehicle_CloseVehicleDoor_Transition_0(this));
		AddTransition(new Expansion_Vehicles_CloseVehicleDoor_Sitting_Transition_0(this));
		AddTransition(new Expansion_Vehicles_Sitting_Sitting_Transition_0(this));
		AddTransition(new Expansion_Vehicles_OpenVehicleDoor_Sitting_Transition_0(this));
		AddTransition(new Expansion_Vehicles_CloseVehicleDoor__Transition_0(this));
		AddTransition(new Expansion_Vehicles_OpenVehicleDoor__Transition_0(this));
		AddTransition(new Expansion_Vehicles_GoToVehicle__Transition_0(this));
	}
}
ExpansionFSM Create_Expansion_Vehicles_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
	return new Expansion_Vehicles_FSM_0(owner, parentState);
}
class Expansion_Fighting_Positioning_State_0: eAIState_Fighting_Positioning {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Positioning_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Positioning_State_0";
		m_Name = "Positioning";
	}
}
class Expansion_Fighting_Evade_State_0: eAIState_Fighting_Evade {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Evade_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Evade_State_0";
		m_Name = "Evade";
	}
}
class Expansion_Fighting_FireWeapon_State_0: eAIState_Fighting_FireWeapon {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_FireWeapon_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_FireWeapon_State_0";
		m_Name = "FireWeapon";
	}
}
class Expansion_Fighting_Melee_State_0: eAIState_Fighting_Melee {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Melee_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Melee_State_0";
		m_Name = "Melee";
	}
}
class Expansion_Fighting__Melee_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Fighting_Melee_State_0 dst;
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting__Melee_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting__Melee_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Fighting_Melee_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Fighting__Evade_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Fighting_Evade_State_0 dst;
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting__Evade_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting__Evade_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Fighting_Evade_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Fighting__FireWeapon_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Fighting_FireWeapon_State_0 dst;
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting__FireWeapon_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting__FireWeapon_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Fighting_FireWeapon_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Fighting__Positioning_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Fighting_Positioning_State_0 dst;
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting__Positioning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting__Positioning_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Fighting_Positioning_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Fighting_FSM_0: eAIFSM {
	void Expansion_Fighting_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
		m_Name = "Fighting";
		m_DefaultState = "Expansion_Fighting_Positioning_State_0";
		Setup();
	}
	void Setup() {
		AddState(new Expansion_Fighting_Positioning_State_0(this));
		AddState(new Expansion_Fighting_Evade_State_0(this));
		AddState(new Expansion_Fighting_FireWeapon_State_0(this));
		AddState(new Expansion_Fighting_Melee_State_0(this));
		AddTransition(new Expansion_Fighting__Melee_Transition_0(this));
		AddTransition(new Expansion_Fighting__Evade_Transition_0(this));
		AddTransition(new Expansion_Fighting__FireWeapon_Transition_0(this));
		AddTransition(new Expansion_Fighting__Positioning_Transition_0(this));
	}
}
ExpansionFSM Create_Expansion_Fighting_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
	return new Expansion_Fighting_FSM_0(owner, parentState);
}
class Expansion_Reloading_Start_State_0: eAIState_Weapon_Reloading_Start {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Start_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Start_State_0";
		m_Name = "Start";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		OnEntryEx(Event, From, fsm.last_attempt_time);
	}
}
class Expansion_Reloading_Reloading_State_0: eAIState_Weapon_Reloading_Reloading {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Reloading_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading_State_0";
		m_Name = "Reloading";
	}
}
class Expansion_Reloading_Reloading_Fail_State_0: eAIState_Weapon_Reloading_Fail {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Reloading_Fail_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading_Fail_State_0";
		m_Name = "Reloading_Fail";
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return OnUpdateEx(DeltaTime, SimulationPrecision, fsm.weapon);
	}
}
class Expansion_Reloading_Removing_State_0: eAIState_Weapon_Reloading_Removing {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Removing_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Removing_State_0";
		m_Name = "Removing";
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return OnUpdateEx(DeltaTime, SimulationPrecision, fsm.weapon);
	}
}
class Expansion_Reloading_Start_Reloading_Transition_0: eAITransition {
	private Expansion_Reloading_Start_State_0 src;
	private Expansion_Reloading_Reloading_State_0 dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Start_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Start_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Reloading_Start_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Reloading_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(fsm.weapon, fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading_Start_Reloading_Fail_Transition_0: eAITransition {
	private Expansion_Reloading_Start_State_0 src;
	private Expansion_Reloading_Reloading_Fail_State_0 dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Start_Reloading_Fail_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Start_Reloading_Fail_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Reloading_Start_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Reloading_Reloading_Fail_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading_Reloading_Fail_Removing_Transition_0: eAITransition {
	private Expansion_Reloading_Reloading_Fail_State_0 src;
	private Expansion_Reloading_Removing_State_0 dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Reloading_Fail_Removing_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading_Fail_Removing_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Reloading_Reloading_Fail_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Reloading_Removing_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading_Reloading__Transition_0: eAITransition {
	private Expansion_Reloading_Reloading_State_0 src;
	private ExpansionState dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Reloading__Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading__Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Reloading_Reloading_State_0"));
		Class.CastTo(dst, _fsm.GetState("ExpansionState"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading_Removing__Transition_0: eAITransition {
	private Expansion_Reloading_Removing_State_0 src;
	private ExpansionState dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Removing__Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Removing__Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Reloading_Removing_State_0"));
		Class.CastTo(dst, _fsm.GetState("ExpansionState"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading__Start_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Reloading_Start_State_0 dst;
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading__Start_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading__Start_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Reloading_Start_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Reloading_FSM_0: eAIFSM {
	Weapon_Base weapon;
	Magazine magazine;
	int last_attempt_time;
	void Expansion_Reloading_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
		m_Name = "Reloading";
		m_DefaultState = "Expansion_Reloading_Start_State_0";
		Setup();
	}
	void Setup() {
		AddState(new Expansion_Reloading_Start_State_0(this));
		AddState(new Expansion_Reloading_Reloading_State_0(this));
		AddState(new Expansion_Reloading_Reloading_Fail_State_0(this));
		AddState(new Expansion_Reloading_Removing_State_0(this));
		AddTransition(new Expansion_Reloading_Start_Reloading_Transition_0(this));
		AddTransition(new Expansion_Reloading_Start_Reloading_Fail_Transition_0(this));
		AddTransition(new Expansion_Reloading_Reloading_Fail_Removing_Transition_0(this));
		AddTransition(new Expansion_Reloading_Reloading__Transition_0(this));
		AddTransition(new Expansion_Reloading_Removing__Transition_0(this));
		AddTransition(new Expansion_Reloading__Start_Transition_0(this));
	}
}
ExpansionFSM Create_Expansion_Reloading_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
	return new Expansion_Reloading_FSM_0(owner, parentState);
}
class Expansion_Master_Idle_State_0: eAIState_Idle {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_State_0";
		m_Name = "Idle";
	}
}
class Expansion_Master_Dormant_State_0: eAIState_Dormant {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Dormant_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Dormant_State_0";
		m_Name = "Dormant";
	}
}
class Expansion_Master_Unconscious_State_0: eAIState_Unconscious {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Unconscious_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Unconscious_State_0";
		m_Name = "Unconscious";
	}
}
class Expansion_Master_Leave_State_0: eAIState_Leave {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Leave_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Leave_State_0";
		m_Name = "Leave";
	}
}
class Expansion_Master_Interacting_State_0: eAIState_Interacting {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Interacting_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Interacting_State_0";
		m_Name = "Interacting";
	}
}
class Expansion_Master_FollowFormation_State_0: eAIState_FollowFormation {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_State_0";
		m_Name = "FollowFormation";
	}
}
class Expansion_Master_TraversingWaypoints_State_0: eAIState_TraversingWaypoints {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_State_0";
		m_Name = "TraversingWaypoints";
	}
}
class Expansion_Master_Flank_State_0: eAIState_Flank {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_State_0";
		m_Name = "Flank";
	}
}
class Expansion_Master_Vehicles_State_0: eAIState_Vehicles {
	Expansion_Vehicles_FSM_0 sub_fsm;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Vehicles_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Vehicles_State_0";
		m_Name = "Vehicles";
		m_SubFSM = new Expansion_Vehicles_FSM_0(_fsm.GetOwner(), this);
		Class.CastTo(sub_fsm, m_SubFSM);
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
		if (Aborted) m_SubFSM.Abort(Event);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return OnUpdateEx(DeltaTime, SimulationPrecision, sub_fsm.entity, sub_fsm.seat);
	}
}
class Expansion_Master_Fighting_State_0: eAIState_Fighting {
	Expansion_Fighting_FSM_0 sub_fsm;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_State_0";
		m_Name = "Fighting";
		m_SubFSM = new Expansion_Fighting_FSM_0(_fsm.GetOwner(), this);
		Class.CastTo(sub_fsm, m_SubFSM);
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
		if (Aborted) m_SubFSM.Abort(Event);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return EXIT;
	}
}
class Expansion_Master_Weapon_Reloading_State_0: eAIState_Weapon_Reloading {
	Expansion_Reloading_FSM_0 sub_fsm;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Weapon_Reloading_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Weapon_Reloading_State_0";
		m_Name = "Reloading";
		m_SubFSM = new Expansion_Reloading_FSM_0(_fsm.GetOwner(), this);
		Class.CastTo(sub_fsm, m_SubFSM);
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
		if (Aborted) m_SubFSM.Abort(Event);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Weapon_Unjamming_State_0: eAIState_Weapon_Unjamming {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Weapon_Unjamming_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Weapon_Unjamming_State_0";
		m_Name = "Weapon_Unjamming";
	}
}
class Expansion_Master_TakeItemToHands_State_0: eAIState_TakeItemToHands {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToHands_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToHands_State_0";
		m_Name = "TakeItemToHands";
	}
}
class Expansion_Master_TakeItemToInventory_State_0: eAIState_TakeItemToInventory {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToInventory_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToInventory_State_0";
		m_Name = "TakeItemToInventory";
	}
}
class Expansion_Master_Bandaging_Self_State_0: eAIState_Bandaging_Self {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Bandaging_Self_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Bandaging_Self_State_0";
		m_Name = "Bandaging_Self";
	}
}
class Expansion_Master_Repair_State_0: eAIState_Repair {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Repair_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Repair_State_0";
		m_Name = "Repair";
	}
}
class Expansion_Master_Skinning_State_0: eAIState_Skinning {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Skinning_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Skinning_State_0";
		m_Name = "Skinning";
	}
}
class Expansion_Master_PlayEmote_State_0: eAIState_PlayEmote {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_PlayEmote_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_PlayEmote_State_0";
		m_Name = "PlayEmote";
	}
}
class Expansion_Master_DropItem_State_0: eAIState_DropItem {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_DropItem_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_DropItem_State_0";
		m_Name = "DropItem";
	}
}
class Expansion_Master_TidyCargo_State_0: eAIState_TidyCargo {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TidyCargo_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TidyCargo_State_0";
		m_Name = "TidyCargo";
	}
}
class Expansion_Master_Struggle_State_0: eAIState_Struggle {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Struggle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Struggle_State_0";
		m_Name = "Struggle";
	}
}
class Expansion_Master__Unconscious_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Master_Unconscious_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master__Unconscious_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master__Unconscious_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Unconscious_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Unconscious_Idle_Transition_0: eAITransition {
	private Expansion_Master_Unconscious_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Unconscious_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Unconscious_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Unconscious_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Struggle_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Struggle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Struggle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Struggle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Struggle_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Struggle_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Struggle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Struggle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Struggle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Struggle_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Struggle_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Struggle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Struggle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Struggle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Struggle_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Struggle_Idle_Transition_0: eAITransition {
	private Expansion_Master_Struggle_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Struggle_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Struggle_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Struggle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Leave_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Leave_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Leave_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Leave_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Leave_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Leave_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Leave_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Leave_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Leave_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Leave_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Leave_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Leave_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Leave_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Leave_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Leave_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master__Interacting_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Master_Interacting_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master__Interacting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master__Interacting_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Interacting_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Interacting_Idle_Transition_0: eAITransition {
	private Expansion_Master_Interacting_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Interacting_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Interacting_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Interacting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToHands_Bandaging_Self_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToHands_State_0 src;
	private Expansion_Master_Bandaging_Self_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToHands_Bandaging_Self_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToHands_Bandaging_Self_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Bandaging_Self_Idle_Transition_0: eAITransition {
	private Expansion_Master_Bandaging_Self_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Bandaging_Self_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Bandaging_Self_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Bandaging_Self_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Weapon_Reloading_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Weapon_Reloading_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Weapon_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Weapon_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.last_attempt_time, dst.sub_fsm.weapon, dst.sub_fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Weapon_Reloading_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Weapon_Reloading_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Weapon_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Weapon_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.last_attempt_time, dst.sub_fsm.weapon, dst.sub_fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Weapon_Reloading_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Weapon_Reloading_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Weapon_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Weapon_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.last_attempt_time, dst.sub_fsm.weapon, dst.sub_fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Weapon_Reloading_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Weapon_Reloading_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Weapon_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Weapon_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.last_attempt_time, dst.sub_fsm.weapon, dst.sub_fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_Weapon_Reloading_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_Weapon_Reloading_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_Weapon_Reloading_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_Weapon_Reloading_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.last_attempt_time, dst.sub_fsm.weapon, dst.sub_fsm.magazine);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToInventory_TakeItemToHands_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToInventory_State_0 src;
	private Expansion_Master_TakeItemToHands_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToInventory_TakeItemToHands_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToInventory_TakeItemToHands_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Skinning_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_Skinning_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Skinning_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Skinning_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Skinning_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToInventory_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToInventory_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToInventory_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToInventory_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToHands_TakeItemToInventory_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToHands_State_0 src;
	private Expansion_Master_TakeItemToInventory_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToHands_TakeItemToInventory_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToHands_TakeItemToInventory_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToHands_Idle_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToHands_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToHands_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToHands_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToHands_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TakeItemToInventory_Idle_Transition_0: eAITransition {
	private Expansion_Master_TakeItemToInventory_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToInventory_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToInventory_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TakeItemToInventory_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Weapon_Unjamming_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Weapon_Unjamming_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Weapon_Unjamming_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Weapon_Unjamming_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Weapon_Unjamming_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Weapon_Unjamming_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Weapon_Unjamming_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Weapon_Unjamming_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Weapon_Unjamming_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Weapon_Unjamming_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Weapon_Unjamming_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Weapon_Unjamming_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Weapon_Unjamming_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Weapon_Unjamming_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Weapon_Unjamming_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Weapon_Unjamming_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_Weapon_Unjamming_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_Weapon_Unjamming_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_Weapon_Unjamming_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_Weapon_Unjamming_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Weapon_Reloading_Idle_Transition_0: eAITransition {
	private Expansion_Master_Weapon_Reloading_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Weapon_Reloading_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Weapon_Reloading_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Weapon_Reloading_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Weapon_Unjamming_Idle_Transition_0: eAITransition {
	private Expansion_Master_Weapon_Unjamming_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Weapon_Unjamming_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Weapon_Unjamming_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Weapon_Unjamming_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Skinning_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Skinning_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Skinning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Skinning_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Skinning_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Skinning_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Skinning_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Skinning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Skinning_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Skinning_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Skinning_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Skinning_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Skinning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Skinning_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Skinning_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Skinning_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Skinning_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Skinning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Skinning_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Skinning_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_Skinning_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_Skinning_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_Skinning_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_Skinning_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Skinning_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Skinning_Idle_Transition_0: eAITransition {
	private Expansion_Master_Skinning_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Skinning_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Skinning_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Skinning_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Fighting_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Fighting_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Fighting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Fighting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Fighting_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Fighting_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Fighting_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Fighting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Fighting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Fighting_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Fighting_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Fighting_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Fighting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Fighting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Fighting_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Fighting_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Fighting_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Fighting_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Fighting_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Fighting_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Fighting_Idle_Transition_0: eAITransition {
	private Expansion_Master_Fighting_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Fighting_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Fighting_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Fighting_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Vehicles_Idle_Transition_0: eAITransition {
	private Expansion_Master_Vehicles_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Vehicles_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Vehicles_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Vehicles_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Vehicles_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Vehicles_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Vehicles_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Vehicles_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Vehicles_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.entity, dst.sub_fsm.seat);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Vehicles_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Vehicles_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Vehicles_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Vehicles_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Vehicles_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.entity, dst.sub_fsm.seat);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Vehicles_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Vehicles_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Vehicles_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Vehicles_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Vehicles_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.entity, dst.sub_fsm.seat);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Vehicles_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Vehicles_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Vehicles_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Vehicles_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Vehicles_State_0"));
	}
	override int Guard() {
		return dst.GuardEx(dst.sub_fsm.entity, dst.sub_fsm.seat);
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_PlayEmote_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_PlayEmote_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_PlayEmote_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_PlayEmote_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_PlayEmote_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_PlayEmote_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_PlayEmote_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_PlayEmote_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_PlayEmote_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_PlayEmote_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_PlayEmote_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_PlayEmote_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_PlayEmote_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_PlayEmote_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_PlayEmote_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_PlayEmote_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_PlayEmote_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_PlayEmote_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_PlayEmote_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_PlayEmote_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_PlayEmote_Idle_Transition_0: eAITransition {
	private Expansion_Master_PlayEmote_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_PlayEmote_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_PlayEmote_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_PlayEmote_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Repair_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Repair_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Repair_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Repair_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Repair_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Repair_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Repair_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Repair_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Repair_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Repair_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Repair_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Repair_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Repair_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Repair_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Repair_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Repair_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Repair_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Repair_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Repair_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Repair_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Repair_Idle_Transition_0: eAITransition {
	private Expansion_Master_Repair_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Repair_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Repair_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Repair_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_DropItem_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_DropItem_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_DropItem_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_DropItem_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_DropItem_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_DropItem_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_DropItem_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_DropItem_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_DropItem_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_DropItem_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_DropItem_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_DropItem_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_DropItem_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_DropItem_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_DropItem_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_DropItem_Idle_Transition_0: eAITransition {
	private Expansion_Master_DropItem_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_DropItem_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_DropItem_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_DropItem_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_TidyCargo_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_TidyCargo_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_TidyCargo_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_TidyCargo_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TidyCargo_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_TidyCargo_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_TidyCargo_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_TidyCargo_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_TidyCargo_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TidyCargo_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_TidyCargo_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_TidyCargo_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_TidyCargo_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_TidyCargo_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TidyCargo_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TidyCargo_Idle_Transition_0: eAITransition {
	private Expansion_Master_TidyCargo_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TidyCargo_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TidyCargo_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TidyCargo_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_FollowFormation_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_FollowFormation_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_FollowFormation_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_FollowFormation_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_TraversingWaypoints_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_TraversingWaypoints_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_TraversingWaypoints_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_TraversingWaypoints_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Flank_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Flank_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Flank_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Flank_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Flank_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Flank_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Flank_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Flank_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Flank_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Flank_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Flank_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Flank_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Flank_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Flank_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Flank_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Idle_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Idle_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_Idle_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return src.GuardIdle();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Dormant_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Dormant_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Dormant_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Dormant_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Dormant_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_TraversingWaypoints_Dormant_Transition_0: eAITransition {
	private Expansion_Master_TraversingWaypoints_State_0 src;
	private Expansion_Master_Dormant_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_Dormant_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_Dormant_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Dormant_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FollowFormation_Dormant_Transition_0: eAITransition {
	private Expansion_Master_FollowFormation_State_0 src;
	private Expansion_Master_Dormant_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_FollowFormation_Dormant_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_Dormant_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Dormant_State_0"));
	}
	override int Guard() {
		return dst.Guard();
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Dormant_Idle_Transition_0: eAITransition {
	private Expansion_Master_Dormant_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Dormant_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Dormant_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Dormant_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Idle_Idle_Transition_0: eAITransition {
	private Expansion_Master_Idle_State_0 src;
	private Expansion_Master_Idle_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_Idle_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_Idle_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Idle_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Idle_State_0"));
	}
	override int Guard() {
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_FSM_0: eAIFSM {
	void Expansion_Master_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
		m_Name = "Master";
		m_DefaultState = "Expansion_Master_Idle_State_0";
		Setup();
	}
	void Setup() {
		AddState(new Expansion_Master_Idle_State_0(this));
		AddState(new Expansion_Master_Dormant_State_0(this));
		AddState(new Expansion_Master_Unconscious_State_0(this));
		AddState(new Expansion_Master_Leave_State_0(this));
		AddState(new Expansion_Master_Interacting_State_0(this));
		AddState(new Expansion_Master_FollowFormation_State_0(this));
		AddState(new Expansion_Master_TraversingWaypoints_State_0(this));
		AddState(new Expansion_Master_Flank_State_0(this));
		AddState(new Expansion_Master_Vehicles_State_0(this));
		AddState(new Expansion_Master_Fighting_State_0(this));
		AddState(new Expansion_Master_Weapon_Reloading_State_0(this));
		AddState(new Expansion_Master_Weapon_Unjamming_State_0(this));
		AddState(new Expansion_Master_TakeItemToHands_State_0(this));
		AddState(new Expansion_Master_TakeItemToInventory_State_0(this));
		AddState(new Expansion_Master_Bandaging_Self_State_0(this));
		AddState(new Expansion_Master_Repair_State_0(this));
		AddState(new Expansion_Master_Skinning_State_0(this));
		AddState(new Expansion_Master_PlayEmote_State_0(this));
		AddState(new Expansion_Master_DropItem_State_0(this));
		AddState(new Expansion_Master_TidyCargo_State_0(this));
		AddState(new Expansion_Master_Struggle_State_0(this));
		AddTransition(new Expansion_Master__Unconscious_Transition_0(this));
		AddTransition(new Expansion_Master_Unconscious_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Struggle_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Struggle_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Struggle_Transition_0(this));
		AddTransition(new Expansion_Master_Struggle_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Leave_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Leave_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Leave_Transition_0(this));
		AddTransition(new Expansion_Master__Interacting_Transition_0(this));
		AddTransition(new Expansion_Master_Interacting_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToHands_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_Bandaging_Self_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Weapon_Reloading_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Weapon_Reloading_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Weapon_Reloading_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Weapon_Reloading_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Weapon_Reloading_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToInventory_TakeItemToHands_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Skinning_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToInventory_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToHands_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Skinning_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToHands_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToInventory_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Weapon_Reloading_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Weapon_Unjamming_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Skinning_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Skinning_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Skinning_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Skinning_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Skinning_Transition_0(this));
		AddTransition(new Expansion_Master_Skinning_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Fighting_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Fighting_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Fighting_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Fighting_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Vehicles_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Vehicles_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Vehicles_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Vehicles_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Vehicles_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_PlayEmote_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_PlayEmote_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_PlayEmote_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_PlayEmote_Transition_0(this));
		AddTransition(new Expansion_Master_PlayEmote_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Repair_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Repair_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Repair_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Repair_Transition_0(this));
		AddTransition(new Expansion_Master_Repair_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_DropItem_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_DropItem_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_DropItem_Transition_0(this));
		AddTransition(new Expansion_Master_DropItem_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TidyCargo_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_TidyCargo_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_TidyCargo_Transition_0(this));
		AddTransition(new Expansion_Master_TidyCargo_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_FollowFormation_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TraversingWaypoints_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Dormant_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Dormant_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Dormant_Transition_0(this));
		AddTransition(new Expansion_Master_Dormant_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Idle_Transition_0(this));
	}
}
ExpansionFSM Create_Expansion_Master_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
	return new Expansion_Master_FSM_0(owner, parentState);
}
