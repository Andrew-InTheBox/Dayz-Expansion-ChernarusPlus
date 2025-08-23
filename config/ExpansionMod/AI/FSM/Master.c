class Expansion_Vehicles_GoToVehicle_State_0: ExpansionState_GoToVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GoToVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GoToVehicle_State_0";
		m_Name = "GoToVehicle";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
		entity = fsm.entity;
		seat = fsm.seat;
		super.OnEntry(Event, null);
		unit.OverrideMovementDirection(false, 0);
		unit.OverrideMovementSpeed(false, 0);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Vehicles_GetInVehicle_State_0: ExpansionState_GetInVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetInVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetInVehicle_State_0";
		m_Name = "GetInVehicle";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Vehicles_GetOutVehicle_State_0: ExpansionState_GetOutVehicle {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_GetOutVehicle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_GetOutVehicle_State_0";
		m_Name = "GetOutVehicle";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Vehicles_OpenVehicleDoor_State_0: ExpansionState_OpenVehicleDoor {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_OpenVehicleDoor_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_OpenVehicleDoor_State_0";
		m_Name = "OpenVehicleDoor";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Vehicles_CloseVehicleDoor_State_0: ExpansionState_CloseVehicleDoor {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_CloseVehicleDoor_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_CloseVehicleDoor_State_0";
		m_Name = "CloseVehicleDoor";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Vehicles_Sitting_State_0: eAIState {
	Expansion_Vehicles_FSM_0 fsm;
	void Expansion_Vehicles_Sitting_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Vehicles_Sitting_State_0";
		m_Name = "Sitting";
	}
	override void OnEntry(string Event, ExpansionState From) {
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
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
		if (vector.DistanceSq(unit.GetPosition(), src.position) > 1.0) return FAIL;
		if (!src.transport.IsAreaAtDoorFree(src.seat)) return FAIL;
		CarScript cs;
		if (src.transport.CrewMember(src.seat) || (Class.CastTo(cs, src.transport) && cs.Expansion_IsSeatReservedByOther(src.seat, unit))) return FAIL;
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
		if (vector.DistanceSq(unit.GetPosition(), src.position) < 1.0) return FAIL;
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
		if (vector.DistanceSq(unit.GetPosition(), src.position) > 1.0) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		if (!src.transport.CrewCanGetThrough(src.seat) || !src.transport.IsAreaAtDoorFree(src.seat)) return FAIL;
		CarScript cs;
		if (src.transport.CrewMember(src.seat) || (Class.CastTo(cs, src.transport) && cs.Expansion_IsSeatReservedByOther(src.seat, unit))) return FAIL;
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
		if (!dst.transport.IsAreaAtDoorFree(dst.seat)) return FAIL;
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
		if (!src.transport.CrewCanGetThrough(src.seat) || !src.transport.IsAreaAtDoorFree(src.seat)) return FAIL;
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
class Expansion_Fighting_Positioning_State_0: ExpansionState_Fighting_Positioning {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Positioning_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Positioning_State_0";
		m_Name = "Positioning";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Fighting_Evade_State_0: ExpansionState_Fighting_Evade {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Evade_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Evade_State_0";
		m_Name = "Evade";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Fighting_FireWeapon_State_0: ExpansionState_Fighting_FireWeapon {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_FireWeapon_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_FireWeapon_State_0";
		m_Name = "FireWeapon";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Fighting_Melee_State_0: ExpansionState_Fighting_Melee {
	Expansion_Fighting_FSM_0 fsm;
	void Expansion_Fighting_Melee_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Fighting_Melee_State_0";
		m_Name = "Melee";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
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
		if (unit.IsRestrained()) return FAIL;
		if (!unit.CanRaiseWeapon() || !unit.eAI_HasLOS()) return FAIL;
		if (unit.eAI_ShouldBandage() && unit.GetBandageToUse()) return FAIL;
		dst.m_Target = unit.GetTarget();
		if (!dst.m_Target) return FAIL;
		if (!dst.m_Target.IsMeleeViable() || dst.m_Target.GetThreat() < 0.4) return FAIL;
		if (dst.m_Target.ShouldAvoid()) return FAIL;
		if (unit.m_eAI_HasProjectileWeaponInHands)
		{
			if (unit.eAI_SkipMelee("skipping melee", dst.m_Target, false))
			return FAIL;
		}
		return SUCCESS;
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
		int missionTime = GetGame().GetTime();
		Weapon_Base aiWeapon;
		if (Class.CastTo(aiWeapon, unit.GetHumanInventory().GetEntityInHands()) && missionTime - unit.m_eAI_LastEvadeTime < Math.RandomInt(2500, 5000)) return FAIL;
		auto target = unit.GetTarget();
		if (!target) return FAIL;
		auto targetPlayer = DayZPlayerImplement.Cast(target.GetEntity());
		if (!targetPlayer) return FAIL;
		if (!targetPlayer.IsRaised()) return FAIL;  //! Ignore if target player isn't raised
		if (!target.m_LOS) return FAIL;
		auto weapon = Weapon_Base.Cast(targetPlayer.GetHumanInventory().GetEntityInHands());
		if (!weapon) return FAIL;  //! Ignore if target player doesn't have a firearm
		vector fromTargetDirection = vector.Direction(targetPlayer.GetPosition(), unit.GetPosition()).Normalized();
		float fromTargetDot = vector.Dot(targetPlayer.Expansion_GetAimDirection(), fromTargetDirection);
		if (fromTargetDot < 0.97) return FAIL;  //! Ignore if target player isn't aiming at us
		if (Math.RandomInt(0, 5) > 0) return FAIL;  //! 1 in 5 chance to evade
		if (unit.eAI_IsDangerousAltitude()) return FAIL;  //! Don't evade if high above ground
		if (unit.m_eAI_IsOnLadder) return FAIL;
		unit.m_eAI_LastEvadeTime = missionTime;
		return SUCCESS;
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
		if (unit.IsRestrained()) return FAIL;
		// we are aiming at something?
		dst.m_Target = unit.GetTarget();
		if (!dst.m_Target) return FAIL;
		PlayerBase player;
		EntityAI targetEntity = dst.m_Target.GetEntity();
		ItemBase itemTarget;
		float dist = dst.m_Target.GetDistance();
		if (!targetEntity)
		{
			return FAIL;
		}
		else if (Class.CastTo(player, targetEntity))
		{
			if (player.IsUnconscious())
			return FAIL;
		}
		else if (Class.CastTo(itemTarget, targetEntity))
		{
			// don't shoot at bandages, ammo/magazines, melee weapons, clothing or headtorches, silly
			if (itemTarget.Expansion_CanBeUsedToBandage())
			return FAIL;
			if (itemTarget.IsMagazine())
			return FAIL;
			if (itemTarget.IsWeapon())
			return FAIL;
			if (itemTarget.Expansion_IsMeleeWeapon())
			return FAIL;
			if (itemTarget.IsClothing())
			return FAIL;
		}
		if (unit.IsFighting()) return FAIL;
		if (!Class.CastTo(dst.m_Weapon, unit.GetItemInHands()) || dst.m_Weapon.IsDamageDestroyed()) return FAIL;
		if (!unit.CanRaiseWeapon() || !dst.m_Target.m_LOS) return FAIL;
		if (!dst.m_Weapon.Expansion_IsChambered()) return FAIL;
		if (unit.GetWeaponManager().CanUnjam(dst.m_Weapon)) return FAIL;
		float minDist;
		if (dst.m_Weapon.ShootsExplosiveAmmo())
		minDist = dst.m_Weapon.Expansion_GetMinSafeFiringDistance();
		if (dst.m_Target.IsExplosive())
		minDist = Math.Max(dst.m_Target.GetMinDistance(), minDist);
		if (minDist)
		{
			//! Avoid firing if within minDist
			if (dist < minDist) return FAIL;
			//! Avoid firing if other friendly units within minDist from tgt
			float minDistSq = minDist * minDist;
			vector aimPosition = dst.m_Target.GetPosition() + dst.m_Target.GetAimOffset();
			vector min = Vector(aimPosition[0] - minDist, aimPosition[1] - minDist, aimPosition[2] - minDist);
			vector max = Vector(aimPosition[0] + minDist, aimPosition[1] + minDist, aimPosition[2] + minDist);
			array<EntityAI> entities = {};
			DayZPlayerUtils.SceneGetEntitiesInBox(min, max, entities);
			vector hitPos;
			vector hitDir;
			int hitComponent;
			set<Object> results = new set<Object>;
			foreach (EntityAI entity: entities)
			{
				vector entityCenter = entity.GetCenter();
				if (vector.DistanceSq(entityCenter, aimPosition) > minDistSq)
				continue;
				if (!unit.PlayerIsEnemy(entity))
				{
					//! Friendly unit in blast radius
					if (DayZPhysics.RaycastRV(aimPosition, entityCenter, hitPos, hitDir, hitComponent, results, null, targetEntity, false, false, ObjIntersectFire, 0.2))
					{
						Object parentObject;
						if (results.Find(entity) > -1 || (Class.CastTo(parentObject, entity.GetParent()) && results.Find(parentObject) > -1))
						{
							if (!unit.IsRaised())
							unit.RaiseWeapon(true);
							return FAIL;  //! Friendly unit in blast radius and nothing blocking the blast
						}
					}
				}
			}
		}
		return SUCCESS;
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
class Expansion_Reloading_Start_State_0: eAIState {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Start_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Start_State_0";
		m_Name = "Start";
	}
	override void OnEntry(string Event, ExpansionState From) {
		fsm.last_attempt_time = GetGame().GetTime();
		unit.OverrideMovementSpeed(false, 0);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		return EXIT;
	}
}
class Expansion_Reloading_Reloading_State_0: ExpansionState_Reloading {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Reloading_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading_State_0";
		m_Name = "Reloading";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Reloading_Reloading_Fail_State_0: eAIState {
	Expansion_Reloading_FSM_0 fsm;
	float time;
	void Expansion_Reloading_Reloading_Fail_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Reloading_Fail_State_0";
		m_Name = "Reloading_Fail";
	}
	override void OnEntry(string Event, ExpansionState From) {
		unit.RaiseWeapon(false);
		time = 0;
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		time += DeltaTime;
		// waiting for the weapon to be lowered
		if (fsm.weapon && time < 0.5)
		return CONTINUE;
		return EXIT;
	}
}
class Expansion_Reloading_Removing_State_0: eAIState {
	Expansion_Reloading_FSM_0 fsm;
	void Expansion_Reloading_Removing_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Reloading_Removing_State_0";
		m_Name = "Removing";
	}
	override void OnEntry(string Event, ExpansionState From) {
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (!fsm.weapon || unit.GetItemInHands() != fsm.weapon)
		return EXIT;  // remove complete
		if (unit.GetActionManager().GetRunningAction())
		return CONTINUE;
		if (fsm.weapon.IsDamageDestroyed() || !unit.eAI_TakeItemToInventoryDropShoulderImpl(fsm.weapon))
		unit.eAI_DropItem(fsm.weapon);
		return CONTINUE;
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
		if (!fsm.weapon || fsm.weapon.IsDamageDestroyed())
		return FAIL;
		if (!fsm.magazine && !fsm.weapon.Expansion_HasAmmo(fsm.magazine))
		{
			if (!unit.eAI_HasAmmoForFirearm(fsm.weapon, fsm.magazine))
			return FAIL;
		}
		#ifdef EXTRACE_DIAG
		if (!fsm.magazine)
		EXTrace.Start0(EXTrace.AI, this, "Reloading " + fsm.weapon + " from internal mag");
		else
		EXTrace.Start0(EXTrace.AI, this, "Reloading " + fsm.weapon + " from mag " + fsm.magazine);
		#endif
		dst.weapon = fsm.weapon;
		dst.magazine = fsm.magazine;
		return SUCCESS;
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
	int failed_attempts;
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
class Expansion_Master_Idle_State_0: ExpansionState_Idle {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Idle_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Idle_State_0";
		m_Name = "Idle";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Unconscious_State_0: eAIState {
	Expansion_Master_FSM_0 fsm;
	float time;
	void Expansion_Master_Unconscious_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Unconscious_State_0";
		m_Name = "Unconscious";
	}
	override void OnEntry(string Event, ExpansionState From) {
		time = 0;
		unit.OverrideTargetPosition(unit.GetPosition());
		unit.OverrideMovementSpeed(true, 0);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		if (EXTrace.AI)
		EXPrint(unit.ToString() + " left uncon state after " + time + " seconds");
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (time > 3)
		{
			return EXIT;
		}
		if (!unit.IsUnconscious())
		{
			time += DeltaTime;  //! Allow time to stand up so we don't instantly start firing
			if (unit.Expansion_IsAnimationIdle()) return EXIT;
		}
		return CONTINUE;
	}
}
class Expansion_Master_Leave_State_0: ExpansionState_Leave {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Leave_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Leave_State_0";
		m_Name = "Leave";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Interacting_State_0: eAIState {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Interacting_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Interacting_State_0";
		m_Name = "Interacting";
	}
	override void OnEntry(string Event, ExpansionState From) {
		unit.OverrideTargetPosition(unit.GetPosition() + unit.GetDirection() * unit.Expansion_GetMovementSpeed() * 0.333333);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (unit.IsUnconscious()) return EXIT;
		if (unit.eAI_HasInteractingPlayers())
		{
			return CONTINUE;
		}
		return EXIT;
	}
}
class Expansion_Master_FollowFormation_State_0: eAIState {
	Expansion_Master_FSM_0 fsm;
	eAIGroup group;
	int speedLimit;
	bool gotUp;
	void Expansion_Master_FollowFormation_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_FollowFormation_State_0";
		m_Name = "FollowFormation";
	}
	override void OnEntry(string Event, ExpansionState From) {
		gotUp = false;
		unit.eAI_LeaveCover();
		unit.OverrideMovementDirection(false, 0);
		unit.OverrideMovementSpeed(false, 0);
		speedLimit = unit.GetMovementSpeedLimit();
		if (speedLimit > 0)
		unit.SetMovementSpeedLimit(3);  //! Make sure AI can reach formation positions when following leader by overriding speed limit
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		if (speedLimit > 0)
		unit.SetMovementSpeedLimit(unit.m_eAI_SpeedLimitPreference);  //! Restore speed limit
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (!group) return EXIT;
		unit.OverrideTargetPosition(group.GetFormationPosition(unit));
		if (!gotUp && unit.Expansion_GetMovementSpeed() > 0 && unit.GetGroup().GetLeader().IsAI())
		{
			unit.Expansion_GetUp(true);
			gotUp = true;
		}
		return EXIT;
	}
}
class Expansion_Master_TraversingWaypoints_State_0: ExpansionState_TraversingWaypoints {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TraversingWaypoints_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TraversingWaypoints_State_0";
		m_Name = "TraversingWaypoints";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Flank_State_0: eAIState {
	Expansion_Master_FSM_0 fsm;
	eAITarget target;
	void Expansion_Master_Flank_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_State_0";
		m_Name = "Flank";
	}
	override void OnEntry(string Event, ExpansionState From) {
		unit.OverrideMovementDirection(false, 0);
		unit.OverrideMovementSpeed(false, 0);
		unit.eAI_SetShouldTakeCover(true);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		unit.eAI_SetShouldTakeCover(false);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (target)
		unit.OverrideTargetPosition(target);
		return EXIT;
	}
}
class Expansion_Master_Vehicles_State_0: eAIState {
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
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		if (Aborted) m_SubFSM.Abort(Event);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		auto group = unit.GetGroup();
		if (!group) return EXIT;
		if (!unit.IsInTransport() && unit.GetThreatToSelf() >= 0.4) return EXIT;
		auto leader = group.GetFormationLeader();
		//! @note leader can only briefly be null (disconnected/killed).
		//! We wait until a new leader has been determined (which may be the current unit).
		if (!leader) return CONTINUE;
		if (!sub_fsm.entity) return EXIT;
		if ((leader != unit && leader.IsInTransport() && leader.GetParent() == sub_fsm.entity) || unit.IsInTransport()) return CONTINUE;
		//! Wait until AI has left the vehicle and closed the door (if any)
		bool hasDoor;
		string source;
		ExpansionFSMHelper.DoorAnimationSource(sub_fsm.entity, sub_fsm.seat, hasDoor, source);
		if (hasDoor && sub_fsm.entity.GetAnimationPhase(source) > 0.5) return CONTINUE;
		return EXIT;
	}
}
class Expansion_Master_Fighting_State_0: eAIState {
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
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
		if (unit.GetEmoteManager().IsEmotePlaying())
		unit.GetEmoteManager().ServerRequestEmoteCancel();
		unit.eAI_SetIsFightingFSM(true);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		if (Aborted) m_SubFSM.Abort(Event);
		unit.eAI_SetIsFightingFSM(false);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return EXIT;
	}
}
class Expansion_Master_Weapon_Reloading_State_0: eAIState {
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
		if (Event != "") m_SubFSM.Start(Event);
		else m_SubFSM.StartDefault();
		if (unit.GetEmoteManager().IsEmotePlaying())
		unit.GetEmoteManager().ServerRequestEmoteCancel();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		if (Aborted) m_SubFSM.Abort(Event);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (m_SubFSM.Update(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Weapon_Unjamming_State_0: ExpansionState_Unjamming {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Weapon_Unjamming_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Weapon_Unjamming_State_0";
		m_Name = "Weapon_Unjamming";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_TakeItemToHands_State_0: ExpansionState_TakeItemToHands {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToHands_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToHands_State_0";
		m_Name = "TakeItemToHands";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_TakeItemToInventory_State_0: ExpansionState_TakeItemToInventory {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_TakeItemToInventory_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_TakeItemToInventory_State_0";
		m_Name = "TakeItemToInventory";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_Bandaging_Self_State_0: ExpansionState_Bandaging_Self {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Bandaging_Self_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Bandaging_Self_State_0";
		m_Name = "Bandaging_Self";
	}
	override void OnEntry(string Event, ExpansionState From) {
		super.OnEntry(Event, From);
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
		super.OnExit(Event, Aborted, To);
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		if (super.OnUpdate(DeltaTime, SimulationPrecision) == EXIT) return EXIT;
		return CONTINUE;
	}
}
class Expansion_Master_PlayEmote_State_0: eAIState {
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_PlayEmote_State_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_PlayEmote_State_0";
		m_Name = "PlayEmote";
	}
	override void OnEntry(string Event, ExpansionState From) {
		unit.Expansion_PlayEmote();
	}
	override void OnExit(string Event, bool Aborted, ExpansionState To) {
	}
	override int OnUpdate(float DeltaTime, int SimulationPrecision) {
		return EXIT;
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
		if (!(unit.IsUnconscious())) return FAIL;
		return SUCCESS;
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
		if (unit.IsUnconscious()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master__Leave_Transition_0: eAITransition {
	private ExpansionState src;
	private Expansion_Master_Leave_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master__Leave_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master__Leave_Transition_0";
		Class.CastTo(src, _fsm.GetState("ExpansionState"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_Leave_State_0"));
	}
	override int Guard() {
		if (unit.IsUnconscious()) return FAIL;
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.IsInCombat()) return FAIL;
		if (!group.m_Leave) return FAIL;
		return SUCCESS;
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
		if (!(unit.eAI_HasInteractingPlayers())) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		return SUCCESS;
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
		if (unit.eAI_HasInteractingPlayers()) return FAIL;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.eAI_ShouldBandage()) return FAIL;
		if (GetGame().GetTime() - dst.last_bandage_attempt_time < 4000) return FAIL;
		auto hands = unit.GetItemInHands();
		if (!hands) return FAIL;
		if (!hands.Expansion_CanBeUsedToBandage() || hands.IsDamageDestroyed()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		dst.bandage = hands;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.eAI_ShouldBandage()) return FAIL;
		if (GetGame().GetTime() - dst.last_bandage_attempt_time < 4000) return FAIL;
		auto hands = unit.GetItemInHands();
		if (!hands) return FAIL;
		if (!hands.Expansion_CanBeUsedToBandage() || hands.IsDamageDestroyed()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		dst.bandage = hands;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.eAI_ShouldBandage()) return FAIL;
		if (GetGame().GetTime() - dst.last_bandage_attempt_time < 4000) return FAIL;
		auto hands = unit.GetItemInHands();
		if (!hands) return FAIL;
		if (!hands.Expansion_CanBeUsedToBandage() || hands.IsDamageDestroyed()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		dst.bandage = hands;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.eAI_ShouldBandage()) return FAIL;
		if (GetGame().GetTime() - dst.last_bandage_attempt_time < 4000) return FAIL;
		auto hands = unit.GetItemInHands();
		if (!hands) return FAIL;
		if (!hands.Expansion_CanBeUsedToBandage() || hands.IsDamageDestroyed()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		dst.bandage = hands;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.eAI_ShouldBandage()) return FAIL;
		if (GetGame().GetTime() - dst.last_bandage_attempt_time < 4000) return FAIL;
		auto hands = unit.GetItemInHands();
		if (!hands) return FAIL;
		if (!hands.Expansion_CanBeUsedToBandage() || hands.IsDamageDestroyed()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		dst.bandage = hands;
		return SUCCESS;
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
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		if (GetGame().GetTime() - src.last_bandage_attempt_time < 4000) return FAIL;
		return SUCCESS;
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
		if (GetGame().GetTime() - dst.sub_fsm.last_attempt_time < 1000) return FAIL;
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, unit.GetItemInHands())) return FAIL;
		//! Allow sub-FSM to handle destroyed weapon so it gets dropped
		if (weapon.IsDamageDestroyed()) return SUCCESS;
		Magazine magazine;
		if (weapon.Expansion_IsChambered())
		{
			if (!unit.eAI_IsSafeToFillMag()) return FAIL;
			int mi = weapon.GetCurrentMuzzle();
			if (weapon.HasInternalMagazine(mi))
			{
				//! If this is a gun with internal mag and we are not in combat, reload when mag is not at capacity
				//! even if chamber is not empty
				if (weapon.GetInternalMagazineCartridgeCount(mi) >= weapon.GetInternalMagazineMaxCartridgeCount(mi) - 1)
				return FAIL;
				if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
				return FAIL;
			}
			else
			{
				//! If this is a gun with attached mag and we are not in combat, reload when mag is empty
				//! even if chamber is not empty
				Magazine currentMag = weapon.GetMagazine(mi);
				if (currentMag)
				{
					int ammoCount = currentMag.GetAmmoCount();
					//! Don't reload if attached mag is still at capacity
					if (ammoCount >= currentMag.GetAmmoMax() - 1)
					return FAIL;
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					//! Don't swap magazine if attached mag is not empty
					if (!magazine.IsAmmoPile() && ammoCount > 0)
					return FAIL;
				}
				else
				{
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					if (magazine.IsAmmoPile())
					return FAIL;
				}
			}
		}
		if (unit.GetWeaponManager().CanUnjam(weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		dst.sub_fsm.weapon = weapon;
		dst.sub_fsm.magazine = magazine;
		return SUCCESS;
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
		if (GetGame().GetTime() - dst.sub_fsm.last_attempt_time < 1000) return FAIL;
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, unit.GetItemInHands())) return FAIL;
		//! Allow sub-FSM to handle destroyed weapon so it gets dropped
		if (weapon.IsDamageDestroyed()) return SUCCESS;
		Magazine magazine;
		if (weapon.Expansion_IsChambered())
		{
			if (!unit.eAI_IsSafeToFillMag()) return FAIL;
			int mi = weapon.GetCurrentMuzzle();
			if (weapon.HasInternalMagazine(mi))
			{
				//! If this is a gun with internal mag and we are not in combat, reload when mag is not at capacity
				//! even if chamber is not empty
				if (weapon.GetInternalMagazineCartridgeCount(mi) >= weapon.GetInternalMagazineMaxCartridgeCount(mi) - 1)
				return FAIL;
				if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
				return FAIL;
			}
			else
			{
				//! If this is a gun with attached mag and we are not in combat, reload when mag is empty
				//! even if chamber is not empty
				Magazine currentMag = weapon.GetMagazine(mi);
				if (currentMag)
				{
					int ammoCount = currentMag.GetAmmoCount();
					//! Don't reload if attached mag is still at capacity
					if (ammoCount >= currentMag.GetAmmoMax() - 1)
					return FAIL;
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					//! Don't swap magazine if attached mag is not empty
					if (!magazine.IsAmmoPile() && ammoCount > 0)
					return FAIL;
				}
				else
				{
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					if (magazine.IsAmmoPile())
					return FAIL;
				}
			}
		}
		if (unit.GetWeaponManager().CanUnjam(weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		dst.sub_fsm.weapon = weapon;
		dst.sub_fsm.magazine = magazine;
		return SUCCESS;
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
		if (GetGame().GetTime() - dst.sub_fsm.last_attempt_time < 1000) return FAIL;
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, unit.GetItemInHands())) return FAIL;
		//! Allow sub-FSM to handle destroyed weapon so it gets dropped
		if (weapon.IsDamageDestroyed()) return SUCCESS;
		Magazine magazine;
		if (weapon.Expansion_IsChambered())
		{
			if (!unit.eAI_IsSafeToFillMag()) return FAIL;
			int mi = weapon.GetCurrentMuzzle();
			if (weapon.HasInternalMagazine(mi))
			{
				//! If this is a gun with internal mag and we are not in combat, reload when mag is not at capacity
				//! even if chamber is not empty
				if (weapon.GetInternalMagazineCartridgeCount(mi) >= weapon.GetInternalMagazineMaxCartridgeCount(mi) - 1)
				return FAIL;
				if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
				return FAIL;
			}
			else
			{
				//! If this is a gun with attached mag and we are not in combat, reload when mag is empty
				//! even if chamber is not empty
				Magazine currentMag = weapon.GetMagazine(mi);
				if (currentMag)
				{
					int ammoCount = currentMag.GetAmmoCount();
					//! Don't reload if attached mag is still at capacity
					if (ammoCount >= currentMag.GetAmmoMax() - 1)
					return FAIL;
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					//! Don't swap magazine if attached mag is not empty
					if (!magazine.IsAmmoPile() && ammoCount > 0)
					return FAIL;
				}
				else
				{
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					if (magazine.IsAmmoPile())
					return FAIL;
				}
			}
		}
		if (unit.GetWeaponManager().CanUnjam(weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		dst.sub_fsm.weapon = weapon;
		dst.sub_fsm.magazine = magazine;
		return SUCCESS;
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
		if (GetGame().GetTime() - dst.sub_fsm.last_attempt_time < 1000) return FAIL;
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, unit.GetItemInHands())) return FAIL;
		//! Allow sub-FSM to handle destroyed weapon so it gets dropped
		if (weapon.IsDamageDestroyed()) return SUCCESS;
		Magazine magazine;
		if (weapon.Expansion_IsChambered())
		{
			if (!unit.eAI_IsSafeToFillMag()) return FAIL;
			int mi = weapon.GetCurrentMuzzle();
			if (weapon.HasInternalMagazine(mi))
			{
				//! If this is a gun with internal mag and we are not in combat, reload when mag is not at capacity
				//! even if chamber is not empty
				if (weapon.GetInternalMagazineCartridgeCount(mi) >= weapon.GetInternalMagazineMaxCartridgeCount(mi) - 1)
				return FAIL;
				if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
				return FAIL;
			}
			else
			{
				//! If this is a gun with attached mag and we are not in combat, reload when mag is empty
				//! even if chamber is not empty
				Magazine currentMag = weapon.GetMagazine(mi);
				if (currentMag)
				{
					int ammoCount = currentMag.GetAmmoCount();
					//! Don't reload if attached mag is still at capacity
					if (ammoCount >= currentMag.GetAmmoMax() - 1)
					return FAIL;
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					//! Don't swap magazine if attached mag is not empty
					if (!magazine.IsAmmoPile() && ammoCount > 0)
					return FAIL;
				}
				else
				{
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					if (magazine.IsAmmoPile())
					return FAIL;
				}
			}
		}
		if (unit.GetWeaponManager().CanUnjam(weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		dst.sub_fsm.weapon = weapon;
		dst.sub_fsm.magazine = magazine;
		return SUCCESS;
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
		if (GetGame().GetTime() - dst.sub_fsm.last_attempt_time < 1000) return FAIL;
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, unit.GetItemInHands())) return FAIL;
		//! Allow sub-FSM to handle destroyed weapon so it gets dropped
		if (weapon.IsDamageDestroyed()) return SUCCESS;
		Magazine magazine;
		if (weapon.Expansion_IsChambered())
		{
			if (!unit.eAI_IsSafeToFillMag()) return FAIL;
			int mi = weapon.GetCurrentMuzzle();
			if (weapon.HasInternalMagazine(mi))
			{
				//! If this is a gun with internal mag and we are not in combat, reload when mag is not at capacity
				//! even if chamber is not empty
				if (weapon.GetInternalMagazineCartridgeCount(mi) >= weapon.GetInternalMagazineMaxCartridgeCount(mi) - 1)
				return FAIL;
				if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
				return FAIL;
			}
			else
			{
				//! If this is a gun with attached mag and we are not in combat, reload when mag is empty
				//! even if chamber is not empty
				Magazine currentMag = weapon.GetMagazine(mi);
				if (currentMag)
				{
					int ammoCount = currentMag.GetAmmoCount();
					//! Don't reload if attached mag is still at capacity
					if (ammoCount >= currentMag.GetAmmoMax() - 1)
					return FAIL;
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					//! Don't swap magazine if attached mag is not empty
					if (!magazine.IsAmmoPile() && ammoCount > 0)
					return FAIL;
				}
				else
				{
					if (!unit.eAI_HasAmmoForFirearm(weapon, magazine))
					return FAIL;
					if (magazine.IsAmmoPile())
					return FAIL;
				}
			}
		}
		if (unit.GetWeaponManager().CanUnjam(weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		dst.sub_fsm.weapon = weapon;
		dst.sub_fsm.magazine = magazine;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		ItemBase hands = unit.GetItemInHands();
		//! If ruined, drop
		if (hands && hands.IsDamageDestroyed())
		{
			unit.eAI_DropItem(hands, false);
			hands = null;
		}
		//! First check if we want to switch to bandage
		if (unit.eAI_ShouldBandage())
		{
			if (!hands || !hands.Expansion_CanBeUsedToBandage())
			{
				//! Item in hand is either not bandage/rag or is ruined
				dst.item = unit.GetBandageToUse();
				if (dst.item)
				{
					return SUCCESS;
				}
			}
			else
			{
				//! Item in hands and can be used to bandage
				return FAIL;
			}
		}
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (target)
		Class.CastTo(targetItem, target.GetEntity());
		bool preferExplosiveAmmo;
		bool preferMelee;
		bool hasMeleeInHands;
		bool preferTargetItem;
		if (hands)
		{
			if (hands.Expansion_IsMeleeWeapon())
			hasMeleeInHands = true;
			if (target)
			{
				if (target.IsMechanicalTrap() && target.IsActive() && !target.IsExplosive() && !target.CanPutInCargo(unit))
				{
					preferMelee = true;
				}
				else if (target.IsZombie())
				{
					if ((hasMeleeInHands || (!hands.eAI_IsSilent() && GetGame().GetTime() - dst.requestSwapToMeleeForZombieTime > 60000)) && unit.m_eAI_SilentAttackViabilityTime > 2.0 && unit.eAI_HasLOS() && unit.GetHealth01() > 0.8)
					{
						preferMelee = true;
						if (!hasMeleeInHands)
						dst.requestSwapToMeleeForZombieTime = GetGame().GetTime();
					}
				}
			}
			if (preferMelee)
			{
				if (hasMeleeInHands)
				return FAIL;
			}
			else if (targetItem && unit.eAI_WeaponSelection(hands, targetItem))
			{
				preferTargetItem = true;
			}
			else if (hands.IsWeapon())
			{
				if (unit.eAI_ShouldPreferExplosiveAmmo())
				{
					if (hands.ShootsExplosiveAmmo())
					return FAIL;
					else
					preferExplosiveAmmo = true;
				}
			}
		}
		ItemBase item;  //! The item we may want to take to hands
		if (!preferMelee)
		{
			if (!preferTargetItem)
			{
				item = unit.eAI_GetWeaponToUse(true, preferExplosiveAmmo);
				if (item)
				{
					if (hands)
					{
						if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
						return FAIL;
					}
					dst.item = item;
					EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee or target and weapon to use is not current hand item or better than " + hands);
					return SUCCESS;
				}
			}
			if (targetItem && ((targetItem.IsWeapon() && (!preferExplosiveAmmo || targetItem.ShootsExplosiveAmmo())) || (!preferExplosiveAmmo && targetItem.Expansion_IsMeleeWeapon() && (!hasMeleeInHands || hands.Expansion_CompareDPS(targetItem) < 0))) && !targetItem.Expansion_GetRootPlayerAliveExcluding(null) && !targetItem.IsSetForDeletion())
			{
				if (target.GetDistanceSq(true) <= 4.0 && target.GetThreat() > 0.1 && !unit.eAI_IsItemObstructed(targetItem))
				{
					dst.item = targetItem;
					EXTrace.Print(EXTrace.AI, unit, "Taking target " + targetItem + " to hands because not prefering melee but prefering target over " + hands);
					return SUCCESS;
				}
			}
			if (!preferTargetItem && !preferExplosiveAmmo)
			{
				item = unit.eAI_GetWeaponToUse(true, false);
				//! If we have no non-explosive ammo weapon and target is not an item and distance is at least 30 m,
				//! use explosive ammo weapon if we have any
				if (!item && target && !targetItem && target.GetDistanceSq() > 30.0)
				item = unit.eAI_GetWeaponToUse(true, true);
			}
			if (item)
			{
				if (hands)
				{
					if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
					return FAIL;
				}
				dst.item = item;
				EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee and weapon to use is not current hand item or better than " + hands);
				return SUCCESS;
			}
			if (hands)
			return FAIL;
		}
		if (hasMeleeInHands)
		return FAIL;
		item = unit.GetMeleeWeaponToUse();
		if (item)
		{
			if (hands)
			{
				if (item == hands || item.Expansion_GetHierarchyRootItem() == hands)
				return FAIL;
			}
			dst.item = item;
			return SUCCESS;
		}
		return FAIL;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		ItemBase hands = unit.GetItemInHands();
		//! If ruined, drop
		if (hands && hands.IsDamageDestroyed())
		{
			unit.eAI_DropItem(hands, false);
			hands = null;
		}
		//! First check if we want to switch to bandage
		if (unit.eAI_ShouldBandage())
		{
			if (!hands || !hands.Expansion_CanBeUsedToBandage())
			{
				//! Item in hand is either not bandage/rag or is ruined
				dst.item = unit.GetBandageToUse();
				if (dst.item)
				{
					return SUCCESS;
				}
			}
			else
			{
				//! Item in hands and can be used to bandage
				return FAIL;
			}
		}
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (target)
		Class.CastTo(targetItem, target.GetEntity());
		bool preferExplosiveAmmo;
		bool preferMelee;
		bool hasMeleeInHands;
		bool preferTargetItem;
		if (hands)
		{
			if (hands.Expansion_IsMeleeWeapon())
			hasMeleeInHands = true;
			if (target)
			{
				if (target.IsMechanicalTrap() && target.IsActive() && !target.IsExplosive() && !target.CanPutInCargo(unit))
				{
					preferMelee = true;
				}
				else if (target.IsZombie())
				{
					if ((hasMeleeInHands || (!hands.eAI_IsSilent() && GetGame().GetTime() - dst.requestSwapToMeleeForZombieTime > 60000)) && unit.m_eAI_SilentAttackViabilityTime > 2.0 && unit.eAI_HasLOS() && unit.GetHealth01() > 0.8)
					{
						preferMelee = true;
						if (!hasMeleeInHands)
						dst.requestSwapToMeleeForZombieTime = GetGame().GetTime();
					}
				}
			}
			if (preferMelee)
			{
				if (hasMeleeInHands)
				return FAIL;
			}
			else if (targetItem && unit.eAI_WeaponSelection(hands, targetItem))
			{
				preferTargetItem = true;
			}
			else if (hands.IsWeapon())
			{
				if (unit.eAI_ShouldPreferExplosiveAmmo())
				{
					if (hands.ShootsExplosiveAmmo())
					return FAIL;
					else
					preferExplosiveAmmo = true;
				}
			}
		}
		ItemBase item;  //! The item we may want to take to hands
		if (!preferMelee)
		{
			if (!preferTargetItem)
			{
				item = unit.eAI_GetWeaponToUse(true, preferExplosiveAmmo);
				if (item)
				{
					if (hands)
					{
						if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
						return FAIL;
					}
					dst.item = item;
					EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee or target and weapon to use is not current hand item or better than " + hands);
					return SUCCESS;
				}
			}
			if (targetItem && ((targetItem.IsWeapon() && (!preferExplosiveAmmo || targetItem.ShootsExplosiveAmmo())) || (!preferExplosiveAmmo && targetItem.Expansion_IsMeleeWeapon() && (!hasMeleeInHands || hands.Expansion_CompareDPS(targetItem) < 0))) && !targetItem.Expansion_GetRootPlayerAliveExcluding(null) && !targetItem.IsSetForDeletion())
			{
				if (target.GetDistanceSq(true) <= 4.0 && target.GetThreat() > 0.1 && !unit.eAI_IsItemObstructed(targetItem))
				{
					dst.item = targetItem;
					EXTrace.Print(EXTrace.AI, unit, "Taking target " + targetItem + " to hands because not prefering melee but prefering target over " + hands);
					return SUCCESS;
				}
			}
			if (!preferTargetItem && !preferExplosiveAmmo)
			{
				item = unit.eAI_GetWeaponToUse(true, false);
				//! If we have no non-explosive ammo weapon and target is not an item and distance is at least 30 m,
				//! use explosive ammo weapon if we have any
				if (!item && target && !targetItem && target.GetDistanceSq() > 30.0)
				item = unit.eAI_GetWeaponToUse(true, true);
			}
			if (item)
			{
				if (hands)
				{
					if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
					return FAIL;
				}
				dst.item = item;
				EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee and weapon to use is not current hand item or better than " + hands);
				return SUCCESS;
			}
			if (hands)
			return FAIL;
		}
		if (hasMeleeInHands)
		return FAIL;
		item = unit.GetMeleeWeaponToUse();
		if (item)
		{
			if (hands)
			{
				if (item == hands || item.Expansion_GetHierarchyRootItem() == hands)
				return FAIL;
			}
			dst.item = item;
			return SUCCESS;
		}
		return FAIL;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		ItemBase hands = unit.GetItemInHands();
		//! If ruined, drop
		if (hands && hands.IsDamageDestroyed())
		{
			unit.eAI_DropItem(hands, false);
			hands = null;
		}
		//! First check if we want to switch to bandage
		if (unit.eAI_ShouldBandage())
		{
			if (!hands || !hands.Expansion_CanBeUsedToBandage())
			{
				//! Item in hand is either not bandage/rag or is ruined
				dst.item = unit.GetBandageToUse();
				if (dst.item)
				{
					return SUCCESS;
				}
			}
			else
			{
				//! Item in hands and can be used to bandage
				return FAIL;
			}
		}
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (target)
		Class.CastTo(targetItem, target.GetEntity());
		bool preferExplosiveAmmo;
		bool preferMelee;
		bool hasMeleeInHands;
		bool preferTargetItem;
		if (hands)
		{
			if (hands.Expansion_IsMeleeWeapon())
			hasMeleeInHands = true;
			if (target)
			{
				if (target.IsMechanicalTrap() && target.IsActive() && !target.IsExplosive() && !target.CanPutInCargo(unit))
				{
					preferMelee = true;
				}
				else if (target.IsZombie())
				{
					if ((hasMeleeInHands || (!hands.eAI_IsSilent() && GetGame().GetTime() - dst.requestSwapToMeleeForZombieTime > 60000)) && unit.m_eAI_SilentAttackViabilityTime > 2.0 && unit.eAI_HasLOS() && unit.GetHealth01() > 0.8)
					{
						preferMelee = true;
						if (!hasMeleeInHands)
						dst.requestSwapToMeleeForZombieTime = GetGame().GetTime();
					}
				}
			}
			if (preferMelee)
			{
				if (hasMeleeInHands)
				return FAIL;
			}
			else if (targetItem && unit.eAI_WeaponSelection(hands, targetItem))
			{
				preferTargetItem = true;
			}
			else if (hands.IsWeapon())
			{
				if (unit.eAI_ShouldPreferExplosiveAmmo())
				{
					if (hands.ShootsExplosiveAmmo())
					return FAIL;
					else
					preferExplosiveAmmo = true;
				}
			}
		}
		ItemBase item;  //! The item we may want to take to hands
		if (!preferMelee)
		{
			if (!preferTargetItem)
			{
				item = unit.eAI_GetWeaponToUse(true, preferExplosiveAmmo);
				if (item)
				{
					if (hands)
					{
						if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
						return FAIL;
					}
					dst.item = item;
					EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee or target and weapon to use is not current hand item or better than " + hands);
					return SUCCESS;
				}
			}
			if (targetItem && ((targetItem.IsWeapon() && (!preferExplosiveAmmo || targetItem.ShootsExplosiveAmmo())) || (!preferExplosiveAmmo && targetItem.Expansion_IsMeleeWeapon() && (!hasMeleeInHands || hands.Expansion_CompareDPS(targetItem) < 0))) && !targetItem.Expansion_GetRootPlayerAliveExcluding(null) && !targetItem.IsSetForDeletion())
			{
				if (target.GetDistanceSq(true) <= 4.0 && target.GetThreat() > 0.1 && !unit.eAI_IsItemObstructed(targetItem))
				{
					dst.item = targetItem;
					EXTrace.Print(EXTrace.AI, unit, "Taking target " + targetItem + " to hands because not prefering melee but prefering target over " + hands);
					return SUCCESS;
				}
			}
			if (!preferTargetItem && !preferExplosiveAmmo)
			{
				item = unit.eAI_GetWeaponToUse(true, false);
				//! If we have no non-explosive ammo weapon and target is not an item and distance is at least 30 m,
				//! use explosive ammo weapon if we have any
				if (!item && target && !targetItem && target.GetDistanceSq() > 30.0)
				item = unit.eAI_GetWeaponToUse(true, true);
			}
			if (item)
			{
				if (hands)
				{
					if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
					return FAIL;
				}
				dst.item = item;
				EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee and weapon to use is not current hand item or better than " + hands);
				return SUCCESS;
			}
			if (hands)
			return FAIL;
		}
		if (hasMeleeInHands)
		return FAIL;
		item = unit.GetMeleeWeaponToUse();
		if (item)
		{
			if (hands)
			{
				if (item == hands || item.Expansion_GetHierarchyRootItem() == hands)
				return FAIL;
			}
			dst.item = item;
			return SUCCESS;
		}
		return FAIL;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		ItemBase hands = unit.GetItemInHands();
		//! If ruined, drop
		if (hands && hands.IsDamageDestroyed())
		{
			unit.eAI_DropItem(hands, false);
			hands = null;
		}
		//! First check if we want to switch to bandage
		if (unit.eAI_ShouldBandage())
		{
			if (!hands || !hands.Expansion_CanBeUsedToBandage())
			{
				//! Item in hand is either not bandage/rag or is ruined
				dst.item = unit.GetBandageToUse();
				if (dst.item)
				{
					return SUCCESS;
				}
			}
			else
			{
				//! Item in hands and can be used to bandage
				return FAIL;
			}
		}
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (target)
		Class.CastTo(targetItem, target.GetEntity());
		bool preferExplosiveAmmo;
		bool preferMelee;
		bool hasMeleeInHands;
		bool preferTargetItem;
		if (hands)
		{
			if (hands.Expansion_IsMeleeWeapon())
			hasMeleeInHands = true;
			if (target)
			{
				if (target.IsMechanicalTrap() && target.IsActive() && !target.IsExplosive() && !target.CanPutInCargo(unit))
				{
					preferMelee = true;
				}
				else if (target.IsZombie())
				{
					if ((hasMeleeInHands || (!hands.eAI_IsSilent() && GetGame().GetTime() - dst.requestSwapToMeleeForZombieTime > 60000)) && unit.m_eAI_SilentAttackViabilityTime > 2.0 && unit.eAI_HasLOS() && unit.GetHealth01() > 0.8)
					{
						preferMelee = true;
						if (!hasMeleeInHands)
						dst.requestSwapToMeleeForZombieTime = GetGame().GetTime();
					}
				}
			}
			if (preferMelee)
			{
				if (hasMeleeInHands)
				return FAIL;
			}
			else if (targetItem && unit.eAI_WeaponSelection(hands, targetItem))
			{
				preferTargetItem = true;
			}
			else if (hands.IsWeapon())
			{
				if (unit.eAI_ShouldPreferExplosiveAmmo())
				{
					if (hands.ShootsExplosiveAmmo())
					return FAIL;
					else
					preferExplosiveAmmo = true;
				}
			}
		}
		ItemBase item;  //! The item we may want to take to hands
		if (!preferMelee)
		{
			if (!preferTargetItem)
			{
				item = unit.eAI_GetWeaponToUse(true, preferExplosiveAmmo);
				if (item)
				{
					if (hands)
					{
						if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
						return FAIL;
					}
					dst.item = item;
					EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee or target and weapon to use is not current hand item or better than " + hands);
					return SUCCESS;
				}
			}
			if (targetItem && ((targetItem.IsWeapon() && (!preferExplosiveAmmo || targetItem.ShootsExplosiveAmmo())) || (!preferExplosiveAmmo && targetItem.Expansion_IsMeleeWeapon() && (!hasMeleeInHands || hands.Expansion_CompareDPS(targetItem) < 0))) && !targetItem.Expansion_GetRootPlayerAliveExcluding(null) && !targetItem.IsSetForDeletion())
			{
				if (target.GetDistanceSq(true) <= 4.0 && target.GetThreat() > 0.1 && !unit.eAI_IsItemObstructed(targetItem))
				{
					dst.item = targetItem;
					EXTrace.Print(EXTrace.AI, unit, "Taking target " + targetItem + " to hands because not prefering melee but prefering target over " + hands);
					return SUCCESS;
				}
			}
			if (!preferTargetItem && !preferExplosiveAmmo)
			{
				item = unit.eAI_GetWeaponToUse(true, false);
				//! If we have no non-explosive ammo weapon and target is not an item and distance is at least 30 m,
				//! use explosive ammo weapon if we have any
				if (!item && target && !targetItem && target.GetDistanceSq() > 30.0)
				item = unit.eAI_GetWeaponToUse(true, true);
			}
			if (item)
			{
				if (hands)
				{
					if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
					return FAIL;
				}
				dst.item = item;
				EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee and weapon to use is not current hand item or better than " + hands);
				return SUCCESS;
			}
			if (hands)
			return FAIL;
		}
		if (hasMeleeInHands)
		return FAIL;
		item = unit.GetMeleeWeaponToUse();
		if (item)
		{
			if (hands)
			{
				if (item == hands || item.Expansion_GetHierarchyRootItem() == hands)
				return FAIL;
			}
			dst.item = item;
			return SUCCESS;
		}
		return FAIL;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		ItemBase hands = unit.GetItemInHands();
		//! If ruined, drop
		if (hands && hands.IsDamageDestroyed())
		{
			unit.eAI_DropItem(hands, false);
			hands = null;
		}
		//! First check if we want to switch to bandage
		if (unit.eAI_ShouldBandage())
		{
			if (!hands || !hands.Expansion_CanBeUsedToBandage())
			{
				//! Item in hand is either not bandage/rag or is ruined
				dst.item = unit.GetBandageToUse();
				if (dst.item)
				{
					return SUCCESS;
				}
			}
			else
			{
				//! Item in hands and can be used to bandage
				return FAIL;
			}
		}
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (target)
		Class.CastTo(targetItem, target.GetEntity());
		bool preferExplosiveAmmo;
		bool preferMelee;
		bool hasMeleeInHands;
		bool preferTargetItem;
		if (hands)
		{
			if (hands.Expansion_IsMeleeWeapon())
			hasMeleeInHands = true;
			if (target)
			{
				if (target.IsMechanicalTrap() && target.IsActive() && !target.IsExplosive() && !target.CanPutInCargo(unit))
				{
					preferMelee = true;
				}
				else if (target.IsZombie())
				{
					if ((hasMeleeInHands || (!hands.eAI_IsSilent() && GetGame().GetTime() - dst.requestSwapToMeleeForZombieTime > 60000)) && unit.m_eAI_SilentAttackViabilityTime > 2.0 && unit.eAI_HasLOS() && unit.GetHealth01() > 0.8)
					{
						preferMelee = true;
						if (!hasMeleeInHands)
						dst.requestSwapToMeleeForZombieTime = GetGame().GetTime();
					}
				}
			}
			if (preferMelee)
			{
				if (hasMeleeInHands)
				return FAIL;
			}
			else if (targetItem && unit.eAI_WeaponSelection(hands, targetItem))
			{
				preferTargetItem = true;
			}
			else if (hands.IsWeapon())
			{
				if (unit.eAI_ShouldPreferExplosiveAmmo())
				{
					if (hands.ShootsExplosiveAmmo())
					return FAIL;
					else
					preferExplosiveAmmo = true;
				}
			}
		}
		ItemBase item;  //! The item we may want to take to hands
		if (!preferMelee)
		{
			if (!preferTargetItem)
			{
				item = unit.eAI_GetWeaponToUse(true, preferExplosiveAmmo);
				if (item)
				{
					if (hands)
					{
						if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
						return FAIL;
					}
					dst.item = item;
					EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee or target and weapon to use is not current hand item or better than " + hands);
					return SUCCESS;
				}
			}
			if (targetItem && ((targetItem.IsWeapon() && (!preferExplosiveAmmo || targetItem.ShootsExplosiveAmmo())) || (!preferExplosiveAmmo && targetItem.Expansion_IsMeleeWeapon() && (!hasMeleeInHands || hands.Expansion_CompareDPS(targetItem) < 0))) && !targetItem.Expansion_GetRootPlayerAliveExcluding(null) && !targetItem.IsSetForDeletion())
			{
				if (target.GetDistanceSq(true) <= 4.0 && target.GetThreat() > 0.1 && !unit.eAI_IsItemObstructed(targetItem))
				{
					dst.item = targetItem;
					EXTrace.Print(EXTrace.AI, unit, "Taking target " + targetItem + " to hands because not prefering melee but prefering target over " + hands);
					return SUCCESS;
				}
			}
			if (!preferTargetItem && !preferExplosiveAmmo)
			{
				item = unit.eAI_GetWeaponToUse(true, false);
				//! If we have no non-explosive ammo weapon and target is not an item and distance is at least 30 m,
				//! use explosive ammo weapon if we have any
				if (!item && target && !targetItem && target.GetDistanceSq() > 30.0)
				item = unit.eAI_GetWeaponToUse(true, true);
			}
			if (item)
			{
				if (hands)
				{
					if (item == hands || item.Expansion_GetHierarchyRootItem() == hands || !unit.eAI_WeaponSelection(hands, item))
					return FAIL;
				}
				dst.item = item;
				EXTrace.Print(EXTrace.AI, unit, "Taking " + item + " to hands because not prefering melee and weapon to use is not current hand item or better than " + hands);
				return SUCCESS;
			}
			if (hands)
			return FAIL;
		}
		if (hasMeleeInHands)
		return FAIL;
		item = unit.GetMeleeWeaponToUse();
		if (item)
		{
			if (hands)
			{
				if (item == hands || item.Expansion_GetHierarchyRootItem() == hands)
				return FAIL;
			}
			dst.item = item;
			return SUCCESS;
		}
		return FAIL;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		if (unit.IsRaised()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (!target || !Class.CastTo(targetItem, target.GetEntity()) || targetItem.Expansion_GetRootPlayerAliveExcluding(null) || targetItem.IsSetForDeletion() || unit.eAI_GetThreatOverride(targetItem))
		return FAIL;
		bool isClothing;
		if (targetItem.IsClothing())
		isClothing = true;
		if (targetItem.Expansion_IsLiveExplosive() || (!isClothing && !targetItem.CanPutInCargo(unit)))
		return FAIL;
		if (target.GetDistanceSq(true) > 4.0 || unit.eAI_IsItemObstructed(targetItem))
		return FAIL;
		if (target.GetThreat() <= 0.1)
		return FAIL;
		if (targetItem.IsWeapon())
		{
			//! PREPARE SWAP FROM CURRENT HAND ITEM TO GUN IN INV OR ON GROUND
			//! If target is gun and we have melee or bandage in hand (but shouldn't bandage right now), prepare swap
			ItemBase hands = unit.GetItemInHands();
			if (hands && (hands.Expansion_IsMeleeWeapon() || (hands.Expansion_CanBeUsedToBandage() && !unit.eAI_ShouldBandage())))
			{
				//! Only drop hand item if destroyed or doesn't fit in inventory
				if (hands.IsDamageDestroyed())
				{
					unit.eAI_DropItem(hands, false);
				}
				else if (!unit.eAI_TakeItemToInventory(hands))
				{
					unit.eAI_ThreatOverride(hands, true);  //! Make sure we do not attempt to take it again after  dropping
					unit.eAI_DropItem(hands, false);
				}
			}
			return FAIL;  //! Picking up guns is handled by TakeItemToHands state
		}
		else if (targetItem.Expansion_IsMeleeWeapon())
		{
			//! Picking up melee weapons is handled by TakeItemToHands state
			return FAIL;
		}
		if (!isClothing && !unit.eAI_FindFreeInventoryLocationFor(targetItem))
		{
			unit.eAI_ThreatOverride(targetItem, true);
			return FAIL;
		}
		unit.eAI_ThreatOverride(targetItem, false);
		dst.item = targetItem;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		if (unit.IsRaised()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (!target || !Class.CastTo(targetItem, target.GetEntity()) || targetItem.Expansion_GetRootPlayerAliveExcluding(null) || targetItem.IsSetForDeletion() || unit.eAI_GetThreatOverride(targetItem))
		return FAIL;
		bool isClothing;
		if (targetItem.IsClothing())
		isClothing = true;
		if (targetItem.Expansion_IsLiveExplosive() || (!isClothing && !targetItem.CanPutInCargo(unit)))
		return FAIL;
		if (target.GetDistanceSq(true) > 4.0 || unit.eAI_IsItemObstructed(targetItem))
		return FAIL;
		if (target.GetThreat() <= 0.1)
		return FAIL;
		if (targetItem.IsWeapon())
		{
			//! PREPARE SWAP FROM CURRENT HAND ITEM TO GUN IN INV OR ON GROUND
			//! If target is gun and we have melee or bandage in hand (but shouldn't bandage right now), prepare swap
			ItemBase hands = unit.GetItemInHands();
			if (hands && (hands.Expansion_IsMeleeWeapon() || (hands.Expansion_CanBeUsedToBandage() && !unit.eAI_ShouldBandage())))
			{
				//! Only drop hand item if destroyed or doesn't fit in inventory
				if (hands.IsDamageDestroyed())
				{
					unit.eAI_DropItem(hands, false);
				}
				else if (!unit.eAI_TakeItemToInventory(hands))
				{
					unit.eAI_ThreatOverride(hands, true);  //! Make sure we do not attempt to take it again after  dropping
					unit.eAI_DropItem(hands, false);
				}
			}
			return FAIL;  //! Picking up guns is handled by TakeItemToHands state
		}
		else if (targetItem.Expansion_IsMeleeWeapon())
		{
			//! Picking up melee weapons is handled by TakeItemToHands state
			return FAIL;
		}
		if (!isClothing && !unit.eAI_FindFreeInventoryLocationFor(targetItem))
		{
			unit.eAI_ThreatOverride(targetItem, true);
			return FAIL;
		}
		unit.eAI_ThreatOverride(targetItem, false);
		dst.item = targetItem;
		return SUCCESS;
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
		if (unit.IsFighting()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (unit.eAI_IsChangingStance())
		return FAIL;
		if (unit.IsRaised()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		eAITarget target = unit.GetTarget();
		ItemBase targetItem;
		if (!target || !Class.CastTo(targetItem, target.GetEntity()) || targetItem.Expansion_GetRootPlayerAliveExcluding(null) || targetItem.IsSetForDeletion() || unit.eAI_GetThreatOverride(targetItem))
		return FAIL;
		bool isClothing;
		if (targetItem.IsClothing())
		isClothing = true;
		if (targetItem.Expansion_IsLiveExplosive() || (!isClothing && !targetItem.CanPutInCargo(unit)))
		return FAIL;
		if (target.GetDistanceSq(true) > 4.0 || unit.eAI_IsItemObstructed(targetItem))
		return FAIL;
		if (target.GetThreat() <= 0.1)
		return FAIL;
		if (targetItem.IsWeapon())
		{
			//! PREPARE SWAP FROM CURRENT HAND ITEM TO GUN IN INV OR ON GROUND
			//! If target is gun and we have melee or bandage in hand (but shouldn't bandage right now), prepare swap
			ItemBase hands = unit.GetItemInHands();
			if (hands && (hands.Expansion_IsMeleeWeapon() || (hands.Expansion_CanBeUsedToBandage() && !unit.eAI_ShouldBandage())))
			{
				//! Only drop hand item if destroyed or doesn't fit in inventory
				if (hands.IsDamageDestroyed())
				{
					unit.eAI_DropItem(hands, false);
				}
				else if (!unit.eAI_TakeItemToInventory(hands))
				{
					unit.eAI_ThreatOverride(hands, true);  //! Make sure we do not attempt to take it again after  dropping
					unit.eAI_DropItem(hands, false);
				}
			}
			return FAIL;  //! Picking up guns is handled by TakeItemToHands state
		}
		else if (targetItem.Expansion_IsMeleeWeapon())
		{
			//! Picking up melee weapons is handled by TakeItemToHands state
			return FAIL;
		}
		if (!isClothing && !unit.eAI_FindFreeInventoryLocationFor(targetItem))
		{
			unit.eAI_ThreatOverride(targetItem, true);
			return FAIL;
		}
		unit.eAI_ThreatOverride(targetItem, false);
		dst.item = targetItem;
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
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!Class.CastTo(dst.weapon, unit.GetItemInHands())) return FAIL;
		if (!unit.GetWeaponManager().CanUnjam(dst.weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		return SUCCESS;
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
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!Class.CastTo(dst.weapon, unit.GetItemInHands())) return FAIL;
		if (!unit.GetWeaponManager().CanUnjam(dst.weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		return SUCCESS;
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
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!Class.CastTo(dst.weapon, unit.GetItemInHands())) return FAIL;
		if (!unit.GetWeaponManager().CanUnjam(dst.weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		return SUCCESS;
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
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!Class.CastTo(dst.weapon, unit.GetItemInHands())) return FAIL;
		if (!unit.GetWeaponManager().CanUnjam(dst.weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		return SUCCESS;
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
		if (unit.IsClimbing() || unit.IsFalling() || unit.IsFighting() || !unit.GetCommand_MoveAI()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!Class.CastTo(dst.weapon, unit.GetItemInHands())) return FAIL;
		if (!unit.GetWeaponManager().CanUnjam(dst.weapon)) return FAIL;
		// don't move to the state if the action manager is operating
		if (!unit.GetActionManager() || unit.GetActionManager().GetRunningAction()) return FAIL;
		return SUCCESS;
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
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.GetThreatToSelf() < 0.4) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
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
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.GetThreatToSelf() < 0.4) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
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
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.GetThreatToSelf() < 0.4) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
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
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.GetThreatToSelf() < 0.4) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
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
		if (unit.GetThreatToSelf() > 0.2) return FAIL;
		if (unit.IsFighting()) return FAIL;
		return SUCCESS;
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
		if (unit.IsInTransport()) return FAIL;
		return SUCCESS;
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
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (!leader.IsInTransport()) return FAIL;
		CarScript car;
		if (!Class.CastTo(car, leader.GetParent())) return FAIL;
		//TODO: make this event based instead and store as a variable within CarScript.
		//Prevents looping through the crew and insteads just compares a bool.
		for (int i = 1; i < car.CrewSize(); i++)
		{
			if (car.CrewMember(i) == null && !car.Expansion_IsSeatReservedByOther(i, unit) && car.IsAreaAtDoorFree(i))
			{
				dst.sub_fsm.seat = i;
				dst.sub_fsm.entity = car;
				car.Expansion_ReserveSeat(i, unit);
				return SUCCESS;
			}
		}
		return FAIL;
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
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (!leader.IsInTransport()) return FAIL;
		CarScript car;
		if (!Class.CastTo(car, leader.GetParent())) return FAIL;
		//TODO: make this event based instead and store as a variable within CarScript.
		//Prevents looping through the crew and insteads just compares a bool.
		for (int i = 1; i < car.CrewSize(); i++)
		{
			if (car.CrewMember(i) == null && !car.Expansion_IsSeatReservedByOther(i, unit) && car.IsAreaAtDoorFree(i))
			{
				dst.sub_fsm.seat = i;
				dst.sub_fsm.entity = car;
				car.Expansion_ReserveSeat(i, unit);
				return SUCCESS;
			}
		}
		return FAIL;
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
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (!leader.IsInTransport()) return FAIL;
		CarScript car;
		if (!Class.CastTo(car, leader.GetParent())) return FAIL;
		//TODO: make this event based instead and store as a variable within CarScript.
		//Prevents looping through the crew and insteads just compares a bool.
		for (int i = 1; i < car.CrewSize(); i++)
		{
			if (car.CrewMember(i) == null && !car.Expansion_IsSeatReservedByOther(i, unit) && car.IsAreaAtDoorFree(i))
			{
				dst.sub_fsm.seat = i;
				dst.sub_fsm.entity = car;
				car.Expansion_ReserveSeat(i, unit);
				return SUCCESS;
			}
		}
		return FAIL;
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
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (!leader.IsInTransport()) return FAIL;
		CarScript car;
		if (!Class.CastTo(car, leader.GetParent())) return FAIL;
		//TODO: make this event based instead and store as a variable within CarScript.
		//Prevents looping through the crew and insteads just compares a bool.
		for (int i = 1; i < car.CrewSize(); i++)
		{
			if (car.CrewMember(i) == null && !car.Expansion_IsSeatReservedByOther(i, unit) && car.IsAreaAtDoorFree(i))
			{
				dst.sub_fsm.seat = i;
				dst.sub_fsm.entity = car;
				car.Expansion_ReserveSeat(i, unit);
				return SUCCESS;
			}
		}
		return FAIL;
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
		if (unit.IsRaised()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsClimbing()) return FAIL;
		if (unit.IsFalling()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		if (unit.eAI_IsChangingStance()) return FAIL;
		if (!unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetEmoteManager().IsEmotePlaying() || unit.GetEmoteManager().Expansion_GetCurrentGesture() == unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetThreatToSelf(true) > 0.2) return FAIL;
		if (unit.IsFighting()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		auto hands = unit.GetItemInHands();
		if (hands && hands.Expansion_CanBeUsedToBandage())
		return FAIL;
		return SUCCESS;
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
		if (unit.IsRaised()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsClimbing()) return FAIL;
		if (unit.IsFalling()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		if (unit.eAI_IsChangingStance()) return FAIL;
		if (!unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetEmoteManager().IsEmotePlaying() || unit.GetEmoteManager().Expansion_GetCurrentGesture() == unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetThreatToSelf(true) > 0.2) return FAIL;
		if (unit.IsFighting()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		auto hands = unit.GetItemInHands();
		if (hands && hands.Expansion_CanBeUsedToBandage())
		return FAIL;
		return SUCCESS;
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
		if (unit.IsRaised()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsClimbing()) return FAIL;
		if (unit.IsFalling()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		if (unit.eAI_IsChangingStance()) return FAIL;
		if (!unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetEmoteManager().IsEmotePlaying() || unit.GetEmoteManager().Expansion_GetCurrentGesture() == unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetThreatToSelf(true) > 0.2) return FAIL;
		if (unit.IsFighting()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		auto hands = unit.GetItemInHands();
		if (hands && hands.Expansion_CanBeUsedToBandage())
		return FAIL;
		return SUCCESS;
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
		if (unit.IsRaised()) return FAIL;
		if (unit.IsRestrained()) return FAIL;
		if (unit.IsUnconscious()) return FAIL;
		if (unit.IsClimbing()) return FAIL;
		if (unit.IsFalling()) return FAIL;
		if (unit.IsSwimming()) return FAIL;
		if (!unit.GetCommand_MoveAI()) return FAIL;
		if (unit.eAI_IsChangingStance()) return FAIL;
		if (!unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetEmoteManager().IsEmotePlaying() || unit.GetEmoteManager().Expansion_GetCurrentGesture() == unit.m_Expansion_EmoteID) return FAIL;
		if (unit.GetThreatToSelf(true) > 0.2) return FAIL;
		if (unit.IsFighting()) return FAIL;
		if (unit.GetWeaponManager().IsRunning()) return FAIL;
		if (unit.GetActionManager().GetRunningAction()) return FAIL;
		auto hands = unit.GetItemInHands();
		if (hands && hands.Expansion_CanBeUsedToBandage())
		return FAIL;
		return SUCCESS;
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
		dst.group = unit.GetGroup();
		if (!dst.group) return FAIL;
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (dst.group.IsInCombat())
		{
			eAITarget target = unit.GetTarget();
			if (target && !target.IsItem() && unit.GetThreatToSelf(true) >= 0.4) return FAIL;
		}
		if (dst.group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = dst.group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (leader.IsInTransport()) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_FollowFormation_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_FollowFormation_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_FollowFormation_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_FollowFormation_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_FollowFormation_State_0"));
	}
	override int Guard() {
		dst.group = unit.GetGroup();
		if (!dst.group) return FAIL;
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (dst.group.IsInCombat())
		{
			eAITarget target = unit.GetTarget();
			if (target && !target.IsItem() && unit.GetThreatToSelf(true) >= 0.4) return FAIL;
		}
		if (dst.group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		auto leader = dst.group.GetFormationLeader();
		if (!leader || leader == unit) return FAIL;
		if (leader.IsInTransport()) return FAIL;
		return SUCCESS;
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
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (group.IsInCombat())
		{
			eAITarget target = unit.GetTarget();
			if (target && !target.IsItem() && unit.GetThreatToSelf(true) >= 0.4) return FAIL;
		}
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		// we are the leader so we traverse the waypoints
		auto leader = group.GetFormationLeader();
		if (leader && leader != unit) return FAIL;
		if (leader.IsInTransport()) return FAIL;
		if (group.GetWaypoints().Count() == 0 && group.GetWaypointBehaviour() != eAIWaypointBehavior.ROAMING) return FAIL;
		return SUCCESS;
	}
	override ExpansionState GetSource() { return src; }
	override ExpansionState GetDestination() { return dst; }
	override string GetEvent() { return ""; }
}
class Expansion_Master_Flank_TraversingWaypoints_Transition_0: eAITransition {
	private Expansion_Master_Flank_State_0 src;
	private Expansion_Master_TraversingWaypoints_State_0 dst;
	Expansion_Master_FSM_0 fsm;
	void Expansion_Master_Flank_TraversingWaypoints_Transition_0(ExpansionFSM _fsm) {
		Class.CastTo(fsm, _fsm);
		m_ClassName = "Expansion_Master_Flank_TraversingWaypoints_Transition_0";
		Class.CastTo(src, _fsm.GetState("Expansion_Master_Flank_State_0"));
		Class.CastTo(dst, _fsm.GetState("Expansion_Master_TraversingWaypoints_State_0"));
	}
	override int Guard() {
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (group.IsInCombat())
		{
			eAITarget target = unit.GetTarget();
			if (target && !target.IsItem() && unit.GetThreatToSelf(true) >= 0.4) return FAIL;
		}
		if (group.GetFormationState() != eAIGroupFormationState.IN) return FAIL;
		// we are the leader so we traverse the waypoints
		auto leader = group.GetFormationLeader();
		if (leader && leader != unit) return FAIL;
		if (leader.IsInTransport()) return FAIL;
		if (group.GetWaypoints().Count() == 0 && group.GetWaypointBehaviour() != eAIWaypointBehavior.ROAMING) return FAIL;
		return SUCCESS;
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
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.FLANK && !group.IsInCombat()) return FAIL;
		dst.target = unit.GetTarget();
		if (!dst.target || dst.target.IsItem() || unit.GetThreatToSelf(true) < 0.4)
		return FAIL;
		//if (!unit.eAI_IsInFlankRange(dst.target)) return FAIL;
		return SUCCESS;
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
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.FLANK && !group.IsInCombat()) return FAIL;
		dst.target = unit.GetTarget();
		if (!dst.target || dst.target.IsItem() || unit.GetThreatToSelf(true) < 0.4)
		return FAIL;
		//if (!unit.eAI_IsInFlankRange(dst.target)) return FAIL;
		return SUCCESS;
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
		if (unit.GetThreatToSelf() >= 0.4) return FAIL;
		if (unit.IsInTransport()) return FAIL;
		auto group = unit.GetGroup();
		if (!group) return FAIL;
		if (group.GetFormationState() != eAIGroupFormationState.FLANK && !group.IsInCombat()) return FAIL;
		dst.target = unit.GetTarget();
		if (!dst.target || dst.target.IsItem() || unit.GetThreatToSelf(true) < 0.4)
		return FAIL;
		//if (!unit.eAI_IsInFlankRange(dst.target)) return FAIL;
		return SUCCESS;
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
		auto group = unit.GetGroup();
		if (group.GetFormationState() != eAIGroupFormationState.IN) return SUCCESS;
		if (unit.GetThreatToSelf() >= 0.4 || !group || group.GetFormationLeader() != unit || (group.GetWaypoints().Count() == 0 && group.GetWaypointBehaviour() != eAIWaypointBehavior.ROAMING)) return SUCCESS;
		return FAIL;
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
		auto group = unit.GetGroup();
		if (!group || group.GetFormationLeader() == unit || group.GetFormationState() != eAIGroupFormationState.IN) return SUCCESS;
		if (unit.GetThreatToSelf() >= 0.4) return SUCCESS;
		return FAIL;
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
		auto group = unit.GetGroup();
		if (group && (group.GetFormationState() == eAIGroupFormationState.FLANK || group.IsInCombat()) && src.target && !src.target.IsItem() && unit.GetThreatToSelf(true) >= 0.4 /*&& unit.eAI_IsInFlankRange(src.target)*/) return FAIL;
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
		AddState(new Expansion_Master_PlayEmote_State_0(this));
		AddTransition(new Expansion_Master__Unconscious_Transition_0(this));
		AddTransition(new Expansion_Master_Unconscious_Idle_Transition_0(this));
		AddTransition(new Expansion_Master__Leave_Transition_0(this));
		AddTransition(new Expansion_Master__Interacting_Transition_0(this));
		AddTransition(new Expansion_Master_Interacting_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Bandaging_Self_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Bandaging_Self_Transition_0(this));
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
		AddTransition(new Expansion_Master_TakeItemToHands_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_TakeItemToInventory_Transition_0(this));
		AddTransition(new Expansion_Master_TakeItemToInventory_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Fighting_Weapon_Unjamming_Transition_0(this));
		AddTransition(new Expansion_Master_Weapon_Reloading_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Weapon_Unjamming_Idle_Transition_0(this));
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
		AddTransition(new Expansion_Master_Idle_FollowFormation_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_FollowFormation_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_TraversingWaypoints_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_TraversingWaypoints_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Flank_Transition_0(this));
		AddTransition(new Expansion_Master_TraversingWaypoints_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_FollowFormation_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Flank_Idle_Transition_0(this));
		AddTransition(new Expansion_Master_Idle_Idle_Transition_0(this));
	}
}
ExpansionFSM Create_Expansion_Master_FSM_0(ExpansionFSMOwnerType owner, ExpansionState parentState) {
	return new Expansion_Master_FSM_0(owner, parentState);
}
