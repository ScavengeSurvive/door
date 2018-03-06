#include "door.inc"

main() {
	new buttonids[4];
	new doorid = CreateDoor(1337, buttonids, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	DestroyDoor(doorid);
	OpenDoor(doorid);
	CloseDoor(doorid);
	IsValidDoor(doorid);

	new objectid;
	GetDoorObjectID(doorid, objectid);

	new model;
	GetDoorModel(doorid, model);
	SetDoorModel(doorid, model);

	new buttonid;
	GetDoorButton(doorid, 0, buttonid);

	new count;
	GetDoorButtonCount(doorid, count);

	new closeDelay;
	GetDoorCloseDelay(doorid, closeDelay);
	SetDoorCloseDelay(doorid, closeDelay);

	new Float:moveSpeed;
	GetDoorMoveSpeed(doorid, Float:moveSpeed);
	SetDoorMoveSpeed(doorid, Float:moveSpeed);

	new moveSound;
	GetDoorMoveSound(doorid, moveSound);
	SetDoorMoveSound(doorid, moveSound);

	new stopSound;
	GetDoorStopSound(doorid, stopSound);
	SetDoorStopSound(doorid, stopSound);

	new Float:x, Float:y, Float:z;
	GetDoorPos(doorid, Float:x, Float:y, Float:z);
	SetDoorPos(doorid, Float:x, Float:y, Float:z);

	new Float:rx, Float:ry, Float:rz;
	GetDoorRot(doorid, Float:rx, Float:ry, Float:rz);
	SetDoorRot(doorid, Float:rx, Float:ry, Float:rz);
	GetDoorMovePos(doorid, Float:x, Float:y, Float:z);
	SetDoorMovePos(doorid, Float:x, Float:y, Float:z);
	GetDoorMoveRot(doorid, Float:rx, Float:ry, Float:rz);
	SetDoorMoveRot(doorid, Float:rx, Float:ry, Float:rz);

	GetDoorState(doorid);
}

public OnPlayerActivateDoor(playerid, doorid, DOOR_STATE:newstate) {
	log("OnPlayerActivateDoor",
		_i("playerid", playerid),
		_i("doorid", doorid),
		_i("newstate", _:newstate)
	);
}

public OnDoorStateChange(doorid, DOOR_STATE:doorstate) {
	log("OnDoorStateChange",
		_i("doorid", doorid),
		_i("doorstate", _:doorstate)
	);
}
