// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_door
	#undef _inc_door
#endif
// custom include-guard to ensure we don't duplicate
#if defined _door_included
	#endinput
#endif
#define _door_included


#include <a_samp>
#include <logger>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Core\y_utils>
#include <streamer>
#include <button>

#include <YSI_Coding\y_hooks>


/*==============================================================================

	Constant Definitions, Function Declarations and Documentation

==============================================================================*/


// Maximum amount of doors that can be created.
#if !defined MAX_DOORS
	#define MAX_DOORS (64)
#endif

// Maximum amount of buttons that can be assigned to a door.
#if !defined MAX_BUTTONS_PER_DOOR
	#define MAX_BUTTONS_PER_DOOR (4)
#endif

#define INVALID_DOOR_ID (-1)

enum DOOR_STATE {
	DOOR_STATE_INVALID = -1, // Invalid door state.
	DOOR_STATE_OPEN,         // Door is open.
	DOOR_STATE_CLOSED,       // Door is closed.
	DOOR_STATE_OPENING,      // Door is moving from closed to open position.
	DOOR_STATE_CLOSING,      // Door is moving from open to closed position.
}


// Functions


forward CreateDoor(
	model,
	const Button:buttonids[],
	Float:px,
 	Float:py,
 	Float:pz,
 	Float:rx,
 	Float:ry,
 	Float:rz,
	Float:mpx,
	Float:mpy,
	Float:mpz,
	Float:mrx,
	Float:mry,
	Float:mrz,
	Float:moveSpeed = 1.0,
	closeDelay = 3000,
	maxButtons = sizeof(buttonids),
	moveSound = 1186,
	stopSound = 1186,
	worldid = 0,
	interiorid = 0,
	DOOR_STATE:initstate = DOOR_STATE_CLOSED
);
/*
# Description
Creates a world object that is assigned a move position and a set of buttons
that will trigger it's movement.

# Parameters

- model: The GTA model ID of the door.
- buttonids[]: An array of buttons that will be used to activate the door.
- px, py, pz: The world position of the door object.
- rx, ry, rz: The rotation of the door object.
- mpx, mpy, mpz: The world position which the door will move to.
- mrx, mry, mrz: The rotation which the door will rotate to when moved.
- moveSpeed: The speed at which the door will move (both open and close)
- closeDelay: Time to stay open, 0 to disable automatic closing.
- maxButtons: Size of button array.
- moveSound: The sound that will be played when the door moves.
- stopSound: The sound that will be played when the door stops moving.
- worldid: The virtual world in which the door object will be made.
- interiorid: The interior world in which the door object will be made.
- initstate: The initial state for the door, either open or closed.

# Returns
ID of the newly created door or INVALID_DOOR_ID upon failure.
*/

forward DestroyDoor(doorid);
/*
# Description
Destroys a door object and clears it's memory. This does not destroy the buttons
associated with the door.
*/

forward OpenDoor(doorid);
/*
# Description
Moves a door object to it's open position.
*/

forward CloseDoor(doorid);
/*
# Description
Moves a door object to it's closed position.
*/

forward bool:IsValidDoor(doorid);
/*
# Description
Checks if a door is valid.
*/

forward GetDoorObjectID(doorid, &objectid);
/*
# Description
Returns the object ID used for the door.
*/

forward GetDoorModel(doorid, &model);
/*
# Description
Returns the model ID used for the door.
*/

forward SetDoorModel(doorid, model);
/*
# Description
Changes a door object model.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorButton(doorid, slot, &buttonid);
/*
# Description
Returns the button ID handle in the specified slot of a door.
*/

forward GetDoorButtonCount(doorid, &count);
/*
# Description
Returns the amount of buttons assigned to a door.
*/

forward GetDoorCloseDelay(doorid, &closeDelay);
/*
# Description
Returns the close delay for a door in milliseconds.
*/

forward SetDoorCloseDelay(doorid, closeDelay);
/*
# Description
Sets the close delay for a door in milliseconds.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorMoveSpeed(doorid, &Float:moveSpeed);
/*
# Description
Returns a door open/close move speed.
*/

forward SetDoorMoveSpeed(doorid, Float:moveSpeed);
/*
# Description
Sets a door open/close move speed.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorMoveSound(doorid, &moveSound);
/*
# Description
Returns a door sound ID for when it moves.
*/

forward SetDoorMoveSound(doorid, moveSound);
/*
# Description
Sets the door sound ID for when it moves.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorStopSound(doorid, &stopSound);
/*
# Description
Returns the door sound ID for when it stops moving.
*/

forward SetDoorStopSound(doorid, stopSound);
/*
# Description
Sets the door sound ID for when it stops moving.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorPos(doorid, &Float:x, &Float:y, &Float:z);
/*
# Description
Assigns the door object position into the referenced variables.

# Returns
Boolean to indicate success or failure.
*/

forward SetDoorPos(doorid, Float:x, Float:y, Float:z);
/*
# Description
Sets the door object position.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorRot(doorid, &Float:rx, &Float:ry, &Float:rz);
/*
# Description
Assigns the door object rotation into the referenced variables.

# Returns
Boolean to indicate success or failure.
*/

forward SetDoorRot(doorid, Float:rx, Float:ry, Float:rz);
/*
# Description
Sets the door object rotation.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorMovePos(doorid, &Float:x, &Float:y, &Float:z);
/*
# Description
Assigns the door object move position into the referenced variables.
*/

forward SetDoorMovePos(doorid, Float:x, Float:y, Float:z);
/*
# Description
Sets the door object move position.

# Returns
Boolean to indicate success or failure.
*/

forward GetDoorMoveRot(doorid, &Float:rx, &Float:ry, &Float:rz);
/*
# Description
Assigns the door object move rotation into the referenced variables.
*/

forward SetDoorMoveRot(doorid, Float:rx, Float:ry, Float:rz);
/*
# Description
Sets the door object move rotation.

# Returns
Boolean to indicate success or failure.
*/

forward DOOR_STATE:GetDoorState(doorid);
/*
# Description
Returns the state of a door.
*/


// Events


forward OnPlayerActivateDoor(playerid, doorid, DOOR_STATE:newstate);
/*
# Called
Called when a player presses a door button. Depending on whether the door is
currently open, closed, opening or closing the door will act differently.

# Returns
1 To cancel the door action request. This will stop the door from opening or
closing. Useful for a door lock system.
*/

forward OnDoorStateChange(doorid, DOOR_STATE:doorstate);
/*
# Called
Called when a door changes state between: DOOR_STATE_OPEN, DOOR_STATE_CLOSED,
DOOR_STATE_OPENING, DOOR_STATE_CLOSING. Note: A door can never change state
between OPEN and CLOSED without CLOSING or OPENING in between.
*/


/*==============================================================================

	Setup

==============================================================================*/


static enum E_DOOR_DATA {
	door_objectid,
	door_model,
	Button:door_buttonArray[MAX_BUTTONS_PER_DOOR],
	door_buttonCount,
	door_closeDelay,
	Float:door_moveSpeed,
	door_moveSound,
	door_stopSound,
	DOOR_STATE:door_state,

	Float:door_posX,
	Float:door_posY,
	Float:door_posZ,
	Float:door_rotX,
	Float:door_rotY,
	Float:door_rotZ,

	Float:door_posMoveX,
	Float:door_posMoveY,
	Float:door_posMoveZ,
	Float:door_rotMoveX,
	Float:door_rotMoveY,
	Float:door_rotMoveZ
}

static
	door_Data[MAX_DOORS][E_DOOR_DATA],
	Iterator:door_Index<MAX_DOORS>;


/*==============================================================================

	Core Functions

==============================================================================*/


stock CreateDoor(
	model,
	const Button:buttonids[],
	Float:px,
	Float:py,
	Float:pz,
	Float:rx,
	Float:ry,
	Float:rz,
	Float:mpx,
	Float:mpy,
	Float:mpz,
	Float:mrx,
	Float:mry,
	Float:mrz,
	Float:moveSpeed = 1.0,
	closeDelay = 3000,
	maxButtons = sizeof(buttonids),
	moveSound = 1186,
	stopSound = 1186,
	worldid = 0,
	interiorid = 0,
	DOOR_STATE:initstate = DOOR_STATE_CLOSED
) {
	new id = Iter_Free(door_Index);

	if(id == -1) {
		return INVALID_DOOR_ID;
	}

	if(initstate == DOOR_STATE_CLOSED) {
		door_Data[id][door_objectid] = CreateDynamicObject(model, px, py, pz, rx, ry, rz, worldid, interiorid);
	} else {
		door_Data[id][door_objectid] = CreateDynamicObject(model, mpx, mpy, mpz, mrx, mry, mrz, worldid, interiorid);
	}

	door_Data[id][door_model] = model;
	door_Data[id][door_buttonCount] = maxButtons;
	door_Data[id][door_closeDelay] = closeDelay;
	door_Data[id][door_moveSpeed] = moveSpeed;

	for(new i; i < maxButtons; i++) {
		door_Data[id][door_buttonArray][i] = buttonids[i];
	}

	door_Data[id][door_moveSound] = moveSound;
	door_Data[id][door_stopSound] = stopSound;
	door_Data[id][door_state] = initstate;

	door_Data[id][door_posX] = px;
	door_Data[id][door_posY] = py;
	door_Data[id][door_posZ] = pz;
	door_Data[id][door_rotX] = rx;
	door_Data[id][door_rotY] = ry;
	door_Data[id][door_rotZ] = rz;

	door_Data[id][door_posMoveX] = mpx;
	door_Data[id][door_posMoveY] = mpy;
	door_Data[id][door_posMoveZ] = mpz;
	door_Data[id][door_rotMoveX] = mrx;
	door_Data[id][door_rotMoveY] = mry;
	door_Data[id][door_rotMoveZ] = mrz;

	Iter_Add(door_Index, id);
	return id;
}

stock DestroyDoor(doorid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	for(new i; i < door_Data[doorid][door_buttonCount]; i++) {
		door_Data[doorid][door_buttonArray][i] = INVALID_BUTTON_ID;
	}

	DestroyDynamicObject(door_Data[doorid][door_objectid]);
	door_Data[doorid][door_buttonCount] = 0;
	door_Data[doorid][door_closeDelay] = 0;
	door_Data[doorid][door_moveSpeed] = 0.0;

	door_Data[doorid][door_moveSound] = 0;
	door_Data[doorid][door_stopSound] = 0;
	door_Data[doorid][door_state] = DOOR_STATE_INVALID;

	door_Data[doorid][door_posX] = 0.0;
	door_Data[doorid][door_posY] = 0.0;
	door_Data[doorid][door_posZ] = 0.0;
	door_Data[doorid][door_rotX] = 0.0;
	door_Data[doorid][door_rotY] = 0.0;
	door_Data[doorid][door_rotZ] = 0.0;

	door_Data[doorid][door_posMoveX] = 0.0;
	door_Data[doorid][door_posMoveY] = 0.0;
	door_Data[doorid][door_posMoveZ] = 0.0;
	door_Data[doorid][door_rotMoveX] = 0.0;
	door_Data[doorid][door_rotMoveY] = 0.0;
	door_Data[doorid][door_rotMoveZ] = 0.0;

	Iter_Remove(door_Index, doorid);
	return 0;
}

stock OpenDoor(doorid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	MoveDynamicObject(door_Data[doorid][door_objectid],
		door_Data[doorid][door_posMoveX], door_Data[doorid][door_posMoveY], door_Data[doorid][door_posMoveZ], door_Data[doorid][door_moveSpeed],
		door_Data[doorid][door_rotMoveX], door_Data[doorid][door_rotMoveY], door_Data[doorid][door_rotMoveZ]);

	door_Data[doorid][door_state] = DOOR_STATE_OPENING;

	if(door_Data[doorid][door_moveSound] != -1) {
		_door_playSoundForAll(door_Data[doorid][door_moveSound], door_Data[doorid][door_posX], door_Data[doorid][door_posY], door_Data[doorid][door_posZ]);
	}

	CallLocalFunction("OnDoorStateChange", "dd", doorid, _:DOOR_STATE_OPENING);

	return 0;
}

stock CloseDoor(doorid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	MoveDynamicObject(door_Data[doorid][door_objectid],
		door_Data[doorid][door_posX], door_Data[doorid][door_posY], door_Data[doorid][door_posZ], door_Data[doorid][door_moveSpeed],
		door_Data[doorid][door_rotX], door_Data[doorid][door_rotY], door_Data[doorid][door_rotZ]);

	door_Data[doorid][door_state] = DOOR_STATE_CLOSING;

	if(door_Data[doorid][door_moveSound] != -1) {
		_door_playSoundForAll(door_Data[doorid][door_moveSound], door_Data[doorid][door_posX], door_Data[doorid][door_posY], door_Data[doorid][door_posZ]);
	}

	CallLocalFunction("OnDoorStateChange", "dd", doorid, _:DOOR_STATE_CLOSING);

	return 0;
}

stock bool:IsValidDoor(doorid) {
	return Iter_Contains(door_Index, doorid);
}


// door_objectid
stock GetDoorObjectID(doorid, &objectid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	objectid = door_Data[doorid][door_objectid];
	return 0;
}


// door_model
stock GetDoorModel(doorid, &model) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	model = door_Data[doorid][door_model];
	return 0;
}

stock SetDoorModel(doorid, model) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, door_Data[doorid][door_objectid], E_STREAMER_MODEL_ID, model);
	door_Data[doorid][door_model] = model;
	return 0;
}


// door_buttonArray
stock GetDoorButton(doorid, slot, &buttonid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	if(!(0 <= slot < door_Data[doorid][door_buttonCount])) {
		return 2;
	}

	buttonid = door_Data[doorid][door_buttonArray][slot];
	return 0;
}


// door_buttonCount
stock GetDoorButtonCount(doorid, &count) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	count = door_Data[doorid][door_buttonCount];
	return 0;
}


// door_closeDelay
stock GetDoorCloseDelay(doorid, &closeDelay) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	closeDelay = door_Data[doorid][door_closeDelay];
	return 0;
}

stock SetDoorCloseDelay(doorid, closeDelay) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_closeDelay] = closeDelay;
	return 0;
}


// door_moveSpeed
stock GetDoorMoveSpeed(doorid, &Float:moveSpeed) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	moveSpeed = door_Data[doorid][door_moveSpeed];
	return 0;
}

stock SetDoorMoveSpeed(doorid, Float:moveSpeed) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_moveSpeed] = moveSpeed;
	return 0;
}


// door_moveSound
stock GetDoorMoveSound(doorid, &moveSound) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	moveSound = door_Data[doorid][door_moveSound];
	return 0;
}

stock SetDoorMoveSound(doorid, moveSound) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_moveSound] = moveSound;
	return 0;
}


// door_stopSound
stock GetDoorStopSound(doorid, &stopSound) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	stopSound = door_Data[doorid][door_stopSound];
	return 0;
}

stock SetDoorStopSound(doorid, stopSound) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_stopSound] = stopSound;
	return 0;
}

// door_posX
// door_posY
// door_posZ
stock GetDoorPos(doorid, &Float:x, &Float:y, &Float:z) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	x = door_Data[doorid][door_posX];
	y = door_Data[doorid][door_posY];
	z = door_Data[doorid][door_posZ];
	
	return 0;
}

stock SetDoorPos(doorid, Float:x, Float:y, Float:z) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_posX] = x;
	door_Data[doorid][door_posY] = y;
	door_Data[doorid][door_posZ] = z;

	SetDynamicObjectPos(door_Data[doorid][door_objectid], x, y, z);

	return 0;
}

// door_rotX
// door_rotY
// door_rotZ
stock GetDoorRot(doorid, &Float:rx, &Float:ry, &Float:rz) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	rx = door_Data[doorid][door_rotX];
	ry = door_Data[doorid][door_rotY];
	rz = door_Data[doorid][door_rotZ];
	
	return 0;
}

stock SetDoorRot(doorid, Float:rx, Float:ry, Float:rz) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_rotX] = rx;
	door_Data[doorid][door_rotY] = ry;
	door_Data[doorid][door_rotZ] = rz;

	SetDynamicObjectRot(door_Data[doorid][door_objectid], rx, ry, rz);
	
	return 0;
}

// door_posMoveX
// door_posMoveY
// door_posMoveZ
stock GetDoorMovePos(doorid, &Float:x, &Float:y, &Float:z) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	x = door_Data[doorid][door_posMoveX];
	y = door_Data[doorid][door_posMoveY];
	z = door_Data[doorid][door_posMoveZ];
	
	return 0;
}

stock SetDoorMovePos(doorid, Float:x, Float:y, Float:z) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_posMoveX] = x;
	door_Data[doorid][door_posMoveY] = y;
	door_Data[doorid][door_posMoveZ] = z;

	return 0;
}

// door_rotMoveX
// door_rotMoveY
// door_rotMoveZ
stock GetDoorMoveRot(doorid, &Float:rx, &Float:ry, &Float:rz) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	rx = door_Data[doorid][door_rotMoveX];
	ry = door_Data[doorid][door_rotMoveY];
	rz = door_Data[doorid][door_rotMoveZ];
	
	return 0;
}

stock SetDoorMoveRot(doorid, Float:rx, Float:ry, Float:rz) {
	if(!Iter_Contains(door_Index, doorid)) {
		return 1;
	}

	door_Data[doorid][door_rotMoveX] = rx;
	door_Data[doorid][door_rotMoveY] = ry;
	door_Data[doorid][door_rotMoveZ] = rz;
	
	return 0;
}

// door_state
stock DOOR_STATE:GetDoorState(doorid) {
	if(!Iter_Contains(door_Index, doorid)) {
		return DOOR_STATE_INVALID;
	}

	return door_Data[doorid][door_state];
}


/*==============================================================================

	Internal Functions and Hooks

==============================================================================*/


hook OnButtonPress(playerid, Button:buttonid) {
	// todo: optimise with map
	foreach(new i : door_Index) {
		for(new j; j < door_Data[i][door_buttonCount]; j++) {
			if(buttonid == door_Data[i][door_buttonArray][j]) {
				_door_onButton(playerid, i);
			}
		}
	}

	return 0;
}

hook OnDynamicObjectMoved(objectid) {
	// todo: optimise with map
	foreach(new i : door_Index) {
		if(objectid == door_Data[i][door_objectid]) {
			_door_onMove(i);
		}
	}
	return 0;
}

_door_onButton(playerid, doorid) {
	if(door_Data[doorid][door_state] == DOOR_STATE_CLOSED || door_Data[doorid][door_state] == DOOR_STATE_CLOSING) {
		if(CallLocalFunction("OnPlayerActivateDoor", "ddd", playerid, doorid, _:DOOR_STATE_OPENING)) {
			return;
		}
		OpenDoor(doorid);
	} else if(door_Data[doorid][door_state] == DOOR_STATE_OPEN || door_Data[doorid][door_state] == DOOR_STATE_OPENING) {
		if(CallLocalFunction("OnPlayerActivateDoor", "ddd", playerid, doorid, _:DOOR_STATE_CLOSING)) {
			return;
		}
		CloseDoor(doorid);
	}
}

_door_onMove(doorid) {
	if(door_Data[doorid][door_state] == DOOR_STATE_OPENING) {
		door_Data[doorid][door_state] = DOOR_STATE_OPEN;

		if(door_Data[doorid][door_closeDelay] >= 0) {
			defer _door_closeDelay(doorid);
		}

		if(door_Data[doorid][door_stopSound] != -1) {
			_door_playSoundForAll(door_Data[doorid][door_stopSound], door_Data[doorid][door_posX], door_Data[doorid][door_posY], door_Data[doorid][door_posZ]);
		}

		CallLocalFunction("OnDoorStateChange", "dd", doorid, _:DOOR_STATE_OPEN);
	} else if(door_Data[doorid][door_state] == DOOR_STATE_CLOSING) {
		door_Data[doorid][door_state] = DOOR_STATE_CLOSED;

		if(door_Data[doorid][door_stopSound] != -1) {
			_door_playSoundForAll(door_Data[doorid][door_stopSound], door_Data[doorid][door_posX], door_Data[doorid][door_posY], door_Data[doorid][door_posZ]);
		}

		CallLocalFunction("OnDoorStateChange", "dd", doorid, _:DOOR_STATE_CLOSED);
	}
}

timer _door_closeDelay[ door_Data[doorid][door_closeDelay] ](doorid) {
	CloseDoor(doorid);
}

_door_playSoundForAll(sound, Float:x, Float:y, Float:z) {
	foreach(new i : Player) {
		PlayerPlaySound(i, sound, x, y, z);
	}
}
